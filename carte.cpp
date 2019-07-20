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
			break;
		}

		default : {
			std::cout << "Type de terrain incorrect." << std::endl;
			exit(-10);
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

	this->cases[++taille] = ucase;

	// Si pas premier de colonne, connecter avec voisin de gauche
	if(this->taille % this->largeur != 1){

		ucase->ajouter_voisin_orthogonal(this->cases[this->taille -1]);
		this->cases[this->taille-1]->ajouter_voisin_orthogonal(ucase);
	}

	// Si dernier de colonne 
	if(this->taille % this->largeur == 0){

		// prendre la première case de la ligne et lui ajouter ce voisin
		ucase->ajouter_voisin_orthogonal(this->cases[this->taille - this->largeur + 1]);
		this->cases[this->taille - this->largeur + 1]->ajouter_voisin_orthogonal(ucase);

	}

	// Si pas première ligne
	if(this->taille > this->largeur){

		//ajouter voisin de haut
		ucase->ajouter_voisin_orthogonal(this->cases[this->taille - this->largeur]);
		this->cases[this->taille - this->largeur]->ajouter_voisin_orthogonal(ucase);

		// Si pas premier de colonne
		if(this->taille % this->largeur != 1){

			// voisin haut/gauche
			ucase->ajouter_voisin_diagonal(this->cases[this->taille - this->largeur -1]);
		}

		// Si pas dernier de colonne 
		if(this->taille % this->largeur != 0){

			// voisin haut/droit
			ucase->ajouter_voisin_diagonal(this->cases[this->taille - this->largeur + 1]);

		}

	}

}

void Carte::ajouter_tresor(int position){

	if(position > this->capacite) {
		std::cerr << "Coordonées de trésor invalides." << std::endl;
		exit(-3);
	}

	if(this->cases[position]->type == Carte::Terrain::Eau){
		std::cerr << "Un trésor ne peut pas être dans l'eau." << std::endl;
		exit(-4);
	}

	this->cases[position]->tresor = true;
}

void Carte::Case::ajouter_voisin_orthogonal(Carte::Case* ucase){

	double distance = 0;

	// Vérifier que c'est pas de l'eau et que élevation est acceptbable
	if(this->type != Carte::Terrain::Eau 
		&& ucase->type != Carte::Terrain::Eau
		&& this->elevation - ucase->elevation >= -1
		&& this->elevation - ucase->elevation <= 1){


		switch (ucase->type){

			case Carte::Terrain::Foret : {
				distance = 2;
				break;
			}

			case Carte::Terrain::Route : {

				if(this->type == Carte::Terrain::Route) distance = 0.5;
				break;
			}

			default : {
				distance = 1;
				break;
			}
		}

		if(this->elevation - ucase->elevation < 0) distance *= 2; 

		this->voisins.insert(std::make_pair(ucase, distance));

	}

}

void Carte::Case::ajouter_voisin_diagonal(Carte::Case* ucase){

	double distance = 0;

	// Vérifier que c'est pas de l'eau et que élevation est acceptbable
	if(this->type != Carte::Terrain::Eau 
		&& ucase->type != Carte::Terrain::Eau
		&& this->elevation - ucase->elevation >= -1
		&& this->elevation - ucase->elevation <= 1){


		switch (ucase->type){

			case Carte::Terrain::Foret : {
				distance = 2.8;
				break;
			}

			case Carte::Terrain::Route : {

				if(this->type == Carte::Terrain::Route) distance = 0.7;
				break;
			}

			default : {
				distance = 1.4;
				break;
			}
		}

		if(this->elevation - ucase->elevation < 0) distance *= 2; 

		this->voisins.insert(std::make_pair(ucase, distance));

	}

}


