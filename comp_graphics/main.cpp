#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>

int w = 1280;
int h = 1024;


double points[7][3] = {
	{ 0.5, -0.8660254037844386, 0.0},
	{ 1.0, 0.0, 0.0 },
	{ 0.5, 0.8660254037844386, 0.0 },
	{ -0.5, 0.8660254037844386, 0.0 },
	{ -1.0, 0.0, 0.0 },
	{ -0.5, -0.8660254037844386, 0.0 },
	{ 0.0, 0.0, 2.0 }
};

double newPoints[7][3] = {};

double points2d[7][2] = {};

double edges[12][4] = {};


int rotX = 0, rotY = 0, rotZ = 0;   // углы поворота по X,Y,Z в градусах
double shiftX = 0.0, shiftY = 0.0;    // сдвиг начала координат
unsigned int scale = 100;

void perspective(double points2d[7][2], double points[7][3]) {
	for (int i = 0; i < 7; i++) {
		points2d[i][0] = points[i][0] + points[i][2] / 2;
		points2d[i][1] = points[i][1] - points[i][2] / 2;
	}
}

// 3-D преобразования
void compute()
{
	double sinx = sin((rotX * M_PI) / 180.0);
	double siny = sin((rotY * M_PI) / 180.0);
	double sinz = sin((rotZ * M_PI) / 180.0);
	double cosx = cos((rotX * M_PI) / 180.0);
	double cosy = cos((rotY * M_PI) / 180.0);
	double cosz = cos((rotZ * M_PI) / 180.0);
	double x, y, z, x1, y1, z1;
	for (int i = 0; i < 7; i++)
	{
		x = points[i][0];   //Исходное направление
		y = points[i][1];
		z = points[i][2];

		x1 = x * cosz + y * sinz;       // вокруг Z
		y1 = -x * sinz + y * cosz;
		z1 = z;

		x = x1;                     // вокруг X
		y = y1 * cosx + z1 * sinx;
		z = -y1 * sinx + z1 * cosx;

		x1 = x * cosy - z * siny;       // вокруг Y
		y1 = y;
		z1 = x * siny + z * cosy;

		newPoints[i][0] = x1;// *scale;    // Масштабирование
		newPoints[i][1] = y1;// *scale;
		newPoints[i][2] = z1;// *scale;


		//points[i][0] += shiftX;     // сдвиг по осям X и Y
		//points[i][1] += shiftY;
		//points[i][2] += 0;
	}

	perspective(points2d, newPoints);

	for (int i = 0; i < 7; i++)
	{
		points2d[i][0] += shiftX;     // сдвиг по осям X и Y
		points2d[i][1] += shiftY;
	}

}


