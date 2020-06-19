#pragma once

#include "Button.hpp"

class BigButton : public Button 
{
    protected:
    void load_button_texture();
    void load_highlighted_button_texture();
    
    public:
    explicit BigButton(const std::string& button_text);
};