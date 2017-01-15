#pragma once
#include <cstddef>
#include <array>

#ifdef DEBUG
  #include <ostream>
  #include <iostream>
#endif

enum class Where { Less, Equal, More };

#ifdef DEBUG
  std::ostream& operator<<(std::ostream& os, Where w)
  {
    switch (w)
    {
      case Where::Less: return (os << "less");
      case Where::More: return (os << "more");
      default: return (os << "equal");
    }
  }
#endif

template <std::size_t DIM>
class ISpace
{
public:
  virtual ~ISpace() {}
  virtual std::array<std::size_t, DIM> const& dimensions() const = 0;
  virtual std::array<Where, DIM> guess(std::array<std::size_t, DIM> const& choice) = 0;
  virtual bool is_solution(std::array<std::size_t, DIM> const& choice) const = 0;
};

