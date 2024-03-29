/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A3AudioProcessorEditor::A3AudioProcessorEditor(A3AudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(800, 400);
    addAndMakeVisible(&openButton);
    openButton.onClick = [this] { buttonClicked(); };

    //filterMenu.setJustificationType(juce::Justification::centred);
    //filterMenu.addItem("Filter: Low Pass", 1);
    //filterMenu.addItem("Filter: Band Pass", 2);
    //filterMenu.addItem("Filter: High Pass", 3);
    //filterMenu.addItem("Filter: Off", 4);
    //addAndMakeVisible(&filterMenu);

    //phaserMenu.setJustificationType(juce::Justification::centred);
    //phaserMenu.addItem("Phaser: On", 1);
    //phaserMenu.addItem("Phaser: Off", 2);
    //addAndMakeVisible(&phaserMenu);

    emulatedImpulseMenu.setJustificationType(juce::Justification::centred);
    emulatedImpulseMenu.addItem("Emulated IR Off", 1);
    emulatedImpulseMenu.addItem("Fast Decay IR", 2);
    emulatedImpulseMenu.addItem("Slow Decay IR", 3);
    addAndMakeVisible(&emulatedImpulseMenu);

    reverbType.setJustificationType(juce::Justification::centred);
    reverbType.addItem("No Reverb", 1);
    reverbType.addItem("Basic Reverb", 2);
    reverbType.addItem("Recorded Impulse Response", 3);
    reverbType.addItem("Constructed Impulse Response", 4);
    reverbType.addItem("Simluation Reverb(Not Implemented)", 5);
    addAndMakeVisible(&reverbType);


    impulseMenu.setJustificationType(juce::Justification::centred);
    //auto files = juce::File::getSpecialLocation(juce::File::userDesktopDirectory).getChildFile("Resources").findChildFiles(3, true, "*.wav");
    impulseMenu.addItem("Impulse Response: Off", 1);
    /*   for (int i = 0; i < files.size(); i++) {
           impulseMenu.addItem(files[i].getFileNameWithoutExtension(), i + 1);
       }*/
    impulseMenu.addItem("Parking Garage", 2);
    impulseMenu.addItem("St Nicolaes Church", 3);
    impulseMenu.addItem("Large Wide Echo Hall", 4);
    impulseMenu.addItem("Conic Long Echo Hall", 5);
    impulseMenu.addItem("On a Star", 6);
    impulseMenu.addItem("Large Long Echo Hall", 7);
    impulseMenu.addItem("In a Silo", 8);
    impulseMenu.addItem("{ Uploaded Impulse Response }", 9);
    //int numimp = desktop.getSpecialLocation(desktop.userDesktopDirectory).getChildFile("Resources").getNumberOfChildFiles(3, "*.wav");
    //audioProcessor.desktop.getFileNameWithoutExtension
    addAndMakeVisible(&impulseMenu);


    cutOffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    cutOffSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    cutOffSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&cutOffSlider);
    delaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    delaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    delaySlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&delaySlider);


    //rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    //rateSlider.setPopupDisplayEnabled(true, true, this);
    //addAndMakeVisible(&rateSlider);
    //
    //depthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    //depthSlider.setPopupDisplayEnabled(true, true, this);
    //addAndMakeVisible(&depthSlider);
    //
    //gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    //gainSlider.setPopupDisplayEnabled(true, true, this);
    //addAndMakeVisible(&gainSlider);

    //reverb
  /*  dampSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    dampSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dampSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&dampSlider);*/
    drySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    drySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    drySlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&drySlider);
    /* freezeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
     freezeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
     freezeSlider.setPopupDisplayEnabled(true, true, this);
     addAndMakeVisible(&freezeSlider);*/
    roomSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    roomSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    roomSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&roomSlider);
    wetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    wetSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    wetSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&wetSlider);
    widthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    widthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    widthSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&widthSlider);

    IRLengthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    IRLengthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    IRLengthSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&IRLengthSlider);


    cutOffValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "CUTOFF", cutOffSlider);
    rateValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "PHASERRATE", rateSlider);
    depthValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "PHASERDEPTH", depthSlider);
    gainValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN", gainSlider);
    gainValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DELAY", delaySlider);
    //reverb
    //dampValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DAMPING", dampSlider);
    dryValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRYLEVEL", drySlider);
    //freezeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREEZE", freezeSlider);
    roomValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ROOMSIZE", roomSlider);
    wetValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WET", wetSlider);
    widthValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WIDTH", widthSlider);
    widthValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "IRLENGTH", IRLengthSlider);
    //buttonValue = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "BUTTON", openButton);

    filterMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "FILTERMENU", filterMenu);
    phaserMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "PHASERMENU", phaserMenu);
    ImpulseValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "IMPULSEMENU", impulseMenu);
    reverbValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "REVERBMENU", reverbType);
    emulatedImpulseValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "EMULATEDMENU", emulatedImpulseMenu);

}

A3AudioProcessorEditor::~A3AudioProcessorEditor()
{
}

