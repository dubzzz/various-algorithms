#pragma once
#include <algorithm>
#include <cstddef>
#include <iterator>

#include "maze.hpp"

class Array2D final
{
  char** _data;
  std::size_t _width;
  std::size_t _height;

public:
  Array2D(Dimension const& dim) : _data(new char*[dim.height]), _width(dim.width), _height(dim.height)
  {
    std::generate(_data, std::next(_data, _height)
        , [width=_width]() { return new char[width]; });
  }
  Array2D(Array2D&&) = default;
  Array2D(Array2D const&) = delete;
  Array2D& operator=(Array2D&&) = delete;
  Array2D& operator=(Array2D const&) = delete;
  ~Array2D()
  {
    std::for_each(_data, std::next(_data, _height)
        , [](char* line) { delete line; });
    delete _data;
  }
  
  class const_iterator : public std::iterator<std::forward_iterator_tag, char>
  {
    char** _cur_line;
    char** _end_line;
    char* _cur_column;
    char* _end_column;
    std::size_t _width;
    
    const_iterator(char** sline, char** eline, char* scol, char* ecol, std::size_t width)
        : _cur_line(sline)
        , _end_line(eline)
        , _cur_column(scol)
        , _end_column(ecol)
        , _width(width)
    {}
  
  public:
    static const_iterator begin(Array2D const& array)
    {
      return const_iterator(array._data, std::next(array._data, array._height)
          , *array._data, std::next(*array._data, array._width)
          , array._width);
    }
    static const_iterator end(Array2D const& array)
    {
      return const_iterator(std::next(array._data, array._height), std::next(array._data, array._height)
          , std::next(*std::next(array._data, array._height -1), array._width), std::next(*array._data, array._width)
          , array._width);
    }
    const_iterator& operator++()
    {
      ++_cur_column;
      if (_cur_column == _end_column)
      {
        ++_cur_line;
        if (_cur_line != _end_line)
        {
          _cur_column = *_cur_line;
          _end_column = std::next(_cur_column, _width);
        }
      }
      return *this;
    }
    const_iterator operator++(int)
    {
      const_iterator ret = *this;
      ++(*this);
      return ret;
    }
    bool operator==(const_iterator other) const { return _cur_line == other._cur_line && _cur_column == other._cur_column; }
    bool operator!=(const_iterator other) const { return !(*this == other); }
    char const& operator*() const { return *_cur_column; }
  };
  
  char** data() { return _data; }
  char const * const * data() const { return _data; }
  
  const_iterator begin() const { return const_iterator::begin(*this); }
  const_iterator end() const   { return const_iterator::end(*this); }
  
  template <class Ostream> Ostream& print(Ostream& oss) const
  {
    for (std::size_t j {} ; j != _height ; ++j)
    {
      for (std::size_t i {} ; i != _width ; ++i)
      {
        oss << _data[j][i];
      }
      oss << std::endl;
    }
    return oss;
  }
};

