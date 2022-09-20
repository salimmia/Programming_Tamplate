vector<int>Tree[mx*4];

void init(int node,int be,int en){
    Tree1[node].clear();
    Tree2[node].clear();
    if(be==en){
        Tree1[node].push_back(a[be]);
        return;
    }
    int mid=(be+en)/2;
    init(node*2,be,mid);
    init(node*2+1,mid+1,en);
    merge(Tree[node*2].begin(),Tree[node*2].end(),Tree[node*2+1].begin(),Tree[node*2+1].end(),back_inserter(Tree[node]));
}
