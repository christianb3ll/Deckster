/*
  ==============================================================================

    TapeDeck.cpp
    Created: 2 Sep 2022 4:38:21pm
    Author:  Christian Bell

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TapeDeck.h"

//==============================================================================
TapeDeck::TapeDeck()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TapeDeck::~TapeDeck()
{
}

void TapeDeck::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    
    // speaker shadows
    DropShadow shadow = DropShadow(juce::Colours::black, 4, Point<int>(0,0));

    // Draw the speaker
    double tapeDeckHeight = getHeight();
    double tapeHeight = getWidth()*0.4;
    double speakerHeight = tapeDeckHeight - tapeHeight;

    // speaker border
    g.drawRoundedRectangle(10, 10, getWidth()-20, speakerHeight-20, 4, 1);

    //draw the speaker holes
    Path speakerHolesPath;
    for (auto i = 0; i < 4; ++i){
        for (auto j = 0; j < 10; ++j){
            speakerHolesPath.addEllipse(22*j, 14*i, 10, 10);
        }
    }
    DrawablePath speakerHoles;

    speakerHolesPath.scaleToFit(getWidth()*0.25, speakerHeight*0.25, getWidth()/2, speakerHeight/2, true);
    speakerHoles.setPath(speakerHolesPath);
    speakerHoles.setFill(FillType());
    speakerHoles.draw(g, 1.0f,AffineTransform());

    shadow.drawForPath(g,speakerHolesPath);



    // Draw the tapedeck BG
    g.setColour(Colour(107, 107, 107));
    g.fillRect(0, speakerHeight, getWidth(), tapeHeight);

    //Draw the Tape body

    Rectangle<int> tapeBody(getWidth()*0.1, speakerHeight, getWidth()*0.8, tapeHeight);




//    shadow.drawForRectangle(g, tapeBody);
    g.setColour(Colour(200, 200, 200));
    g.fillRect(tapeBody);

    //Draw tape window
    double tapeWindowWidth = getWidth()*0.5;
    double sprocket1X = tapeWindowWidth/2;
    double sprocket2X = sprocket1X + tapeWindowWidth;
    double sprocketWidth = tapeHeight*0.3;
    g.setColour(Colour(142, 142, 142));
    g.fillRect(float(sprocket1X), speakerHeight + sprocketWidth, tapeWindowWidth, sprocketWidth);
    g.setColour(juce::Colours::white);
    g.fillEllipse(float(sprocket1X), speakerHeight + sprocketWidth, sprocketWidth, sprocketWidth);
    g.fillEllipse(float(sprocket2X - sprocketWidth), speakerHeight + sprocketWidth, sprocketWidth, sprocketWidth);
    
    // draw sprockets
//    double sprocketOrigin = sprocket1X + ;
    
    g.setColour(juce::Colours::black);
    Path sprocket1;
    sprocket1.addRectangle(0,sprocketWidth/2,sprocketWidth,1);
    sprocket1.addRectangle(sprocketWidth/2,0,1,sprocketWidth);
    
    Path sprocket2(sprocket1);
    
    sprocket1.applyTransform(AffineTransform::rotation(0.1, sprocketWidth/2, sprocketWidth/2));
    sprocket1.applyTransform(AffineTransform::translation(sprocket1X,speakerHeight + sprocketWidth));
    g.strokePath(sprocket1, PathStrokeType(1.0f,PathStrokeType::beveled));
    
    sprocket2.applyTransform(AffineTransform::rotation(0.1, sprocketWidth/2, sprocketWidth/2));
    sprocket2.applyTransform(AffineTransform::translation(sprocket2X - sprocketWidth,speakerHeight + sprocketWidth));
    g.strokePath(sprocket2, PathStrokeType(1.0f,PathStrokeType::beveled));
    

    
    // draw the tape base
    double tapeBaseBottom = speakerHeight + tapeHeight;
    double tapeBaseOriginX = (getWidth()/4)*0.9;
    double tapeBaseOriginY = speakerHeight + (tapeHeight*0.75);
    
    Path tapeBase;
    tapeBase.startNewSubPath (Point<float> (getWidth()/4, tapeBaseOriginY));
    tapeBase.lineTo (Point<float> (tapeBaseOriginX, tapeBaseBottom));
    tapeBase.lineTo (Point<float> (getWidth() - tapeBaseOriginX, tapeBaseBottom));
    tapeBase.lineTo (Point<float> (getWidth() - getWidth()/4, tapeBaseOriginY));
    tapeBase.closeSubPath();
    
    g.setColour(Colour(220, 220, 220));
    g.fillPath(tapeBase);
    g.setColour(juce::Colours::white);
    g.strokePath(tapeBase, PathStrokeType(1.0f,PathStrokeType::beveled));
    
    // Draw tape base holes
    g.setColour(juce::Colours::black);
    // left side
    g.fillEllipse(tapeBaseOriginX*1.2, speakerHeight+(tapeHeight*0.85), tapeHeight*0.1, tapeHeight*0.1);
    g.fillEllipse(tapeBaseOriginX*1.5, speakerHeight+(tapeHeight*0.83), tapeHeight*0.05, tapeHeight*0.05);
    // right side
    g.fillEllipse((getWidth() - tapeBaseOriginX)*0.9, speakerHeight+(tapeHeight*0.85), tapeHeight*0.1, tapeHeight*0.1);
    g.fillEllipse((getWidth() - tapeBaseOriginX)*0.85, speakerHeight+(tapeHeight*0.83), tapeHeight*0.05, tapeHeight*0.05);
    
    
    // Draw the shine
//    g.setColour(Colour(255.0f,255.0f,255.0f, 0.4f));
//    g.fillRect(getWidth()/2,0,getWidth()*0.1,getHeight()*2);
//
    
    
    
    
    
}

void TapeDeck::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
