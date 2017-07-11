#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

struct Ciudad {
	int num, x ,y;
};

double aux, distancia_total=0,max_aux = 0;
double distancias_locales[3],distan[3];
// Leer el conjunto de datos de las ciudades
void LeerCiudades(char *nombre, vector<Ciudad> &ciudades) {
	
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
double distancia(Ciudad ciudad1, Ciudad ciudad2) {

	return round(sqrt((ciudad2.x - ciudad1.x)*(ciudad2.x - ciudad1.x) + ((ciudad2.y-ciudad1.y) \
		*(ciudad2.y-ciudad1.y))));
}

// Calcular el índice del vecino más cercano
Ciudad vecinoMasCercano(Ciudad actual, vector<Ciudad> &ciudades,double &distanc,double & dista) {
	Ciudad ciudAux;
	int index = 0;
	double min = 999999999;
	
	
	for(int i=0; i<ciudades.size(); i++) {
		if(actual.num!=ciudades[i].num)//No se tienen en cuenta a ellas mismas como ciudad posible
			aux = distancia(actual, ciudades[i]);
		if(aux < min) {
			min = aux;
			index = i;
			ciudAux = ciudades[i];
			max_aux = min;
			dista=min;
			
		}
	}
	distanc+=min;//Distancia Acumulada local a cada norte este y oeste
	return ciudAux;
}


void imprimir(vector<Ciudad> ciudades) {

	for (int i = 0; i<ciudades.size(); i++)
		cout << ciudades[i].num << " " <<ciudades[i].x<<" " <<ciudades[i].y<<endl;

	cout << endl;
}

Ciudad ciudadInicial(vector<Ciudad> ciudadesPosibles, char eje, bool mayor){
	Ciudad ciudAux;
	int param;
	int aux;
	ciudAux= ciudadesPosibles[0];
	if (eje=='x'){
		param = ciudadesPosibles[0].x;
	}else{
		param = ciudadesPosibles[0].y;
	}
	for (int i = 1; i < ciudadesPosibles.size(); i++) {
		if (eje == 'x'){
			aux = ciudadesPosibles[i].x;
			if (!mayor)
			{
				if (aux < param) {
					param = aux;
					ciudAux = ciudadesPosibles[i];
				}
			}
			else
			{
				if (aux > param) {
					param = aux;
					ciudAux = ciudadesPosibles[i];
				}
			}
		}
		else
		{
			aux = ciudadesPosibles[i].y;
			if (!mayor)
			{
				if (aux < param) {
					param = aux;
					ciudAux = ciudadesPosibles[i];
				}
			}
			else
			{
				if (aux > param) {
					param = aux;
					ciudAux = ciudadesPosibles[i];
				}
			}
		}
	}
	return ciudAux;
}
int mejorCiudad(double * distancias,double *distan){
	double total=distancias[0]+distancias[1]+distancias[2];
	if(total+distan[0] < total+distan[1]){
		if(total+distan[0]<total+distan[2])
			return 0;
		else
			return 2;
	}else
		if(total+distan[1]<total+distan[2])
			return 1;
		else
			return 2;
}
int buscar(vector<Ciudad>  ciudadesPosibles,Ciudad abuscar){
	
	for(int i=0;i<ciudadesPosibles.size();++i)
	{
		if(ciudadesPosibles[i].num==abuscar.num)
			return i;
	}
}
int main(int argc,char**argv){
	if (argc < 2) {
		cout << "ERROR. Uso: " << argv[0] << " <datos.tsp> (datos para el programa)" << endl;
		return -1;
	}

	int ciu=0;
	double distanciaTotal=0;
	vector<Ciudad> ciudadesPosibles;
	vector<Ciudad> ciudadesRecorridas;

	LeerCiudades(argv[1], ciudadesPosibles);

	/*Escojo las ciudades iniciales*/

	Ciudad este = ciudadInicial(ciudadesPosibles, 'x', true);
	Ciudad oeste = ciudadInicial(ciudadesPosibles, 'x', false);
	Ciudad norte = ciudadInicial(ciudadesPosibles, 'y', false);
	Ciudad esteAux=este;
	Ciudad oesteAux=oeste;
	Ciudad norteAux=norte;
	Ciudad volver;
	bool primera=true;
	
	cout<<"CIUDADES INICIALES ESTE:"<<este.num<<" OESTE: "<<oeste.num<<" NORTE: "<<norte.num<<endl;
	while (!ciudadesPosibles.empty()) {
		este = vecinoMasCercano(este, ciudadesPosibles,distancias_locales[0],distan[0]);
		if(!ciudadesPosibles.empty())
			oeste = vecinoMasCercano(oeste, ciudadesPosibles,distancias_locales[1],distan[1]);
		if(!ciudadesPosibles.empty())
			norte = vecinoMasCercano(norte, ciudadesPosibles,distancias_locales[2],distan[2]);
							

		if(!ciudadesPosibles.empty()){
			ciu = mejorCiudad(distancias_locales,distan);//Compruebo que ciudad aumenta el minimo el total de la distancia que llevo recorrida.
			if(ciu==0){
				//Por cual ciudad empiezo
				if(primera){
					ciudadesRecorridas.push_back(esteAux);
					volver=esteAux;//Para el final
					primera=false;
					ciudadesPosibles.erase(ciudadesPosibles.begin() +buscar(ciudadesPosibles,esteAux));
				}
				ciudadesRecorridas.push_back(este);
				ciudadesPosibles.erase(ciudadesPosibles.begin() +buscar(ciudadesPosibles,este));
			}
			else if(ciu==1){
				if(primera){
					ciudadesRecorridas.push_back(oesteAux);
					volver=oesteAux;//Para el final
					ciudadesPosibles.erase(ciudadesPosibles.begin() +buscar(ciudadesPosibles,oesteAux));
					primera=false;
				}
				
				ciudadesRecorridas.push_back(oeste);
				ciudadesPosibles.erase(ciudadesPosibles.begin() +buscar(ciudadesPosibles,oeste));
			}else{
				if(primera){
					ciudadesRecorridas.push_back(norteAux);
					volver=norteAux;//Para el final
					ciudadesPosibles.erase(ciudadesPosibles.begin() +buscar(ciudadesPosibles,norteAux));
					primera=false;
				}
				
				ciudadesRecorridas.push_back(norte);
				ciudadesPosibles.erase(ciudadesPosibles.begin() +buscar(ciudadesPosibles,norte));
			}
			distanciaTotal+=distan[ciu];//Sumo la distancia minima que voy obteniendo
		}

	}
	//La distancia para la vuelta al inicio
	distanciaTotal+=distancia(volver,ciudadesRecorridas[ciudadesRecorridas.size()-1]);
	ciudadesRecorridas.push_back(volver);//La vuelta
	imprimir(ciudadesRecorridas);
	cout<<"Distancia Total "<<distanciaTotal<<" "<<endl;
	return 0;
}
