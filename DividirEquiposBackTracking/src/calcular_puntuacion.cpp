

int calcular_puntuacion(pair<vector<int>,vector<int> > nodo)
{
	int suma1 = 0, suma2 = 0;
	
	for(int i = 0; i < nodo.first.size(); i++)
	{
		suma1 += nodo.first[i]
	}
	
	for(int i = 0; i < nodo.first.size(); i++)
	{
		suma2 += nodo.second[i]
	}
	
	if(suma1 > suma2)
		return 1;
	else if(suma1 == suma2)
		return 0;
	else
		return -1;
	
}