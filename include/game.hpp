#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "main_menu_state.hpp"

struct GameData
{
    StateMachine sm;
    sf::RenderWindow window;
};

using GameDataRef = std::shared_ptr<GameData>;
        
class Game
{
    
    public: 
        Game(sf::Vector2u window_size, std::string title);
        void run();
    private:
        // dados usados pelo jogo
        GameDataRef m_data = std::make_shared<GameData>();
};

Game::Game(sf::Vector2u window_size, std::string title)
{
    m_data->window.create(sf::VideoMode(window_size.x, window_size.y), title, sf::Style::Titlebar + sf::Style::Close);
}

void Game::run()
{
    // inicia no menu
    sf::Image icon;
    icon.loadFromFile(FAVICON_FILE);
    m_data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    m_data->sm.add_state(StateRef(new MainMenuState(m_data->window, &m_data->sm)));
    m_data->sm.get_active_state()->init();
    // game loop
    while (m_data->window.isOpen())
    {
        sf::Event e;
		while (m_data->window.pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
			{
				m_data->window.close();
				break;

			}
        }
        m_data->sm.get_active_state()->process_events(e);
        if(m_data->sm.empty())
            return;
        m_data->sm.get_active_state()->update();
        m_data->window.clear();
        m_data->sm.get_active_state()->render();
        m_data->window.display();
    }
}

#endif
