//
//  Knob.hpp
//  Disperse
//
//  Created by Connor Barker on 1/31/23.
//

#ifndef Knob_hpp
#define Knob_hpp

#include <JuceHeader.h>

class KnobLF : public juce::LookAndFeel_V3
{
private:
  std::vector<juce::Image> knobs;
  
public:
  
  static KnobLF& getInstance()
  {
        static KnobLF instance;
        return instance;
  }
  
  
  KnobLF() : juce::LookAndFeel_V3() {
    this->knobs = {
      juce::ImageCache::getFromMemory (BinaryData::knob1_png, BinaryData::knob1_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob2_png, BinaryData::knob2_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob3_png, BinaryData::knob3_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob4_png, BinaryData::knob4_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob5_png, BinaryData::knob5_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob6_png, BinaryData::knob6_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob7_png, BinaryData::knob7_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob8_png, BinaryData::knob8_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob9_png, BinaryData::knob9_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob10_png, BinaryData::knob10_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob11_png, BinaryData::knob11_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob12_png, BinaryData::knob12_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob13_png, BinaryData::knob13_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob14_png, BinaryData::knob14_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob15_png, BinaryData::knob15_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob16_png, BinaryData::knob16_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob17_png, BinaryData::knob17_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob18_png, BinaryData::knob18_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob19_png, BinaryData::knob19_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob20_png, BinaryData::knob20_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob21_png, BinaryData::knob21_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob22_png, BinaryData::knob22_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob23_png, BinaryData::knob23_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob24_png, BinaryData::knob24_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob25_png, BinaryData::knob25_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob26_png, BinaryData::knob26_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob27_png, BinaryData::knob27_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob28_png, BinaryData::knob28_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob29_png, BinaryData::knob29_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob30_png, BinaryData::knob30_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob31_png, BinaryData::knob31_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob32_png, BinaryData::knob32_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob33_png, BinaryData::knob33_pngSize),
      juce::ImageCache::getFromMemory (BinaryData::knob34_png, BinaryData::knob34_pngSize)
    };
  }
  
//  void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
//                         const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
//  {
//      const float radius = juce::jmin (width / 2, height / 2) - 4.0f;
//      const float centreX = x + width * 0.5f;
//      const float centreY = y + height * 0.5f;
//      const float rx = centreX - radius;
//      const float ry = centreY - radius;
//      const float rw = radius * 2.0f;
//      const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
//
//      // fill
//      g.setColour (juce::Colours::orange);
//      g.fillEllipse (rx, ry, rw, rw);
//
//      // outline
//      g.setColour (juce::Colours::red);
//      g.drawEllipse (rx, ry, rw, rw, 1.0f);
//
//    juce::Path p;
//      const float pointerLength = radius * 0.33f;
//      const float pointerThickness = 2.0f;
//      p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
//      p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
//
//      // pointer
//      g.setColour (juce::Colours::yellow);
//      g.fillPath (p);
//  }
  
  void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                         const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
  {
    // sliderPos: [0,1] no matter what
    juce::Image knob = getKnobImage(sliderPos);//juce::ImageCache::getFromMemory (BinaryData::knob1_png, BinaryData::knob1_pngSize);
    const float sideLength = juce::jmin (width, height);

    if (sliderPos > 0.5) {
      g.addTransform(juce::AffineTransform(-1, 0, sideLength,
                                           0, 1, 0));
    }
    
    g.drawImage(knob, x, y, sideLength, sideLength, 0, 0, 320, 320);
//    g.drawImageTransformed(knob, juce::AffineTransform::scale(3.0));


//    g.drawImage(knob, x, y, sideLength, sideLength, 0, 0, 32, 32);
  }

  juce::Image getKnobImage(float sliderPos) {
    if (sliderPos > 0.5) {
      sliderPos = 1.0 - sliderPos;
    }

    sliderPos *= 2;

    int knobIdx = floorf(sliderPos * this->knobs.size());

    return this->knobs.at(knobIdx);
  }
  
};

#endif /* Knob_hpp */
