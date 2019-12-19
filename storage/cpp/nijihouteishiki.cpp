// 二次方程式の解を求める

/*
	aX^2+bX+c=0の解を求める
	出力はこんな感じ
	if(x1 == DBL_MIN)cout<<"解なし"<<endl;
	else if(x1==DBL_MAX)cout<<"不定"<<endl;
	else if(!i)cout<<x1<<" , "<<x2<<endl;
	else cout<<x1<<" +- "<<x2<<"i"<<endl;
*/
double x1, x2;
bool i = false;
void quadeq(double a, double b, double c){
	double d, x;
	if(a != 0){
		b /= a; c /= a;
		if(c != 0){
			b /= 2;
			d = b*b - c;
			if(d > 0){
				if(b > 0) x = -b - sqrt(d);
				else x = -b + sqrt(d);
				x1 = x; x2 = c/x;
			}else if(d < 0){
				x1 = -b; x2 = sqrt(-d); i = true;
			}else{
				x1 = x2 = -b;
			}
		}else{
			x1 = -b; x2 = 0;
		}
	}else if(b != 0){
		x1 = x2 = -c/b;
	}
	else if(c != 0) x1 = x2 = DBL_MIN;
	else x1 = x2 = DBL_MAX;
}
