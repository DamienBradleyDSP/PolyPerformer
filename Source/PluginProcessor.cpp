/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolyPerformerAudioProcessor::PolyPerformerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), undoManager(30000, 30),
    parameters(*this, &undoManager, "state", createParameterLayout()),
    sequencer(parameters)
#endif
{
    for (auto&& name : moduleFileNames) name = juce::String("<empty>");

    // Set 4 module name trees, each with empty string
    auto tree = parameters.copyState();
    auto nameTree = juce::ValueTree("nameTree");
    nameTree.setProperty(moduleFileNames[0], 0, nullptr);
    nameTree.setProperty(moduleFileNames[1], 1, nullptr);
    nameTree.setProperty(moduleFileNames[2], 2, nullptr);
    nameTree.setProperty(moduleFileNames[3], 3, nullptr);
    tree.addChild(nameTree, 0, nullptr);
    parameters.replaceState(tree);
}

PolyPerformerAudioProcessor::~PolyPerformerAudioProcessor()
{
}

//==============================================================================
const juce::String PolyPerformerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PolyPerformerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PolyPerformerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PolyPerformerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PolyPerformerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PolyPerformerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PolyPerformerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PolyPerformerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PolyPerformerAudioProcessor::getProgramName (int index)
{
    return {};
}

void PolyPerformerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PolyPerformerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    srate = sampleRate;
    buff = samplesPerBlock;
    sequencer.initialise(sampleRate, samplesPerBlock);
}

void PolyPerformerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PolyPerformerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PolyPerformerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    auto currentplayhead = getPlayHead();

    if (currentplayhead != nullptr) {		// checks if plugin is being run from DAW host
        currentplayhead->getCurrentPosition(currentpositionstruct);
    }
    else // TESTING
    {
        currentpositionstruct.bpm = 120;
        double SR = getSampleRate();	// Gets sample rate

        auto TESTbpm = 120;				// test BPM - STRUCT
        double beatspersecond = TESTbpm / 60.0;		// 2 beats per second
        double barspersecond = beatspersecond / 4.0;	// 0.5 bars per second

        double barspersample = barspersecond / SR;		// <<<<1 bars per sample

        auto samplesperquarternote = SR / beatspersecond;	// 24000 samples per quarter note

        auto quarternotespersample = 1 / samplesperquarternote;	// 1/24000 quarter notes per sample

        currentpositionstruct.ppqPosition = quarternotespersample * frameCounter;	// calculates current number of quarter notes - this will be done by the struct
        currentpositionstruct.ppqPositionOfLastBarStart = floor(frameCounter * barspersample) * 4;	// calculates number of quarter notes at start of last bar, 4/4 time
        currentpositionstruct.timeInSamples = frameCounter;
        frameCounter += 480;

        //sequencer.initialise(SR, 480);
        auto message = MidiMessage::noteOn(1, 60, 1.0f);
        if(frameCounter<200) midiMessages.addEvent(message, 0);
        sequencer.generateMidi(midiMessages, currentpositionstruct);
        return;
    } // testing


    // PUT IN SOMETHING HERE TO RESET EVERYTHING WHEN DAW PLAYS
    sequencer.generateMidi(midiMessages, currentpositionstruct); // generate midi for buffer using current playead from host
}

//==============================================================================
bool PolyPerformerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PolyPerformerAudioProcessor::createEditor()
{
    return new PolyPerformerAudioProcessorEditor (*this,parameters);
}

//==============================================================================
void PolyPerformerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    if (auto xmlState = parameters.copyState().createXml())
    {
        copyXmlToBinary(*xmlState, destData);
    }
}

void PolyPerformerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    if (auto xmlState = getXmlFromBinary(data, sizeInBytes))
    {
        auto tree = ValueTree::fromXml(*xmlState);

        auto nameTree = tree.getChildWithName("nameTree");
        moduleFileNames[0] = nameTree.getPropertyName(0).toString();
        moduleFileNames[1] = nameTree.getPropertyName(1).toString();
        moduleFileNames[2] = nameTree.getPropertyName(2).toString();
        moduleFileNames[3] = nameTree.getPropertyName(3).toString();

        parameters.replaceState(tree);
        parameters.getRawParameterValue("loadSaveState")->store(true);
    }
}
void PolyPerformerAudioProcessor::buttonClicked(juce::Button* b)
{
    File rootFolder = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory);
    rootFolder = rootFolder.getChildFile("SuperConductor").getChildFile("PolyPerformer");
    Result res = rootFolder.createDirectory();

    FileChooser myChooser("load from file",
        rootFolder,
        "*.polym,*.polyk");

    auto buttonName = b->getName();
    auto moduleState = ValueTree();
    auto newPluginState = ValueTree();
    auto fileName = String();
    auto fileExtension = String();

    if (myChooser.browseForFileToOpen())
    {
        File presetToLoad = myChooser.getResult();

        if (presetToLoad.existsAsFile())
        {
            XmlDocument loaded(presetToLoad);
            if (auto mainElement = loaded.getDocumentElement())
            {
                moduleState = juce::ValueTree::fromXml(*mainElement);
                fileName = String(presetToLoad.getFileNameWithoutExtension());
                fileExtension = String(presetToLoad.getFileExtension());
            }
            else
            {
                String error = loaded.getLastParseError();
                return;
            }
        }
        else return;
    }
    else return;

    // Translate given value tree for the parameters set ie if. extension == .polym
    if (fileExtension == ".polym") newPluginState = translatePolyManFile(moduleState, buttonName.getIntValue());
    else if (fileExtension == ".polyk") newPluginState = translatePolykolFile(moduleState, buttonName.getIntValue());
    else return;

    moduleFileNames[buttonName.getIntValue()] = fileName;
    auto nameTree = juce::ValueTree("nameTree");
    nameTree.setProperty(fileName, buttonName.getIntValue(), nullptr);
    newPluginState.removeChild(0, nullptr);
    newPluginState.addChild(nameTree, 0, nullptr);
    parameters.replaceState(newPluginState);
    parameters.getRawParameterValue("loadSaveState")->store(true);
}
juce::String PolyPerformerAudioProcessor::getPresetName()
{
    return juce::String();
}
juce::AudioProcessorValueTreeState::ParameterLayout PolyPerformerAudioProcessor::createParameterLayout()
{
    AudioProcessorValueTreeState::ParameterLayout layout;

    // Sequencer / Global Parameters

    layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
        /*ParamID*/ "loadSaveState",
        /*paramName*/ "loadSaveState",
        /*LabelText*/ "loadSaveState",
        /*Min,max, optional:precision*/ juce::NormalisableRange<float>(0, 1, 1),
        /*Default/Initial value*/ 0,
        /*value to text func*/ nullptr,
        /*text to value func*/ nullptr,
        /*isMetaParameter*/ false,
        /*Automatable*/ false,
        /*Discrete*/ true,
        /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
        /*Boolean*/ true));

    layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
        /*ParamID*/ "modeSelect",
        /*paramName*/ "modeSelect",
        /*LabelText*/ "modeSelect",
        /*Min,max, optional:precision*/ juce::NormalisableRange<float>(1, 4, 1),
        /*Default/Initial value*/ 1,
        /*value to text func*/ nullptr,
        /*text to value func*/ nullptr,
        /*isMetaParameter*/ false,
        /*Automatable*/ false,
        /*Discrete*/ true,
        /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
        /*Boolean*/ false));

    //return layout;


    // MODULE PARAMETERS
    

    for (int m = 0; m < ProjectSettings::numberOfModules; m++)
    {
        layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
            /*ParamID*/ "Module" + juce::String(m) + "concurrentORsequentialRead",
            /*paramName*/ "concurrentORsequentialRead",
            /*LabelText*/ "concurrentORsequentialRead",
            /*Min,max, optional:precision*/ juce::NormalisableRange<float>(ProjectSettings::minNumberOfRhythmModules, ProjectSettings::maxNumberOfRhythmModules, 1),
            /*Default/Initial value*/ ProjectSettings::startingNumberOfRhythmModules,
            /*value to text func*/ nullptr,
            /*text to value func*/ nullptr,
            /*isMetaParameter*/ false,
            /*Automatable*/ false,
            /*Discrete*/ true,
            /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
            /*Boolean*/ false));
        //parameterList.push_back(juce::String("numberOfModules"));

        layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
            /*ParamID*/ "Module" + juce::String(m)+"numberOfModules",
            /*paramName*/ "Module" + juce::String(m) + "numberOfModules",
            /*LabelText*/ "Module" + juce::String(m) + "numberOfModules",
            /*Min,max, optional:precision*/ juce::NormalisableRange<float>(ProjectSettings::minNumberOfRhythmModules, ProjectSettings::maxNumberOfRhythmModules, 1),
            /*Default/Initial value*/ ProjectSettings::startingNumberOfRhythmModules,
            /*value to text func*/ nullptr,
            /*text to value func*/ nullptr,
            /*isMetaParameter*/ false,
            /*Automatable*/ false,
            /*Discrete*/ true,
            /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
            /*Boolean*/ false));
        //parameterList.push_back(juce::String("numberOfModules"));

        layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
            /*ParamID*/ "Module" + juce::String(m)+"barOffset",
            /*paramName*/ "Module" + juce::String(m) + "barOffset",
            /*LabelText*/ "Module" + juce::String(m) + "barOffset",
            /*Min,max, optional:precision*/ juce::NormalisableRange<float>(0, 16, 0.00001),
            /*Default/Initial value*/ 0,
            /*value to text func*/ nullptr,
            /*text to value func*/ nullptr,
            /*isMetaParameter*/ false,
            /*Automatable*/ false,
            /*Discrete*/ false,
            /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
            /*Boolean*/ false));
        //parameterList.push_back(juce::String("barOffset"));

        // Rhythm Specific Parameters

        for (int i = 0; i < ProjectSettings::maxNumberOfRhythmModules; i++) // +1 for parameter move operations on gui side
        {
            layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                "Module" + juce::String(m) + "numberOfBeats" + juce::String(i),
                "Module" + juce::String(m) + "numberOfBeats",
                "Module" + juce::String(m) + "numberOfBeats",
                juce::NormalisableRange<float>(ProjectSettings::minNumberOfBeats, ProjectSettings::maxNumberOfBeats),
                ProjectSettings::startingNumberOfBeats,
                nullptr,
                nullptr,
                false,
                true,
                false,
                juce::AudioProcessorParameter::Category::genericParameter,
                false));
            //parameterList.push_back(juce::String("numberOfBeats" + juce::String(i)));

            layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                "Module" + juce::String(m) + "numberOfBars" + juce::String(i),
                "Module" + juce::String(m) + "numberOfBars",
                "Module" + juce::String(m) + "numberOfBars",
                juce::NormalisableRange<float>(ProjectSettings::minNumberOfBars, ProjectSettings::maxNumberOfBars),
                ProjectSettings::startingNumberOfBars,
                nullptr,
                nullptr,
                false,
                true,
                false,
                juce::AudioProcessorParameter::Category::genericParameter,
                false));
            //parameterList.push_back(juce::String("numberOfBars" + juce::String(i)));

            layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                "Module" + juce::String(m) + "selectionOfBeats" + juce::String(i),
                "Module" + juce::String(m) + "selectionOfBeats",
                "Module" + juce::String(m) + "selectionOfBeats",
                juce::NormalisableRange<float>(ProjectSettings::minNumberOfBeats, ProjectSettings::maxNumberOfBeats),
                ProjectSettings::startingNumberOfBeats,
                nullptr,
                nullptr,
                false,
                true,
                false,
                juce::AudioProcessorParameter::Category::genericParameter,
                false));
            //parameterList.push_back(juce::String("selectionOfBeats" + juce::String(i)));

            auto onState = i >= ProjectSettings::startingNumberOfRhythmModules ? 0 : 1;
            layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                "Module" + juce::String(m) + "moduleTurnedOn" + juce::String(i),
                "Module" + juce::String(m) + "moduleTurnedOn",
                "Module" + juce::String(m) + "moduleTurnedOn",
                juce::NormalisableRange<float>(0, 1),
                onState,
                nullptr,
                nullptr,
                false,
                true,
                true,
                juce::AudioProcessorParameter::Category::genericParameter,
                false));
            //parameterList.push_back(juce::String("moduleTurnedOn" + juce::String(i)));

            layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                "Module" + juce::String(m) + "moduleReadOrder" + juce::String(i),
                "Module" + juce::String(m) + "moduleReadOrder",
                "Module" + juce::String(m) + "moduleReadOrder",
                juce::NormalisableRange<float>(0, ProjectSettings::maxNumberOfRhythmModules),
                i,
                nullptr,
                nullptr,
                false,
                true,
                true,
                juce::AudioProcessorParameter::Category::genericParameter,
                true));
            //parameterList.push_back(juce::String("moduleReadOrder" + juce::String(i)));

        }

        // Beat Specific Parameters

        for (int i = 0; i < ProjectSettings::maxNumberOfRhythmModules; i++) // +1 for parameter move operations on gui side
        {
            for (int j = 1; j <= ProjectSettings::maxNumberOfBeats; j++)
            {
                layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                    /*ParamID*/ "Module" + juce::String(m) + "BeatOnOffR" + juce::String(i) + "B" + juce::String(j),
                    /*paramName*/ "Module" + juce::String(m) + "BeatOnOff",
                    /*LabelText*/ "Module" + juce::String(m) + "BeatOnOff",
                    /*Min,max, optional:precision*/ juce::NormalisableRange<float>(0, 1),
                    /*Default/Initial value*/ 1,
                    /*value to text func*/ nullptr,
                    /*text to value func*/ nullptr,
                    /*isMetaParameter*/ false,
                    /*Automatable*/ true,
                    /*Discrete*/ true,
                    /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
                    /*Boolean*/ true));
                //parameterList.push_back(juce::String("BeatOnOffR" + juce::String(i) + "B" + juce::String(j)));

                layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                    /*ParamID*/ "Module" + juce::String(m) + "VelocityR" + juce::String(i) + "B" + juce::String(j),
                    /*paramName*/ "Velocity",
                    /*LabelText*/ "Velocity",
                    /*Min,max, optional:precision*/ juce::NormalisableRange<float>(0, 1),
                    /*Default/Initial value*/ 0.8,
                    /*value to text func*/ nullptr,
                    /*text to value func*/ nullptr,
                    /*isMetaParameter*/ false,
                    /*Automatable*/ true,
                    /*Discrete*/ false,
                    /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
                    /*Boolean*/ false));
                //parameterList.push_back(juce::String("VelocityR" + juce::String(i) + "B" + juce::String(j)));

                layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                    /*ParamID*/ "Module" + juce::String(m) + "noteLengthR" + juce::String(i) + "B" + juce::String(j),
                    /*paramName*/ "noteLength",
                    /*LabelText*/ "noteLength",
                    /*Min,max, optional:precision*/ juce::NormalisableRange<float>(0, 1),
                    /*Default/Initial value*/ 0.5,
                    /*value to text func*/ nullptr,
                    /*text to value func*/ nullptr,
                    /*isMetaParameter*/ false,
                    /*Automatable*/ true,
                    /*Discrete*/ false,
                    /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
                    /*Boolean*/ false));
                //parameterList.push_back(juce::String("noteLengthR" + juce::String(i) + "B" + juce::String(j)));

                layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                    /*ParamID*/ "Module" + juce::String(m) + "SemitoneR" + juce::String(i) + "B" + juce::String(j),
                    /*paramName*/ "Semitone",
                    /*LabelText*/ "Semitone",
                    /*Min,max, optional:precision*/ juce::NormalisableRange<float>(-12, 12),
                    /*Default/Initial value*/ 0,
                    /*value to text func*/ nullptr,
                    /*text to value func*/ nullptr,
                    /*isMetaParameter*/ false,
                    /*Automatable*/ true,
                    /*Discrete*/ true,
                    /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
                    /*Boolean*/ false));
                //parameterList.push_back(juce::String("SemitoneR" + juce::String(i) + "B" + juce::String(j)));

                layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                    /*ParamID*/ "Module" + juce::String(m) + "OctaveR" + juce::String(i) + "B" + juce::String(j),
                    /*paramName*/ "Octave",
                    /*LabelText*/ "Octave",
                    /*Min,max, optional:precision*/ juce::NormalisableRange<float>(-4, 4),
                    /*Default/Initial value*/ 0,
                    /*value to text func*/ nullptr,
                    /*text to value func*/ nullptr,
                    /*isMetaParameter*/ false,
                    /*Automatable*/ true,
                    /*Discrete*/ true,
                    /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
                    /*Boolean*/ false));
                //parameterList.push_back(juce::String("OctaveR" + juce::String(i) + "B" + juce::String(j)));

                layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                    /*ParamID*/ "Module" + juce::String(m) + "SustainR" + juce::String(i) + "B" + juce::String(j),
                    /*paramName*/ "Sustain",
                    /*LabelText*/ "Sustain",
                    /*Min,max, optional:precision*/ juce::NormalisableRange<float>(0, 1),
                    /*Default/Initial value*/ 0,
                    /*value to text func*/ nullptr,
                    /*text to value func*/ nullptr,
                    /*isMetaParameter*/ false,
                    /*Automatable*/ true,
                    /*Discrete*/ true,
                    /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
                    /*Boolean*/ true));
                //parameterList.push_back(juce::String("SustainR" + juce::String(i) + "B" + juce::String(j)));
            }
        }

        // ADDITIONAL SETTINGS FOR POLYMAN INTEGRATION

        for (int i = 0; i < ProjectSettings::maxNumberOfRhythmModules; i++) // +1 for parameter move operations on gui side
        {
            for (int j = 1; j <= ProjectSettings::maxNumberOfBeats; j++)
            {
                layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                    /*ParamID*/ "Module" + juce::String(m) + "barsToRepeatOver" + juce::String(i) + "B" + juce::String(j),
                    /*paramName*/ "barsToRepeatOver",
                    /*LabelText*/ "barsToRepeatOver",
                    /*Min,max, optional:precision*/ juce::NormalisableRange<float>(0, 1),
                    /*Default/Initial value*/ 1,
                    /*value to text func*/ nullptr,
                    /*text to value func*/ nullptr,
                    /*isMetaParameter*/ false,
                    /*Automatable*/ true,
                    /*Discrete*/ true,
                    /*category*/ juce::AudioProcessorParameter::Category::genericParameter,
                    /*Boolean*/ true));

                for (int barNum = 1; barNum <= ProjectSettings::maxNumberOfBarsToRepeatOver; barNum++)
                {
                    layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                        "Module" + juce::String(m) + "barOnOffR" + String(i) + "B" + String(j) + "Bar" + String(barNum),
                        "barOnOff",
                        "barOnOff",
                        NormalisableRange<float>(0.0, 1.0f),
                        1.0,
                        nullptr,
                        nullptr,
                        false,
                        true,
                        true,
                        AudioProcessorParameter::Category::genericParameter,
                        true));

                    layout.add(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(
                        "Module" + juce::String(m) + "barVelocityR" + String(i) + "B" + String(j) + "Bar" + String(barNum),
                        "barVelocity",
                        "barVelocity",
                        NormalisableRange<float>(0.0, 1.0f),
                        1.0f,
                        nullptr,
                        nullptr,
                        false,
                        true,
                        true,
                        AudioProcessorParameter::Category::genericParameter,
                        true));
                }
            }
        }
    }

    return layout;
}

