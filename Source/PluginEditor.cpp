/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DisperseAudioProcessorEditor::DisperseAudioProcessorEditor (DisperseAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize (1600, 800);
  addAndMakeVisible(mainComponent);
}

DisperseAudioProcessorEditor::~DisperseAudioProcessorEditor()
{
}

//==============================================================================
void DisperseAudioProcessorEditor::paint (juce::Graphics& g)
{
  g.fillAll(juce::Colours::black);
  
  mainComponent.setBounds(getLocalBounds());
}

void DisperseAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
