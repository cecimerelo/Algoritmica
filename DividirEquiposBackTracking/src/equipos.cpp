#include <iostream>
#include <fstream>
#include <vector>

#include "tree.h"

using namespace std;

// Leer el conjunto de contenedores 
void LeerPersonas(const char *nombre, vector<int> &personas, int &numPersonas) {
	
	ifstream is(nombre);
	int dato;
	
	if(!is) {
		cout << "ERROR al abrir el fichero." << endl;
	}
	
	while(is >> dato) {
		personas.push_back(dato);
	
		numPersonas++;
	}
}

// Listar un vector de personas
void Listar(vector<int> personas, int numPersonas) {
	
	int total = 0;
	
	for(int i=0; i<numPersonas; i++) {
		cout << personas[i] << " ";
		total += personas[i];
	}
	cout << endl;
	
	cout << "total: " << total << endl;
}

// Calcular la puntuación de un nodo del árbol, que es un estado del problema
int calcular_puntuacion(pair<vector<int>, vector<int>> nodo) {
	
	int suma1=0, suma2=0;
	
	for(int i=0; i<nodo.first.size(); i++){
		suma1 += nodo.first[i];
	}
	
	for(int i=0; i<nodo.first.size(); i++){
		suma2 += nodo.second[i];
	}
	
	if(suma1 > suma2)
		return 1;
	else if(suma1 == suma2)
		return 0;
	else
		return -1;
}

int main(int argc, char **argv) {
	
	if(argc < 2) {
		cout << "ERROR. Uso: " << argv[0] << " <datos.dat> (datos para el programa)" << endl;
		return -1;
	}
	
	vector<int> personas;
	vector<int> equipo1, equipo2;
	int numPersonas = 0;
	
	LeerPersonas(argv[1], personas, numPersonas);
	
	Listar(personas, numPersonas);
	
	return 0;
}