//==============================================================================
void A3AudioProcessorEditor::paint(juce::Graphics& g)
{
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::greenyellow);
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    juce::Rectangle<int> titleArea = area.removeFromTop(20);
    //int width = area.getWidth();
    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::white);
    g.drawText("A3 Starter", titleArea, juce::Justification::centredTop);

    juce::Rectangle <int> innerArea = getLocalBounds().reduced(25);//(25, 25, 350, 150);
    g.setColour(juce::Colours::yellowgreen);
    g.drawRect(innerArea, 1.0f);

    int innerWidth = innerArea.getWidth();
    g.drawText("Cutoff", cutOffSlider.getX() - 10, cutOffSlider.getY() - 10, innerWidth / 6, 25, juce::Justification::centred);
    //g.drawText("Rate", rateSlider.getX() - 10, rateSlider.getY() - 10,  innerWidth / 6, 25, juce::Justification::centred);
    //g.drawText("Depth", depthSlider.getX() - 10, depthSlider.getY() - 10,  innerWidth / 6, 25, juce::Justification::centred);
    //g.drawText("Gain", gainSlider.getX() - 10, gainSlider.getY() - 10,  innerWidth / 6, 25, juce::Justification::centred);
    //reverb
    //g.drawText("Damping", dampSlider.getX() - 10 , dampSlider.getY() - 10, innerWidth / 6, 25, juce::Justification::centred);
    g.drawText("Basic Reverb settings ", drySlider.getX()-(innerWidth/7.5), drySlider.getY()-30 , innerWidth / 4, 25, juce::Justification::centred);
    g.drawText("Simulation Reverb settings ", cutOffSlider.getX()- (innerWidth/4.5), cutOffSlider.getY()-30, innerWidth / 3, 25, juce::Justification::centred);
    g.drawText("Dry", drySlider.getX() - 10, drySlider.getY() - 10, innerWidth / 6, 25, juce::Justification::centred);
    //g.drawText("Freeze", freezeSlider.getX() - 10, freezeSlider.getY() - 10,  innerWidth / 6, 25, juce::Justification::centred);
    g.drawText("Room size", roomSlider.getX() - 10, roomSlider.getY() - 10, innerWidth / 6, 25, juce::Justification::centred);
    g.drawText("Wet", wetSlider.getX() - 10, wetSlider.getY() - 10, innerWidth / 6, 25, juce::Justification::centred);
    g.drawText("Width", widthSlider.getX() - 10, widthSlider.getY() - 10, innerWidth / 6, 25, juce::Justification::centred);
    g.drawText("Delay time ", delaySlider.getX() - 10, delaySlider.getY() - 10, innerWidth / 6, 25, juce::Justification::centred);

    g.drawText("Length of Emulated IR Reverb", IRLengthSlider.getX()-20, IRLengthSlider.getY()-20, innerWidth / 3, 30, juce::Justification::centred);
}

void A3AudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    juce::Rectangle<int> menus = area.removeFromTop(20);
    int width = menus.getWidth();
    //filterMenu.setBounds(menus.removeFromLeft(width / 4 - 5));
    //phaserMenu.setBounds(menus.removeFromLeft(width / 4 - 5));
    reverbType.setBounds(menus.removeFromLeft(width / 3 - 5));
    impulseMenu.setBounds(menus.removeFromLeft(width / 3 - 5));
    //emulatedImpulseMenu.setBounds(menus.removeFromLeft(width / 3 - 5));
    emulatedImpulseMenu.setBounds(impulseMenu.getX()+ impulseMenu.getWidth(), impulseMenu.getY(), impulseMenu.getWidth(), 20);
    openButton.setBounds(impulseMenu.getX(), impulseMenu.getY() + 40, impulseMenu.getWidth(), 40);
    //rateSlider.setBounds (125, 130, width / 6 - 10, 100);
    //depthSlider.setBounds (205, 130, width / 6 - 10, 100);
    //gainSlider.setBounds (290, 130, width / 6 - 10, 100);
    //reverb
    //dampSlider.setBounds(35, 180, width / 6 - 10, 100);
    drySlider.setBounds(145, 140, width / 6 - 10, 100);
    //freezeSlider.setBounds(205, 180, width / 6 - 10, 100);
    roomSlider.setBounds(260, 140, width / 6 - 10, 100);
    wetSlider.setBounds(375, 140, width / 6 - 10, 100);
    widthSlider.setBounds(490, 140, width / 6 - 10, 100);
    cutOffSlider.setBounds(260, 280, width /6 - 10, 100);
    delaySlider.setBounds( 375, 280, width / 6 - 10, 100);
    IRLengthSlider.setBounds(emulatedImpulseMenu.getX()+10, emulatedImpulseMenu.getY() +70, width /  3 - 20, 20);
}

void A3AudioProcessorEditor::buttonClicked() {
    juce::FileChooser chooser("Select a Wave file to play...", {}, "*.wav");

    if (chooser.browseForFileToOpen())
    {

        auto file = chooser.getResult();
        audioProcessor.userfile = file;
        if (file.exists()) {
            //int numfiles = audioProcessor.desktop.getSpecialLocation(juce::File::userDesktopDirectory).getChildFile("Resources").getNumberOfChildFiles(3, "*.wav");
            impulseMenu.changeItemText(9, file.getFileNameWithoutExtension());
            impulseMenu.setSelectedId(9);
            impulseMenu.setText(file.getFileNameWithoutExtension());
        }

    }

}