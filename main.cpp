#include <iostream>
#include "matrix.h"

int main()
{
    Matrix a(3, 4);
    Matrix b(4, 2);
    try
    {
		a.setValue(0, 0, -3.0);
		a.setValue(0, 1, 3.0);
		a.setValue(0, 2, 0.0);
		a.setValue(0, 3, -10.0);

		a.setValue(1, 0, 7.0);
		a.setValue(1, 1, -6.0);
		a.setValue(1, 2, 9.0);
		a.setValue(1, 3, 2.0);

		a.setValue(2, 0, -9.0);
		a.setValue(2, 1, 9.0);
		a.setValue(2, 2, 3.0);
		a.setValue(2, 3, -8.0);

		b.setValue(0, 0, -8.0);
		b.setValue(0, 1, -5.0);

		b.setValue(1, 0, -4.0);
		b.setValue(1, 1, -7.0);

		b.setValue(2, 0, 11.0);
		b.setValue(2, 1, -8.0);

		b.setValue(3, 0, 11.0);
		b.setValue(3, 1, -9.0);

    	a.display();
    	std::cout << std::endl;

    	b.display();
    	std::cout << std::endl;

    	Matrix c = a / 2;
    	c.display();
    }
    catch(std::string error)
    {
    	std::cout << error << std::endl;
    }
    return 0;
}
