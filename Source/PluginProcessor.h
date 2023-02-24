/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Tests/Tests.hpp"
#include "Effects/Disperse.hpp"

#include "Constants.h"

//==============================================================================
/**
*/
class DisperseAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
                             , public juce::AudioProcessorParameter::Listener
{
private:

  Disperse effect;
  double sampleRate;
  
  juce::AudioParameterFloat* mix;
  juce::AudioParameterFloat* time;
  juce::AudioParameterFloat* feedback;
  juce::AudioParameterFloat* spread;
  juce::AudioParameterFloat* dispersion;
  juce::AudioParameterInt* numVoices;
  juce::AudioParameterInt* seed;
  
  juce::AudioBuffer<float> inputBuffer;

public:
  

  
  //==============================================================================
  DisperseAudioProcessor();
  ~DisperseAudioProcessor() override;

  //==============================================================================
  void prepareToPlay (double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

 #ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
 #endif

  void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

  //==============================================================================
  juce::AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;

  //==============================================================================
  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram (int index) override;
  const juce::String getProgramName (int index) override;
  void changeProgramName (int index, const juce::String& newName) override;

  //==============================================================================
  void getStateInformation (juce::MemoryBlock& destData) override;
  void setStateInformation (const void* data, int sizeInBytes) override;

  // parameter listeners
  void parameterValueChanged (int parameterIndex, float newValue) override;
  void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override;
  
  juce::AudioParameterFloat &getMixParam() { return *this->mix; }
  juce::AudioParameterFloat &getTimeParam() { return *this->time; }
  juce::AudioParameterFloat &getFeedbackParam() { return *this->feedback; }
  juce::AudioParameterFloat &getSpreadParam() { return *this->spread; }
  juce::AudioParameterFloat &getDispersionParam() { return *this->dispersion; }
private:
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DisperseAudioProcessor)
};
