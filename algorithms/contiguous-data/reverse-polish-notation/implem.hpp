#include <stack>
#include <string>

// Algorithm to be tested

template <class It> int eval(It beg, It end)
{// take a valid expression
  std::stack<int> data;
  for ( ; beg != end ; ++beg)
  {
    std::string const& s = *beg;
    bool is_op = s.size() == 1 && (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/');
    if (is_op)
    {
      int d2 = data.top();
      data.pop();
      int d1 = data.top();
      data.pop();
      switch (s[0])
      {
        case '+':
          data.push(d1+d2);
          break;
        case '-':
          data.push(d1-d2);
          break;
        case '*':
          data.push(d1*d2);
          break;
        case '/':
          data.push(d1/d2);
          break;
      }
    }
    else
    {
      data.push(std::stoi(s));
    }
  }
  return data.top();
}
