#include <iostream>
#include "matrice.h"

int main()
{
    Matrice a(3, 4);
    Matrice b(4, 2);
    try
    {
		a.setValeur(0, 0, -3.0);
		a.setValeur(0, 1, 3.0);
		a.setValeur(0, 2, 0.0);
		a.setValeur(0, 3, -10.0);

		a.setValeur(1, 0, 7.0);
		a.setValeur(1, 1, -6.0);
		a.setValeur(1, 2, 9.0);
		a.setValeur(1, 3, 2.0);

		a.setValeur(2, 0, -9.0);
		a.setValeur(2, 1, 9.0);
		a.setValeur(2, 2, 3.0);
		a.setValeur(2, 3, -8.0);

		b.setValeur(0, 0, -8.0);
		b.setValeur(0, 1, -5.0);

		b.setValeur(1, 0, -4.0);
		b.setValeur(1, 1, -7.0);

		b.setValeur(2, 0, 11.0);
		b.setValeur(2, 1, -8.0);

		b.setValeur(3, 0, 11.0);
		b.setValeur(3, 1, -9.0);

    	a.afficher();
    	std::cout << std::endl;

    	b.afficher();
    	std::cout << std::endl;

    	Matrice c = a * b;
    	c.afficher();
    }
    catch(std::string erreur)
    {
    	std::cout << erreur << std::endl;
    }
    return 0;
}
