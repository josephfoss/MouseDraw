#include "MouseDraw.h"

MouseDraw::MouseDraw()
{
	point = { 0,0 };
	mouseBoundCoords = { {0,0}, {0,0} };
	mouseBounds = { 0,0 };
	horizontalRes = 0;
	verticalRes = 0;
	verticalOffset = 0;
	horizontalOffset = 0;
}

ostream& operator<<(ostream& os, const Coord& c)
{
	os << "(" << c.x << ", " << c.y << ")";
	return os;
}

bool operator!=(const Coord& c1, const Coord& c2)
{

	if (c1.x == c2.x && c1.y == c2.y)
	{
		return false;
	}
	else
	{
		return true;
	}
}


/*
	//		CursFunc Functions		//
	//								//
*/
Coord MouseDraw::getBounds()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	horizontalRes = desktop.right;
	verticalRes = desktop.bottom;

	return { desktop.right, -desktop.bottom };
}

Coord MouseDraw::GetMouseCoord()
{
	GetCursorPos(&point);

	return { point.x, point.y };
}

void MouseDraw::CurrCoords()
{
	cout << "(" << point.x << ", " << point.y << ")";
}


/*
	//		MouseDraw Functions		//
	//								//
*/
dCoord MouseDraw::Cardioid(double& x, double& y, double& t, double z)
{
	x = z * (1 - cos(t)) * cos(t);
	y = z * sin(t) * (1 - cos(t));

	t++;
	return { x, y };
}

dCoord MouseDraw::Circle(double& x, double& y, double& t, double z)
{
	x = z * cos(t);
	y = z * sin(t);
	t++;

	return { x, y };
}

dCoord MouseDraw::Spiro(double& x, double& y, double& t, double z)
{
	x = z * sin(2 * t);
	y = z * sin(3 * t);
	t++;

	return { x, y };
}

dCoord MouseDraw::Spiro2(double& x, double& y, double& t, double z)
{
	x = (z * cos(t) + 65 * cos(-.35 * t));
	y = (z * sin(t) - 65 * sin(-.35 * t));

	t++;
	return { x, y };
}

dCoord MouseDraw::Spiro3(double& x, double& y, double& t, double z)
{
	x = (75 - 30) * cos(t) + 85 * cos((75 - 30) * t / -30);
	y = (75 - 30) * sin(t) + 85 * sin((75 - 30) * t / -30);

	t++;
	return { x, y };
}

dCoord MouseDraw::SinWave(double& x, double& y, double& t, double z)
{
	y = z * (sin(t * (3.1415 / 180)));

	t++;
	return { t, y };
}

void MouseDraw::Draw(int s)
{
	bool flip = false, mode = true;
	double x = 0, y = 0, z = 100, t = 0;
	string shapes[] = { "Cardioid", "Circle", "Spirograph 1", "Spirograph 2" , "Spirograph 3", "Sin Wave" };

	while (!GetKeyState('L'))
	{
		pointBeforeDraw = GetMouseCoord();

		int curposx = 0;
		int curposy = 0;
		int lastposx = 0;
		int lastposy = 0;

		if (GetKeyState(0x68) & 0x8000)
		{
			z += 5;
			cout << "Size: " << z << endl;
			Sleep(100);
		}
		if (GetKeyState(0x62) & 0x8000)
		{
			z -= 5;
			cout << "Size: " << z << endl;
			Sleep(100);
		}
		if (GetKeyState(0x64) & 0x8000)
		{
			if (s > 0)
			{
				s--;
				cout << "Shape Mode: " << shapes[s] << endl;
			}
			Sleep(100);
		}
		if (GetKeyState(0x66) & 0x8000)
		{
			if (s < 5)
			{
				s++;
				cout << "Shape Mode: " << shapes[s] << endl;
			}
			Sleep(100);
		}


		while (GetKeyState('P') & 0x8000)
		{
			flip = true;

			if (s == 0)
			{
				curposx = Cardioid(x, y, t, z).x;
				curposy = Cardioid(x, y, t, z).y;
			}
			else if (s == 1)
			{
				curposx = Circle(x, y, t, z).x;
				curposy = Circle(x, y, t, z).y;

			}
			else if (s == 2)
			{
				curposx = Spiro(x, y, t, z).x;
				curposy = Spiro(x, y, t, z).y;
			}
			else if (s == 3)
			{
				curposx = Spiro2(x, y, t, z).x;
				curposy = Spiro2(x, y, t, z).y;
			}
			else if (s == 4)
			{
				curposx = Spiro3(x, y, t, z).x;
				curposy = Spiro3(x, y, t, z).y;
			}
			else if (s == 5)
			{
				curposx = SinWave(x, y, t, z).x;
				curposy = SinWave(x, y, t, z).y;
			}

			int xslope = curposx - lastposx;
			int yslope = curposy - lastposy;

			SetCursorPos(GetMouseCoord().x + xslope, GetMouseCoord().y + yslope);

			Sleep(150);

			lastposx = curposx;
			lastposy = curposy;

		}

		if (flip)
		{
			SetCursorPos(pointBeforeDraw.x, pointBeforeDraw.y);
			flip = false;
		}

		x = 0;
		y = 0;
		t = 0;
	}

}