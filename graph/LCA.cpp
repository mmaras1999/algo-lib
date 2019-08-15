namespace LCA
{
    vector <int> preorder, depth;
    vector <int> eulerTour;
    vector <pair <int, int> > RMQ[26];
    vector <int> log;

    void DFS(int v, int prev = -1)
    {
        preorder[v] = SIZE(eulerTour);
        eulerTour.PB(v);
        for(auto& u : tree[v])
            if(u != prev)
            {
                depth[u] = depth[v] + 1;
                DFS(u, v);
                eulerTour.PB(v);
            }
    }

    void init(vector <vector <int> >& tree)
    {
        int n = SIZE(tree);
        preorder.resize(n, -1);
        depth.resize(n);
        DFS(0);
        int m = SIZE(eulerTour);
        log.resize(m, 0);
        FOR(i, 2, m)
            log[i] = log[i / 2] + 1;
        FOR(i, 0, 26)
            RMQ[i].resize(m);
        FOR(i, 0, m)
            RMQ[0][i] = MP(depth[eulerTour[i]], eulerTour[i]);
        FOR(j, 1, 26)
        {
            int temp = 1 << (j - 1);
            FOR(i, 0, m)
            {
                RMQ[j][i] = RMQ[j - 1][i];
                if(i + temp < m)
                    RMQ[j][i] = min(RMQ[j][i], RMQ[j - 1][i + temp]);
            }
        }
    }

    int LCA(int v, int u)
    {
        v = preorder[v];
        u = preorder[u];
        if(v > u)
            swap(v, u);
        int j = log[u - v + 1];
        auto x = min(RMQ[j][v], RMQ[j][u - (1 << j) + 1]);
        return x.second;
    }
}