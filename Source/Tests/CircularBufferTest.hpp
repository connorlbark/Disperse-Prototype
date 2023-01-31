//
//  CircularBufferTest.hpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/20/23.
//

#ifndef CircularBufferTest_hpp
#define CircularBufferTest_hpp

#include <JuceHeader.h>
#include <iostream>

class CircularBufferTest  : public juce::UnitTest
{
public:
  CircularBufferTest()  : juce::UnitTest ("Circular Buffer") {}

  void runTest() override
  {    
    this->runAllTests();
  }

  void runAllTests();

  // tests:
  void testInitializeBuffer();
  void testReadWrite();
  void testReadWriteNegativeIndex();
  void testWriteWrongNumberChannels();
};
 
// Creating a static instance will automatically add the instance to the array
// returned by UnitTest::getAllTests(), so the test will be included when you call
// UnitTestRunner::runAllTests()
static CircularBufferTest circularBufferTest;

#endif /* CircularBufferTest_hpp */
