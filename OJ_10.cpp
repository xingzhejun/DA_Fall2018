﻿#include <stdio.h>
#include <map>
#include <queue>
#include <stack>
#define M
#pragma warning(disable:4996)
using namespace std;

typedef unsigned long long Codetype;

enum operation { F1, F2, F3, R1, R2, R3, U1, U2, U3, END };

void swap(short &a, short &b) {
	short tmp = a; a = b; b = tmp;
}

Codetype power(int x, int y)
{
	Codetype result = 1;
	for (int i = 0;i < y;i++)
		result *= x;
	return result;
}

Codetype encrypt(short *a)
{
	Codetype code = 0;
	for (int i = 0;i < 24;i++)
		code += a[i] * power(6, i);
	return code;
}

void rotate_f(Codetype &key, int a, int b, int c, int d) //(a, b, c, d) --> (d, a, b, c)
{
	short xa, xb, xc, xd;
	xa = (key%power(6, a + 1)) / power(6, a);
	xb = (key%power(6, b + 1)) / power(6, b);
	xc = (key%power(6, c + 1)) / power(6, c);
	xd = (key%power(6, d + 1)) / power(6, d);
	key -= (xa*power(6, a) + xb * power(6, b) + xc * power(6, c) + xd * power(6, d));
	key += (xa*power(6, b) + xb * power(6, c) + xc * power(6, d) + xd * power(6, a));
}

void rotate_b(Codetype &key, int a, int b, int c, int d, int e, int f, int g, int h) { // (a1, a2, ..., a8) --> (a7, a8, a1, a2, ..., a6)
	short xa, xb, xc, xd, xe, xf, xg, xh;
	xa = (key%power(6, a + 1)) / power(6, a);
	xb = (key%power(6, b + 1)) / power(6, b);
	xc = (key%power(6, c + 1)) / power(6, c);
	xd = (key%power(6, d + 1)) / power(6, d);
	xe = (key%power(6, e + 1)) / power(6, e);
	xf = (key%power(6, f + 1)) / power(6, f);
	xg = (key%power(6, g + 1)) / power(6, g);
	xh = (key%power(6, h + 1)) / power(6, h);
	key -= (xa*power(6, a) + xb * power(6, b) + xc * power(6, c) + xd * power(6, d) + xe * power(6, e) + xf * power(6, f) + xg * power(6, g) + xh * power(6, h));
	key += (xa*power(6, c) + xb * power(6, d) + xc * power(6, e) + xd * power(6, f) + xe * power(6, g) + xf * power(6, h) + xg * power(6, a) + xh * power(6, b));
}

Codetype F(Codetype key) //
{
	rotate_f(key, 0, 3, 9, 6);
	rotate_b(key, 2, 4, 5, 10, 11, 7, 8, 1);
	return key;
}

Codetype R(Codetype key) //
{
	rotate_f(key, 5, 16, 23, 10);
	rotate_b(key, 4, 17, 15, 21, 22, 11, 9, 3);
	return key;
}

Codetype U(Codetype key) //
{
	rotate_f(key, 13, 17, 4, 2);
	rotate_b(key, 12, 15, 16, 5, 3, 0, 1, 14);
	return key;
}

Codetype operate(Codetype key, operation x)
{
	switch (x)
	{
	case 0:return F(key);
	case 1:return F(F(key));
	case 2:return F(F(F(key)));
	case 3:return R(key);
	case 4:return R(R(key));
	case 5:return R(R(R(key)));
	case 6:return U(key);
	case 7:return U(U(key));
	case 8:return U(U(U(key)));
	default:return 0;
	}
}

