#pragma once

#include "State.h"
#include "Gui.h"

class SettingsState :
    public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;

    sf::Text optionsText;

	std::vector<std::string> modes2{ "No", "Yes" };
    std::vector<sf::VideoMode> modes;
	GraphicsSettings gfxSettings;

    //Functions
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initGui();
	void resetGui();

public:
    SettingsState(StateData* state_data);
    ~SettingsState();

    //Accessors

    //Functions
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

