#pragma once

#include <array>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Array2D.h"
#include "Tile.hpp"
#include "Turn.hpp"
#include "unit/Unit.hpp"

enum class State {
  Uninitialized,
  Initialized,
  Full,
};

constexpr int MAX_UNIT_COUNT = 40;

class Board {
private:
  int height{};
  int width{};
  State current_state{};
  int unit_count{};
  Array2D<std::optional<Unit>> units;
  std::array<Tile, 8> obstacles;

  void set_default_units();
  void set_obstacles();
  Tile point_reflection(int col, int row);
  bool out_of_range(int col, int row) const;
  void set_state(State state);
  bool is_unit_set(Tile tile) const;
  void unset_unit(Tile tile);

public:
  Board();
  bool set_unit(int col, int row, Turn player, int choice);
  void remove_unit(int col, int row);
  void reverse_remove_unit(int col, int row);
  std::string get_tile_info(int col, int row, Turn player) const;
  std::string get_tile_info(const Tile &tile, Turn player) const;
  int get_height() const { return height; };
  int get_width() const { return width; };
  const std::optional<Unit> &get_unit(int col, int row) const;
  const std::optional<Unit> &get_unit(const Tile &chosen_unit) const;
  bool can_move(const Tile &from, const Tile &to) const;
  bool move_unit(const Tile &from, const Tile &to);
  void reverse_move_unit(const Tile &from, const Tile &to);
  void update(const Board &other_board);
  Board &operator=(const Board &rhs);
  State get_state() const { return current_state; };
  int get_max_unit_count(int idx) const;
};