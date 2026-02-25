//
// Created by lenap on 2/23/2026.
//
#include "DroneSynthGUI.h"
#include <cmath>

//==============================================================================
DroneSynthGUI::DroneSynthGUI()
{
    // Setup title
    titleLabel.setText("ARRAS", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(28.0f, juce::Font::bold));
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::white.withAlpha(0.95f));
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    // Power label
    powerLabel.setText("POWER", juce::dontSendNotification);
    powerLabel.setFont(juce::Font(9.0f, juce::Font::bold));
    powerLabel.setColour(juce::Label::textColourId, juce::Colours::white.withAlpha(0.6f));
    powerLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(powerLabel);

    // Create sliders with proper initialization
    slider1 = std::make_unique<juce::Slider>();
    slider2 = std::make_unique<juce::Slider>();
    slider3 = std::make_unique<juce::Slider>();
    slider4 = std::make_unique<juce::Slider>();
    slider5 = std::make_unique<juce::Slider>();
    slider6 = std::make_unique<juce::Slider>();

    // Configure each slider
    auto configureSlider = [this](juce::Slider* slider, const juce::String& name,
                                   double min, double max, double initial)
    {
        slider->setName(name);
        slider->setSliderStyle(juce::Slider::LinearVertical);
        slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

        slider->setColour(juce::Slider::thumbColourId, juce::Colours::transparentWhite);
        slider->setColour(juce::Slider::trackColourId, juce::Colours::transparentWhite);
        slider->setColour(juce::Slider::backgroundColourId, juce::Colours::transparentWhite);

        slider->setVelocityBasedMode(true);
        slider->setDoubleClickReturnValue(true, initial);
        slider->setRange(min, max, 0.01);
        slider->setValue(initial, juce::dontSendNotification);

        slider->addListener(this);
        addAndMakeVisible(slider);
    };

    // Configure all 6 sliders with appropriate ranges for drone synthesis
    configureSlider(slider1.get(), "METRO", 0.0, 1000.0, 50.0);  // Metro rate
    configureSlider(slider2.get(), "MOD", 0.0, 10.0, 0.0);    // Modulation depth
    configureSlider(slider3.get(), "ATT", 0.0, 100.0, 0.0);     // Attack time
    configureSlider(slider4.get(), "DEC", 0.0, 100.0, 50.0);    // Decay time
    configureSlider(slider5.get(), "SUS", 0.0, 100.0, 100.0);   // Sustain level
    configureSlider(slider6.get(), "REL", 0.0, 500.0, 50.0);    // Release time

    startTimerHz(30);
    setSize(700, 360);  // Slightly wider to accommodate spread sliders
}

DroneSynthGUI::~DroneSynthGUI()
{
    stopTimer();
}

//==============================================================================
void DroneSynthGUI::paint(juce::Graphics& g)
{
    drawBackground(g);

    auto bounds = getLocalBounds();
    auto sliderArea = bounds.reduced(40, 70).withTrimmedBottom(40);

    // Slimmer sliders - reduced width, more spacing
    int sliderWidth = 28;  // Slimmer
    int spacing = 25;      // More spacing between sliders
    int totalWidth = sliderWidth * 6 + spacing * 5;
    int startX = bounds.getCentreX() - totalWidth / 2;

    // Array of slider colors for neon effect
    std::array<juce::Colour, 6> sliderColors = {
        neonCyan, neonMagenta, neonGreen, neonOrange, neonPink, neonPurple
    };

    std::array<juce::String, 6> sliderLabels = {
        "METRO", "MOD", "ATT", "DEC", "SUS", "REL"
    };

    std::array<juce::Slider*, 6> sliders = {slider1.get(), slider2.get(), slider3.get(),
                                            slider4.get(), slider5.get(), slider6.get()};

    for (int i = 0; i < 6; ++i)
    {
        auto sliderBounds = juce::Rectangle<int>(
            startX + i * (sliderWidth + spacing),
            sliderArea.getY(),
            sliderWidth,
            sliderArea.getHeight()
        );

        drawSliderBackground(g, sliderBounds, i);

        if (sliders[i] != nullptr)
        {
            float fillLevel = (float)((sliders[i]->getValue() - sliders[i]->getMinimum()) /
                                      (sliders[i]->getMaximum() - sliders[i]->getMinimum()));

            // Draw neon liquid fill
            drawSliderFill(g, sliders[i], sliderColors[i]);

            // Add particle effects
            drawParticleEffects(g, sliderBounds, fillLevel, sliderColors[i]);

            // Draw slider label
            g.setColour(juce::Colours::white.withAlpha(0.7f));
            g.setFont(juce::Font(10.0f, juce::Font::bold));
            g.drawText(sliderLabels[i],
                      sliderBounds.withTrimmedBottom(-25).translated(0, -15),
                      juce::Justification::centred, false);

            // Draw value label
            if (fillLevel > 0.01f)
            {
                int value = (int)sliders[i]->getValue();
                g.setColour(sliderColors[i].withAlpha(0.9f));
                g.setFont(juce::Font(9.0f));
                g.drawText(juce::String(value),
                          sliderBounds.withTrimmedTop(sliderBounds.getHeight() - 20),
                          juce::Justification::centred, false);
            }
        }
    }

    drawPowerButton(g);
}

