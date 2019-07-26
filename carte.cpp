#include "carte.h"

/**
 * Constructeur de Carte
 *
 * @param base la base de la carte
 * @param hauteur la hauteur de la carte
 */
Carte::Carte(int base, int hauteur) : taille(0), porte(nullptr) {

    if (base < 1 || hauteur < 1) {
        std::cerr
                << "La longueur et la largeur de la matrice doivent êtres plus grand que 1."
                << std::endl;
        exit(-1);
    }

    this->base = base;
    this->capacite = base * hauteur;

}

/**
 * Destructeur de carte
 */
Carte::~Carte() {

    for (auto it : this->cases) delete it.second;

}

/**
 * Constructeur de case, un premier voisin est ajouté à la liste
 * d'adjacence : lui-même.
 *
 * @param type le type de terrain
 * @param elevation l'élevatin de la case
 */
Carte::Case::Case(char type, int elevation) :
        elevation(elevation),
        visite(false),
        index(0) {

    switch (type) {

        case 'N' :
            this->type = Carte::Terrain::Plaine;
            break;

        case 'E' :
            this->type = Carte::Terrain::Eau;
            break;

        case 'F' :
            this->type = Carte::Terrain::Foret;
            break;

        case 'R' :
            this->type = Carte::Terrain::Route;
            break;

        case 'P' :
            this->type = Carte::Terrain::Porte;
            break;


        default :
            std::cerr << "Type de terrain incorrect." << std::endl;
            exit(-10);

    }

    this->voisins.insert(std::make_pair(this, 0));

}

/**
 * Ajoute une case à la grille et calcule ses voisins.
 *
 * @param ucase la case à ajouter
 */
void Carte::ajouter_case(Carte::Case *ucase) {

    if (ucase->type == Carte::Terrain::Porte) {

        if (porte) {
            std::cerr << "Il ne peut y avoir plus d'une porte dans la matrice.";
            std::cerr << std::endl;
            exit(-2);
        }

        this->porte = ucase;

    }

    if (this->taille >= this->capacite) {
        std::cerr << "La capacité maximale de la matrice a été dépassée.";
        std::cerr << std::endl;
        exit(-5);

    }

    this->cases[++taille] = ucase;
    ucase->index = this->taille;

    // Si pas premier de colonne, connecter avec voisin de gauche
    if (this->taille % this->base != 1) {
        ucase->ajouter_voisin_orthogonal(this->cases[this->taille - 1]);
        this->cases[this->taille - 1]->ajouter_voisin_orthogonal(ucase);
    }

    // Si dernier de colonne
    if (this->taille % this->base == 0) {

        // prendre la première case de la ligne et lui ajouter ce voisin
        this->cases[this->taille - this->base + 1]->ajouter_voisin_orthogonal(
                ucase);

    }

    // Si pas première ligne
    if (this->taille > this->base) {

        //ajouter voisin de haut
        ucase->ajouter_voisin_orthogonal(
                this->cases[this->taille - this->base]);
        this->cases[this->taille - this->base]->ajouter_voisin_orthogonal(
                ucase);

        // Si pas premier de colonne
        if (this->taille % this->base != 1) {

            // voisin haut/gauche
            ucase->ajouter_voisin_diagonal(
                    this->cases[this->taille - this->base - 1]);
            this->cases[this->taille - this->base - 1]->ajouter_voisin_diagonal(
                    ucase);
        }

        // Si pas dernier de colonne
        if (this->taille % this->base != 0) {

            // voisin haut/droit
            ucase->ajouter_voisin_diagonal(
                    this->cases[this->taille - this->base + 1]);
            this->cases[this->taille - this->base + 1]->ajouter_voisin_diagonal(
                    ucase);

        }

    }

}

/**
 * Ajoute une trésor à la grille
 *
 * @param position la position du trésor sur la grille
 */
