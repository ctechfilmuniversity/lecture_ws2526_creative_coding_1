//
// Created by lenap on 2/23/2026.
//

#ifndef RNBO_JUCE_EXAMPLE_DRONESYNTHGUI_H
#define RNBO_JUCE_EXAMPLE_DRONESYNTHGUI_H

#pragma once

#include <JuceHeader.h>
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"
#include <array>

class DroneSynthGUI : public juce::Component,
                      private juce::Timer,
                      private juce::Slider::Listener
{
public:
    DroneSynthGUI();
    ~DroneSynthGUI() override;

    // RNBO integration (commented out as in original)
    // void setRNBOObject(juce::ReferenceCountedObjectPtr<rnbo::RNBOWrapper> rnboObject);

    // Component overrides
    void paint(juce::Graphics&) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent&) override;

    //[UserMethods]     -- You can add your own custom methods in this section.
    void setAudioProcessor(RNBO::JuceAudioProcessor *p);
    void updateSliderForParam(unsigned long index, double value);
    //[/UserMethods]

private:
    //==============================================================================
    // Timer callback
    void timerCallback() override;

    // Slider listener callback
    void sliderValueChanged(juce::Slider* slider) override;

    //==============================================================================
    // Drawing helpers
    void drawBackground(juce::Graphics&);
    void drawPowerButton(juce::Graphics&);
    void drawSliderBackground(juce::Graphics&, juce::Rectangle<int>, int index);
    void drawSliderFill(juce::Graphics&, juce::Slider*, juce::Colour);
    void drawParticleEffects(juce::Graphics&, juce::Rectangle<int>, float fillLevel, juce::Colour);

    //==============================================================================
    // RNBO wrapper (commented out as in original)
    // juce::ReferenceCountedObjectPtr<rnbo::RNBOWrapper> rnboWrapper;
    //[UserVariables]   -- You can add your own custom variables in this section.
    RNBO::JuceAudioProcessor *processor = nullptr;
    HashMap<int, Slider *> slidersByParameterIndex; // used to map parameter index to slider we want to control
    //[/UserVariables]

    //==============================================================================
    // UI Components
    juce::Label titleLabel;
    juce::Label powerLabel;

    std::unique_ptr<juce::Slider> slider1;
    std::unique_ptr<juce::Slider> slider2;
    std::unique_ptr<juce::Slider> slider3;
    std::unique_ptr<juce::Slider> slider4;
    std::unique_ptr<juce::Slider> slider5;
    std::unique_ptr<juce::Slider> slider6;

    //==============================================================================
    // Animation / State
    float time = 0.0f;
    float powerButtonAnim = 0.0f;
    bool isPoweredOn = false;

    //==============================================================================
    // Colors - Neon palette
    juce::Colour backgroundColor1 { juce::Colour::fromRGB(8, 8, 12) };
    juce::Colour backgroundColor2 { juce::Colour::fromRGB(2, 2, 6) };

    // Main accent colors (keeping for compatibility with existing code)
    juce::Colour primaryColor   { juce::Colour::fromRGB(0, 255, 180) };
    juce::Colour secondaryColor { juce::Colour::fromRGB(0, 140, 255) };

    // Neon colors for each slider
    juce::Colour neonCyan    { juce::Colour::fromRGB(0, 255, 255) };
    juce::Colour neonMagenta { juce::Colour::fromRGB(255, 0, 255) };
    juce::Colour neonGreen   { juce::Colour::fromRGB(0, 255, 128) };
    juce::Colour neonOrange  { juce::Colour::fromRGB(255, 128, 0) };
    juce::Colour neonPink    { juce::Colour::fromRGB(255, 64, 128) };
    juce::Colour neonPurple  { juce::Colour::fromRGB(160, 64, 255) };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DroneSynthGUI)
};

#endif //RNBO_JUCE_EXAMPLE_DRONESYNTHGUI_H