void DroneSynthGUI::resized()
{
    auto bounds = getLocalBounds();

    // Title at the top
    titleLabel.setBounds(bounds.removeFromTop(50));

    // Position sliders
    auto sliderArea = bounds.reduced(40, 10).withTrimmedBottom(40);

    int sliderWidth = 28;  // Slimmer
    int spacing = 25;      // More spacing
    int totalWidth = sliderWidth * 6 + spacing * 5;
    int startX = bounds.getCentreX() - totalWidth / 2;

    std::array<juce::Slider*, 6> sliders = {slider1.get(), slider2.get(), slider3.get(),
                                            slider4.get(), slider5.get(), slider6.get()};

    for (int i = 0; i < 6; ++i)
    {
        if (sliders[i] != nullptr)
        {
            sliders[i]->setBounds(
                startX + i * (sliderWidth + spacing),
                sliderArea.getY(),
                sliderWidth,
                sliderArea.getHeight()
            );
        }
    }
}

void DroneSynthGUI::mouseDown(const juce::MouseEvent& event)
{
    auto bounds = getLocalBounds();

    int buttonSize = 28;  // Smaller
    int buttonX = bounds.getCentreX() - buttonSize / 2;
    int buttonY = bounds.getBottom() - 50;

    juce::Rectangle<int> buttonBounds(buttonX, buttonY, buttonSize, buttonSize);

    if (buttonBounds.contains(event.getPosition()))
    {
        isPoweredOn = !isPoweredOn;
        powerButtonAnim = 1.0f;

        repaint();
    }
}

//==============================================================================
void DroneSynthGUI::timerCallback()
{
    time += 0.02f;

    if (powerButtonAnim > 0.0f)
    {
        powerButtonAnim -= 0.05f;
        powerButtonAnim = juce::jmax(0.0f, powerButtonAnim);
    }

    repaint();
}

void DroneSynthGUI::sliderValueChanged(juce::Slider* slider)  // Changed from 'sliderThatWasMoved' to 'slider'
{
    //[UsersliderValueChanged_Pre]
    if (processor == nullptr) return;
    RNBO::CoreObject& coreObject = processor->getRnboObject();
    auto parameters = processor->getParameters();
    //[/UsersliderValueChanged_Pre]

    if (slider == slider1.get())  // Changed from 'sliderThatWasMoved' to 'slider'
    {
        //[UserSliderCode_slider1] -- add your slider handling code here..
        //[/UserSliderCode_slider1]
    }
    else if (slider == slider2.get())  // Changed from 'sliderThatWasMoved' to 'slider'
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        //[/UserSliderCode_slider2]
    }
    else if (slider == slider3.get())  // Changed from 'sliderThatWasMoved' to 'slider'
    {
        //[UserSliderCode_slider3] -- add your slider handling code here..
        //[/UserSliderCode_slider3]
    }
    else if (slider == slider4.get())  // Changed from 'sliderThatWasMoved' to 'slider'
    {
        //[UserSliderCode_slider4] -- add your slider handling code here..
        //[/UserSliderCode_slider4]
    }
    else if (slider == slider5.get())  // Changed from 'sliderThatWasMoved' to 'slider'
    {
        //[UserSliderCode_slider5] -- add your slider handling code here..
        //[/UserSliderCode_slider5]
    }
    else if (slider == slider6.get())  // Changed from 'sliderThatWasMoved' to 'slider'
    {
        //[UserSliderCode_slider6] -- add your slider handling code here..
        //[/UserSliderCode_slider6]
    }

    //[UsersliderValueChanged_Post]
    RNBO::ParameterIndex index = coreObject.getParameterIndexForID(slider->getName().toRawUTF8());  // Changed from 'sliderThatWasMoved' to 'slider'
    if (index != -1) {
        const auto param = processor->getParameters()[index];
        auto newVal = slider->getValue();  // Changed from 'sliderThatWasMoved' to 'slider'

        if (param && param->getValue() != newVal)
        {
            auto normalizedValue = coreObject.convertToNormalizedParameterValue(index, newVal);
            param->beginChangeGesture();
            param->setValueNotifyingHost(normalizedValue);
            param->endChangeGesture();
        }
    }
    //[/UsersliderValueChanged_Post]
}


