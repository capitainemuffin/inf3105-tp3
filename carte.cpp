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

	this->cases.insert(std::pair<int, Case&>(taille, ucase));
	this->taille++;

}