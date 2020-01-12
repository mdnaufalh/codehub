struct DisjointSet {
    vector<int> parent, size;
    DisjointSet(int n) {
        size.resize(n); parent.resize(n);
        for(int i = 0; i < n; ++i)
            parent[i] = i, size[i] = 1;
    }

    int find_parent(int i) {
        while(i != parent[i]) {
            parent[i] = parent[parent[i]];
            i = parent[i];
        }
        return i;
    }

    void union1(int i, int j) {
        int a = find_parent(i);
        int b = find_parent(j);
        if(a == b) return;
        if(size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
};

