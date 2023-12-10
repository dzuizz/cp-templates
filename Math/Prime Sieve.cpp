// Prime Sieve of Eratosthenes
// https://codebreaker.xyz/problem/nprime

#include <bits/stdc++.h>
using namespace std;

#define int long long

int sieve[(int) 2e7]; // 0 -> Prime, 1 -> Not Prime
vector<int> primes; // 0-based indexing

signed main() {
    sieve[0] = sieve[1] = 1;
    for (int i = 2; i < (int) 2e7; i++) {
        if (sieve[i]) continue;
        primes.push_back(i);

        for (int j = i * i; j < (int) 2e7; j += i)
            sieve[j] = 1;
    }

    int n; cin >> n;
    cout << primes[n-1] << '\n';
}