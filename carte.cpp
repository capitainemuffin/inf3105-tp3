#include "carte.h"

Carte::Carte(int longueur, int largeur):
longueur(longueur),
largeur(largeur),
taille(0) {}


Carte::Case::Case(char type, int elevation, bool tresor):
elevation(elevation),
tresor(false)

{

	switch(type){

		case 'N' : {
			this->type = Carte::Terrain::Plaine;
			break;
		}
		case 'E' : {
			this->type = Carte::Terrain::Eau;
			break;
		}
		case 'F' : {
			this->type = Carte::Terrain::Foret;
			break;
		}
		case 'R' : {
			this->type = Carte::Terrain::Route;
			break;
		}
		case 'P' : {
			this->type = Carte::Terrain::Porte;
		}
	}

}

void Carte::ajouter_case(Carte::Case& ucase){

	this->cases[++taille] = ucase;


	// Si pas premier de colonne
	if(this->taille % this->largeur != 1){

		ucase.ajouter_voisin(this->cases[this->taille -1]);
	}

	// Si dernier de colonne 
	if(this->taille % this->largeur == 0){

		// prendre la première case de la ligne et lui ajouter ce voisin
		this->cases[this->taille - this->largeur + 1].ajouter_voisin(ucase);

	}

	// Si pas première ligne
	if(this->taille > this->largeur){

		//ajouter voisin de haut
		ucase.ajouter_voisin(this->cases[this->taille - this->largeur]);

		// Si pas premier de colonne
		if(this->taille % this->largeur != 1){

			// voisin haut/gauche
			ucase.ajouter_voisin(this->cases[this->taille - this->largeur -1]);
		}

		// Si pas dernier de colonne 
		if(this->taille % this->largeur != 0){

			// voisin haut/droit
			ucase.ajouter_voisin(this->cases[this->taille - this->largeur + 1]);

		}

	}




	// voisin haut


	//vérifier si dernière colonne, si oui connecter avec la case de gauche et de droite

	if
	//verifier si voisin 

	//vérifier si d



}