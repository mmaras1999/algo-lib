struct CHT
{
    vector <pair <LL, LL> > lines;

    bool check(pair <LL, LL> l1, pair <LL, LL> l2, pair <LL, LL> l3)
    {
        LD a1 = l1.first, b1 = l1.second;
        LD a2 = l2.first, b2 = l2.second;
        LD a3 = l3.first, b3 = l3.second;
        
        return (b3 - b1) * (a2 - a3) >= (a1 - a3) * (b3 - b2);
    }

    void insert(LL a, LL b)
    {
        auto newl = MP(a, b);

        while(SIZE(lines) > 1 && check(lines[SIZE(lines) - 2], lines.back(), newl))
        {
            lines.pop_back();
        }

        lines.PB(newl);
    }

    LL query(LL x)
    {
        int minn = 0;
        int maxx = SIZE(lines) - 2;

        while(minn < maxx)
        {
            int mid = (minn + maxx + 1) / 2;
            LD a1 = lines[mid].first, b1 = lines[mid].second;
            LD a2 = lines[mid + 1].first, b2 = lines[mid + 1].second;

            if((b2 - b1) <= x * (a1 - a2))
            {
                minn = mid;
            }
            else
            {
                maxx = mid - 1;
            }
        }

        LL res = lines[minn].first * x + lines[minn].second;

        if(minn + 1 < SIZE(lines))
        {
            //change to max if needed, also change comparators in query and check!
            res = min(res, lines[minn + 1].first * x + lines[minn + 1].second);
        }

        return res;
    }
};