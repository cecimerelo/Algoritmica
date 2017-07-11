#include <stack>
#include <iostream>
//#include <algorithm>
#include <utility> 
#include <vector>

using namespace std;

int calcular_puntuacion(pair<vector<int>,vector<int> > nodo)
{
	int suma1 = 0, suma2 = 0;
	
	for(int i = 0; i < nodo.first.size(); i++)
	{
		suma1 = suma1 + nodo.first[i];
	}
	
	for(int i = 0; i < nodo.second.size(); i++)
	{
		suma2 += nodo.second[i];
	}
	
	//cout << "El valor de suma1 es: " << suma1 << endl << "El valor de suma2 es: " << suma2 << endl;
	
	if(suma1 > suma2)
		return 1;
	else if(suma1 == suma2)
		return 0;
	else
		return -1;
	
}

pair<pair<vector<int>,vector<int> >, int > generaHijo(int iteracion,pair<vector<int>,vector<int> >  padre){

	pair<vector<int> ,vector<int> > hijo;
	
	for(int i=0;i<padre.first.size();++i)
		hijo.first.push_back(padre.first[i]);

	hijo.first.push_back(padre.second[iteracion]);
	
	
	padre.second.erase(padre.second.begin()+iteracion);
	
	for(int i=0; i<padre.second.size();i++)
		hijo.second.push_back(padre.second[i]);
	
	pair<pair<vector<int>,vector<int> >, int > result;
	result.first = hijo;
	result.second = 0;
	
	return result;

}

pair<vector <int>, vector <int> > dividir_equipos(vector<int> source)
{
	int iteracion = 0;
	stack< pair<pair<vector<int>,vector<int> >, int > > pila_nodos;
	pair<vector<int>,vector<int> > raiz_par;
	pair<pair<vector<int>,vector<int> >, int > inicio,aux;
	pair<vector <int>, vector <int> > resultado;
	
	inicio.second = 0;
	
	
	for(int i=0; i < source.size(); ++i )
	{
		inicio.first.second.push_back(source[i]);
	}
	
	

	
	pila_nodos.push(inicio);

	while((calcular_puntuacion(pila_nodos.top().first)!=0))
	{
		//cout << "Vamos por la iteracion numero: " << iteracion << endl;
		iteracion++;
		//cout << "Calcular puntuacion develve: " << calcular_puntuacion(pila_nodos.top().first) << endl;
		if((pila_nodos.top().second < pila_nodos.top().first.second.size())&&(calcular_puntuacion(pila_nodos.top().first)< 0))
		{
			aux = generaHijo(pila_nodos.top().second++,pila_nodos.top().first);
			pila_nodos.push(aux);
		}
		else
		{
			pila_nodos.pop();
		}
	}
	
	
	
	if(!pila_nodos.empty())
	{
			resultado.first = pila_nodos.top().first.first;
			resultado.second = pila_nodos.top().first.second;
	}
	
	for(int i =0; i < resultado.first.size(); i++)
		{
			cout << "Jugador valoraaaa: " << resultado.first[i] << endl;
			
		}
		
	for(int i =0; i < resultado.second.size(); i++)
		{
			cout << "Jugador valoraaaa2: " << resultado.second[i] << endl;
			
		}
	
	return resultado;
		
	
}


int main(int argc, char * argv[])
{

		vector<int> equipo;
		pair<vector <int>, vector <int> > resultado;
		
		/*
		equipo.push_back(5);
		equipo.push_back(2);
		equipo.push_back(6);
		equipo.push_back(3);
		equipo.push_back(4);
		equipo.push_back(6);
		equipo.push_back(2);
		equipo.push_back(6);*/
		
		
		//4 5 6 2 1 0 9 8 7 64 8 2
		
		
		equipo.push_back(4);
		equipo.push_back(5);
		equipo.push_back(6);
		equipo.push_back(2);
		equipo.push_back(1);
		equipo.push_back(0);
		equipo.push_back(9);
		//equipo.push_back(8);
		equipo.push_back(7);
		equipo.push_back(36);
		//equipo.push_back(8);
		equipo.push_back(2);
		equipo.push_back(2);
		equipo.push_back(2);
		equipo.push_back(2);
		equipo.push_back(1);
		equipo.push_back(3);
		
		
		
		resultado = dividir_equipos(equipo);
		
		
		
		cout << "El equipo a dividir es: " << endl;
		
		for(int i =0; i < equipo.size(); i++)
		{
			cout << "Jugador valor: " << equipo[i] << endl;
			
		}
		
		cout << "\n_____________________________________________\n " << endl;
		
		cout << "El primer equipo dividido es: " << endl;
		
		for(int i =0; i < resultado.first.size(); i++)
		{
			cout << "Jugador valor: " << resultado.first[i] << endl;
			
		}
		
		cout << "\n_____________________________________________ \n" << endl;
		
		
		cout << "El segundo equipo dividido es: " << endl;
		
		for(int i =0; i < resultado.second.size(); i++)
		{
			cout << "Jugador valor: " << resultado.second[i] << endl;
			
		}
		

}
