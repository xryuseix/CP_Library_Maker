// ユークリッドの互除法

ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a;}
