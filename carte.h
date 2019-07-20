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
        std::set<std::pair<Case*, double>> voisins;

        // Constructeur 
		Case(char, int, bool);
		~Case();

		// Methode -> l'ajouter à la liste en calculant la distance.
		void ajouter_voisin_orthogonal(Case*);
		void ajouter_voisin_diagonal(Case*);

		// Ajouter un voisin

	};

	std::map<int,Case*> cases;
	int taille;
	bool porte_presente;
	int longueur;
	int largeur;
	int capacite;

	Carte(int, int);
	~Carte();

	void ajouter_case(Case*);
	void ajouter_tresor(int position);
	double meilleur_chemin(Case*, Case*);
	void afficher_meilleurs_chemins();

	void inserer(Case&);
	friend std::istream& operator >> (std::ifstream&, Carte&);
};