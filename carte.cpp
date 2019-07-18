#include "carte.h"
#include <iostream>

Carte::Carte(int longueur, int largeur): taille(0), porte_presente(false) {

	if(longueur < 1 || largeur < 1) {
		std::cerr << "La longueur et la largeur de la matrice doivent êtres plus grand que 1." << std::endl;
		exit(-1);
	}

	this->longueur = longueur;
	this->largeur = largeur;
	this->capacite = longueur * largeur;

}


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

void Carte::ajouter_case(Carte::Case* ucase){

	if(ucase->type == Carte::Terrain::Porte){

		if(this->porte_presente){
			std::cerr << "Il ne peut y avoir plus d'une porte dans la matrice";
			std::cerr << std::endl;
			exit(-2);
		}

		this->porte_presente = true;

	}

	this->cases[++taille] = &ucase;

	// Si pas premier de colonne
	if(this->taille % this->largeur != 1){

		ucase->ajouter_voisin(this->cases[this->taille -1]);
	}

	// Si dernier de colonne 
	if(this->taille % this->largeur == 0){

		// prendre la première case de la ligne et lui ajouter ce voisin
		this->cases[this->taille - this->largeur + 1].ajouter_voisin(&ucase);

	}

	// Si pas première ligne
	if(this->taille > this->largeur){

		//ajouter voisin de haut
		ucase->ajouter_voisin(this->cases[this->taille - this->largeur]);

		// Si pas premier de colonne
		if(this->taille % this->largeur != 1){

			// voisin haut/gauche
			ucase->ajouter_voisin(this->cases[this->taille - this->largeur -1]);
		}

		// Si pas dernier de colonne 
		if(this->taille % this->largeur != 0){

			// voisin haut/droit
			ucase->ajouter_voisin(this->cases[this->taille - this->largeur + 1]);

		}

	}

}

void Carte::ajouter_tresor(int x, int y){

	int position = this->largeur * x + y;

	if(position > this->capacite) {
		std::cerr << "Coordonées de trésor invalide." << std::endl;
		exit(-3);
	}

	if()

	this->cases[position].tresor = true;
}

void Carte::Case::ajouter_voisin(Carte::Case& ucase){

	double distance;


}
