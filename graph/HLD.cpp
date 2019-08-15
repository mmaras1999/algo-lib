namespace HLD //LCA needed
{
    vector <int> parent, depth, heavy, head, pos;
    int cur_pos;

    int DFS(int v, vector <vector <int> >& tree)
    {
        int size = 1;
        int max_size = 0;
        for(auto& u : tree[v])
        {
            if(u != parent[v])
            {
                parent[u] = v;
                depth[u] = depth[v] + 1;
                int temp = DFS(u, tree);
                size += temp;
                if(temp > max_size)
                {
                    max_size = temp;
                    heavy[v] = u;
                }
            }
        }
        return size;
    }

    void decompose(int v, int h, vector <vector <int> >& tree)
    {
        head[v] = h;
        pos[v] = cur_pos++;
        if(heavy[v] != -1)
        {
            decompose(heavy[v], h, tree);
        }
        for(auto& u : tree[v])
        {
            if(u != parent[v] && u != heavy[v])
            {
                decompose(u, u, tree);
            }
        }
    }

    void init(vector <vector <int> >& tree)
    {
        int n = SIZE(tree);
        parent.resize(n);
        depth.resize(n);
        heavy.resize(n, -1);
        head.resize(n);
        pos.resize(n);
        cur_pos = 0;
        DFS(0, tree);
        decompose(0, 0, tree);
    }
}

/*void query(int a, int b)
{
    while(HLD::head[a] != HLD::head[b])
    {
        if(HLD::depth[HLD::head[a]] > HLD::depth[HLD::head[b]])
            swap(a, b);
        //do sth from HLD::pos[HLD::head[b]] to HLD::pos[b]
        b = HLD::parent[HLD::head[b]];
    }

    if(HLD::depth[a] > HLD::depth[b])
        swap(a, b);
    //do sth from HLD::pos[a] (+ 1 if on edges) to HLD::pos[b]
}
*/