// カルダノの公式を用いて三次方程式 ax^3+bx^2+cx+d=0 を解く 

//三次方程式 ax^3+bx^2+cx+d=0を解く 
double ans1=0, ans2=0, ans3=0;
void cardano(double a, double b, double c, double d){
	double p, q, t, a3, b3, x1, x2, x3;
	b /= (3*a); c /= a; d /= a;
	p = b*b - c/3;
	q = (b*(c - 2*b*b) - d)/2;
	a = q*q - p*p*p;
	if(a == 0){
		q = cbrt(q); x1 = 2*q - b; x2 = -q - b;
		cout << "x=" << x1 << ", " << x2 << "(重解)" << endl;
		ans1 = x1; ans2 = x2;
	}else if(a > 0){
		if(q > 0) a3 = cbrt(q + sqrt(a));
		else   a3 = cbrt(q - sqrt(a));
		b3 = p/a3;
		x1 = a3 + b3 - b; x2 = -0.5 + (a3 + b3) - b;
		x3 = fabs(a3 - b3)*sqrt(3.0)/2;
		cout << "x=" << x1 << "; " << x2 << "+- " << x3 << "i" << endl;
		ans1 = x1; ans2 = x2; ans3 = x3;
	}else{
		a = sqrt(p); t = acos(q/(p*a)); a *= 2;
		x1 = a*cos(t/3) - b;
		x2 = a*cos((t+2*M_PI)/3) - b;
		x3 = a*cos((t+4*M_PI)/3) - b;
		cout << "x=" << x1 << ", " << x2 << ", " << x3 << endl;
		ans1 = x1; ans2 = x2; ans3 = x3;
	}
}