//==============================================================================
void DroneSynthGUI::drawBackground(juce::Graphics& g)
{
    juce::ColourGradient backgroundGradient(
        backgroundColor1, 0.0f, 0.0f,
        backgroundColor2, 0.0f, (float)getHeight(),
        false
    );

    g.setGradientFill(backgroundGradient);
    g.fillAll();

    // Add subtle grid lines
    g.setColour(juce::Colours::white.withAlpha(0.03f));
    for (int i = 0; i < getWidth(); i += 20)
    {
        g.drawVerticalLine(i, 0, (float)getHeight());
    }
}

void DroneSynthGUI::drawPowerButton(juce::Graphics& g)
{
    auto bounds = getLocalBounds();

    int buttonSize = 28;  // Smaller
    int buttonX = bounds.getCentreX() - buttonSize / 2;
    int buttonY = bounds.getBottom() - 50;

    juce::Rectangle<int> buttonBounds(buttonX, buttonY, buttonSize, buttonSize);

    float glowIntensity = isPoweredOn ? (0.4f + powerButtonAnim * 0.3f)
                                      : (0.1f + powerButtonAnim * 0.1f);

    g.setColour(juce::Colours::white.withAlpha(glowIntensity));
    g.fillEllipse(buttonBounds.reduced(-6).toFloat());

    // Create combined color from all slider colors
    std::array<juce::Colour, 6> sliderColors = {
        neonCyan, neonMagenta, neonGreen, neonOrange, neonPink, neonPurple
    };

    juce::Colour combinedColor;
    if (isPoweredOn)
    {
        // Average all the neon colors for the power button
        float totalR = 0, totalG = 0, totalB = 0;
        for (const auto& color : sliderColors)
        {
            totalR += color.getFloatRed();
            totalG += color.getFloatGreen();
            totalB += color.getFloatBlue();
        }

        combinedColor = juce::Colour::fromFloatRGBA(
            totalR / 6.0f,
            totalG / 6.0f,
            totalB / 6.0f,
            1.0f
        );
    }
    else
    {
        combinedColor = juce::Colour::fromRGB(40, 40, 50);
    }

    if (powerButtonAnim > 0.0f)
        combinedColor = combinedColor.brighter(powerButtonAnim * 0.5f);

    g.setColour(combinedColor);
    g.fillEllipse(buttonBounds.toFloat());

    // Add subtle rainbow gradient ring when powered on
    if (isPoweredOn)
    {
        juce::ColourGradient ringGradient(
            neonCyan, buttonBounds.getX(), buttonBounds.getY(),
            neonMagenta, buttonBounds.getRight(), buttonBounds.getBottom(),
            true
        );
        g.setGradientFill(ringGradient);
        g.drawEllipse(buttonBounds.reduced(2).toFloat(), 1.5f);
    }
    else
    {
        g.setColour(juce::Colours::black.withAlpha(0.3f));
        g.drawEllipse(buttonBounds.reduced(2).toFloat(), 1.0f);
    }

    g.setColour(juce::Colours::white.withAlpha(isPoweredOn ? 0.9f : 0.5f));
    g.setFont(juce::Font(14.0f, juce::Font::bold));

    if (isPoweredOn)
        g.drawText("⏻", buttonBounds.translated(0, -1), juce::Justification::centred);
    else
        g.drawText("⏻", buttonBounds, juce::Justification::centred);

    powerLabel.setBounds(buttonX - 15, buttonY + buttonSize + 5, buttonSize + 30, 15);
}

void DroneSynthGUI::drawSliderBackground(juce::Graphics& g, juce::Rectangle<int> bounds, int index)
{
    // Array of neon colors for subtle background tint
    std::array<juce::Colour, 6> sliderColors = {
        neonCyan, neonMagenta, neonGreen, neonOrange, neonPink, neonPurple
    };

    // Create a glowing background for each slider
    juce::ColourGradient gradient(
        sliderColors[index].withAlpha(0.08f),
        bounds.getX(), bounds.getY(),
        sliderColors[index].withAlpha(0.02f),
        bounds.getRight(), bounds.getBottom(),
        true
    );

    g.setGradientFill(gradient);
    g.fillRoundedRectangle(bounds.toFloat(), 4.0f);

    g.setColour(juce::Colours::white.withAlpha(0.15f));
    g.drawRoundedRectangle(bounds.toFloat(), 4.0f, 1.0f);

    // Add subtle inner glow
    g.setColour(sliderColors[index].withAlpha(0.1f));
    g.drawRoundedRectangle(bounds.reduced(1).toFloat(), 3.0f, 0.5f);
}

