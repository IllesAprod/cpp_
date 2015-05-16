#include "Application.hpp"
#include <iostream>
using namespace genv;

/*** CONSTRUCTOR ***/
Application::Application(int w, int h)
: width(w), height(h)
{

    FocusIndex = FocusableWidgets.size()+1;
    gout.open(width, height);
}

/*** FUNCTIONS ***/

void Application::EventHandler()
{
    if (ev.keycode == key_tab)
    {
        KeyTab();
    }

    if (ev.type == ev_mouse && ev.button == btn_left)
    {
        LeftClick(ev.pos_x, ev.pos_y);
    }
    if(FocusIndex < FocusableWidgets.size() && FocusIndex >= 0); //-> EventHandler(ev);
}

void Application::KeyTab()
{
    if(FocusIndex < FocusableWidgets.size()) FocusIndex++;
    else FocusIndex = 0;
    if(FocusIndex > 0) FocusableWidgets[FocusIndex-1] -> SetFocusOff();
    if(FocusIndex < FocusableWidgets.size()) FocusableWidgets[FocusIndex] -> SetFocusOn();
}

void Application::LeftClick(int x, int y)
{
    bool still = false;
    for (unsigned int i=0; i<FocusableWidgets.size() && !still; i++)
    {
        FocusableWidgets[i] -> SetFocusOff();
        if(FocusableWidgets[i] -> GetOnMe(x, y))
        {
            still = true;
            FocusableWidgets[i] -> SetFocusOn();
            FocusIndex = i;
        }
    }
    if(!still)
    {
        FocusIndex = FocusableWidgets.size();
    }
}

void Application::Initialize()
{
}

void Application::LoadWidget(Widget* widget)
{
    Widgets.push_back(widget);
    if (widget -> GetFocusable())  FocusableWidgets.push_back(widget);
}
