LL extgcd(LL a, LL b, LL& x, LL& y) 
{
    if (!b) 
    {
        x = 1;
        y = 0;
        return a;
    }
    LL d = extgcd(b, a % b, x, y);
    LL temp = y;
    y = x - a / b * y;
    x = temp;
    return d;
}
//modular inverse(a, MOD) = extgcd(a, MOD) -> x