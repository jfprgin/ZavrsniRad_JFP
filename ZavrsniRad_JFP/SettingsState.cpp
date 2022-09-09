#include "stdafx.h"
#include "SettingsState.h"

//Private functions
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::SETTINGS_STATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void SettingsState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background init
	this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.jpg"))
	{
		throw "ERROR::SETTINGS_STATE::FAILED TO LOAD BACKGROUND TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);

	//Button init
	this->buttons["BACK"] = new gui::Button(
		gui::p2px(78.1f, vm), gui::p2py(81.5f, vm),
		gui::p2px(13.f, vm), gui::p2py(6.f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),	//text color
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		//button color

	this->buttons["APPLY"] = new gui::Button(
		gui::p2px(60.f, vm), gui::p2py(81.5f, vm),
		gui::p2px(13.f, vm), gui::p2py(6.f, vm),
		&this->font, "Apply", gui::calcCharSize(vm),
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),	//text color
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		//button color
	
	//Modes init
	std::vector<std::string> modes_str;
	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	//Dropdown list init
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(
		gui::p2px(42.f, vm), gui::p2py(42.f, vm),
		gui::p2px(10.4f, vm), gui::p2py(4.5f, vm),
		font, modes_str.data(), modes_str.size()
	);

	this->dropDownLists["FULLSCREEN"] = new gui::DropDownList(
		gui::p2px(42.f, vm), gui::p2py(52.f, vm),
		gui::p2px(10.4f, vm), gui::p2py(4.5f, vm),
		font, this->modes2.data(), this->modes2.size()
	);

	//Text init
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(gui::p2px(5.2f, vm), gui::p2py(41.7f, vm)));
	this->optionsText.setCharacterSize(gui::calcCharSize(vm, 70));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n");
}

void SettingsState::resetGui()
{
	/*
	* Clears the GUI elements and re-initialises the GUI
	*/

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropDownLists.clear();

	this->initGui();
}

//Constructor and Destructor
SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

//Functions
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	/*Update all the gui elements in the state and handles their functionality*/
	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Buttons functionality
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	//Apply selected state
	if (this->buttons["APPLY"]->isPressed())
	{
		//TEST REMOVE LATER
		this->gfxSettings.loadFromFile("Config/graphics.ini");

		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];

		if (this->modes2[this->dropDownLists["FULLSCREEN"]->getActiveElementId()] == "Yes")
		{
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Fullscreen);
			this->gfxSettings.title = "SFML C++";
			this->gfxSettings.resolution.width = this->stateData->gfxSettings->resolution.width;
			this->gfxSettings.resolution.height = this->stateData->gfxSettings->resolution.height;
			this->gfxSettings.fullscreen = true;
			this->gfxSettings.saveToFile("Config/graphics.ini");
		}
		else
		{
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
			this->gfxSettings.title = "SFML C++";
			this->gfxSettings.resolution.width = this->stateData->gfxSettings->resolution.width;
			this->gfxSettings.resolution.height = this->stateData->gfxSettings->resolution.height;
			this->gfxSettings.fullscreen = false;
			this->gfxSettings.saveToFile("Config/graphics.ini");
		}

		this->resetGui();
	}

	//Dropdown lists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosView, dt);
	}

	//Dropdown lists functionality

}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);
}