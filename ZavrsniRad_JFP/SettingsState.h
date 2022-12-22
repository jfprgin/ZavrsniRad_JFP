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

	std::vector<std::string> fModes{ "No", "Yes" };
    std::vector<sf::VideoMode> rModes;
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

    //Functions
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

