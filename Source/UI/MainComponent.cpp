//
//  MainContent.cpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/21/23.
//

#include "MainComponent.hpp"

void MainComponent::paint(juce::Graphics& graphics) {
  auto area = getLocalBounds();
  
  header.setBounds(area.removeFromTop(200));
  footer.setBounds(area.removeFromBottom(200));

  leftSidebar.setBounds(area.removeFromLeft(200));
  leftSidebar.setBounds(area.removeFromRight(200));
  
  
  text.setBounds(area);
}
