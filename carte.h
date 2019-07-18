#include <set>
#include <string>
#include <map>

class Carte {

	enum class Terrain { Plaine, Eau, Foret, Route, Porte };

	class Case {

	public:

		// Attributs 
		Carte::Terrain type;
		int elevation;
		bool tresor;
        std::set<std::pair<Case&, double>> voisins;

        // Constructeur
		Case(char, int, bool);

		// Methode -> l'ajouter à la liste en calculant la distance.
		void ajouter_voisin(Case&);

		// Ajouter un voisin

	};

	std::map<int, Case*> cases;
	int taille;
	bool porte_presente;
	int longueur;
	int largeur;
	int capacite;

	Carte(int, int);

	void ajouter_case(Case*);
	void ajouter_tresor(int, int);
	double distance_minimale(Case&, Case&);

	void inserer(Case&);
	friend std::istream& operator >> (std::istream&, Carte&);
};