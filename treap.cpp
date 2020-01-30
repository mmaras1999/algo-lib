namespace Treap
{
    random_device r;
    mt19937_64 gen(r());
    uniform_int_distribution<LL> range(1, INT_MAX);
    
    int Randomint()
    {    
        return range(gen);
    }

    template <class T>
    struct Treap
    {
        T key;
        int pr;
        Treap* left, * right;
        LL sum;
        int cnt;
        Treap() {};
        Treap(T key, int pr = Randomint()) : key(key), pr(pr), left(nullptr), right(nullptr), sum(0), cnt(0) {};
    };

    template <class T>
    void update(Treap<T>* t)
    {
        if(t == nullptr) return;
        t->sum = t->key;
        t->cnt = 1;
    
        if(t->left != nullptr)
        {
            t->sum += t->left->sum;
            t->cnt += t->left->cnt;
        }

        if(t->right != nullptr)
        {
            t->sum += t->right->sum;
            t->cnt += t->right->cnt;
        }
    }

    template <class T>
    void split(Treap<T>* t, T key, Treap<T>*& l, Treap<T>*& r)
    {
        if(t == nullptr)  
        {
            l = nullptr;
            r = nullptr;
        }
        else if(key < t->key)
        {
            split(t->left, key, l, t->left);
            r = t;
        }
        else
        {
            split(t->right, key, t->right, r);
            l = t;
        }
        
        update(t);
    }

    template <class T>
    void insert(Treap<T>* & t, Treap<T>* elem)
    {
        if(t == nullptr)
        {
            t = elem;
        }
        else if(t->pr < elem->pr)
        {
            if(t->key > elem->key)
                insert(t->left, elem);
            else
                insert(t->right, elem);
        }
        else
        {
            split(t, elem->key, elem->left, elem->right);
            t = elem;   
        }

        update(t);
    }

    template <class T>
    void merge(Treap<T>* & t, Treap<T>* l, Treap<T>* r)
    {
        if(l == nullptr)
        {
            t = r;
        }
        else if(r == nullptr)
        {
            t = l;
        }
        else if(l->pr < r->pr)
        {
            merge(l->right, l->right, r);
            t = l;
        }
        else
        {
            merge(r->left, l, r->left);
            t = r;
        }

        update(t);
    }

    template <class T>
    void erase(Treap<T>* & t, T key)
    {
        if(t == nullptr)
            return;
        if(t->key == key)
        {
            Treap<T>* temp = t;
            merge(t, t->left, t->right);
            delete temp;
        }
        else
        {
            if(t->key > key)
                erase(t->left, key);
            else
                erase(t->right, key);
        }
        update(t);
    }
}