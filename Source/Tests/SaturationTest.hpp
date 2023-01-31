//
//  SaturationTest.hpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/31/23.
//

#ifndef SaturationTest_hpp
#define SaturationTest_hpp

#include <JuceHeader.h>

class SaturationTest  : public juce::UnitTest
{
public:
  SaturationTest()  : juce::UnitTest ("Saturation") {}

  void runTest() override
  {
    this->runAllTests();
  }

  void runAllTests();

  // tests:
  void testTanhSoftClip();
};
 
// Creating a static instance will automatically add the instance to the array
// returned by UnitTest::getAllTests(), so the test will be included when you call
// UnitTestRunner::runAllTests()
static SaturationTest saturationTest;
#endif /* SaturationTest_hpp */
