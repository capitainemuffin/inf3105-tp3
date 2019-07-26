#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <limits>

/**
 * Représente la carte du monde
 */
class Carte {

public:

    /**
     * Représente les types de terrain possible d'une case
     */
    enum class Terrain {
        Plaine, Eau, Foret, Route, Porte
    };

    /**
     * Représente une case de la carte
     */
    class Case {

    public:

        Carte::Terrain type;
        int elevation;
        bool visite;
        int index;

        /**
         * Liste d'adjacence <Case*, distance>
         */
        std::map<Case *, double> voisins;

        /**
         * Constructeur d'une case
         *
         * @param char : le type de terrain
         * @param int : l'élevation
         */
        Case(char, int);

        /**
         * Ajoute un voisin orthogonal dans la liste d'adjacence de la case
         * courante.
         *
         * @param Case * : le voisin à ajouter
         */
        void ajouter_voisin_orthogonal(Case *);

        /**
         * Ajoute un voisin diagonal dans la liste d'adjacence de la case
         * courante.
         *
         * @param Case * : le voisin à ajouter
         */
        void ajouter_voisin_diagonal(Case *);

    };

    std::map<int, Case *> cases;
    std::vector<Carte::Case *> tresors;
    int taille;
    Case *porte;
    int base;
    int capacite;

    /**
     * Constructeur d'une carte..
     *
     * @param int : la base de la carte
     * @param int : la hauteur de la carte
     */
    Carte(int, int);

    /**
     * Destructeur d'une carte
     */
    ~Carte();

    /**
     * Ajoute une case dans la carte
     *
     * @param Case * : la case à ajouter
     */
    void ajouter_case(Case *);

    /**
     * Ajoute un trésor dans la carte
     *
     * @param int : la position du trésor
     */
    void ajouter_tresor(int);

    /**
     * Calcule la distance d'une case vers toutes les autres cases.
     *
     * @param Case * : la case de départ
     */
    void calculer_chemins(Case *);

    /**
     * Affiche les meilleurs chemins possibles pour récolter les 3 trésors
     * et retourner à la porte
     */
    void afficher_meilleurs_chemins();

};