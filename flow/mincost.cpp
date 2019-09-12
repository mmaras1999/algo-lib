class MinCostMaxFlow
{
public:
    struct Edge
    {
        int source, dest, rev;
        LL flow, cost;
        Edge(int source, int dest, LL flow, int rev, LL cost) : source(source), dest(dest), flow(flow), rev(rev), cost(cost) {}
    };

    int N;
    vector <Edge> edges;
    vector <LL> dist;
    vector <int> prevv;
    vector <vector <int> > graph;

    MinCostMaxFlow(int n)
    {
        N = n;
        graph.resize(n);
        dist.resize(n);
        prevv.resize(n);
    }

    void addEdge(int a, int b, LL cost, LL cap)
    {
        int ID = SIZE(edges);
        edges.PB(Edge(a, b, cap, ID + 1, cost));
        edges.PB(Edge(b, a, 0, ID, -cost));
        graph[a].PB(ID);
        graph[b].PB(ID + 1);
    }

    void SPFA(int start)
    {
        FOR(i, 0, N) dist[i] = LLINF;
        vector <bool> inqueue(N, 0);
        
        dist[start] = 0;
        queue <int> q;

        q.push(start);
        inqueue[start] = 1;

        while (SIZE(q)) 
        {
            int v = q.front();
            q.pop();
            inqueue[v] = 0;

            for (auto u : graph[v]) 
            {
                auto e = edges[u];
                if(!e.flow) continue;
                if (dist[v] + e.cost < dist[e.dest]) 
                {
                    dist[e.dest] = dist[v] + e.cost;
                    if (!inqueue[e.dest]) 
                    {
                        q.push(e.dest);
                        inqueue[e.dest] = 1;
                    }
                }
            }
        }
    }

    void Dijkstra(int start)
    {
        FOR(i, 0, N) dist[i] = LLINF;
        dist[start] = 0;
        set <pair <LL, LL> > dijkstra;
        dijkstra.insert(MP(0, start));

        while(SIZE(dijkstra))
        {
            auto v = dijkstra.begin()->second;
            dijkstra.erase(dijkstra.begin());

            for(auto& u : graph[v])
            {
                auto e = edges[u];
                if(!e.flow) continue;
                if(dist[v] + e.cost < dist[e.dest])
                {
                    dijkstra.erase(MP(dist[e.dest], e.dest));
                    dist[e.dest] = dist[v] + e.cost;
                    prevv[e.dest] = u;
                    dijkstra.insert(MP(dist[e.dest], e.dest));
                }
            }
        }
    }

    void ReduceCosts()
    {
        for(auto& e : edges)
            e.cost = e.cost + dist[e.source] - dist[e.dest];
    }

    LL calc(int start, int end)
    {
        SPFA(start);
        ReduceCosts();
        LL res = 0;
        LL temp = 0;
        
        while(true)
        {
            temp += dist[end];
            Dijkstra(start);
            if(dist[end] == LLINF) break;
            LL flow = LLINF;
            int v = end;
            while(v != start)
            {
                auto e = edges[prevv[v]];
                flow = min(flow, e.flow);
                v = e.source;
            }
            v = end;
            while(v != start)
            {
                auto& e = edges[prevv[v]];
                if(e.flow != LLINF) e.flow -= flow;
                if(edges[e.rev].flow != LLINF) edges[e.rev].flow += flow;
                v = e.source;
            }
            res += flow * (temp + dist[end]);
            ReduceCosts();
        }

        return res;
    }
};