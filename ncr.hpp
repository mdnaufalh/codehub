/*
	Notes:
		O(n) precomputation
		O(1) queries
		Use this for ansering queries of form nCr where:
			1) n is small, ideally <= 10^7
			2) p is a prime and p > n always
*/

struct nCr_queries {
	private:
	ll N, p;
	vector<ll> fact, ifact, inv;
	ll inverse(const ll& x) {
		if(x == 1) return 1;
		return ((p - p/x) * (inv[p % x] % p)) % p;
	}
	public:
	nCr_queries(ll N,ll p) {
		this->N = N;
		this->p = p;
		fact.resize(N + 1);
		ifact.resize(N + 1);
		inv.resize(N + 1);
		fact[0] = ifact[0] = 1;
		for(int i = 1; i < fact.size(); ++i) {
			fact[i] = fact[i-1] * i % p;
			inv[i] = inverse(i);
			ifact[i] = ifact[i-1] * inv[i] % p;
		}
	}

	ll query(ll n, ll r) {
 		return (fact[n] * ifact[r])%p * ifact[n-r] % p;
	}
};
