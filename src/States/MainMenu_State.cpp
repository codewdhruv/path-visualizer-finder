#include "MainMenu_State.h"

// Constructor
MainMenu_State::MainMenu_State(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states) {
  initBackground();
  initFonts();
  initButtons();
}

// Destructor
MainMenu_State::~MainMenu_State()
{
  for (auto it = buttons_.begin(); it != buttons_.end(); ++it) {
    delete it->second;
  }

  delete testDDL_;
}

void MainMenu_State::initBackground()
{
  background_.setSize(sf::Vector2f(window_->getSize().x, window_->getSize().y));

  if (!backgroundTexture_.loadFromFile("../figures/main_menu.jpeg")) {
    throw("ERROR::MainMenuSTATE::COULD NOT LOAD FIGURE.");
  }

  background_.setTexture(&backgroundTexture_);
}

void MainMenu_State::initFonts()
{
  if (!font_.loadFromFile("../fonts/ostrich-regular.ttf")) {
    throw("ERROR::MainMenuSTATE::COULD NOT LOAD FONT.");
  }
}

void MainMenu_State::initButtons()
{

  // int x = window_->getSize().x/2;

  int x = window_->getSize().x / 2 - 200;
  int y = window_->getSize().y / 2 - 150;

  std::string li[] = {"BFS", "DFS", "A-Star", "Dijkstra"};
  testDDL_ = new gui::DropDownList(x, y,  150, 50, &font_, "Select Algorithm", li, 4);

  // buttons_["START"] = new gui::Button(x, y, 150, 50,
  //     &font_, "RUN", 25,
  //     sf::Color(255, 255, 255, 255),
  //     sf::Color(240, 240, 240, 200),
  //     sf::Color(240, 240, 240, 200)
  // );

  buttons_["EXIT"] = new gui::Button(x, y+400, 150, 50,
      &font_, "EXIT", 25,
      sf::Color(255, 255, 255, 255),
      sf::Color(240, 240, 240, 200),
      sf::Color(240, 240, 240, 200)
  );
}

// TODO: Need to update this hardcoded function
void MainMenu_State::updateButtons(const float &dt)
{
  for (auto &it: buttons_) {
    it.second->update(sf::Vector2f(mousePositionWindow_));
  }

  testDDL_->update(sf::Vector2f(mousePositionWindow_), dt);

  if (testDDL_->hasActiveButton()) {
    int algo_num = 0;

    std::string algo = testDDL_->getActiveButton()->getText();

    if (algo == "BFS") {
      algo_num = 1;
    }

    switch (algo_num) {
      case 1:
        states_->push(new BFS(window_, states_));
        break;
      case 2:
        break;
      default:
        break;
    }
  }

  // Quit the game
  if (buttons_["EXIT"]->isPressed()) {
    quit_ = true;
  }
}

void MainMenu_State::renderButtons()
{
  for (auto &it: buttons_) {
    it.second->render(window_);
  }

  testDDL_->render(window_);
}

void MainMenu_State::renderBackground()
{
  window_->draw(background_);
}

void MainMenu_State::endState()
{
  std::cout << "Ending MainMenu State" << '\n';
}

void MainMenu_State::updateKeybinds()
{
  checkForQuit();
}

void MainMenu_State::update(const float &dt)
{
  updateMousePosition();
  updateKeybinds();
  updateButtons(dt);
}

void MainMenu_State::render()
{
  renderBackground();
  renderButtons();
}
