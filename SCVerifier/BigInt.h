#pragma once
#ifndef BIGINT_H
#define BIGINT_H

#include "stdc++.h"
using namespace std;

//Source: https://paste.ubuntu.com/10270983/ or https://codeforces.com/blog/entry/16380

typedef int64_t ll;
typedef long long ll;
typedef pair<ll, ll> lll;
typedef pair<ll, int> lli;
typedef pair<int, int> ii;

#define EL printf("\n")
#define OK printf("OK")
#define pb push_back
#define mp make_pair
#define ep emplace_back
#define X  first
#define Y  second
#define fillchar(a,x) memset(a, x, sizeof(a))
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)

const int base = 1e9;
typedef vector<int> BigInt;

void Set(BigInt & a);
string Print(BigInt a);
BigInt Integer(string s);
BigInt Integer(char c[]);
BigInt Integer(ll x);

BigInt Integer(int x);




void operator >> (istream & in, BigInt & a);

ostream& operator << (ostream & out, BigInt a);




bool operator < (BigInt a, BigInt b);

bool operator > (BigInt a, BigInt b);
bool operator == (BigInt a, BigInt b);

bool operator <= (BigInt a, BigInt b);

bool operator >= (BigInt a, BigInt b);

bool operator < (BigInt a, int b);

bool operator > (BigInt a, int b);
bool operator == (BigInt a, int b);

bool operator >= (BigInt a, int b);

bool operator <= (BigInt a, int b);



BigInt max(BigInt a, BigInt b);

BigInt min(BigInt a, BigInt b);




BigInt operator + (BigInt a, BigInt b);

BigInt operator + (BigInt a, int b);

BigInt operator ++ (BigInt& a);

void operator += (BigInt& a, BigInt b);

void operator += (BigInt& a, int b);



BigInt operator - (BigInt a, BigInt b);

BigInt operator - (BigInt a, int b);

void operator -- (BigInt& a);

void operator -= (BigInt& a, BigInt b);

void operator -= (BigInt& a, int b);




BigInt operator * (BigInt a, BigInt b);

BigInt operator * (BigInt a, int b);

void operator *= (BigInt& a, BigInt b);

void operator *= (BigInt& a, int b);



BigInt operator / (BigInt a, BigInt b);

BigInt operator / (BigInt a, int b);

void operator /= (BigInt& a, BigInt b);

void operator /= (BigInt& a, int b);



BigInt operator % (BigInt a, BigInt b);

int operator % (BigInt a, int b);

void operator %= (BigInt& a, BigInt b);

void operator %= (BigInt& a, int b);

BigInt gcd(BigInt a, BigInt b);

BigInt lcm(BigInt a, BigInt b);


BigInt sqrt(BigInt a);


BigInt pow(BigInt a, BigInt b);


BigInt pow(BigInt a, int b);

int log(int n, BigInt a);


#endif