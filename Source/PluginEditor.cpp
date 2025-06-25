#include "PluginEditor.h"

SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor(SimpleEQAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    auto& apvts = processor.apvts;

    hpfLabel.setText("HPF", juce::dontSendNotification);
    bellFreqLabel.setText("Bell Freq", juce::dontSendNotification);
    bellGainLabel.setText("Bell Gain", juce::dontSendNotification);
    lpfLabel.setText("LPF", juce::dontSendNotification);

    for (auto* slider : { &hpfSlider, &bellFreqSlider, &bellGainSlider, &lpfSlider })
    {
        slider->setSliderStyle(juce::Slider::Rotary);
        slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible(slider);
    }
    for (auto* label : { &hpfLabel, &bellFreqLabel, &bellGainLabel, &lpfLabel })
    {
        label->setJustificationType(juce::Justification::centred);
        addAndMakeVisible(label);
    }

    hpfAttachment      = std::make_unique<Attachment>(apvts, "HPF", hpfSlider);
    bellFreqAttachment = std::make_unique<Attachment>(apvts, "BELL_FREQ", bellFreqSlider);
    bellGainAttachment = std::make_unique<Attachment>(apvts, "BELL_GAIN", bellGainSlider);
    lpfAttachment      = std::make_unique<Attachment>(apvts, "LPF", lpfSlider);

    setSize(450, 220);
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor() {}

void SimpleEQAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void SimpleEQAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto w = area.getWidth() / 4;

    hpfSlider.setBounds(area.removeFromLeft(w).withTrimmedBottom(20));
    hpfLabel .setBounds(hpfSlider.getX(), hpfSlider.getBottom(), w, 20);

    bellFreqSlider.setBounds(area.removeFromLeft(w).withTrimmedBottom(20));
    bellFreqLabel .setBounds(bellFreqSlider.getX(), bellFreqSlider.getBottom(), w, 20);

    bellGainSlider.setBounds(area.removeFromLeft(w).withTrimmedBottom(20));
    bellGainLabel .setBounds(bellGainSlider.getX(), bellGainSlider.getBottom(), w, 20);

    lpfSlider.setBounds(area.removeFromLeft(w).withTrimmedBottom(20));
    lpfLabel .setBounds(lpfSlider.getX(), lpfSlider.getBottom(), w, 20);
}
