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
    for (auto&& name : moduleFileNames) name = juce::String("empty");

    auto tree = parameters.copyState();

    // Set 4 empty trees
    auto emptyTree0 = juce::ValueTree("emptyTree0");
    auto emptyTree1 = juce::ValueTree("emptyTree1");
    auto emptyTree2 = juce::ValueTree("emptyTree2");
    auto emptyTree3 = juce::ValueTree("emptyTree3");
    tree.addChild(emptyTree0, 0, nullptr); // Module 1
    tree.addChild(emptyTree1, 1, nullptr); // Module 2
    tree.addChild(emptyTree2, 2, nullptr); // Module 3
    tree.addChild(emptyTree3, 3, nullptr); // Module 4

    // Set 4 module name trees, each with empty string
    auto nameTree = juce::ValueTree("nameTree");
    setNameTree(nameTree);
    tree.addChild(nameTree, 4, nullptr);

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

        loadModuleState(tree, 0);
        loadModuleState(tree, 1);
        loadModuleState(tree, 2);
        loadModuleState(tree, 3);

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
    auto moduleNumber = buttonName.getIntValue();
    auto fileName = String();
    auto fileExtension = String();
    auto newModuleState = ValueTree();

    if (!myChooser.browseForFileToOpen()) return;
    File presetToLoad = myChooser.getResult();
    if (!presetToLoad.existsAsFile()) return;

    XmlDocument loaded(presetToLoad);
    if (auto mainElement = loaded.getDocumentElement())
    {
        newModuleState = juce::ValueTree::fromXml(*mainElement);
        fileName = myChooser.getResult().getFileNameWithoutExtension();
        fileExtension = myChooser.getResult().getFileExtension();
    }
    else
    {
        String error = loaded.getLastParseError();
    }

    std::unordered_map<juce::String, float> newParameters;
    analyseParameterTree(newModuleState, newParameters);
    newModuleState.removeChild(newModuleState.getChildWithName("nameTree"), nullptr);

    auto pluginState = parameters.copyState();
    pluginState.removeChild(moduleNumber,nullptr);
    pluginState.addChild(newModuleState,moduleNumber,nullptr);
    sequencer.replaceModuleState(newParameters, moduleNumber);

    moduleFileNames[moduleNumber] = fileName;
    auto nameTree = juce::ValueTree("nameTree");
    setNameTree(nameTree);
    pluginState.removeChild(4,nullptr);
    pluginState.addChild(nameTree, 4, nullptr);

    parameters.replaceState(pluginState);
    parameters.getRawParameterValue("loadSaveState")->store(true);

}
std::vector<juce::String> PolyPerformerAudioProcessor::getPresetNames()
{
    std::vector<juce::String> fileNames;
    fileNames.push_back(moduleFileNames[0]);
    fileNames.push_back(moduleFileNames[1]);
    fileNames.push_back(moduleFileNames[2]);
    fileNames.push_back(moduleFileNames[3]);
    return fileNames;
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

    // Module on/off
    // module release
    // Module note number

    return layout;
}
void PolyPerformerAudioProcessor::setNameTree(juce::ValueTree& tree)
{
    tree.setProperty("module0",juce::var(moduleFileNames[0]), nullptr);
    tree.setProperty("module1",juce::var(moduleFileNames[1]), nullptr);
    tree.setProperty("module2",juce::var(moduleFileNames[2]), nullptr);
    tree.setProperty("module3",juce::var(moduleFileNames[3]), nullptr);
}
void PolyPerformerAudioProcessor::loadModuleState(juce::ValueTree& tree, int moduleNumber)
{
    auto nameTree = tree.getChildWithName("nameTree");
    moduleFileNames[moduleNumber] = nameTree.getProperty("module"+juce::String(moduleNumber)).toString();

    auto moduleState = tree.getChild(moduleNumber);

    std::unordered_map<juce::String, float> parameterList;
    analyseParameterTree(moduleState, parameterList);
    sequencer.replaceModuleState(parameterList, moduleNumber);
}
void PolyPerformerAudioProcessor::analyseParameterTree(juce::ValueTree& tree, std::unordered_map<juce::String, float>& parameterList)
{
    std::list<juce::ValueTree> children;
    auto childTree = tree.getChild(1);
    auto noOfChildren = tree.getNumChildren();
    for (int i = 0; i <= noOfChildren; i++)
    {
        auto child = tree.getChild(i);
        if (child.isValid() && child.getPropertyName(0).toString() == juce::String("id")) children.push_back(child);
    }
    for (auto&& child : children)
    {
        auto parameterName = child.getProperty(child.getPropertyName(0)).toString();
        auto parameterValue = (float)child.getProperty(child.getPropertyName(1));
        parameterList.insert(std::make_pair(parameterName, parameterValue));
    }
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PolyPerformerAudioProcessor();
}
