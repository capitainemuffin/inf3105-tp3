#include "carte.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
Carte::Carte(int base, int hauteur): taille(0), porte(nullptr) {

	if(base < 1 || hauteur < 1) {
		std::cerr << "La longueur et la largeur de la matrice doivent êtres plus grand que 1." << std::endl;
		exit(-1);
	}

	this->base = base;
	this->hauteur = hauteur;
	this->capacite = base * hauteur;

}

Carte::~Carte(){

	for(int i = 0 ; i < this->taille ; i++) {

		delete this->cases[i];
	}
}


Carte::Case::Case(char type, int elevation):
elevation(elevation),
visite(false)

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
			std::cerr << "Type de terrain incorrect." << std::endl;
			exit(-10);
		}
	}

}

void Carte::ajouter_case(Carte::Case* ucase){

	if(ucase->type == Carte::Terrain::Porte){

		if(porte){
			std::cerr << "Il ne peut y avoir plus d'une porte dans la matrice.";
			std::cerr << std::endl;
			exit(-2);
		}

		this->porte = ucase;

	}

	if(this->taille >= this->capacite) {
			std::cerr << "La taille maximale de la matrice a été dépassée.";
			std::cerr << std::endl;
			exit(-5);

	}

	this->cases[++taille] = ucase;
	ucase->index = this->taille;

	// Si pas premier de colonne, connecter avec voisin de gauche
	if(this->taille % this->base != 1){
		ucase->ajouter_voisin_orthogonal(this->cases[this->taille -1]);
		this->cases[this->taille-1]->ajouter_voisin_orthogonal(ucase);
	}

	// Si dernier de colonne 
	if(this->taille % this->base == 0){

		// prendre la première case de la ligne et lui ajouter ce voisin
		this->cases[this->taille - this->base + 1]->ajouter_voisin_orthogonal(ucase);

	}

	// Si pas première ligne
	if(this->taille > this->base){

		//ajouter voisin de haut
		ucase->ajouter_voisin_orthogonal(this->cases[this->taille - this->base]);
		this->cases[this->taille - this->base]->ajouter_voisin_orthogonal(ucase);

		// Si pas premier de colonne
		if(this->taille % this->base != 1){

			// voisin haut/gauche
			ucase->ajouter_voisin_diagonal(this->cases[this->taille - this->base -1]);
			this->cases[this->taille - this->base -1]->ajouter_voisin_diagonal(ucase);
		}

		// Si pas dernier de colonne 
		if(this->taille % this->base != 0){

			// voisin haut/droit
			ucase->ajouter_voisin_diagonal(this->cases[this->taille - this->base + 1]);
			this->cases[this->taille - this->base +1]->ajouter_voisin_diagonal(ucase);

		}

	}

}

void Carte::ajouter_tresor(int position){

	if(position > this->capacite) {
		std::cerr << "Coordonées de trésor invalides." << std::endl;
		exit(-3);
	}

	if(this->cases[position]->type == Carte::Terrain::Eau){
		std::cerr << "Un trésor ne peut pas être dans l'eau." << std::endl;
		exit(-4);
	}

	auto iter = this->tresors.begin();
	int i = 1;
	while(iter != this->tresors.end()){
		i++;
		++iter;
	}

	this->tresors[this->cases[position]] = "T" + std::to_string(i);
}

void Carte::Case::ajouter_voisin_orthogonal(Carte::Case* ucase){

	double distance = 0;

	// Vérifier que c'est pas de l'eau et que élevation est acceptbable
	if(this->type != Carte::Terrain::Eau 
		&& ucase->type != Carte::Terrain::Eau
		&& this->elevation - ucase->elevation > -2
		&& this->elevation - ucase->elevation < 2){

		switch (ucase->type){

			case Carte::Terrain::Foret : {

				distance = 2;
				break;
			}

			case Carte::Terrain::Route : {

				distance = this->type == Carte::Terrain::Route ? 0.5 : 1;
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

				distance = this->type == Carte::Terrain::Route ? 0.7 : 1.4;
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

void Carte::calculer_chemins(Carte::Case* debut){

	// Ajouter tous les noeuds dans la liste de voisins de la case debut
	for(auto it = this->cases.begin(); it != this->cases.end() ; ++it) {

		if(it->second == debut){

			debut->voisins.insert(std::make_pair(debut, 0));

		} else if(debut->voisins.find(it->second) == debut->voisins.end()){

			debut->voisins.insert(std::make_pair(it->second, std::numeric_limits<double>::max()));

		}

		it->second->visite = false;

	}

	while (true) {

		// trouver le noeud le plus proche non visité
		std::pair<Carte::Case*, double> ucase (nullptr, NULL);
		for(auto it = debut->voisins.begin() ; it != debut->voisins.end() ; ++it) {

			if(!ucase.first || (it->first->visite == false && it->second < ucase.second)){

				ucase = std::make_pair(it->first, it->second);

			}
		}

		//Si aucun noeud à visiter, sortir de la boucle
		if(ucase.first->visite == true) break;

		// parcourir les voisins du noeud et mettre à jour les distances.
		for(auto it = ucase.first->voisins.begin() ; it != ucase.first->voisins.end() ; ++it) {

			if(ucase.second + it->second < debut->voisins[it->first]){

				debut->voisins[it->first] = ucase.second + it->second;
			}

		}

		ucase.first->visite = true;

	}

}

void Carte::afficher_meilleurs_chemins(){

	calculer_chemins(this->porte);

	for(auto it = this->tresors.begin() ; it != this->tresors.end() ; ++it){

		calculer_chemins(it->first);
	}

	for(auto it = this->porte->voisins.begin() ; it != this->porte->voisins.end() ; ++ it) {

		std::cout << "I : " << it->first->index << " Dist : " << it->second << std::endl;
	}
}