void operate_a(short *a, operation opr) {
	switch (opr) {
	case F1:
		swap(a[7], a[1]); swap(a[11], a[8]); swap(a[10], a[7]); swap(a[5], a[11]); swap(a[4], a[10]); swap(a[2], a[5]);
		swap(a[3], a[6]); swap(a[0], a[3]); swap(a[9], a[6]); break;
	case F2:
		swap(a[2], a[11]); swap(a[4], a[7]); swap(a[1], a[10]); swap(a[5], a[8]);
		swap(a[3], a[6]); swap(a[0], a[9]); break;
	case F3:
		swap(a[2], a[5]); swap(a[4], a[10]); swap(a[5], a[11]); swap(a[10], a[7]); swap(a[11], a[8]); swap(a[7], a[1]);
		swap(a[0], a[9]); swap(a[0], a[3]); swap(a[9], a[6]); break;
	case R1:
		swap(a[11], a[3]); swap(a[22], a[9]); swap(a[21], a[11]); swap(a[15], a[22]); swap(a[17], a[21]); swap(a[4], a[15]);
		swap(a[16], a[10]); swap(a[5], a[16]); swap(a[23], a[10]); break;
	case R2:
		swap(a[4], a[22]); swap(a[17], a[11]); swap(a[3], a[21]); swap(a[15], a[9]);
		swap(a[16], a[10]); swap(a[5], a[23]); break;
	case R3:
		swap(a[4], a[15]); swap(a[17], a[21]); swap(a[15], a[22]); swap(a[21], a[11]); swap(a[22], a[9]); swap(a[11], a[3]);
		swap(a[5], a[23]); swap(a[5], a[16]); swap(a[23], a[10]); break;
	case U1:
		swap(a[0], a[14]); swap(a[3], a[1]); swap(a[5], a[0]); swap(a[16], a[3]); swap(a[15], a[5]); swap(a[12], a[16]);
		swap(a[17], a[2]); swap(a[13], a[17]); swap(a[4], a[2]); break;
	case U2:
		swap(a[12], a[3]); swap(a[15], a[0]); swap(a[14], a[5]); swap(a[1], a[16]);
		swap(a[13], a[4]); swap(a[2], a[17]); break;
	case U3:
		swap(a[12], a[16]); swap(a[15], a[5]); swap(a[16], a[3]); swap(a[5], a[0]); swap(a[3], a[1]); swap(a[0], a[14]);
		swap(a[13], a[4]); swap(a[13], a[17]); swap(a[4], a[2]); break;
	default:;
	}
}

void show(operation x)
{
	switch (x)
	{
	case 0: {printf("F+\n");break;}
	case 1: {printf("F2\n");break;}
	case 2: {printf("F-\n");break;}
	case 3: {printf("R+\n");break;}
	case 4: {printf("R2\n");break;}
	case 5: {printf("R-\n");break;}
	case 6: {printf("U+\n");break;}
	case 7: {printf("U2\n");break;}
	case 8: {printf("U-\n");break;}
	}
}

void output(short *a) {
	for (short i = 0; i < 24; i++) {
		printf("%hd", a[i]);
		if (i < 23) printf(" ");
	}
	printf("\n");
}

void showsolution(map<Codetype, operation> &Ms, map<Codetype, operation> &Mf, Codetype a, Codetype b, operation x, short *a_s)
{
	stack<operation> s;
	queue<operation> final_s;
	Codetype key = a;
	map<Codetype, operation>::iterator p = Ms.find(a);
	operation o = p->second;
	while (o != END)
	{
		if (o < 3)
			s.push(operation(2 - o));
		if (o > 2 && o < 6)
			s.push(operation(8 - o));
		if (o > 5)
			s.push(operation(14 - o));
		key = operate(key, o);
		p = Ms.find(key);
		o = p->second;
	}
	while (!s.empty())
	{
		final_s.push(s.top());
		s.pop();
	}
	final_s.push(x);
	key = b;
	p = Mf.find(b);
	while (p->second != END)
	{
		final_s.push(p->second);
		key = operate(key, p->second);
		p = Mf.find(key);
	}
	while (!final_s.empty()) {
		show(final_s.front());
		operate_a(a_s, final_s.front());
		final_s.pop();
		output(a_s);
	}
}


