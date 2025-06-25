#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleEQAudioProcessor::SimpleEQAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "PARAMS", {
          std::make_unique<juce::AudioParameterFloat>("HPF", "High-pass cutoff", 20.0f, 20000.0f, 20.0f),
          std::make_unique<juce::AudioParameterFloat>("LPF", "Low-pass cutoff", 20.0f, 20000.0f, 20000.0f),
          std::make_unique<juce::AudioParameterFloat>("BELL_FREQ", "Bell frequency", 20.0f, 20000.0f, 1000.0f),
          std::make_unique<juce::AudioParameterFloat>("BELL_GAIN", "Bell gain", -24.0f, 24.0f, 0.0f)
      })
{
}

SimpleEQAudioProcessor::~SimpleEQAudioProcessor() {}

void SimpleEQAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{ sampleRate,
                                 static_cast<juce::uint32>(samplesPerBlock),
                                 static_cast<juce::uint32>(getMainBusNumInputChannels()) };

    for (auto& chain : filterChains)
        chain.prepare(spec);

    updateFilters();
}

void SimpleEQAudioProcessor::releaseResources() {}

bool SimpleEQAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo()
        && layouts.getMainOutputChannelSet() == layouts.getMainInputChannelSet();
}

void SimpleEQAudioProcessor::updateFilters()
{
    auto sr = getSampleRate();
    auto hpCut = apvts.getRawParameterValue("HPF")->load();
    auto lpCut = apvts.getRawParameterValue("LPF")->load();
    auto bellFreq = apvts.getRawParameterValue("BELL_FREQ")->load();
    auto bellGain = juce::Decibels::decibelsToGain(apvts.getRawParameterValue("BELL_GAIN")->load());

    auto hpfCoeffs = juce::dsp::IIR::Coefficients<float>::makeHighPass(sr, hpCut, 0.7071f);
    auto bellCoeffs = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sr, bellFreq, 1.0f, bellGain);
    auto lpfCoeffs = juce::dsp::IIR::Coefficients<float>::makeLowPass(sr, lpCut, 0.7071f);

    for (auto& chain : filterChains)
    {
        *chain.get<0>().coefficients = *hpfCoeffs;
        *chain.get<1>().coefficients = *bellCoeffs;
        *chain.get<2>().coefficients = *lpfCoeffs;
    }
}

void SimpleEQAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    updateFilters();

    auto block = juce::dsp::AudioBlock<float>(buffer);
    for (size_t ch = 0; ch < filterChains.size(); ++ch)
    {
        auto channelBlock = block.getSingleChannelBlock(ch);
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);
        filterChains[ch].process(context);
    }
}

void SimpleEQAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    if (auto xml = std::unique_ptr<juce::XmlElement>(apvts.copyState().createXml()))
        copyXmlToBinary(*xml, destData);
}

void SimpleEQAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    if (auto xmlState = getXmlFromBinary(data, sizeInBytes))
        apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessorEditor* SimpleEQAudioProcessor::createEditor()
{
    return new SimpleEQAudioProcessorEditor(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleEQAudioProcessor();
}
