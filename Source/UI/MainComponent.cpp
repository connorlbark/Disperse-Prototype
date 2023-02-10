//
//  MainContent.cpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/21/23.
//

#include "MainComponent.hpp"

void MainComponent::paint(juce::Graphics& graphics) {
  graphics.fillAll (juce::Colour::fromRGB(100, 100, 100));
  graphics.drawRect(0, 0, getWidth(), getHeight());
  auto area = getLocalBounds();

  header.setBounds(area.removeFromTop(50));
  footer.setBounds(area.removeFromBottom(50));

  leftSidebar.setBounds(area.removeFromLeft(80));
  leftSidebar.setBounds(area.removeFromRight(80));
  

  auto topRow = area.removeFromTop(area.proportionOfHeight(0.5));
  auto bottomRow = area;
  
  int widthTopKnob = topRow.proportionOfWidth(1.f/3.f);
  int widthBottomKnob = bottomRow.proportionOfWidth(0.5);
  
  this->mixKnob.setBounds(topRow.removeFromLeft(widthTopKnob));
  this->timeKnob.setBounds(topRow.removeFromLeft(widthTopKnob));
  this->feedbackKnob.setBounds(topRow.removeFromLeft(widthTopKnob));
  
  this->dispersionKnob.setBounds(bottomRow.removeFromLeft(widthBottomKnob));
  this->spreadKnob.setBounds(bottomRow.removeFromLeft(widthBottomKnob));
}
