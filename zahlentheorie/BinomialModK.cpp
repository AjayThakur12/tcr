// calculate (product_{i=1,i%p!=0}^n i) % p^e. cnt is the exponent of p in n!
// Time: p^e + log(p, n)
int get_part_of_fac_n_mod_pe(int n, int p, int mod, int *upto, int &cnt) {
	if (n < p) { cnt = 0; return upto[n];}
	else {
		int res = PowerMod(upto[mod], n / mod, mod);
		res = (LL) res * upto[n % mod] % mod;
		res = (LL) res * get_part_of_fac_n_mod_pe(n / p, p, mod, upto, cnt)
				% mod;
		cnt += n / p;
		return res;
	}
}
//C(n,k) % p^e.  Use Chinese Remainder Theorem to get C(n,k)%m
int get_n_choose_k_mod_pe(int n, int k, int p, int mod) {
	static int upto[maxm + 1];
	upto[0] = 1 % mod;
	for (int i = 1; i <= mod; ++i)
		upto[i] = i % p ? (LL) upto[i - 1] * i % mod : upto[i - 1];
	int cnt1, cnt2, cnt3;
	int a = get_part_of_fac_n_mod_pe(n, p, mod, upto, cnt1);
	int b = get_part_of_fac_n_mod_pe(k, p, mod, upto, cnt2);
	int c = get_part_of_fac_n_mod_pe(n - k, p, mod, upto, cnt3);
	int res = (LL) a * inv(b, mod) % mod * inv(c, mod) % mod * PowerMod(p, cnt1 - cnt2 - cnt3, mod) % mod;
	return res;
}