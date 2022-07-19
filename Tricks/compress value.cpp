int compress() {
	vector <int> v ; map<int, int> Map ;
	for (int i = 1 ; i <= n ; i++) {
		v.push_back(a[i]) ;
	}
	sort (v.begin(), v.end()) ;
	v.erase(unique(v.begin(), v.end()), v.end()) ;
	for (int i = 0 ; i < v.size() ; i++) {
		Map[v[i]] = i + 1 ;
	}
	for (int i = 1 ; i <= n ; i++) {
		a[i] = Map[a[i]] ;
	}
	return (int)v.size() ;
}
