#ifndef MATRICE_H_INCLUDED
#define MATRICE_H_INCLUDED

#include <vector>

class Matrice
{
	private:
		size_t largeur;
		size_t hauteur;
		std::vector<std::vector<float> > valeurs;

	public:
		Matrice();
		Matrice(size_t hauteur, size_t largeur);
		Matrice(const Matrice& matriceACopier);
		~Matrice();
		void afficher();
		void ajouter(const Matrice& matrice);
		void multiplier(const Matrice& matrice);
		float sommeDesProduits(size_t ligneDeA, size_t colonneDeB, const Matrice& a, const Matrice& b);
		size_t getLargeur(void) const;
		size_t getHauteur(void) const;
		void setValeur(size_t ligne, size_t colonne, float valeur);
		float getValeur(int ligne, int colonne) const;
		std::vector<std::vector<float> > getValeurs(void) const;
		std::vector<float> Matrice::operator[] (size_t x) const;
		Matrice operator+(const Matrice& matrice) const;
		Matrice operator*(const Matrice& matrice) const;
		void resize(size_t nouvelleLargeur, size_t nouvelleHauteur);
};

#endif // MATRICE_H_INCLUDED
