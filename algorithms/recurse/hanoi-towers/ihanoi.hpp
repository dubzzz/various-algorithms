#pragma once
#include <cstddef>

class IHanoi
{
public:
  virtual ~IHanoi() {}
  
  virtual std::size_t height_of(const std::size_t tower_id) const = 0;
  virtual unsigned int head_of(const std::size_t tower_id) const = 0;
  virtual void move(const std::size_t dest, const std::size_t from) = 0;
};

