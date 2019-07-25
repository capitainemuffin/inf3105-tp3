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
		bool visite;
		int index;
		//liste d'adjacence -> la case et la distance 
        std::map<Case*, double> voisins;

        // Constructeur 
		Case(char, int);

		// Methode -> l'ajouter à la liste en calculant la distance.
		void ajouter_voisin_orthogonal(Case*);
		void ajouter_voisin_diagonal(Case*);

		friend std::ostream& operator<< (std::ostream&, Carte::Case*); 
		// Ajouter un voisin

	};

	std::map<int,Case*> cases;
	std::map<Case*, std::string> tresors;
	int taille;
	Case* porte;
	int base;
	int hauteur;
	int capacite;

	Carte(int, int);
	~Carte();

	void ajouter_case(Case*);
	void ajouter_tresor(int position);
	void calculer_chemins(Case*);
	void afficher_meilleurs_chemins();

	void inserer(Case&);
};