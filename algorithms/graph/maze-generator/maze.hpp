#pragma once
#include <cstddef>

enum class MazeElement { Wall, Road, Start, End, Undefined };

static char to_char(MazeElement elt)
{
  switch (elt)
  {
    case MazeElement::Wall:  return '#';
    case MazeElement::Road:  return ' ';
    case MazeElement::Start: return 'S';
    case MazeElement::End:   return 'E';
    default:                 return '?';
  }
}

struct Point
{
  std::size_t x;
  std::size_t y;
  
  Point() = default;
  Point(std::size_t x, std::size_t y) : x(x), y(y) {}
  Point(Point&&) = default;
  Point(Point const&) = default;
  Point& operator=(Point&&) = default;
  Point& operator=(Point const&) = default;
  bool operator==(Point const& other) const { return x == other.x && y == other.y; }
  bool operator!=(Point const& other) const { return !(*this == other); }
};

struct Dimension
{
  std::size_t width;
  std::size_t height;
  
  Dimension() = default;
  Dimension(std::size_t width, std::size_t height) : width(width), height(height) {}
  Dimension(Dimension&&) = default;
  Dimension(Dimension const&) = default;
  Dimension& operator=(Dimension&&) = default;
  Dimension& operator=(Dimension const&) = default;
};

