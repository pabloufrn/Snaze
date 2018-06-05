#include "main_game_state.hpp"

MainGameState::MainGameState(sf::RenderTarget& target, StateMachine* state_machine) : 
m_game_screen(""), m_status_screen(""), m_machine(state_machine),  m_window(&target), m_player(new AI(m_current_level))
{
    sf::Vector2u window_size = m_window->getSize();
    m_view.setSize(sf::Vector2f {(float) window_size.x, (float) window_size.y});
    m_window->setView(m_view);
}

void MainGameState::init()
{
    // --- Load maps
    
    // -- Load mapcycle file
    
    std::ifstream file(std::string(DATA_FILE_PATH) + "mapcycle.dat");
    
    if(file.fail())
        throw std::runtime_error("[ERROR]: Could not load map cycle.");
    
    std::string next_map;
    while(file >> next_map)
    {
        m_mapcycle.push(next_map);
    }
    
    if(m_mapcycle.empty())
        throw std::runtime_error("[ERROR]: Invalid map cycle.");
    
    // -- Load current level
    
    m_current_level.load_map(m_mapcycle.front());
    m_mapcycle.pop();
    
    // --- Load screen
    
    // -- proprieties

    sf::Vector2u level_size = {m_current_level.get_size().x, m_current_level.get_size().y};
    
    // -- quadBoard
    
    // - init board
    m_quadboard = new QuadBoard(sf::Vector2f {0, 50}, QUAD_SIZE, level_size, 0, TILESET_FILE, sf::Vector2u {2, 3},  MAP_GROUND);
    // - populate board
    for(uint i = 0; i < level_size.y; ++i)
    {
        for(uint j = 0; j < level_size.x; ++j)
        {
            switch(m_current_level.get_object(Point(i, j)))
            {
                case Level::WALL:
                case Level::INV_WALL:
                    m_quadboard->set_quad_texture(i, j, MAP_WALL);
                    break;
                case Level::GROUND:
                    break;
                default:
                    throw std::runtime_error("[ERROR]: Unexpected level error.");
            }
        }
    }
    
    // - place snake
    auto spawn_pos(m_current_level.get_spawn());
    m_view.setCenter(QUAD_SIZE * spawn_pos.y, QUAD_SIZE * (spawn_pos.x + 1));
    m_quadboard->set_quad_texture(spawn_pos.x, spawn_pos.y, SNAKE_HEAD_CROWLING);
    m_player->eat(spawn_pos);
    m_current_level.set_object(spawn_pos, Level::SNAKE);
    // - place apple
    auto apple_pos = m_current_level.place_random_apple();
    m_quadboard->set_quad_texture(apple_pos.x, apple_pos.y, MAP_APPLE);
    
    // -- configure window
    
    m_window->setView(m_view);
    m_game_screen.add_widget(m_quadboard);
    
    
}
void MainGameState::process_events(sf::Event& e)
{
    if(e.type != sf::Event::KeyPressed)
        return;
    
    m_game_screen.update(e);
    m_player->update(e);
}
void MainGameState::update()
{
    //=== Update coditions and variables
    
    sf::Time elapsed = m_clock.getElapsedTime();
    if(elapsed < m_update_period)
        return;
    m_clock.restart();
    
    InternalState state = CRAWLED;
    
    //=== Get player position ===
    
    auto head = m_player->head();
    auto tail = m_player->tail();
    auto new_head = head;
    
    //=== Update internal state ===
    
    // change the head by the body
    m_quadboard->set_quad_texture(head.x, head.y, SNAKE_BODY);
    /* NOTE essa condição que será executada de qualquer jeito fará com que a cabeça da cobra
     * seja o corpo quando ela morrer, mas isso não trará impacto para a interpretaçao do jogo.
     */
    
    Level::MapObject object; 
    switch(m_player->next_move())
    {
        case Direction::N:
            --new_head.x;
            object = m_current_level.get_object(new_head);
            if(object == Level::APPLE)
            {
                // Eat apple
                m_quadboard->set_quad_texture(new_head.x, new_head.y, SNAKE_HEAD_EATING);
                state = ATE_APPLE;
            }
            else
            {
                // Die
                if(object != Level::GROUND)
                {
                    state = DIED;
                    break;
                }
                // Move
                m_quadboard->set_quad_texture(new_head.x, new_head.y, SNAKE_HEAD_CROWLING);
            }
            break;
        case Direction::S:
            ++new_head.x;
            object = m_current_level.get_object(new_head);
            if(object == Level::APPLE)
            {
                // Eat apple
                m_quadboard->set_quad_texture(new_head.x, new_head.y, SNAKE_HEAD_EATING);
                state = ATE_APPLE;
            }
            else
            {
                // Die
                if(object != Level::GROUND)
                {
                    state = DIED;
                    break;
                }
                // Move
                m_quadboard->set_quad_texture(new_head.x, new_head.y, SNAKE_HEAD_CROWLING);
            }
            // rotate head and body
            m_quadboard->rotate_quad_texture(new_head.x, new_head.y, 2);
            m_quadboard->rotate_quad_texture(head.x, head.y, 2);
            break;
        case Direction::E:
            ++new_head.y;
            object = m_current_level.get_object(new_head);
            if(object == Level::APPLE)
            {
                // Eat apple
                m_quadboard->set_quad_texture(new_head.x, new_head.y, SNAKE_HEAD_EATING);
                state = ATE_APPLE;
            }
            else
            {
                // Die
                if(object != Level::GROUND)
                {
                    state = DIED;
                    break;
                }
                // Move
                m_quadboard->set_quad_texture(new_head.x, new_head.y, SNAKE_HEAD_CROWLING);
            }
            // rotate new head
            m_quadboard->rotate_quad_texture(new_head.x, new_head.y, 3);
            m_quadboard->rotate_quad_texture(head.x, head.y, 3);
            break;
        case Direction::W:
            --new_head.y;
            object = m_current_level.get_object(new_head);
            if(object == Level::APPLE)
            {
                // Eat apple
                m_quadboard->set_quad_texture(new_head.x, new_head.y, SNAKE_HEAD_EATING);
                state = ATE_APPLE;
            }
            else
            {
                // Die
                if(object != Level::GROUND)
                {
                    state = DIED;
                    break;
                }
                // Move
                m_quadboard->set_quad_texture(new_head.x, new_head.y, SNAKE_HEAD_CROWLING);
            }
            // rotate new head
            m_quadboard->rotate_quad_texture(new_head.x, new_head.y, 1);
            m_quadboard->rotate_quad_texture(head.x, head.y, 1);
            break;
        default:
            throw std::runtime_error("[ERROR]: Invalid player movement detected.");
    }
    
    //=== Check triggers ===
    if(state == DIED)
    {
        game_over();
        return;
    }
    else if(state == ATE_APPLE)
    {
//         m_player->eat(new_head);
        // place new apple
        
        m_player->crawl(new_head);
        // remove the tail
        m_current_level.set_object(tail, Level::GROUND);
        m_quadboard->set_quad_texture(tail.x, tail.y, MAP_GROUND);
        auto apple_pos = m_current_level.place_random_apple();
        m_quadboard->set_quad_texture(apple_pos.x, apple_pos.y, MAP_APPLE);
    }
    else
    {
        m_player->crawl(new_head);
        // remove the tail
        m_current_level.set_object(tail, Level::GROUND);
        m_quadboard->set_quad_texture(tail.x, tail.y, MAP_GROUND);
    }
    
    //=== Update game Stats ===
    
    // update map and player position
    m_current_level.set_object(new_head, Level::SNAKE);
    // update window view
    head = m_player->head();
    m_view.setCenter(QUAD_SIZE * head.y, QUAD_SIZE * head.x + 50);
    m_window->setView(m_view);
}

void MainGameState::render()
{
    // draw map view
    m_window->draw(m_game_screen);
    // draw status bar
//     m_window->draw(m_game_screen);
}

void MainGameState::game_over()
{
//     return;
    m_machine->add_state(StateRef(new GameOverState(*m_window, m_machine)));
    m_machine->get_active_state()->init();
}