#ifdef M
int main()
{
	short a[24];
	int i;
	for (i = 0;i < 24;i++)
		scanf("%hd", &a[i]);
	short a_e[24];
	for (i = 0; i < 24; i++) {
		switch (a[i])
		{
		case 0:case 3:case 6:case 9: {a_e[i] = 0;break;}
		case 2:case 4:case 13:case 17: {a_e[i] = 1;break;}
		case 5:case 16:case 23:case 10: {a_e[i] = 2;break;}
		case 1:case 8:case 14:case 19: {a_e[i] = 3;break;}
		case 12:case 15:case 18:case 21: {a_e[i] = 4;break;}
		case 11:case 22:case 20:case 7: {a_e[i] = 5;break;}
		}
	}
	Codetype start = encrypt(a_e);
	Codetype finish = 2345856587547959430;
	map<Codetype, operation> Maps, Mapf;
	map<Codetype, operation>::iterator p;
	operation x;
	queue<Codetype> Qs;
	Maps.insert(pair<Codetype, operation>(start, END));
	Qs.push(start);
	if (Maps.count(finish))
	{
		printf("0");
		return 0;
	}
	int step = 1;
	queue<Codetype> Qf;
	Mapf.insert(pair<Codetype, operation>(finish, END));
	Qf.push(finish);
	Codetype tempkey, curkey, flags = start, flagf = finish;
	while (true)
	{
		do
		{
			tempkey = curkey = Qs.front();
			Qs.pop();
			p = Maps.find(curkey);
			if (p != Maps.end())
			{
				x = p->second;
				if (x > 2)
				{
					for (i = 0;i < 3;i++)
					{
						curkey = F(curkey);
						if (Maps.count(curkey))
							continue;
						if (!Mapf.count(curkey))
						{
							Maps.insert(pair<Codetype, operation>(curkey, operation(2 - i)));
							Qs.push(curkey);
						}
						else
						{
							printf("%d\n", step);
							showsolution(Maps, Mapf, tempkey, curkey, operation(i), a);
							return 0;
						}
					}
					curkey = F(curkey);
				}
				if (x < 3 || x>5)
				{
					for (i = 0;i < 3;i++)
					{
						curkey = R(curkey);
						if (Maps.count(curkey))
							continue;
						if (!Mapf.count(curkey))
						{
							Maps.insert(pair<Codetype, operation>(curkey, operation(5 - i)));
							Qs.push(curkey);
						}
						else
						{
							printf("%d\n", step);
							showsolution(Maps, Mapf, tempkey, curkey, operation(i + 3), a);
							return 0;
						}
					}
					curkey = R(curkey);
				}
				if (x < 6 || x>8)
				{
					for (i = 0;i < 3;i++)
					{
						curkey = U(curkey);
						if (Maps.count(curkey))
							continue;
						if (!Mapf.count(curkey))
						{
							Maps.insert(pair<Codetype, operation>(curkey, operation(8 - i)));
							Qs.push(curkey);
						}
						else
						{
							printf("%d\n", step);
							showsolution(Maps, Mapf, tempkey, curkey, operation(i + 6), a);
							return 0;
						}
					}
					curkey = U(curkey);
				}
			}
		} while (tempkey != flags);
		flags = Qs.back();
		step++;
		do
		{
			tempkey = curkey = Qf.front();
			Qf.pop();
			p = Mapf.find(curkey);
			if (p != Mapf.end())
			{
				x = p->second;
				if (x > 2)
				{
					for (i = 0;i < 3;i++)
					{
						curkey = F(curkey);
						if (Mapf.count(curkey))
							continue;
						if (!Maps.count(curkey))
						{
							Mapf.insert(pair<Codetype, operation>(curkey, operation(2 - i)));
							Qf.push(curkey);
						}
						else
						{
							printf("%d\n", step);
							showsolution(Maps, Mapf, curkey, tempkey, operation(2 - i), a);
							return 0;
						}
					}
					curkey = F(curkey);
				}
				if (x < 3 || x>5)
				{
					for (i = 0;i < 3;i++)
					{
						curkey = R(curkey);
						if (Mapf.count(curkey))
							continue;
						if (!Maps.count(curkey))
						{
							Mapf.insert(pair<Codetype, operation>(curkey, operation(5 - i)));
							Qf.push(curkey);
						}
						else
						{
							printf("%d\n", step);
							showsolution(Maps, Mapf, curkey, tempkey, operation(5 - i), a);
							return 0;
						}
					}
					curkey = R(curkey);
				}
				if (x < 6 || x>8)
				{
					for (i = 0;i < 3;i++)
					{
						curkey = U(curkey);
						if (Mapf.count(curkey))
							continue;
						if (!Maps.count(curkey))
						{
							Mapf.insert(pair<Codetype, operation>(curkey, operation(8 - i)));
							Qf.push(curkey);
						}
						else
						{
							printf("%d\n", step);
							showsolution(Maps, Mapf, curkey, tempkey, operation(8 - i), a);
							return 0;
						}
					}
					curkey = U(curkey);
				}
			}
		} while (tempkey != flagf);
		flagf = Qf.back();
		step++;
	};
}
#endif


#ifdef GEN
int main() {
	short a[24];
	for (short i = 0; i < 24; i++) {
		a[i] = i;
	}
	operate_a(a, R1);
	operate_a(a, U1);
	operate_a(a, F1);
	operate_a(a, U3);
	operate_a(a, F2);
	operate_a(a, R3);
	output(a);
	return 0;
}
#endif

//Thank jackgxrc for his ideas.
