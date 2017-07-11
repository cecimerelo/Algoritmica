tree<pair<vector,vector> >::node generaHijo(int iteracion, tree<pair<vector,vector> >::node & padre, tree<pair<vector,vector> > & arb){

	tree<pair<vector,vector> >::node hijo;
	
	if(padre.first.size() !=0)
		for(int i=0;i<padre.first.size();++i)
			hijo.first.push_back(padre.first[i]);

	hijo.first.push_back(padre.second[iteracion]);
	
	padre.second.erase(padre.second.begin()+iteracion);
	
		
	return abr.insert_left(padre,hijo);


}