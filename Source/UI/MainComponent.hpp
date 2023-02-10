//
//  MainContent.hpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/21/23.
//

#ifndef MainContent_hpp
#define MainContent_hpp

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "Components/LookAndFeel/Knob.hpp"

class MainComponent : public juce::Component
{
public:
    MainComponent(DisperseAudioProcessor& p) :
      mixAttachment(p.getMixParam(), mixKnob),
      timeAttachment(p.getTimeParam(), timeKnob),
      feedbackAttachment(p.getFeedbackParam(), feedbackKnob),
      spreadAttachment(p.getSpreadParam(), spreadKnob),
      dispersionAttachment(p.getDispersionParam(), dispersionKnob) {

      addAndMakeVisible (header);
      addAndMakeVisible (footer);
      
      addAndMakeVisible (leftSidebar);
      addAndMakeVisible (rightSidebar);

      addAndMakeVisible(timeKnob);
      timeKnob.setComponentID(TIME_PARAM_ID);
      timeKnob.setSliderStyle(juce::Slider::Rotary);
      timeKnob.setName("Time");
      

      addAndMakeVisible(feedbackKnob);
      feedbackKnob.setComponentID(FEEDBACK_PARAM_ID);
      feedbackKnob.setSliderStyle(juce::Slider::Rotary);
      feedbackKnob.setName("Feedback");

      addAndMakeVisible(mixKnob);
      mixKnob.setComponentID(MIX_PARAM_ID);
      mixKnob.setSliderStyle(juce::Slider::Rotary);
      mixKnob.setName("Mix");
      
      addAndMakeVisible(spreadKnob);
      spreadKnob.setComponentID(SPREAD_PARAM_ID);
      spreadKnob.setSliderStyle(juce::Slider::Rotary);
      spreadKnob.setName("Spread");

      addAndMakeVisible(dispersionKnob);
      dispersionKnob.setComponentID(DISPERSION_PARAM_ID);
      dispersionKnob.setSliderStyle(juce::Slider::Rotary);
      dispersionKnob.setName("Dispersion");
    }
 
    void paint (juce::Graphics&) override;
//    void resized() override;
 
private:
  juce::Component header;
  juce::Component footer;
  
  juce::Component leftSidebar;
  juce::Component rightSidebar;
  
  juce::Slider timeKnob;
  juce::Slider feedbackKnob;
  juce::Slider spreadKnob;
  juce::Slider dispersionKnob;
  juce::Slider mixKnob;

  juce::SliderParameterAttachment mixAttachment;
  juce::SliderParameterAttachment timeAttachment;
  juce::SliderParameterAttachment feedbackAttachment;
  juce::SliderParameterAttachment spreadAttachment;
  juce::SliderParameterAttachment dispersionAttachment;
  



  juce::TextEditor seed;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif /* MainContent_hpp */