void draw_line(double points2d[7][2], unsigned int scale) {
	
	
	

	glBegin(GL_LINES);
	glColor3d(0, 0, 0);
	glVertex2d(points2d[0][0] * scale, points2d[0][1] * scale);
	glVertex2d(points2d[1][0] * scale, points2d[1][1] * scale);

	glColor3d(0, 1, 0);
	glVertex2d(points2d[1][0] * scale, points2d[1][1] * scale);
	glVertex2d(points2d[2][0] * scale, points2d[2][1] * scale);

	glColor3d(0, 1, 1);
	glVertex2d(points2d[2][0] * scale, points2d[2][1] * scale);
	glVertex2d(points2d[3][0] * scale, points2d[3][1] * scale);

	glColor3d(1, 0, 0);
	glVertex2d(points2d[3][0] * scale, points2d[3][1] * scale);
	glVertex2d(points2d[4][0] * scale, points2d[4][1] * scale);

	glColor3d(1, 0, 1);
	glVertex2d(points2d[4][0] * scale, points2d[4][1] * scale);
	glVertex2d(points2d[5][0] * scale, points2d[5][1] * scale);

	glColor3d(1, 1, 0);
	glVertex2d(points2d[5][0] * scale, points2d[5][1] * scale);
	glVertex2d(points2d[0][0] * scale, points2d[0][1] * scale);


	glColor3d(1, 1, 1);
	glVertex2d(points2d[6][0] * scale, points2d[6][1] * scale);
	glVertex2d(points2d[0][0] * scale, points2d[0][1] * scale);

	glColor3d(0, 0.5, 0.5);
	glVertex2d(points2d[6][0] * scale, points2d[6][1] * scale);
	glVertex2d(points2d[1][0] * scale, points2d[1][1] * scale);

	glColor3d(0.5, 0.5, 0);
	glVertex2d(points2d[6][0] * scale, points2d[6][1] * scale);
	glVertex2d(points2d[2][0] * scale, points2d[2][1] * scale);

	glColor3d(0.5, 0.5, 0.5);
	glVertex2d(points2d[6][0] * scale, points2d[6][1] * scale);
	glVertex2d(points2d[3][0] * scale, points2d[3][1] * scale);

	glColor3d(0.5, 0.0, 0.5);
	glVertex2d(points2d[6][0] * scale, points2d[6][1] * scale);
	glVertex2d(points2d[4][0] * scale, points2d[4][1] * scale);

	glColor3d(0.8, 0.0, 0.8);
	glVertex2d(points2d[6][0] * scale, points2d[6][1] * scale);
	glVertex2d(points2d[5][0] * scale, points2d[5][1] * scale);

	glEnd();

	//glBegin(GL_POINTS);
	//
	//glVertex2d(points2d[0][0] * scale, points2d[0][1] * scale);// 1 точка

	//
	//glVertex2d(points2d[1][0] * scale, points2d[1][1] * scale);// 2 точка

	//
	//glVertex2d(points2d[2][0] * scale, points2d[2][1] * scale);// 3 точка

	//
	//glVertex2d(points2d[3][0] * scale, points2d[3][1] * scale);// 4 точка

	//
	//glVertex2d(points2d[4][0] * scale, points2d[4][1] * scale);// 5 точка

	//
	//glVertex2d(points2d[5][0] * scale, points2d[5][1] * scale);// 6 точка

	//
	//glVertex2d(points2d[6][0] * scale, points2d[6][1] * scale);// 7 точка

	//glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 1.0f, 0.0f);

	compute();
	
	draw_line(points2d, scale);

	glFlush();
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case ']':
		scale += 1;
		break;
	case '[':
		scale -= 1;
		break;
	case 'z':
		if (rotZ < 357) {
			rotZ += 3;
		}
		else { rotZ = 0; }
		break;
	case 'x':
		// полный круг 360 градусов
		if (rotX < 357) { rotX += 3; }
		else { rotX = 0; } // 360 это 0
		break;
	case 'y':
		if (rotY < 357) { rotY += 3; }
		else { rotY = 0; }
		break;
	default:
		break;
	}
	return;
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		shiftX -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		shiftX += 0.1;
		break;
	case GLUT_KEY_UP:
		shiftY += 0.1;
		break;
	case GLUT_KEY_DOWN:
		shiftY -= 0.1;
		break;
	}
	return;
}

void timer(int = 0) {
	display();
	glutTimerFunc(2, timer, 0);                   //??п??и??е? (этого я не смог расшифровать)
}



int main(int argc, char** argv) {
	

	HWND hWnd = GetForegroundWindow(); // получаем дескриптор окна

	ShowWindow(hWnd, SW_HIDE); // прячем консоль

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);

	glutCreateWindow("comp_graphics");
	glutPositionWindow((GetSystemMetrics(SM_CXSCREEN) - w) / 2, (GetSystemMetrics(SM_CYSCREEN) - h) / 2);
	glClearColor(0.0, 0.2, 0.4, 1.0); // цвет фона
	hWnd = FindWindowA(NULL, "comp_graphics"); // получаем дескриптор окна
	SetWindowLongPtr(hWnd, GWL_STYLE, (GetWindowLong(hWnd, GWL_STYLE) ^ WS_SIZEBOX) ^ WS_MAXIMIZEBOX); // фиксируем размер окна
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);

	

	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutTimerFunc(50, timer, 0);
	glutMainLoop();


	return 0;
}