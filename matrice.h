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
		void ajouter(float n);
		void soustraire(float n);
		void multiplier(const Matrice& matrice);
		void multiplier(float scalaire);
		void diviser(const Matrice& matrice);
		void diviser(float scalaire);
		size_t getLargeur(void) const;
		size_t getHauteur(void) const;
		void setValeur(size_t ligne, size_t colonne, float valeur);
		float getValeur(int ligne, int colonne) const;
		std::vector<std::vector<float> > getValeurs(void) const;
		std::vector<float> operator[] (size_t x) const;
		Matrice operator+(const Matrice& matrice) const;
		Matrice operator+(float n) const;
		Matrice operator-(float n) const;
		Matrice operator*(const Matrice& matrice) const;
		Matrice operator*(float scalaire) const;
		Matrice operator/(const Matrice& matrice) const;
		Matrice operator/(float scalaire) const;
		void resize(size_t nouvelleLargeur, size_t nouvelleHauteur);
};

#endif // MATRICE_H_INCLUDED
