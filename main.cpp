#include <iostream>
#include <fstream>
#include "carte.h"

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

/**
 * Execution principale
 *
 * @return 0 si termine sans erreur
 */
int main() {

    std::ifstream fichier;
    validation_fichier(fichier);
    int base, hauteur;
    fichier >> base >> hauteur;

    Carte carte = Carte(base, hauteur);

    //Lecture et insertion des cases
    for (int i = 0; i < hauteur; i++) {

        for (int j = 0; j < base; j++) {

            char type;
            int elevation;
            fichier >> type >> elevation;
            auto ucase = new Carte::Case(type, elevation);
            carte.ajouter_case(ucase);

        }

        fichier >> std::ws;

    }

    // Lecture et insertion des trésors
    for (int i = 0; i < 3; i++) {

        int x, y;
        fichier >> x >> y >> std::ws;
        int position = base * y + x + 1;
        carte.ajouter_tresor(position);
    }

    fichier.close();

    // Afficher les meilleurs chemins
    carte.afficher_meilleurs_chemins();

    return 0;
}
