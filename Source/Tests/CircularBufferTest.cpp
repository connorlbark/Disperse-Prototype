//
//  CircularBufferTest.cpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/20/23.
//

#include "CircularBufferTest.hpp"
#include "../DSP/CircularBuffer.hpp"

void CircularBufferTest::runAllTests() {
  this->testInitializeBuffer();
  this->testReadWrite();
  this->testReadWriteNegativeIndex();
  this->testWriteWrongNumberChannels();
};

void CircularBufferTest::testInitializeBuffer() {
  beginTest("Initialize Buffer Test");
  
  CircularBuffer<float> buf = CircularBuffer<float>(1, 8);
  
  this->expectEquals(buf.readCircular(0, 0), 0.f);
  this->expectEquals(buf.readCircular(0, 1), 0.f);
  this->expectEquals(buf.readCircular(0, 2), 0.f);
  this->expectEquals(buf.readCircular(0, 3), 0.f);
  this->expectEquals(buf.readCircular(0, 4), 0.f);
  this->expectEquals(buf.readCircular(0, 5), 0.f);
  this->expectEquals(buf.readCircular(0, 6), 0.f);
  this->expectEquals(buf.readCircular(0, 7), 0.f);
  this->expectEquals(buf.readCircular(0, 8), 0.f);
                     
  this->expectEquals(buf.getNumSamples(), 8);
  this->expectEquals(buf.getNumChannels(), 1);
  
  CircularBuffer<float> buf2 = CircularBuffer<float>(3, 16);

  this->expectEquals(buf2.getNumSamples(), 16);
  this->expectEquals(buf2.getNumChannels(), 3);
}

void CircularBufferTest::testReadWrite() {
  beginTest("Read/Write Buffer Test");

  CircularBuffer<float> buf = CircularBuffer<float>(1, 8);
  
  this->expectEquals(buf.readCircular(0, 0), 0.f);
  this->expectEquals(buf.readCircular(0, 1), 0.f);
  this->expectEquals(buf.readCircular(0, 2), 0.f);
  this->expectEquals(buf.readCircular(0, 3), 0.f);
  this->expectEquals(buf.readCircular(0, 4), 0.f);
  this->expectEquals(buf.readCircular(0, 5), 0.f);
  this->expectEquals(buf.readCircular(0, 6), 0.f);
  this->expectEquals(buf.readCircular(0, 7), 0.f);
  this->expectEquals(buf.readCircular(0, 8), 0.f);

  buf.writeCircular({ 1.0 });
  
  this->expectEquals(buf.readCircular(0, 0), 1.f);
  this->expectEquals(buf.readCircular(0, 1), 0.f);
  this->expectEquals(buf.readCircular(0, 2), 0.f);
  this->expectEquals(buf.readCircular(0, 3), 0.f);
  this->expectEquals(buf.readCircular(0, 4), 0.f);
  this->expectEquals(buf.readCircular(0, 5), 0.f);
  this->expectEquals(buf.readCircular(0, 6), 0.f);
  this->expectEquals(buf.readCircular(0, 7), 0.f);
  this->expectEquals(buf.readCircular(0, 8), 1.f);
  
  buf.writeCircular({ 2.0 });
  
  this->expectEquals(buf.readCircular(0, 0), 2.f);
  this->expectEquals(buf.readCircular(0, 1), 1.f);
  this->expectEquals(buf.readCircular(0, 2), 0.f);
  this->expectEquals(buf.readCircular(0, 3), 0.f);
  this->expectEquals(buf.readCircular(0, 4), 0.f);
  this->expectEquals(buf.readCircular(0, 5), 0.f);
  this->expectEquals(buf.readCircular(0, 6), 0.f);
  this->expectEquals(buf.readCircular(0, 7), 0.f);
  this->expectEquals(buf.readCircular(0, 8), 2.f);
  this->expectEquals(buf.readCircular(0, 9), 1.f);
}

void CircularBufferTest::testReadWriteNegativeIndex() {
  beginTest("Read/Write Negative Buffer Test");

  CircularBuffer<float> buf = CircularBuffer<float>(1, 8);
  

  buf.writeCircular({ 1.0 });
  buf.writeCircular({ 2.0 });
  buf.writeCircular({ 3.0 });
  buf.writeCircular({ 4.0 });
  buf.writeCircular({ 5.0 });
  buf.writeCircular({ 6.0 });
  buf.writeCircular({ 7.0 });
  buf.writeCircular({ 8.0 });

  this->expectEquals(buf.readCircular(0, 0), 8.f);
  this->expectEquals(buf.readCircular(0, 1), 7.f);
  this->expectEquals(buf.readCircular(0, 2), 6.f);
  this->expectEquals(buf.readCircular(0, 3), 5.f);
  this->expectEquals(buf.readCircular(0, 4), 4.f);
  this->expectEquals(buf.readCircular(0, 5), 3.f);
  this->expectEquals(buf.readCircular(0, 6), 2.f);
  this->expectEquals(buf.readCircular(0, 7), 1.f);
  this->expectEquals(buf.readCircular(0, 8), 8.f);
  this->expectEquals(buf.readCircular(0, 9), 7.f);
  
  this->expectEquals(buf.readCircular(0, -1), 1.f);
  this->expectEquals(buf.readCircular(0, -2), 2.f);
  this->expectEquals(buf.readCircular(0, -3), 3.f);
  this->expectEquals(buf.readCircular(0, -4), 4.f);
  this->expectEquals(buf.readCircular(0, -5), 5.f);
  this->expectEquals(buf.readCircular(0, -6), 6.f);
  this->expectEquals(buf.readCircular(0, -7), 7.f);
  this->expectEquals(buf.readCircular(0, -8), 8.f);
  this->expectEquals(buf.readCircular(0, -9), 1.f);
}

void CircularBufferTest::testWriteWrongNumberChannels() {
  beginTest("Wrong Num Channel Buffer Test");

  CircularBuffer<float> buf = CircularBuffer<float>(2, 8);
  
  buf.writeCircular({ 1.0, 8.0 });
  buf.writeCircular({ 2.0, 7.0 });
  buf.writeCircular({ 3.0, 6.0 });
  buf.writeCircular({ 4.0, 5.0 });
  buf.writeCircular({ 5.0, 4.0 });
  buf.writeCircular({ 6.0, 3.0 });
  buf.writeCircular({ 7.0, 2.0 });
  buf.writeCircular({ 8.0, 1.0 });

  this->expectEquals(buf.readCircular(0, 0), 8.f);
  this->expectEquals(buf.readCircular(1, 0), 1.f);

  
  buf.writeCircular({});
  
  this->expectEquals(buf.readCircular(0, 0), 0.f);
  this->expectEquals(buf.readCircular(1, 0), 0.f);

  buf.writeCircular({10.0, 11.0, 12.0, 14.0});

  this->expectEquals(buf.readCircular(0, 0), 10.f);
  this->expectEquals(buf.readCircular(1, 0), 11.f);



}
