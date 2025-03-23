#pragma once

class Tile {
public:
  int x{};
  int y{};
  explicit Tile(int col = 0, int row = 0) {
    x = col;
    y = row;
  };
  bool operator==(const Tile &rhs) const { return x == rhs.x && y == rhs.y; };
  void set_cords(const Tile &rhs) {
    x = rhs.x;
    y = rhs.y;
  };
  void set_cords(int Ax, int Ay) {
    x = Ax;
    y = Ay;
  };
};