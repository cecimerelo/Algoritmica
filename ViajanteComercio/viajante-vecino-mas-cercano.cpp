#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

struct Ciudad {
	int num, x ,y;
};

int distancia_total=0, max_aux = 0;

// Leer el conjunto de datos de las ciudades
void LeerCiudades(const char *nombre, vector<Ciudad> &ciudades) {
	
	ifstream is(nombre);
	char next = is.get();
	int dato, cont=0;
	
	if(!is) {
		cout << "ERROR al abrir el fichero." << endl;
		//exit(-1);
	}
	
	while(next != ':') {
		is >> next;
	}

	int aux;
	is >> aux;
	
	while(is >> dato) {
		Ciudad nueva;
		
		nueva.num = dato;
		is >> dato;
		nueva.x = dato;
		is >> dato;
		nueva.y = dato;
		
		ciudades.push_back(nueva);
	}
}

// Calcula la distancia Euclídea entre dos ciudades
int distancia(const Ciudad &ciudad1, const Ciudad &ciudad2) {

	double raiz = sqrt((ciudad2.x - ciudad1.x)*(ciudad2.x - ciudad1.x) + ((ciudad2.y-ciudad1.y) \
		*(ciudad2.y-ciudad1.y)));
		
	return round(raiz);
}

// Calcular el índice del vecino más cercano
Ciudad vecinoMasCercano(const Ciudad actual, vector<Ciudad> &ciudades, const int numCiudades) {
	
	Ciudad ciudAux;
	int index = 0;
	int min = numeric_limits<int>::max();
	
	for(int i=0; i<numCiudades; i++) {
		int dist = distancia(actual, ciudades[i]);
		if(dist < min) {
			min = dist;
			index = i;
			ciudAux = ciudades[i];
			max_aux = min;
		}
	}
	ciudades.erase(ciudades.begin() + index);
	
	return ciudAux;
}

void imprimir(const vector<Ciudad> &ciudades) {
	
	for(int i=0; i<ciudades.size(); i++)
		cout << ciudades[i].num << " " << ciudades[i].x << " " << ciudades[i].y << endl;
	
	cout << endl;
}

int main(int argc, char **argv) {

	if(argc < 3) {
		cout << "ERROR. Uso: " << argv[0] << " <datos.tsp> <origen> (datos para el programa y entero del origen)" << endl;
		return -1;
	}
	
	vector<Ciudad> ciudadesPosibles;
	vector<Ciudad> ciudadesRecorridas;
	
	LeerCiudades(argv[1], ciudadesPosibles);
		
	int origen = atoi(argv[2]);
	
	if(origen >= ciudadesPosibles.size()) {
		cout << "ERRROR. Solo hay " << ciudadesPosibles.size() << " ciudades disponibles." << endl;
		return -2;
	}	

	Ciudad actual = ciudadesPosibles[origen];
	ciudadesPosibles.erase(ciudadesPosibles.begin()+origen);

	
	while(!ciudadesPosibles.empty()) {

		ciudadesRecorridas.push_back(actual);
		
		
		actual = vecinoMasCercano(actual, ciudadesPosibles, ciudadesPosibles.size());
		 
		distancia_total += max_aux;
	}
	distancia_total += distancia(actual,ciudadesRecorridas[0]);
	ciudadesRecorridas.push_back(actual);
	ciudadesRecorridas.push_back(ciudadesRecorridas[0]);
	imprimir(ciudadesRecorridas);
	
	cout << "\nLa distancia total es: " << distancia_total << endl;

	return 0;
}
