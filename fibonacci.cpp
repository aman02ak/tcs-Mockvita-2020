#include<bits/stdc++.h>
#include<string>
#include<sstream>
#include<set>
using namespace std;

typedef long long int ll;
typedef vector<vector<ll>> matrix;

matrix mul(matrix A, matrix B);
matrix pow(matrix A, ll p);
ll fib(ll n, ll f1, ll f2);

bool checkPrime(int x)
{
	for(int i = 2; i <= x/2; i++)
		if(x%i == 0)
			return false;

	return true;
}

int conca(int n1, int n2)
{
	stringstream ss;
	ss << n1;
	string a = ss.str(); // string to int
	stringstream ss1;
	ss1 << n2;
	string b = ss1.str();
	string c = a+b;
	
	stringstream geek(c);  // int to string
	int x;
	geek >> x;
	return x;
}

void solve()
{
	int n1, n2;
	cin >> n1 >> n2;
	vector<int> prime1(n2-n1);
	int count = 0;

	for(int x = n1; x < n2; x++)
	{
		if(checkPrime(x))
			prime1[count++] = x;
	}

	set<int> prime2;
	for(int i = 0; i < count; i++)
	{
		for(int j = 0; j < count; j++)
		{
			if(prime1[i] != prime1[j])
			{
				int x = conca(prime1[i], prime1[j]);
				if(checkPrime(x))
					prime2.insert(x);
			}
		}
	}
	auto it = prime2.begin();
	int max = *prime2.begin();
	int min = *prime2.begin();
	int n = 0;
	for(it = prime2.begin(); it != prime2.end(); it++)
	{
		n++;
		if(max < *it)
			max = *it;
		if(min > *it)
			min = *it;
	}

	
	//cout << min << ' ' << max << ' ' << n << endl;
	ll ans = fib(n-1, min, max);
	cout << ans;
}

void call();
int main()
{
	call();
	int t;
	cin >> t;
	while(t--)
	{
		solve();
		if(t != 0)
			cout << endl;
	}
	return 0;
}

void call()
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
}

matrix pow(matrix A, ll p)
{
	if(p == 1)
		return A;
	matrix temp;
	if(p%2 == 0)
	{
		temp = pow(A, p/2);
		temp = mul(temp, temp);
	}
	else
	{
		temp = pow(A, (p-1)/2);
		temp = mul(temp, temp);
		temp = mul(temp, A);
	}
	return temp;
}

matrix mul(matrix A, matrix B)
{
	matrix C(2, vector<ll>(2));
	for(int i = 0; i<2; i++)
		for(int j = 0; j < 2; j++)
			for(int k = 0; k < 2; k++)
				C[i][j] += A[i][k]*B[k][j];

	return C;
}

ll fib(ll n, ll f1, ll f2)
{
	if(n == 0 || n == 1)
		return 1;

	matrix T(2, vector<ll>(2));
	T[0][0] = 0, T[0][1] = 1;
	T[1][0] = 1, T[1][1] = 1;

	T = pow(T, n-1);
	return (f1*T[1][0]+f2*T[1][1]);
}
