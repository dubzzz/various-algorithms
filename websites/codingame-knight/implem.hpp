#include <algorithm>
#include <array>

#include "ispace.hpp"

// Algorithm to be tested

template <std::size_t DIM> std::array<std::size_t, DIM> locate_in_space(ISpace<DIM>& space)
{
  std::array<std::size_t, DIM> min_ext;
  std::fill(std::begin(min_ext), std::end(min_ext), std::size_t());
  std::array<std::size_t, DIM> max_ext = space.dimensions();
  
  while (true)
  {
    // Analyze remaining possibilities (break if unique solution)

    bool min_is_solution { true };
    for (std::size_t i = 0 ; i != DIM ; ++i)
    {
      if (min_ext[i] +1 != max_ext[i])
      {
        min_is_solution = false;
        break;
      }
    }
    if (min_is_solution)
    {
      break;
    }
    
    // Build a choice/guess
    
    std::array<std::size_t, DIM> choice;
    for (std::size_t i = 0 ; i != DIM ; ++i)
    {
      choice[i] = min_ext[i] + (max_ext[i] - min_ext[i])/2;
    }

    // Try with the choice
    std::array<Where, DIM> hint = space.guess(choice);
    for (std::size_t i = 0 ; i != DIM ; ++i)
    {
      switch (hint[i])
      {
        case Where::Equal:
          min_ext[i] = choice[i];
          max_ext[i] = choice[i] +1;
          break;
        case Where::Less:
          max_ext[i] = choice[i];
          break;
        case Where::More:
          min_ext[i] = choice[i] +1;
          break;
      }
    }
  }

  return min_ext;
}

