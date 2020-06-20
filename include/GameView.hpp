#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

#include "AttackInfoBox.hpp"
#include "BigButton.hpp"
#include "Board.hpp"
#include "Box.hpp"
#include "Button.hpp"

class Player;
enum class TURN;

enum class GAME_STATE {
    BOARDS_NOT_SET,
    BOARD_A_SET,
    BOARD_B_SET,
    BOTH_BOARDS_SET,
    UNIT_MOVED,
    UNIT_ATTACKED,
    TURN_ENDED,
    TURN_APPROVED,
    PLAYER_A_MOVE,
    PLAYER_B_MOVE,
    GAME_FINISHED,
};

class GameView {
    Player& playerA;
    Player& playerB;
    int TILE_SIZE;
    int X_ADDITIONAL_SPACE;
    sf::Vector2f window_size;
    TURN current_player_turn;
    Player* current_player;
    Player* other_player;
    bool dragging;
    float mouse_x;
    float mouse_y;
    float mouseObjectOffSetX;
    float mouseObjectOffSetY;
    sf::Sprite* unit_it;
    sf::Vector2f sprite_initial_position;
    bool board_a_initialized;
    bool board_b_initialized;
    Board::Tile active_unit;
    bool is_active_unit;
    Board::Tile hovering_tile;
    bool unit_moved_this_round;
    const std::string board_textures_path;
    const std::string pieces_textures_path;
    GAME_STATE global_game_state;
    GAME_STATE local_game_state;
    bool end_turn_button_pressed;
    bool turn_approved;
    bool unit_attacked;
    Board::Tile attacking_unit;
    Board::Tile attacked_unit;
    bool clock_started;
    bool remove_button_pressed;
    bool done_button_pressed;
    std::string victorious_player_name;

    sf::Sprite board_border;
    sf::Sprite grass_light;
    sf::Sprite grass_dark;
    std::array<sf::Sprite, 12> red_units_sprites;
    sf::Sprite red_back_sprite;
    std::array<sf::Sprite, 12> blue_units_sprites;
    sf::Sprite blue_back_sprite;
    sf::Sprite yellow_highlight_sprite;
    sf::Sprite white_highlight_sprite;
    sf::Sprite green_highlight_sprite;
    sf::Sprite red_highlight_sprite;

    sf::Texture board_border_texture;
    sf::Texture grass_light_texture;
    sf::Texture grass_dark_texture;
    std::array<std::pair<sf::Sprite, std::string>, 8> obstacle_sprites;
    std::array<std::pair<sf::Texture, std::string>, 8> obstacle_textures;
    std::array<sf::Texture, 12> red_unit_textures;
    sf::Texture red_back_texture;
    std::array<sf::Texture, 12> blue_unit_textures;
    sf::Texture blue_back_texture;
    sf::Texture yellow_highlight_texture;
    sf::Texture white_highlight_texture;
    sf::Texture green_highlight_texture;
    sf::Texture red_highlight_texture;

    sf::Clock clock;
    sf::Font font;
    sf::Text text;
    Button done_button;
    Button remove_button;
    Button end_turn_button;
    BigButton start_screen_button;
    Box info_box;
    AttackInfoBox attack_info_box;
    Box end_game_info_box;

    void load_red_units_textures();
    void load_blue_units_textures();
    void load_highlight_textures();
    void set_red_units_sprites();
    void set_blue_units_sprites();
    void set_highlight_sprites();

    void draw_grass(sf::RenderWindow& win);
    void draw_obstacles(sf::RenderWindow& win);
    void draw_units_for_init(sf::RenderWindow& win);
    void draw_board(sf::RenderWindow& win);
    void draw_sprite(sf::RenderWindow& win, int idx, int sprite_pos_x, int sprite_pos_y);
    void draw_red_init_units(sf::RenderWindow& win);
    void draw_blue_init_units(sf::RenderWindow& win);
    void draw_done_button(sf::RenderWindow& win);
    void draw_remove_button(sf::RenderWindow& win);
    void draw_possible_moves_for_active_unit(sf::RenderWindow& win);
    void draw_info_box(sf::RenderWindow& win);
    void draw_attack_info_box(sf::RenderWindow& win);
    void draw_units(sf::RenderWindow& win);
    void draw_unit_highlight(sf::RenderWindow& win);
    void draw_end_game_screen(sf::RenderWindow& win);

    sf::Vector2f return_pixels(int col, int row) const;
    Board::Tile return_tile(const sf::Vector2f& coords) const;
    Board::Tile return_tile(int x, int y) const;

    void drag_red_player(sf::Event& event);
    void drag_blue_player(sf::Event& event);
    void change_init_turn(sf::Event& event);
    void set_unit(sf::Event& event);
    void remove_unit();
    void set_active_unit(sf::Event& event);
    void set_button_highlights(int mouse_x, int mouse_y);
    void handle_initialization(sf::Event& event);
    void set_hovering_tile(int mouse_x, int mouse_y);
    void change_player_turn();
    void move_active_unit(sf::Event& event);
    bool is_out_of_the_board(int x, int y);
    void set_buttons_pressed();

    bool check_if_viable(Board::Tile from, int to_x, int to_y);
    void highlight_regular_moves(sf::RenderWindow& win);
    void highlight_scout_moves(sf::RenderWindow& win);
    bool highlight_tile(sf::RenderWindow& win, int to_x, int to_y);

    void TEST_SET_RANDOM_UNITS();

public:
    GameView(Player& pA, Player& pB);
    void draw(sf::RenderWindow& win);
    sf::Vector2f get_window_size() { return window_size; };
    void handle_events(sf::Event& event);
};