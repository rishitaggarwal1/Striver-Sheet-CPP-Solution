/*Complete the functions below*/
int find(int par[], int x) {
    // add code here
    if(par[x]==x)
        return x;
    return par[x] = find(par, par[x]);
}

void unionSet(int par[], int x, int z) {
    // add code here.
    int i = find(par, x);
    int j = find(par, z);
    par[i] = j;
}