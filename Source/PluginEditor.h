#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SimpleEQAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    SimpleEQAudioProcessorEditor(SimpleEQAudioProcessor&);
    ~SimpleEQAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    SimpleEQAudioProcessor& processor;

    juce::Slider hpfSlider, bellFreqSlider, bellGainSlider, lpfSlider;
    juce::Label hpfLabel, bellFreqLabel, bellGainLabel, lpfLabel;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> hpfAttachment, bellFreqAttachment, bellGainAttachment, lpfAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleEQAudioProcessorEditor)
};
