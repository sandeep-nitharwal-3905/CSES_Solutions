#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long
#define ld long double

/*---------------------CONSTANTS---------------------*/
#define M 1000000007
#define N 100005
#define MX 1e9

/*---------------------PB_DS---------------------*/
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

// int : is type of data to insert into tree
// null_type : part of maping
// less : ascending / greater / less_equal
// pbds A for itialization
// kth element : .find_by_order
// no of small ele : .order_of_key

/*---------------------Debugging---------------------*/

#ifndef ONLINE_JUDGE
#define debug(x...)               \
    cerr << "[" << #x << "] = ["; \
    _print(x)
#else
#define debug(x)
#endif
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V>
void __print(const pair<T, V> &x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T &x)
{
    int f = 0;
    cerr << '{';
    for (auto &i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}

/*---------------------Segment Tree---------------------*/
struct Node;
struct Update;

template <typename T, typename Node = Node, typename Update = Update>
class SegmentTree
{
private:
    int size = 0;
    vector<Node> seg;

    void build(int start, int end, int ind, vector<T> &arr)
    {
        if (start == end)
        {
            seg[ind] = Node(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        int leftInd = 2 * ind + 1, rightInd = 2 * ind + 2;
        build(start, mid, leftInd, arr);
        build(mid + 1, end, rightInd, arr);
        seg[ind].merge(seg[leftInd], seg[rightInd]);
    }

    Node query(int start, int end, int ind, int left, int right)
    {
        if (start > right || end < left)
        {
            return Node();
        }
        if (start >= left && end <= right)
        {
            return seg[ind];
        }
        int mid = (start + end) / 2;
        int leftInd = 2 * ind + 1, rightInd = 2 * ind + 2;
        Node res;
        Node leftItem = query(start, mid, leftInd, left, right);
        Node rightItem = query(mid + 1, end, rightInd, left, right);
        res.merge(leftItem, rightItem);
        return res;
    }

    void update(int start, int end, int ind, int index, Update &u)
    {
        if (start == end)
        {
            u.apply(seg[ind]);
            return;
        }
        int mid = (start + end) / 2;
        int leftInd = 2 * ind + 1, rightInd = 2 * ind + 2;
        if (index <= mid)
            update(start, mid, leftInd, index, u);
        else
            update(mid + 1, end, rightInd, index, u);
        seg[ind].merge(seg[leftInd], seg[rightInd]);
    }

public:
    SegmentTree()
    {
    }

    SegmentTree(int n)
    {
        size = n;
        seg.resize(4 * size + 1);
    }

    SegmentTree(vector<T> &arr)
    {
        size = arr.size();
        seg.resize(4 * size + 1);
        build(arr);
    }

    void build(vector<T> &arr)
    {
        build(0, size - 1, 0, arr);
    }

    Node query(int left, int right)
    {
        return query(0, size - 1, 0, left, right);
    }

    void update(int index, int value)
    {
        Update u = Update(value);
        return update(0, size - 1, 0, index, u);
    }
};

struct Node
{
    long long sum;
    int mx, mn;
    long long andd;
    long long orr;

    Node() : sum(0), mx(-MX), mn(MX), andd((1LL << 32) - 1), orr(0) {}
    Node(int val) : sum(val), mx(val), mn(val), andd(val), orr(val) {}

    void merge(Node &left, Node &right)
    {
        sum = left.sum + right.sum;
        mx = max(left.mx, right.mx);
        mn = min(left.mn, right.mn);
        andd = left.andd & right.andd;
        orr = left.orr | right.orr;
    }
};

struct Update
{
    int val;

    Update() : val(0) {}
    Update(int v) : val(v) {}

    void apply(Node &node)
    {
        node.sum = val;
        node.mn = val;
        node.mx = val;
        node.andd = val;
    }
};

/*---------------------BinaryExponent/BinaryMultiplication---------------------*/

// Modulo Multiplicative Inverse : binexp(a,M-2,M) : if M is prime
// (a^b)%M = a^(b%(M-1))%M -> if M is prime

int binexp(int a, int b, int m)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res * 1ll * a) % m;
        }
        a = (a * 1ll * a) % m;
        b >>= 1;
    }
    return res;
}
int binmul(int a, int b, int m)
{
    int res = 0;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res + a) % m;
        }
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}

/*---------------------INPUT/OUTPUT---------------------*/

template <typename typA>
istream &operator>>(istream &cin, vector<typA> &v)
{
    for (auto &x : v)
    {
        cin >> x;
    }
    return cin;
}
template <typename typA>
ostream &operator<<(ostream &cout, vector<typA> &v)
{
    for (auto &x : v)
    {
        cout << x << " ";
    }
    cout << "\n";
    return cout;
}
template <typename typA, typename typB>
istream &operator>>(istream &cin, vector<pair<typA, typB>> &v)
{
    int i = 0;
    for (auto &x : v)
    {
        cin >> x.first;
        cin >> x.second;
        // x.second=i;
        i++;
    }
    return cin;
}
template <typename typA, typename typB>
ostream &operator<<(ostream &cout, vector<pair<typA, typB>> &v)
{
    for (auto &x : v)
    {
        cout << x.first << " " << x.second << endl;
    }
    return cout;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tt = 1;
    // cin >> tt;
    while (tt--)
    {
        int n, m;
        cin >> n;
        vector<int> v(n);
        cin >> v;
        vector<int>idx(n,0);
        for(int i=0;i<n;i++){
            idx[v[i]-1]=i;
        }
        int cnt=0;
        for(int i=1;i<n;i++){
            if(idx[i]<idx[i-1]){
                cnt++;
            }
        }
        cout<<cnt+1<<endl;

    }
    return 0;
}
