unsigned most_significant_position(unsigned);

int main(int argc, char **argv)
{
  unsigned out {};
  constexpr unsigned num_runs = 1e8;
  for (unsigned run_id {} ; run_id != num_runs ; ++run_id)
  {
    out += most_significant_position(run_id);
  }
  bool success = out == unsigned(5);
  return out;
}

