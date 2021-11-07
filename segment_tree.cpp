
#include<bits/stdc++.h>

using namespace std;

struct st{
    int size;
    // the heap structure of the segment tree
    vector<long long> sums;

    void init(int n){
        size = 1;
        // get the first power of two greater or equal
        while(size < n){
            size *= 2;
        }
        // a heap structure has size 2*n, all initialized with 0's
        sums.assign(2*size, 0);
    }

    void build(vector<int> &a, int x, int lx, int rx){
        // it is a leaf node
        if(rx - lx == 1){
            // since we rounded to the nearest power of two bigger than the array
            // we need to check if the element is actually an element
            if(lx < (int)a.size()){
                sums[x] = a[lx];
            }
            return;
        }
        // otherwise we recursively call the build function
        int m = (lx + rx)/2;
        build(a, 2*x + 1, lx, m);
        build(a, 2*x + 2, m, rx);
        sums[x] = sums[2*x+1] + sums[2*x+2];
    }

    void build(vector<int> &a){
        build(a, 0, 0, size);
    }
    /* basic operations of the segment tree */
    void set(int i, int v, int x, int lx, int rx){ 
        
        if(rx - lx == 1){
            sums[x] = v;
            return;
        }

        int m = (lx + rx)/2;
        if(i < m){
            set(i, v, 2*x+1, lx, m);
        } else {
            set(i, v, 2*x+2, m, rx);
        }

        sums[x] = sums[2*x+1] + sums[2*x+2];
    }

    void set(int i, int v){ 
        set(i, v, 0, 0, size);
    }

    long long sum(int l, int r, int x, int lx, int rx){
        if(lx >= r || rx <= l)
            return 0;
        if(lx >= l && rx <= r)
            return sums[x];
        
        int m = (lx + rx)/2;
        long long s1 = sum(l, r, 2*x+1, lx, m);
        long long s2 = sum(l, r, 2*x+2, m, rx);
        return s1+s2;


    }
    long long sum(int l, int r){
        return(sum(l, r, 0, 0, size));        
    }


    void print(){
        for(int i = 0; i < size*2; i++){
            cout << sums[i] << ' ';
        }
        cout << endl;
    }
};

int main(){
    st tree;
    int n, m;

    cin >> n >> m;

    tree.init(n);

    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    tree.build(a);
    for(int i = 0; i < m; i++){
        int b, k, l;
        cin >> b >> k >> l;
        if(b == 1){
            tree.set(k, l);
        } else {
            cout << tree.sum(k, l) << endl;
        }
    }

    return 0;
}