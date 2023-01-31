/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "DSP/Saturation.hpp"

//==============================================================================
DisperseAudioProcessor::DisperseAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
  addParameter (time = new juce::AudioParameterFloat ("mix", "Mix", 0.0, 1.0, 0.30));
  addParameter (time = new juce::AudioParameterFloat ("time", "Delay Time (ms)", 30.0, 10000.0, 0.5));
  addParameter (feedback = new juce::AudioParameterFloat ("feedback", "Feedback (%)", 0.0, 1.0, 0.5));
  addParameter (spread = new juce::AudioParameterFloat ("spread", "Stereo Spread", 0.0, 1.0, 0.0));
  addParameter (dispersion = new juce::AudioParameterFloat ("dispersion", "Dispersion", 0.0, 1.0, 0.0));
  addParameter (numVoices = new juce::AudioParameterInt ("numVoices", "Number of Delay Voices", 0, 8, 4));
}

DisperseAudioProcessor::~DisperseAudioProcessor()
{
}

//==============================================================================
const juce::String DisperseAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DisperseAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DisperseAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DisperseAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DisperseAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DisperseAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DisperseAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DisperseAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DisperseAudioProcessor::getProgramName (int index)
{
    return {};
}

void DisperseAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DisperseAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
  
  this->sampleRate = sampleRate;
    
  std::cout << "Running tests!" << std::endl;
  juce::UnitTestRunner testRunner;
  testRunner.runAllTests();
  

  this->effect.initialize(sampleRate);

}

void DisperseAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DisperseAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DisperseAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    for (int i = 0; i < buffer.getNumSamples(); i++) {
      stereofloat val = this->effect.process(stereofloat(buffer.getSample(0, i), buffer.getSample(1, i)));
            
      buffer.setSample(0, i, val.L());
      buffer.setSample(1, i, val.R());
    }

}

//==============================================================================
bool DisperseAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DisperseAudioProcessor::createEditor()
{
    return new DisperseAudioProcessorEditor (*this);
}

//==============================================================================
void DisperseAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DisperseAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DisperseAudioProcessor();
}