void Carte::ajouter_tresor(int position) {

    if (position > this->capacite) {
        std::cerr << "Coordonées de trésor invalides." << std::endl;
        exit(-3);
    }

    if (this->cases[position]->type == Carte::Terrain::Eau) {
        std::cerr << "Un trésor ne peut pas être dans l'eau." << std::endl;
        exit(-4);
    }

    this->tresors.push_back(this->cases[position]);
}

/**
 * Ajoute un voisin orthogonal à la liste d'adjacence de la case.
 *
 * @param ucase le voisin à ajouter
 */
void Carte::Case::ajouter_voisin_orthogonal(Carte::Case *ucase) {

    double distance = 0;

    // Vérifier que c'est pas de l'eau et que élevation est acceptbable
    if (this->type != Carte::Terrain::Eau
        && ucase->type != Carte::Terrain::Eau
        && this->elevation - ucase->elevation > -2
        && this->elevation - ucase->elevation < 2) {

        switch (ucase->type) {

            case Carte::Terrain::Foret :

                distance = 2;
                break;

            case Carte::Terrain::Route :

                distance = this->type == Carte::Terrain::Route ? 0.5 : 1;
                break;

            default :
                distance = 1;

        }

        if (this->elevation - ucase->elevation < 0) distance *= 2;
        this->voisins.insert(std::make_pair(ucase, distance));

    }

}

/**
 * Ajoute un voisin diagonal à la liste d'adjacence de la case.
 *
 * @param ucase le voisin à ajouter
 */
void Carte::Case::ajouter_voisin_diagonal(Carte::Case *ucase) {

    double distance = 0;

    // Vérifier que c'est pas de l'eau et que elévation est acceptable
    if (this->type != Carte::Terrain::Eau
        && ucase->type != Carte::Terrain::Eau
        && this->elevation - ucase->elevation >= -1
        && this->elevation - ucase->elevation <= 1) {


        switch (ucase->type) {

            case Carte::Terrain::Foret :

                distance = 2.8;
                break;

            case Carte::Terrain::Route :

                distance = this->type == Carte::Terrain::Route ? 0.7 : 1.4;
                break;

            default :
                distance = 1.4;

        }

        if (this->elevation - ucase->elevation < 0) distance *= 2;
        this->voisins.insert(std::make_pair(ucase, distance));

    }

}

/**
 * Calcule la distance d'une case vers toutes les autres cases.
 * Utilise Dijkstra.
 *
 * @param debut
 */
void Carte::calculer_chemins(Carte::Case *debut) {

    // Tous les voisins lointains initialisés à <infini>
    for (auto it : this->cases) {

        if (debut->voisins.find(it.second) == debut->voisins.end()) {

            debut->voisins.insert(std::make_pair(it.second,
                                                 std::numeric_limits<double>::max()));

        }

        it.second->visite = false;

    }

    while (true) {

        // Sélectionner le noeud le plus proche et non visité
        auto ucase = new std::pair<Carte::Case *, double>(nullptr, NULL);

        for (auto it : debut->voisins) {

            if (!it.first->visite &&
                (ucase->first == nullptr || it.second < ucase->second)) {

                ucase->first = it.first;
                ucase->second = it.second;

            }
        }

        //Si tous les noeuds sont visités, sortir de la boucle
        if (ucase->first == nullptr) break;

        ucase->first->visite = true;

        // parcourir les voisins du noeud et mettre à jour les distances.
        for (auto it = ucase->first->voisins.begin();
             it != ucase->first->voisins.end(); ++it) {

            if (ucase->second + it->second < debut->voisins[it->first]) {

                debut->voisins[it->first] = ucase->second + it->second;
            }

        }

        delete ucase;

    }

}

/**
 * Affiche les meilleurs chemins possibles pour récolter les 3 trésors
 * et retourner à la porte
 */
void Carte::afficher_meilleurs_chemins() {

    calculer_chemins(this->porte);

    for (auto it : porte->voisins) {

        std::cout << "Index : " << it.first->index << " Distance : "
                  << it.second << std::endl;
    }

    for (auto it : this->tresors) {

        calculer_chemins(it);
        std::cout << "Trésor : Index : " << it->index << std::endl;

    }

}