juce::ValueTree PolyPerformerAudioProcessor::translatePolyManFile(juce::ValueTree loadedFileTree, int moduleNumber)
{
    auto paramState = parameters.copyState();

    // Identical
    /*
    loadSaveState // ignore
    numberOfModules // to calculate modules for polyk
    midiNoteNumber // set to default
    resetLoop // ignore

    PER MODULE
    barOffset = 0
    concurrentORsequentialRead = concurrent
    PER MODULE PER RHYTHM
    numberOfBeats = 
    numberOfBars = 1
    selectionOfBeats = 
    moduleTurnedOn =
    moduleReadOrder // not in polyk
    PER MODULE PER RHYTHM PER BEAT
    BeatOnOffR = 
    VelocityR =
    noteLengthR = ??? may have to user set
    SemitoneR = 0
    OctaveR = 0 
    SustainR = 0

    NEW
    PER MODULE PER RHYTHM
    barsToRepeatOver = 
    PER MODULE PER RHYTHM PER BEAT
    barOnOffR = 
    barVelocityR = 
    */

    return paramState;
}
juce::ValueTree PolyPerformerAudioProcessor::translatePolykolFile(juce::ValueTree loadedFileTree, int moduleNumber)
{
    auto paramState = parameters.copyState();

    // Put module read order result into a list
    // this should now be the module order
    // then go through each module in that list, if its on, add to new list
    // now you have correct modules in order, verify with number of modules

    std::list<int> moduleOrder;
    for (int i = 0; i < ProjectSettings::polykolMaximumRhythmModules; i++)
    {
        moduleOrder.push_back((int)loadedFileTree.getPropertyAsValue("moduleReadOrder" + String(i), nullptr, false).getValue());
    }
    std::list<int> activeModules;
    for (auto&& entry : moduleOrder)
    {
        if ((bool)loadedFileTree.getPropertyAsValue("moduleTurnedOn" + String(entry), nullptr, false).getValue()) activeModules.push_back(entry);
    }
    // Verifying size
    if (activeModules.size() != (bool)loadedFileTree.getPropertyAsValue("numberOfModules", nullptr, false).getValue()) jassertfalse; // if this triggered then somethings gone wrong with loading or saving preset

    // For entry in active modules
    // Enter into this plugins specific rhythm module each property in order

    auto moduleString = "Module" + juce::String(moduleNumber);
    auto rhythmNumber = 0;
    for (auto&& entry : activeModules)
    {
        paramState.setProperty(moduleString + "concurrentORsequentialRead", 1, nullptr);
        paramState.setProperty(moduleString + "barOffset", loadedFileTree.getPropertyAsValue("barOffset",nullptr,false).getValue(), nullptr);
        paramState.setProperty(moduleString + "numberOfBeats"+juce::String(rhythmNumber), loadedFileTree.getPropertyAsValue("numberOfBeats" + juce::String(entry),nullptr,false).getValue(), nullptr);
        paramState.setProperty(moduleString + "numberOfBars"+juce::String(rhythmNumber), loadedFileTree.getPropertyAsValue("numberOfBars" + juce::String(entry),nullptr,false).getValue(), nullptr);
        paramState.setProperty(moduleString + "selectionOfBeats"+juce::String(rhythmNumber), loadedFileTree.getPropertyAsValue("selectionOfBeats" + juce::String(entry),nullptr,false).getValue(), nullptr);
        paramState.setProperty(moduleString + "moduleTurnedOn"+juce::String(rhythmNumber), loadedFileTree.getPropertyAsValue("moduleTurnedOn" + juce::String(entry),nullptr,false).getValue(), nullptr);

        for (int beatNumber = 1; beatNumber <= ProjectSettings::maxNumberOfBeats; beatNumber++)
        {
            auto beatString = "B" + juce::String(beatNumber);
            paramState.setProperty(moduleString + "BeatOnOffR" + juce::String(rhythmNumber)+beatString, loadedFileTree.getPropertyAsValue("BeatOnOffR" + juce::String(entry) + beatString, nullptr, false).getValue(), nullptr);
            paramState.setProperty(moduleString + "VelocityR" + juce::String(rhythmNumber)+beatString, loadedFileTree.getPropertyAsValue("VelocityR" + juce::String(entry) + beatString, nullptr, false).getValue(), nullptr);
            paramState.setProperty(moduleString + "noteLengthR" + juce::String(rhythmNumber)+beatString, loadedFileTree.getPropertyAsValue("noteLengthR" + juce::String(entry) + beatString, nullptr, false).getValue(), nullptr);
            paramState.setProperty(moduleString + "SemitoneR" + juce::String(rhythmNumber)+beatString, loadedFileTree.getPropertyAsValue("SemitoneR" + juce::String(entry) + beatString, nullptr, false).getValue(), nullptr);
            paramState.setProperty(moduleString + "OctaveR" + juce::String(rhythmNumber)+beatString, loadedFileTree.getPropertyAsValue("OctaveR" + juce::String(entry) + beatString, nullptr, false).getValue(), nullptr);
            paramState.setProperty(moduleString + "SustainR" + juce::String(rhythmNumber)+beatString, loadedFileTree.getPropertyAsValue("SustainR" + juce::String(entry) + beatString, nullptr, false).getValue(), nullptr);
            

            paramState.setProperty(moduleString + "barsToRepeatOver" + juce::String(rhythmNumber)+beatString, 1, nullptr);
            for (int barNum = 1; barNum <= ProjectSettings::maxNumberOfBarsToRepeatOver; barNum++)
            {
                paramState.setProperty(moduleString + "barOnOffR" + juce::String(rhythmNumber) + beatString, 1, nullptr);
                paramState.setProperty(moduleString + "barVelocityR" + juce::String(rhythmNumber) + beatString, 1, nullptr);
            }
        }

        rhythmNumber++;
    }


    // Identical
    /*
    loadSaveState // ignore
    numberOfModules // to calculate modules for polyk
    midiNoteNumber // set to default
    resetLoop // ignore

    PER MODULE
    barOffset =
    concurrentORsequentialRead = sequential
    PER MODULE PER RHYTHM
    numberOfBeats = 
    numberOfBars = 
    selectionOfBeats = 
    moduleTurnedOn = 
    moduleReadOrder // use this for calculation
    PER MODULE PER RHYTHM PER BEAT
    BeatOnOffR = 
    VelocityR = 
    noteLengthR = 
    SemitoneR = 
    OctaveR = 
    SustainR = 
    
    NEW
    PER MODULE PER RHYTHM PER BEAT
    barsToRepeatOver = 1
    PER MODULE PER RHYTHM PER BEAT PER BAR
    barOnOffR = 1
    barVelocityR = 1
    */


    return paramState;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PolyPerformerAudioProcessor();
}
