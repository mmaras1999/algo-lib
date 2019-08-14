namespace Z_func
{
    vector <int> Z;

    void CalcZ(string& s)
    {
        int n = SIZE(s);
        Z.clear();
        Z.resize(n, 0);

        int l = 0, r = 0;

        FOR(i, 1, n)
        {
            if(i <= r)
                Z[i] = min(r - i + 1, Z[i - l]);

            while(i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
                ++Z[i];

            if(i + Z[i] - 1 > r)
            {
                l = i;
                r = i + Z[i] - 1;
            }
        }
    }
}