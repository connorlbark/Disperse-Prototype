//
//  MainContent.hpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/21/23.
//

#ifndef MainContent_hpp
#define MainContent_hpp

#include <JuceHeader.h>

class MainComponent : public juce::Component
{
public:
    MainComponent() {

      addAndMakeVisible (header);
      addAndMakeVisible (footer);
      
      addAndMakeVisible (leftSidebar);
      addAndMakeVisible (rightSidebar);
      
      addAndMakeVisible(text);
      
      text.setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras dui lacus, venenatis vel sem nec, varius semper magna. Cras dignissim lacus non dolor elementum, eget dapibus lacus pharetra. Suspendisse mollis massa erat, vitae hendrerit nibh hendrerit vel. Aliquam vitae massa enim. Nullam vitae arcu congue, tristique arcu ut, hendrerit nunc. Integer et eleifend orci. Aliquam sed ante mauris. Fusce sagittis sit amet sapien sit amet fringilla. Donec lorem massa, pulvinar et dui ac, lobortis dapibus sem. Aliquam at libero ultrices erat euismod tincidunt. Nullam blandit, lectus a vehicula molestie, ipsum enim semper erat, in luctus nisi est id risus. Suspendisse leo erat, volutpat ac venenatis in, lacinia vel libero. Etiam facilisis odio a pretium lobortis. Vestibulum pharetra tincidunt leo a pulvinar. Donec ut ornare Donec mattis leo at lacus fermentum, ac malesuada nisi luctus. Suspendisse condimentum viverra urna, nec sollicitudin mi porta at. Nulla turpis quam, tincidunt sit amet nulla eu, tristique condimentum risus. Duis volutpat nisi nisi, non vehicula felis sodales at. Integer dignissim, lectus a auctor dapibus, tellus lectus viverra ipsum, vel molestie felis urna quis magna. Nam ipsum lectus, molestie ac justo vel, aliquam efficitur magna. Etiam congue, diam at viverra pellentesque, lorem massa auctor sapien, ac bibendum orci lectus et tortor. Sed ut quam faucibus, feugiat orci quis, fringilla lorem. Quisque vitae tortor dolor. Mauris lectus nisl, congue et erat et, rutrum tristique leo. Morbi arcu neque, fringilla quis eleifend vel, commodo in nisl. Donec venenatis faucibus erat. Curabitur vel lacus sit amet lectus euismod elementum sit amet id urna. Vivamus nulla neque, pellentesque vitae aliquam vitae, facilisis at metus. Ut consectetur varius tortor non venenatis.", juce::dontSendNotification);
      
      text.setColour (juce::Label::backgroundColourId, juce::Colours::darkblue);

    }
 
    void paint (juce::Graphics&) override;
//    void resized() override;
 
private:
  juce::Component header;
  juce::Component footer;
  
  juce::Component leftSidebar;
  juce::Component rightSidebar;
  
  juce::Label text;

  
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif /* MainContent_hpp */
