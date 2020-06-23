#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "AttackInfoBox.hpp"
#include "BigButton.hpp"
#include "Board.hpp"
#include "Box.hpp"
#include "Button.hpp"
#include "GameController.hpp"

class Player;
enum class TURN;

class GameView {
    Player& playerA;
    Player& playerB;
    Player* current_player;
    Player* other_player;
    TURN current_player_turn;

    const std::string board_textures_path;
    const std::string pieces_textures_path;

    int TILE_SIZE;
    int X_ADDITIONAL_SPACE;
    sf::Vector2f window_size;
    sf::Vector2f sprite_initial_position;

    bool clock_started;

    sf::Sprite board_border;
    sf::Sprite grass_light;
    sf::Sprite grass_dark;
    std::array<sf::Sprite, 8> obstacle_sprites;
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
    std::array<sf::Texture, 8> obstacle_textures;
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
    Button randomize_button;
    Button remove_button;
    Button end_turn_button;
    Box info_box;
    AttackInfoBox attack_info_box;
    Box end_game_info_box;

    void load_obstacle_textures();
    void load_grass_textures();
    void load_board_border_texture();
    void load_red_units_textures();
    void load_blue_units_textures();
    void load_highlight_textures();
    void load_font();
    void set_obstacle_sprites();
    void set_red_units_sprites();
    void set_blue_units_sprites();
    void set_highlight_sprites();

    sf::Vector2f return_pixels(int col, int row) const;
    Board::Tile return_tile(const sf::Vector2f& coords) const;
    Board::Tile return_tile(int x, int y) const;

    bool check_if_viable(Board::Tile from, int to_x, int to_y);
    void highlight_regular_moves(sf::RenderWindow& win, const Board::Tile& active_unit);
    void highlight_scout_moves(sf::RenderWindow& win, const Board::Tile& active_unit);
    bool highlight_tile(sf::RenderWindow& win, const Board::Tile& active_unit, int to_x, int to_y);
    void draw_red_init_units(sf::RenderWindow& win, bool is_dragging, int selected_unit_idx, const mouse_data& m_data);
    void draw_blue_init_units(sf::RenderWindow& win, bool is_dragging, int selected_unit_idx, const mouse_data& m_data);

public:
    GameView(Player& pA, Player& pB);
    void update_players(Player* current, Player* other);
    void set_button_highlights(int mouse_x, int mouse_y);

    sf::Vector2f get_window_size() { return window_size; };
    const std::array<sf::Sprite, 12>& get_red_units_sprites() const { return red_units_sprites; };
    const std::array<sf::Sprite, 12>& get_blue_units_sprites() const { return blue_units_sprites; };
    const Button& get_done_button() const { return done_button; };
    const Button& get_randomize_button() const { return randomize_button; };
    const Button& get_remove_button() const { return remove_button; };
    const Button& get_end_turn_button() const { return end_turn_button; };
    const Box& get_info_box() const { return info_box; };
    const Box& get_end_game_info_box() const { return end_game_info_box; };
    const AttackInfoBox& get_attack_info_box() const { return attack_info_box; };

    void draw_board_border(sf::RenderWindow& win);
    void draw_grass(sf::RenderWindow& win);
    void draw_obstacles(sf::RenderWindow& win);
    void draw_units_for_init(sf::RenderWindow& win, bool is_dragging, int selected_unit_idx, const mouse_data& m_data);
    void draw_sprite(sf::RenderWindow& win, int idx, int sprite_pos_x, int sprite_pos_y);
    void draw_done_button(sf::RenderWindow& win);
    void draw_randomize_button(sf::RenderWindow& win);
    void draw_remove_button(sf::RenderWindow& win);
    void draw_end_turn_button(sf::RenderWindow& win);
    void draw_possible_moves_for_active_unit(sf::RenderWindow& win, const Board::Tile& active_unit);
    void draw_info_box(sf::RenderWindow& win);
    void draw_attack_info_box(sf::RenderWindow& win, const std::shared_ptr<Unit>& attacker, const std::shared_ptr<Unit>& attacked);
    void draw_units(sf::RenderWindow& win);
    void draw_unit_highlight(sf::RenderWindow& win, const Board::Tile& active_unit);
    void draw_end_game_screen(sf::RenderWindow& win, const std::string& victorious_name);
};