#include <iostream>
#include "matrix.h"

int main()
{
    Matrix a(3, 2);
    Matrix b(2, 4);
    try
    {
      a.setValue(0, 0, 6.0);
      a.setValue(0, 1, -1);

      a.setValue(1, 0, -4);
      a.setValue(1, 1, 0);

      a.setValue(2, 0, 1);
      a.setValue(2, 1, -3);

      b.setValue(0, 0, -2.0);
      b.setValue(0, 1, 2.0);
      b.setValue(0, 2, -1.0);
      b.setValue(0, 3, 3.0);

      b.setValue(1, 0, 4.0);
      b.setValue(1, 1, 0);
      b.setValue(1, 2, 5.0);
      b.setValue(1, 3, 6.0);

      a.display();
      std::cout << std::endl;

      b.display();
      std::cout << std::endl;

      Matrix c = a * b;
      c.display();
    }
    catch(std::string error)
    {
      std::cout << error << std::endl;
    }
    return 0;
}
