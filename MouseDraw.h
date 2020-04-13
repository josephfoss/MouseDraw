#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <wtypes.h>
#include <math.h>

using namespace std;

struct Coord {
	int x;
	int y;
};
struct dCoord {
	double x;
	double y;
};
struct dCoord4
{
	double x;
	double y;
	double z;
	double t;
};
struct CoordSys
{
	Coord pos1;
	Coord pos2;
};

class MouseDraw
{
	friend class CursFunc;
	friend ostream& operator<<(ostream& os, const Coord& c);
	friend bool operator!=(const Coord& c1, const Coord& c2);

	private:
		//CursFunc
		POINT point;
		CoordSys mouseBoundCoords;
		Coord mouseBounds;
		Coord pointBeforeDraw;
		int horizontalRes;
		int verticalRes;

		//MouseDraw
		dCoord Cardioid(double& x, double& y, double& t, double z);
		dCoord Circle (double& x, double& y, double& t, double z);
		dCoord Spiro(double& x, double& y, double& t, double z);
		dCoord Spiro2(double& x, double& y, double& t, double z);
		dCoord Spiro3(double& x, double& y, double& t, double z);
		dCoord SinWave(double& x, double& y, double& t, double z);
		int verticalOffset;
		int horizontalOffset;

	public:
		//constructor
		MouseDraw();

		//CursFunc
		Coord getBounds();
		Coord GetMouseCoord();

		void CurrCoords();

		//MouseDraw
		void Draw(int);
};

