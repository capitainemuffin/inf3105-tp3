#include <iostream>
#include <fstream>
#include "carte.h"

std::ostream& operator<< (std::ostream& is , Carte::Case* ucase) {

		switch(ucase->type){

		case Carte::Terrain::Plaine : {
			is << "Type : Plaine";
			break;
		}
		case Carte::Terrain::Eau : {
			is << "Type : Eau";
			break;
		}
		case Carte::Terrain::Foret : {
			is << "Type : Foret";
			break;
		}
		case Carte::Terrain::Route : {
			is << "Type : Route";
			break;
		}
		case Carte::Terrain::Porte : {
			is << "Type : Porte";
			break;
		}
	}

		is << " Tresor : " << ucase->tresor;

		is << " Élevation " << ucase->elevation;

		is << " Nbr de voisins " << ucase->voisins.size();

		is << " Index : " << ucase->index;

		return is;
}


/**
 * Demande d'entrer un nom de fichier puis essaye de l'ouvrir.
 * Valide l'existence du fichier et l'extension ".txt".
 * @param fichier l'instance stream du fichier
 * @return fichier l'instance stream du fichier
 */
void validation_fichier(std::ifstream &fichier) {

        std::string repertoire;
        std::cerr << "Entrez le nom du fichier : ";
        std::cin >> repertoire;
        fichier.open(repertoire.c_str());

        if (repertoire.length() < 5 || fichier.fail()) {

            std::cerr << "Fichier spécifié invalide." << std::endl;
            fichier.close();
            exit(-100);

        } else if (repertoire.substr(repertoire.length() - 4, 4) != ".txt") {

            std::cerr << "Le fichier doit terminer par \".txt\"" << std::endl;
            fichier.close();
            exit(-200);

        }

}

int main (){

	std::ifstream fichier;
	validation_fichier(fichier);
	size_t base, hauteur;
	fichier >> base >> hauteur;

	Carte carte = Carte(base, hauteur);

	for(int i = 0 ; i < hauteur ; i++){

		for(int j = 0 ; j < base ; j++) {

			char type;
			int elevation;
			fichier >> type >> elevation;
			Carte::Case* ucase = new Carte::Case(type, elevation, false);
			carte.ajouter_case(ucase);

		}

		fichier >> std::ws;

	}

	for(int i = 0 ; i < 3 ; i ++ ) {

		int x, y;

		fichier >> x >> y >> std::ws;

		int position = base * y + x + 1;

		carte.cases[position]->tresor = true;
	}

	fichier.close();

	carte.afficher_meilleurs_chemins();
	std::cout << std::endl;
	return 0;
}
