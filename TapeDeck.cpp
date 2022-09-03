#include <JuceHeader.h>
#include "TapeDeck.h"

/** Constructor for TapeDeck class */
TapeDeck::TapeDeck() :
                    position(0),
                    speed(0)
{
}

/** Destructor for TapeDeck class */
TapeDeck::~TapeDeck()
{
}

/** gets called when a region of a component needs redrawing */
void TapeDeck::paint (juce::Graphics& g)
{
    // Fill the background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // Draw component outline
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    
    // Set up speaker shadows
    DropShadow shadow = DropShadow(juce::Colours::black, 4, Point<int>(0,0));

    // Set up height variables
    double tapeDeckHeight = getHeight();
    double tapeHeight = getWidth()*0.4;
    double speakerHeight = tapeDeckHeight - tapeHeight;

    // Draw the speaker
    // speaker border
    g.drawRoundedRectangle(10, 10, getWidth()-20, speakerHeight-20, 4, 1);

    // Add the speaker holes to a new path
    Path speakerHolesPath;
    for (auto i = 0; i < 4; ++i){
        for (auto j = 0; j < 10; ++j){
            speakerHolesPath.addEllipse(22*j, 14*i, 10, 10);
        }
    }
    // Create a drawable path
    DrawablePath speakerHoles;

    // Scale the path
    speakerHolesPath.scaleToFit(getWidth()*0.25, speakerHeight*0.25, getWidth()/2, speakerHeight/2, true);
    // Add the path to the drawable path
    speakerHoles.setPath(speakerHolesPath);
    // Draw the speaker holes
    speakerHoles.setFill(FillType());
    speakerHoles.draw(g, 1.0f,AffineTransform());
    // Add the shadow to the holes
    shadow.drawForPath(g,speakerHolesPath);


    // Draw the tapedeck background
    g.setColour(Colour(107, 107, 107));
    g.fillRect(0, speakerHeight, getWidth(), tapeHeight);

    //Draw the Tape body
    Rectangle<int> tapeBody(getWidth()*0.1, speakerHeight, getWidth()*0.8, tapeHeight);
    g.setColour(Colour(200, 200, 200));
    g.fillRect(tapeBody);
    //    shadow.drawForRectangle(g, tapeBody);

    // Draw tape window and sprocket base
    double tapeWindowWidth = getWidth()*0.5;
    double sprocket1X = tapeWindowWidth/2;
    double sprocket2X = sprocket1X + tapeWindowWidth;
    double sprocketWidth = tapeHeight*0.3;
    g.setColour(Colour(142, 142, 142));
    g.fillRect(float(sprocket1X), speakerHeight + sprocketWidth, tapeWindowWidth, sprocketWidth);
    g.setColour(juce::Colours::white);
    g.fillEllipse(float(sprocket1X), speakerHeight + sprocketWidth, sprocketWidth, sprocketWidth);
    g.fillEllipse(float(sprocket2X - sprocketWidth), speakerHeight + sprocketWidth, sprocketWidth, sprocketWidth);
    
    // Setup the sprocket paths
    g.setColour(juce::Colours::black);
    Path sprocket1;
    sprocket1.addRectangle(0,sprocketWidth/2,sprocketWidth,1);
    sprocket1.addRectangle(sprocketWidth/2,0,1,sprocketWidth);
    
    // Duplicate the sprocket
    Path sprocket2(sprocket1);
    
    // Rotate the sprocket based on current player pos and speed
    sprocket1.applyTransform(AffineTransform::rotation(position*speed, sprocketWidth/2, sprocketWidth/2));
    sprocket2.applyTransform(AffineTransform::rotation(position*speed, sprocketWidth/2, sprocketWidth/2));
    
    // Translate the sprocket to correct position on tape
    sprocket1.applyTransform(AffineTransform::translation(sprocket1X,speakerHeight + sprocketWidth));
    sprocket2.applyTransform(AffineTransform::translation(sprocket2X - sprocketWidth,speakerHeight + sprocketWidth));
    
    // Draw the sprockets
    g.strokePath(sprocket1, PathStrokeType(1.0f,PathStrokeType::beveled));
    g.strokePath(sprocket2, PathStrokeType(1.0f,PathStrokeType::beveled));
    

    
    // Setup tape base variables
    double tapeBaseBottom = speakerHeight + tapeHeight;
    double tapeBaseOriginX = (getWidth()/4)*0.9;
    double tapeBaseOriginY = speakerHeight + (tapeHeight*0.75);
    
    // Create path for tape base
    Path tapeBase;
    tapeBase.startNewSubPath (Point<float> (getWidth()/4, tapeBaseOriginY));
    tapeBase.lineTo (Point<float> (tapeBaseOriginX, tapeBaseBottom));
    tapeBase.lineTo (Point<float> (getWidth() - tapeBaseOriginX, tapeBaseBottom));
    tapeBase.lineTo (Point<float> (getWidth() - getWidth()/4, tapeBaseOriginY));
    tapeBase.closeSubPath();
    
    // Draw the tape base
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
    
    
    // Draw the shine overlay
//    g.setColour(Colour(255.0f,255.0f,255.0f, 0.4f));
//    g.fillRect(getWidth()/2,0,getWidth()*0.1,getHeight()*2);

}

/** Called when this component's size has been changed. */
void TapeDeck::resized()
{
}

/** Set the relative position for tape rotation  */
void TapeDeck::setPositionRelative(double pos){
    if(pos != position){
        position = pos;
        repaint();
    }
}

/** sets the speed as a ratio between 1 and 100  */
void TapeDeck::setSpeed(double ratio){
    speed = ratio;
}
