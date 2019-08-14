// d1 - odd length
// d2 - even length (right)

namespace Manacher
{
    vector <int> odd;
    vector <int> even;
    void runManacher(string& s)
    {
        int n = SIZE(s);
        odd.resize(n);
        even.resize(n);
        int l = 0, r = -1;
        FOR(i, 0, n)
        {
            int x;
            if(r < i)
                x = 1;
            else
                x = min(r - i + 1, odd[l + r - i]);
            while(0 <= i - x && i + x < n && s[i - x] == s[i + x])
                ++x;
            odd[i] = x--;
            if(i + x > r)
            {
                l = i - x;
                r = i + x;
            }
        }
        l = 0;
        r = -1;
        FOR(i, 0, n)
        {
            int x;
            if(r < i)
                x = 0;
            else
                x = min(even[l + r - i + 1], r - i + 1);
            while (0 <= i - x - 1 && i + x < n && s[i - x - 1] == s[i + x])
                x++;
            even[i] = x--;
            if (i + x > r) 
            {
                l = i - x - 1;
                r = i + x ;
            }
        }
    }
}