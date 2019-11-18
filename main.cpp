#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

// Varia´veis globais
GLfloat angle, fAspect;
GLdouble obsX, obsY, obsZ;
GLuint idTextura;

void loadBMP(char *filename) {

	unsigned int width, height;
	unsigned char header[54];

	unsigned char * data;

	FILE * file;
	file = fopen(filename, "rb");

	if (file == NULL)
		return;

	//Leitura do cabeçalho
	if (fread(header, 1, 54, file) != 54) {
		printf("Problema ao ler cabeçalho do arquivo!\n");
		return;
	}
	width = *(int*) &(header[0x12]);
	height = *(int*) &(header[0x16]);

	data = (unsigned char *) malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i) {
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	glGenTextures(1, &idTextura);
	glBindTexture(GL_TEXTURE_2D, idTextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
	GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
}

void display(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsX, obsY, obsZ, 0, 0, 0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Desenha um cubo no qual a textura e´ aplicada
	glBegin( GL_QUADS);
	
	// Face frontal ( Textura do numero 1 )
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.5f, -0.3f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, -0.3f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	
	 //Face posterior
	 glTexCoord2f(0.0f, 0.0f);
	 glVertex3f(-1.0f, -1.0f, -1.0f);
	 glTexCoord2f(0.5f, 0.0f);
	 glVertex3f(-1.0f, 1.0f, -1.0f);
	 glTexCoord2f(0.5f, -0.3f);
   	 glVertex3f(1.0f, 1.0f, -1.0f);
	 glTexCoord2f(0.0f, -0.3f);
	 glVertex3f(1.0f, -1.0f, -1.0f);
	 
	// Face superior
	// glTexCoord2f(0.0f, 1.0f);
	// glVertex3f(-1.0f, 1.0f, -1.0f);
	// glTexCoord2f(0.0f, 0.0f);
	// glVertex3f(-1.0f, 1.0f, 1.0f);
	// glTexCoord2f(1.0f, 0.0f);
	// glVertex3f(1.0f, 1.0f, 1.0f);
	// glTexCoord2f(1.0f, 1.0f);
	// glVertex3f(1.0f, 1.0f, -1.0f);
	// Face inferior
	// glTexCoord2f(1.0f, 1.0f);
	// glVertex3f(-1.0f, -1.0f, -1.0f);
	// glTexCoord2f(0.0f, 1.0f);
	// glVertex3f(1.0f, -1.0f, -1.0f);
	// glTexCoord2f(0.0f, 0.0f);
	// glVertex3f(1.0f, -1.0f, 1.0f);
	// glTexCoord2f(1.0f, 0.0f);
	// glVertex3f(-1.0f, -1.0f, 1.0f);
	// Face lateral direita
	// glTexCoord2f(1.0f, 0.0f);
	// glVertex3f(1.0f, -1.0f, -1.0f);
	// glTexCoord2f(1.0f, 1.0f);
	// glVertex3f(1.0f, 1.0f, -1.0f);
	// glTexCoord2f(0.0f, 1.0f);
	// glVertex3f(1.0f, 1.0f, 1.0f);
	// glTexCoord2f(0.0f, 0.0f);
	// glVertex3f(1.0f, -1.0f, 1.0f);
	// Face lateral esquerda
	// glTexCoord2f(0.0f, 0.0f);
	// glVertex3f(-1.0f, -1.0f, -1.0f);
	// glTexCoord2f(1.0f, 0.0f);
	// glVertex3f(-1.0f, -1.0f, 1.0f);
	// glTexCoord2f(1.0f, 1.0f);
	// glVertex3f(-1.0f, 1.0f, 1.0f);
	// glTexCoord2f(0.0f, 1.0f);
	// glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glutSwapBuffers();
}

void init(void) {
	GLfloat luzAmbiente[4] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat luzDifusa[4] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat posicaoLuz[4] = { 0.0, -40.0, 0.0, 1.0 };

	GLfloat especularidade[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLint especMaterial = 60;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	angle = 20;
	obsX = 10;
	obsY = 10;
	obsZ = 10;

	loadBMP("dado2.bmp");
}

void configProjection(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, fAspect, 0.4, 500);
}
void resize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	fAspect = (GLfloat) w / (GLfloat) h;
	configProjection();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10)
				angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130)
				angle += 5;
		}
	configProjection();
	glutPostRedisplay();
}

void keyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		obsX -= 5;
		break;
	case GLUT_KEY_RIGHT:
		obsX += 5;
		break;
	case GLUT_KEY_UP:
		obsY += 5;
		break;
	case GLUT_KEY_DOWN:
		obsY -= 5;
		break;
	case GLUT_KEY_HOME:
		obsZ += 5;
		break;
	case GLUT_KEY_END:
		obsZ -= 5;
		break;
	case GLUT_KEY_F10: // "camera reset"
		obsX = 10;
		obsY = 10;
		obsZ = 10;
		angle = 18;
		configProjection();
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 350);
	glutCreateWindow("Mapeamento de Textura");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutSpecialFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}
