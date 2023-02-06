// Numerical_methods_for_solving_transcendental_equations.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <cmath>
#include <iostream>

using namespace std;
//Функция для полинома:
double F(double x) {
	return exp(-x) - 2 * sqrt(x);
}

double df(double x)
{
	return -exp(-x) - 1 / sqrt(x);
}

double d2f(double x) {
	return exp(-x)+1/(2*pow(x,2.0/3));
}
//Функция поиска корня:
double method_half(double (*f)(double), double a, double b, double eps) {
	double c = 0;
	while ((b - a) / 2 > eps) {
		c = (a + b) / 2;
		if ((f(a) * f(c)) > 0) a = c;
		else b = c;
	}
	return c;
}

double chord_method(double (*f)(double), double a, double b, double eps) {
	double t = 0;
	while (fabs(b - a) >= eps) {
		t = a + (f(b) * (b - a)) / (f(b) - f(a));
		if (f(a) * f(t) < 0) {
			b = t;
		}
		else if (f(t) * f(b) < 0) {
			a = t;
		}
		else
			return t;
	}
	return t;
}

double method_newton(double (*f)(double), double a, double b, double eps) {
	double x0 = 0, xn = 0;
	if (a > b) // если пользователь перепутал границы отрезка, меняем их местами
	{
		x0 = a;
		a = b;
		b = x0;
	}
	if (f(a) * f(b) > 0) // если знаки функции на краях отрезка одинаковые, то здесь нет корня
		cout << "\nError! No roots in this interval\n";
	else
	{
		if (f(a) * d2f(a) > 0) x0 = a; // для выбора начальной точки проверяем f(x0)*d2f(x0)>0 ?
		else x0 = b;
		xn = x0 - f(x0) / df(x0); // считаем первое приближение
		while (fabs(x0 - xn) > eps) // пока не достигнем необходимой точности, будет продолжать вычислять
		{
			x0 = xn;
			xn = x0 - f(x0) / df(x0); // непосредственно формула Ньютона
		}
		cout << xn << endl;
	}
	return xn;
}



int main() {
	//Интервал, погрешность и корень:
	double a, b, eps, x;
	cout << "interval: ";
	cin >> a >> b;

	//Проверка корректности интервала:
	if (F(a) * F(b) > 0) {
		cout << "Wrong interval!\n";
		return 0;
	}

	cout << "error: ";
	cin >> eps;
	//Поиск решения:
	x = method_half(F, a, b, eps);
	cout << "x = " << x << endl;
	x = chord_method(F, a, b, eps);
	cout << "x = " << x << endl;
	x = method_newton(F, a, b, eps);
	cout << "x = " << x << endl;
	return 0;
}
