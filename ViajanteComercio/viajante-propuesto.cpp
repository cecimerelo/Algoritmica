#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <list>
#include <limits>
#include <cstdlib>

using namespace std;

struct Ciudad {
	int num, x ,y;
};

int distancia_total=0, max_aux = 0;
bool primera=true, cabeza=false, cola=false;

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
double distancia(const Ciudad &ciudad1, const Ciudad &ciudad2) {

	double raiz = sqrt((ciudad2.x - ciudad1.x)*(ciudad2.x - ciudad1.x) + ((ciudad2.y-ciudad1.y) \
		*(ciudad2.y-ciudad1.y)));
		
	return round(raiz);
}

// Calcular el índice del vecino más cercano
int siguienteCiudad(const vector<Ciudad> &ciudadesPosibles, const list<Ciudad> &ciudadesRecorridas, vector<Ciudad> &ciudadesActuales) {
	
	int index = 0;
	int min = numeric_limits<int>::max();
	cabeza=false;
	 cola=false;
	
	for(int i=0; i<ciudadesActuales.size(); i++) {
		for(int j=0; j<ciudadesPosibles.size(); j++) {
			int dist = distancia(ciudadesActuales[i], ciudadesPosibles[j]);
				
			//Calculamos la distancia entre la ciudad de nuestro conjunto camino y las disponibles
			if(dist < min) {
				min = dist;
				index = j;
				max_aux = min;
			}
		}
	}
	
	return index;
}

void imprimir(const list<Ciudad> &ciudades) {
	
	for(list<Ciudad>::const_iterator i=ciudades.begin(); i!=ciudades.end(); i++)
		cout << (*i).num << " " << (*i).x << " " << (*i).y << endl;
	
	cout << endl;
}

int main(int argc, char **argv) {

	if(argc < 3) {
		cout << "ERROR. Uso: " << argv[0] << " <datos.tsp> <origen> (datos para el programa y entero del origen)" << endl;
		return -1;
	}
	
	vector<Ciudad> ciudadesPosibles;
	list<Ciudad> ciudadesRecorridas;
	vector<Ciudad> ciudadesActuales;
	vector<Ciudad> convertido;
	
	LeerCiudades(argv[1], ciudadesPosibles);
	
	int origen = atoi(argv[2]);
	
	if(origen >= ciudadesPosibles.size()) {
		cout << "ERRROR. Solo hay " << ciudadesPosibles.size() << " ciudades disponibles." << endl;
		return -2;
	}

	ciudadesRecorridas.push_back(ciudadesPosibles[origen]);
	ciudadesActuales.push_back(ciudadesPosibles[origen]);
	ciudadesPosibles.erase(ciudadesPosibles.begin()+origen);
	
	while(!ciudadesPosibles.empty()) {
		int siguiente = siguienteCiudad(ciudadesPosibles, ciudadesRecorridas,ciudadesActuales);

		distancia_total += max_aux;
		if(primera) {
			ciudadesActuales.push_back(ciudadesPosibles[siguiente]);
			ciudadesRecorridas.push_back(ciudadesPosibles[siguiente]);
			primera = false;
		}
		else {
			if(distancia(ciudadesActuales[0], ciudadesPosibles[siguiente]) == max_aux) {
				cabeza = true;
			}
			else {
				cola = true;
			}
			
			if(cabeza) {
				ciudadesActuales[0] = ciudadesPosibles[siguiente];
				ciudadesRecorridas.push_back(ciudadesPosibles[siguiente]);
			}
			else if(cola) {
				ciudadesActuales[1] = ciudadesPosibles[siguiente];
				ciudadesRecorridas.push_front(ciudadesPosibles[siguiente]);
			}
		}
		
		ciudadesPosibles.erase(ciudadesPosibles.begin()+siguiente);
	}
	
	ciudadesRecorridas.push_back(ciudadesRecorridas[0]);
	
	distancia_total += distancia((*(--ciudadesRecorridas.end())),(*(ciudadesRecorridas.begin())));
	
	imprimir(ciudadesRecorridas);
	
	cout << "La distancia total es: " << distancia_total << endl;

	return 0;
}
