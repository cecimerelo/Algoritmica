#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
//#include <algorithm>
//#include <vector>

//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tamaño k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tamaño n para obtener los k vectores. Están ordeados porque el algoritmo de muestreo mantiene el orden

//Genera un número uniformemente distribuido en el intervalo [0,1) a partir de uno de los generadores
//disponibles en C. 
double uniforme() {

	int t = rand();
	double f = ((double)RAND_MAX+1.0);
	
	return (double)t/f;
}
void transformar(int ** vector, int * v,int n, int k){
	for(int i=0;i<k;i++)
		for(int j=0;j<n;++j)
			v[(i*n)+j]= vector[i][j];
			
}
// Algoritmo mezcla a la fuerza
void mezcla_fuerza(int **vector, int n, int k,int *v) {
	
	int *aux;
	aux = new int [n*k];
	int f=1,i=0,iaux=0;
	int cont1=0,cont2=f*n;
	transformar(vector,v,n,k);
	
	while(i<k-1){
		cont1=0;
		cont2=f*n;
		while( (cont1 < f*n) && (cont2 < (f+1)*n) ){
			if(v[cont1] < v[cont2]){
				aux[iaux++] = v[cont1++]; 
				
			}
			else
			{
				aux[iaux++] = v[cont2++]; 
			}
			
		}
		while((cont1<f*n)){
			aux[iaux++] = v[cont1++]; 
		}
		while(cont2<(f+1)*n){
			aux[iaux++] = v[cont2++]; 
		}
		for(int h=0;h<iaux;++h){
			v[h] =aux[h];
		}
		
		iaux=0;
		i++,f++;
	}

}
void mezcla(int * v,int * v1, int * v2, int n1, int n2){
	int cont1=0,cont2=0,i=0;
	
	while(cont1<n1 && cont2< n2){
		if(v1[cont1]<v2[cont2])
			v[i++] = v1[cont1++];
		else
			v[i++] = v2[cont2++];
		
	}
	while(cont1<n1){
		v[i++] = v1[cont1++]; 
	}
	while(cont2<n2){
		v[i++] = v2[cont2++]; 
	}
}
void mezcla_recursiva(int *v, int n){
	
	if(n==2){
		if( (v[1] < v[0]) ){
			int aux=v[0];
			v[0]=v[1];
			v[1]=aux;
			
		}
		
		
	}
	else if(n>2){
		int * v1 = new int[(int)(n/2)];
		int * v2 = new int[(int)(n-(n/2))];
		for(int i=0; i<n/2; i++) {
			v1[i] = v[i];
		}
		for(int i=n/2,j=0; i<n; i++,j++) {
			v2[j] = v[i];
		}
		mezcla_recursiva(v1,n/2);
		mezcla_recursiva(v2,n-(n/2));
		mezcla(v,v1,v2,n/2,n-(n/2));
		
	}
	

}
// Algoritmo mezcla divide y vencerás
void mezcla_dv(int **vector, int n, int k,int * v) {
	transformar(vector,v,n,k);
	mezcla_recursiva(v,n*k);
}

int main(int argc, char * argv[]) {

	if(argc != 3) {
		cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
		return -1;
	}

	int n = atoi(argv[1]);
	int k = atoi(argv[2]);


	int **T;
	T = new int * [k];
	assert(T);

	for(int i = 0; i < k; i++)
		T[i]= new int [n];

	int N=k*n;
	int * aux = new int[N];
	assert(aux);

	srand(time(0));

	//genero todos los enteros entre 0 y k*n-1
	for(int j=0; j<N; j++) 
		aux[j]=j;

	//para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
	for(int i=0; i<k; i++) {
		int t=0;
		int m=0;
		while(m < n) {
			double u = uniforme();
			if ((N-t)*u >= (n-m))
				t++;
			else {
				T[i][m]=aux[t];
				t++;
				m++;
			}
		}
	}

	delete [] aux;
	cout<<"DESORDENADO"<<endl;
	// Vectores sin ordenar
	for(int i=0; i<k; i++) {
		for(int j=0; j<n; j++)
			cout << T[i][j] << " ";
		cout << " " << endl;
	}
	int *v = new int[k*n];
	// Vectores ordenados
	//mezcla_fuerza(T, n, k,v);
	mezcla_dv(T, n, k,v);
	cout<<"ORDENADO"<<endl;
	for(int i=0; i<k*n; i++) {
			cout << v[i] << " ";
		cout << " ";
	}
	cout << " " << endl;
}
