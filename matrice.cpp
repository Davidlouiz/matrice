#include "matrice.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

Matrice::Matrice()
{
	this->largeur = 0;
	this->hauteur = 0;
}

Matrice::Matrice(size_t hauteur, size_t largeur)
{
	this->largeur = largeur;
	this->hauteur = hauteur;
	for (size_t i = 0; i < hauteur; i++)
	{
		std::vector<float> ligne;
		for (size_t j = 0; j < largeur; j++)
		{
			ligne.push_back(0.0);
		}
		this->valeurs.push_back(ligne);
	}
}

Matrice::Matrice(const Matrice& matriceACopier)
{
	this->largeur = matriceACopier.getLargeur();
	this->hauteur = matriceACopier.getHauteur();
	this->valeurs = matriceACopier.getValeurs();
}

Matrice::~Matrice()
{

}

void Matrice::afficher()
{
	std::cout << "---" << std::endl;

	for(size_t ligne = 0; ligne < this->hauteur; ligne++)
	{
		for(size_t colonne = 0; colonne < this->largeur; colonne++)
		{
			std::cout << this->valeurs[ligne][colonne] << "\t";
		}
		std::cout << std::endl;
	}
}

void Matrice::ajouter(const Matrice& matrice)
{
	size_t nouvelleLargeur = std::min(this->largeur, matrice.getLargeur());
	size_t nouvelleHauteur = std::min(this->hauteur, matrice.getHauteur());

	this->valeurs.resize(nouvelleHauteur);

	for (size_t i = 0; i < this->valeurs.size(); i++)
	{
		this->valeurs[i].resize(nouvelleLargeur);
	}

	for (size_t ligne = 0; ligne < nouvelleHauteur; ligne++)
	{
		for (size_t colonne = 0; colonne < nouvelleLargeur; colonne++)
		{
			this->valeurs[ligne][colonne] += matrice.getValeur(ligne, colonne);
		}
	}

	this->largeur = nouvelleLargeur;
	this->hauteur = nouvelleHauteur;
}

void Matrice::ajouter(float n)
{
	for (size_t ligne = 0; ligne < this->hauteur; ligne++)
	{
		for (size_t colonne = 0; colonne < this->largeur; colonne++)
		{
			this->valeurs[ligne][colonne] += n;
		}
	}
}

void Matrice::soustraire(float n)
{
	this->ajouter(-n);
}

void Matrice::multiplier(const Matrice& matrice)
{
	Matrice a = *this;
	Matrice b = matrice;

	if (a.getLargeur() != b.getHauteur())
	{
		throw std::string("La hauteur de la matrice en parametre ne correspond pas a largeur de cette matrice");
	}

	size_t nouvelleLargeur = b.getLargeur();
	size_t nouvelleHauteur = a.getHauteur();

	Matrice c; // Ici on se permet de creer un objet, bien que ce soit inutil car ca clarifie vraiment le code (enfin c'est discutable)
	c.resize(nouvelleLargeur, nouvelleHauteur);

	for (size_t colonne = 0; colonne < nouvelleLargeur; colonne++)
	{
		for (size_t ligne = 0; ligne < nouvelleHauteur; ligne++)
		{
			float somme = 0.0;

			for (size_t i = 0; i < a.getLargeur(); i++)
			{
				somme += a[ligne][i] * b[i][colonne];
			}
			c.setValeur(ligne, colonne, somme);
		}
	}

	*this = c;
}

void Matrice::multiplier(float n)
{
	for (size_t ligne = 0; ligne < this->hauteur; ligne++)
	{
		for (size_t colonne = 0; colonne < this->largeur; colonne++)
		{
			this->setValeur(ligne, colonne, this->valeurs[ligne][colonne] * n);
		}
	}
}

void Matrice::diviser(float n)
{
	// Ici on affecte directement l'objet donc inutile de creer une copie, modifier la copie et reaffecter tout à this
	this->multiplier(1/n);
}

void Matrice::diviser(const Matrice& matrice)
{
	Matrice a = *this;
	Matrice b = matrice;

	if (a.getLargeur() != b.getHauteur())
	{
		throw std::string("La hauteur de la matrice en parametre ne correspond pas a largeur de cette matrice");
	}

	size_t nouvelleLargeur = b.getLargeur();
	size_t nouvelleHauteur = a.getHauteur();

	Matrice c; // Ici on se permet de creer un objet, bien que ce soit inutil car ca clarifie vraiment le code (enfin c'est discutable)
	c.resize(nouvelleLargeur, nouvelleHauteur);

	for (size_t colonne = 0; colonne < nouvelleLargeur; colonne++)
	{
		for (size_t ligne = 0; ligne < nouvelleHauteur; ligne++)
		{
			float somme = 0.0;

			for (size_t i = 0; i < a.getLargeur(); i++)
			{
				somme += a[ligne][i] / b[i][colonne];
			}
			c.setValeur(ligne, colonne, somme);
		}
	}

	*this = c;
}

void Matrice::setValeur(size_t ligne, size_t colonne, float valeur)
{
	if (colonne >= this->largeur || ligne >= this->hauteur)
	{
		std::stringstream flux;
		flux << "La case [" << ligne << "," << colonne << "] n'existe pas" << std::endl << "Largeur : " << this->largeur << std::endl << "Hauteur : " << this->hauteur << std::endl;
		throw flux.str();
	}
	this->valeurs[ligne][colonne] = valeur;
}

size_t Matrice::getLargeur(void) const
{
	return this->largeur;
}

size_t Matrice::getHauteur(void) const
{
	return this->hauteur;
}

float Matrice::getValeur(int ligne, int colonne) const
{
	return this->valeurs[ligne][colonne];
}

std::vector<std::vector<float> > Matrice::getValeurs(void) const
{
	return this->valeurs;
}

std::vector<float> Matrice::operator[] (size_t ligne) const
{
	return this->valeurs[ligne];
}

Matrice Matrice::operator+(const Matrice& matrice) const
{
	Matrice resultat(*this);
	resultat.ajouter(matrice);
	return resultat;
}

Matrice Matrice::operator+(float n) const
{
	Matrice resultat(*this);
	resultat.ajouter(n);
	return resultat;
}

Matrice Matrice::operator-(float n) const
{
	Matrice resultat(*this);
	resultat.soustraire(n);
	return resultat;
}

Matrice Matrice::operator*(const Matrice& matrice) const
{
	Matrice resultat(*this);
	resultat.multiplier(matrice);
	return resultat;
}

Matrice Matrice::operator*(float n) const
{
	Matrice resultat(*this);
	resultat.multiplier(n);
	return resultat;
}

Matrice Matrice::operator/(const Matrice& matrice) const
{
	Matrice resultat(*this);
	resultat.diviser(matrice);
	return resultat;
}

Matrice Matrice::operator/(float n) const
{
	Matrice resultat(*this);
	resultat.diviser(n);
	return resultat; // Quand on retourne le resultat, il faut creer un nouvel objet
}

void Matrice::resize(size_t nouvelleLargeur, size_t nouvelleHauteur)
{
	this->valeurs.resize(nouvelleHauteur);
	for (size_t i = 0; i < this->valeurs.size(); i++)
	{
		this->valeurs[i].resize(nouvelleLargeur);
	}
	this->largeur = nouvelleLargeur;
	this->hauteur = nouvelleHauteur;
}
