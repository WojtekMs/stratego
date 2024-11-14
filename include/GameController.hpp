#pragma once

#include <SFML/Graphics.hpp>

#include "Board.hpp"

struct mouse_data {
    float mouse_x;
    float mouse_y;
    float mouse_object_offset_x;
    float mouse_object_offset_y;
};

enum class Turn;
class Player;
class GameView;

class GameController {
    Player& playerA;
    Player& playerB;
    GameView& game_view;
    Player* current_player;
    Player* other_player;
    std::shared_ptr<Unit> attacker;
    std::shared_ptr<Unit> attacked;
    sf::Clock clock;
    sf::Time total_time_unit_attacked;

    std::string victorious_player_name;
    Turn current_player_turn;
    mouse_data m_data;
    size_t TILE_SIZE;
    size_t selected_unit_idx;

    bool dragging;
    bool board_a_initialized;
    bool board_b_initialized;
    bool is_active_unit;
    bool unit_moved_this_round;
    bool end_turn_button_pressed;
    bool turn_approved;
    bool unit_attacked;
    bool remove_button_pressed;
    bool done_button_pressed;
    bool randomize_button_pressed;
    bool end_game_info_box_button_pressed;
    bool game_finished;
    bool clock_started;

    Tile active_unit;
    Tile attacking_unit;
    Tile attacked_unit;

    void TEST_SET_RANDOM_UNITS();
    sf::Vector2f return_pixels(int col, int row) const;
    Tile return_tile(const sf::Vector2f& coords) const;
    Tile return_tile(int x, int y) const;

    void drag_red_player(sf::Event& event);
    void drag_blue_player(sf::Event& event);
    void change_init_turn(sf::Event& event);
    void set_unit(sf::Event& event);
    void remove_unit();
    void randomize_units();
    void set_active_unit(sf::Event& event);
    void change_player_turn();
    void move_active_unit(sf::Event& event);
    bool is_out_of_the_board(int x, int y);
    void set_buttons_pressed();
    void resolve_unit_conflict(const Tile& attacked_unit);

public:
    GameController(Player& pA, Player& pB, GameView& g_view);
    bool get_dragging() { return dragging; };
    bool get_board_a_initialized() { return board_a_initialized; };
    bool get_board_b_initialized() { return board_b_initialized; };
    bool get_is_active_unit() { return is_active_unit; };
    bool get_unit_moved_this_round() { return unit_moved_this_round; };
    bool get_end_turn_button_pressed() { return end_turn_button_pressed; };
    bool get_turn_approved() { return turn_approved; };
    bool get_unit_attacked() const { return unit_attacked; };
    bool get_remove_button_pressed() { return remove_button_pressed; };
    bool get_done_button_pressed() { return done_button_pressed; };
    bool get_randomize_button_pressed() { return randomize_button_pressed; };
    bool get_end_game_info_box_button_pressed() { return end_game_info_box_button_pressed; };
    bool get_game_finished() { return game_finished; };
    bool both_boards_set() const;
    std::shared_ptr<Unit> get_attacker() const { return attacker; };
    std::shared_ptr<Unit> get_attacked() const { return attacked; };
    std::string get_victorious_player_name() const { return victorious_player_name; };
    const Tile& get_active_unit() const { return active_unit; };
    int get_selected_init_unit_idx() const { return selected_unit_idx; };
    const mouse_data& get_mouse_data() const { return m_data; };
    Player* get_current_player() const { return current_player; };
    Player* get_other_player() const { return other_player; };
    void update_unit_attacked(const sf::Time& time_past);

    void handle_events(sf::Event& event);
};