void DroneSynthGUI::drawSliderFill(juce::Graphics& g, juce::Slider* slider, juce::Colour color)
{
    if (slider == nullptr) return;

    auto bounds = slider->getBounds().toFloat();
    float value = (float)((slider->getValue() - slider->getMinimum()) /
                          (slider->getMaximum() - slider->getMinimum()));

    float fillHeight = bounds.getHeight() * value;
    auto fillBounds = bounds.removeFromBottom(fillHeight);

    // Create neon liquid effect with gradient and glow
    juce::ColourGradient gradient(
        color.brighter(0.7f),
        fillBounds.getX(), fillBounds.getY(),
        color.darker(0.2f),
        fillBounds.getRight(), fillBounds.getBottom(),
        true
    );

    g.setGradientFill(gradient);
    g.fillRoundedRectangle(fillBounds, 3.0f);

    // Add liquid shine effect (top highlight)
    if (value > 0.05f)
    {
        auto highlightBounds = fillBounds.removeFromTop(3);
        g.setColour(juce::Colours::white.withAlpha(0.3f));
        g.fillRoundedRectangle(highlightBounds, 2.0f);
    }

    // Add subtle glow around the filled area
    g.setColour(color.withAlpha(0.15f));
    g.drawRoundedRectangle(fillBounds.reduced(1).toFloat(), 3.0f, 1.5f);
}

void DroneSynthGUI::drawParticleEffects(juce::Graphics& g, juce::Rectangle<int> bounds, float fillLevel, juce::Colour color)
{
    // Add animated particles based on slider level
    if (fillLevel > 0.01f && isPoweredOn)
    {
        int numParticles = (int)(fillLevel * 8);  // More particles
        for (int i = 0; i < numParticles; ++i)
        {
            float x = bounds.getX() + (std::sin(time * 2.0f + i * 0.5f) * 0.3f + 0.5f) * bounds.getWidth();
            float y = bounds.getBottom() - (fillLevel * bounds.getHeight()) - 5.0f - (i * 4.0f);

            // Add some vertical drift
            y += std::sin(time * 3.0f + i) * 2.0f;

            float alpha = 0.4f + 0.3f * std::sin(time * 4.0f + i);
            float size = 1.5f + 1.0f * std::sin(time * 5.0f + i);

            g.setColour(color.withAlpha(alpha));
            g.fillEllipse(x, y, size, size);

            // Add a second layer of smaller particles
            if (fillLevel > 0.5f)
            {
                float x2 = bounds.getX() + (std::cos(time + i) * 0.3f + 0.5f) * bounds.getWidth();
                float y2 = y - 8.0f;
                g.setColour(color.withAlpha(alpha * 0.5f));
                g.fillEllipse(x2, y2, size * 0.7f, size * 0.7f);
            }
        }

        // Add occasional "bubble" at the bottom when liquid is high
        if (fillLevel > 0.7f && std::fmod(time, 0.5f) < 0.1f)
        {
            float x = bounds.getX() + bounds.getWidth() * 0.5f;
            float y = bounds.getBottom() - (fillLevel * bounds.getHeight());
            g.setColour(color.withAlpha(0.2f));
            g.fillEllipse(x - 3, y - 3, 6, 6);
        }
    }
}

// [MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void DroneSynthGUI::setAudioProcessor(RNBO::JuceAudioProcessor *p)
{
    processor = p;

    RNBO::ParameterInfo parameterInfo;
    RNBO::CoreObject& coreObject = processor->getRnboObject();

    for (unsigned long i = 0; i < coreObject.getNumParameters(); i++) {
        auto parameterName = coreObject.getParameterId(i);
        RNBO::ParameterValue value = coreObject.getParameterValue(i);
        Slider *slider = nullptr;

        if (juce::String(parameterName) == slider1->getName()) {
            slider = slider1.get();
        } else if (juce::String(parameterName) == slider2->getName()) {
            slider = slider2.get();
        } else if (juce::String(parameterName) == slider3->getName()) {
            slider = slider3.get();
        } else if (juce::String(parameterName) == slider4->getName()) {
            slider = slider4.get();
        } else if (juce::String(parameterName) == slider5->getName()) {
            slider = slider5.get();
        } else if (juce::String(parameterName) == slider6->getName()) {
            slider = slider6.get();
        }

        if (slider) {
            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            slider->setValue(value, juce::dontSendNotification);
        }
    }
}
// [/MiscUserCode]