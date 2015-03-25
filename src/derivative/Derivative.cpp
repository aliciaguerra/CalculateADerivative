#include <iostream>

using namespace std;

class Var;

class Base {
public:
  virtual ~Base() {};
  virtual const Base *clone() = 0;
  virtual const Base *d(const string &v) const = 0;
  virtual ostream &print(ostream &o) const = 0;
};

ostream &operator<<(ostream &o, const Base &e) { e.print(o); return o; }

class Int : public Base {
  const int n;
public:
  Int(int m) : n(m) {}
  ~Int() {}
  const Base *clone() { return new Int(n); }
  const Base *d(const string &v) const { return new Int(0); }
  ostream &print(ostream &o) const { return o << n; }
};

class Var : public Base {
  const string var;
public:
  Var(string v) : var(v) {}
  ~Var() {}
  const Base *clone() { return new Var(var); }
  const Base *d(const string &v) const { return new Int(var == v ? 1 : 0); }
  ostream &print(ostream &o) const { return o << var; }
};

class Plus : public Base {
  const Base *e1, *e2;
public:
  Plus(const Base *a, const Base *b) : e1(a), e2(b) {}
  ~Plus() { delete e1; delete e2; }
  const Base *clone() { return new Plus(e1, e2); }
  const Base *d(const string &v) const { return new Plus(e1->d(v), e2->d(v)); }
  ostream &print(ostream &o) const
  { return o << "(" << *e1 << " + " << *e2 << ")"; }
};

class Times : public Base {
  const Base *e1, *e2;
public:
  Times(const Base *a, const Base *b) : e1(a), e2(b) {}
  ~Times() { delete e1; delete e2; }
  const Base *clone() { return new Times(e1, e2); }
  const Base *d(const string &v) const
  { return new Plus(new Times(e1, e2->d(v)), new Times(e1->d(v), e2)); }
  ostream &print(ostream &o) const { return o << "(" << *e1 << " * " << *e2 << ")"; }
};

class Expr {
public:
  Base *e;
  Expr(Base *a) : e(a) {}
};

const Expr operator+(const Expr e1, const Expr e2)
{ return Expr(new Plus(e1.e->clone(), e2.e->clone())); }
const Expr operator*(const Expr e1, const Expr e2)
{ return Expr(new Times(e1.e->clone(), e2.e->clone())); }

ostream &operator<<(ostream &o, const Expr e) { return o << e.e; }

int main() {
  Var vx("x"), va("a"), vb("b"), vc("c");
  Expr x(&vx), a(&va), b(&vb), c(&vc);
  Expr e = a*x*x + b*x + c;
  cout << "d(" << *(e.e) << ", x) = " << *(e.e->d("x")) << endl;
  return 0;
}
