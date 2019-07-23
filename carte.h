#include <set>
#include <string>
#include <map>

class Carte {

public:
	enum class Terrain { Plaine, Eau, Foret, Route, Porte };

	class Case {

	public:

		// Attributs 
		Carte::Terrain type;
		int elevation;
		bool tresor;
		bool visite;
		int index;
		//liste d'adjacence -> la case et la distance 
        std::set<std::pair<Case*, double>> voisins;

        // Constructeur 
		Case(char, int, bool);

		// Methode -> l'ajouter à la liste en calculant la distance.
		void ajouter_voisin_orthogonal(Case*);
		void ajouter_voisin_diagonal(Case*);

		friend std::ostream& operator<< (std::ostream&, Carte::Case*); 
		// Ajouter un voisin

	};

	std::map<int,Case*> cases;
	int taille;
	bool porte_presente;
	int base;
	int hauteur;
	int capacite;

	Carte(int, int);
	~Carte();

	void ajouter_case(Case*);
	void ajouter_tresor(int position);
	double meilleur_chemin(Case*, Case*);
	void afficher_meilleurs_chemins();

	void inserer(Case&);
};