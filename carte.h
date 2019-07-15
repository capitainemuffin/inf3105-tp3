#include <set>
#include <string>
#include <map>

class Carte {

	Carte(int, int);

	enum class Terrain { Plaine, Eau, Foret, Route, Porte};

	class Case {

		Terrain type;
		int elevation;
		bool tresor;

		Case(Terrain, int, bool);

	};

	std::map<std::string, Case> cases; 
	friend std::istream& operator >> (std::istream&, Carte&);
};