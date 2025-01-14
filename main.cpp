#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLfloat fAspecto;

// Especifica��o do �ngulo da proje��o perspectiva
GLfloat angulo = 45;

// Vari�veis usadas para alterar a posi��o do observador virtual
GLfloat obsX = 0, obsY = 10, obsZ = 100;
GLfloat rotX = 30, rotY = 0, rotX_ini, rotY_ini;
GLfloat obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

void Inicializa (void) {
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);
	// Habilita as fontes de luz
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);
}

void Desenha(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa a janela de visualiza��o com a cor de fundo definida previamente
	
	// Desenha Ch�o
	glColor3f (0.0,1.0,0.0);
	glPushMatrix ();
		glScalef (50.0,0.1,50.0);
		glutSolidCube (1);
	glPopMatrix ();
	
	// Desenha Cord�o
	glColor3f (0.0,1.0,0.5);
	glPushMatrix ();
        glTranslatef (25.0,2.5,17.0);
        glScalef (5.0,5.0,20.0);
        glutSolidCube (1);
    glPopMatrix (); 
	glPushMatrix ();
        glTranslatef (25.0,2.5,-17);
        glScalef (5.0,5.0,20.0);
        glutSolidCube (1);
    glPopMatrix ();    
    glPushMatrix ();
        glTranslatef (-25.0,2.5,0.0);
        glScalef (5.0,5.0,50.0);
        glutSolidCube (1);
    glPopMatrix ();
    glPushMatrix ();
        glRotatef (90.0,0,1,0);
        glTranslatef (-25.0,2.5,0.0);
        glScalef (5.0,5.0,55.0);
        glutSolidCube (1);
    glPopMatrix ();
    glPushMatrix ();
        glRotatef (90.0,0,1,0);
        glTranslatef (25.0,2.5,0.0);
        glScalef (5.0,5.0,55.0);
        glutSolidCube (1);
    glPopMatrix ();
    
    // Desenha casa
	glColor3f (0.0,0.0,1.0);
	glPushMatrix ();
		glTranslatef (0.0,15,0.0);
        glScalef (45.0,30,45.0);
        glutSolidCube (1);
    glPopMatrix ();
    
    // Desenha porta
    glColor3f (1.0,1.0,0.0);
	glPushMatrix ();
		glTranslatef (22.5,10,0.0);
		glScalef (0.1,20,10);
		glutSolidCube (1);
	glPopMatrix ();
	
	// Desenha janelas
    glColor3f (1.0,1.0,0.0);
	glPushMatrix ();
		glTranslatef (-22.5,15,0.0);
		glScalef (0.1,10,10);
		glutSolidCube (1);
	glPopMatrix ();
	
	glPushMatrix ();
		glTranslatef (0,15,22.5);
		glScalef (10,10,0.1);
		glutSolidCube (1);
	glPopMatrix ();
	
	glPushMatrix ();
		glTranslatef (0,15,-22.5);
		glScalef (10,10,0.1);
		glutSolidCube (1);
	glPopMatrix ();
	
	// Desenha telhado
	glColor3f (1.0,1.0,0.0);
	glPushMatrix ();
		glTranslatef (0,30,0.0);
		glScalef (35,15,35);
		glRotatef (45,0,1,0);
		glutSolidOctahedron ();
	glPopMatrix ();
	
	// Desenha fechadura
	
	glColor3f (0.0,0.0,1.0);
	glPushMatrix ();
		glTranslatef (22.5,10,3);
		glScalef (1,1,1);
		glutSolidSphere (1,10,10);
	glPopMatrix ();
    
	glutSwapBuffers (); // Executa os comandos OpenGL
}

// Fun��o usada para especificar a posi��o do observador virtual
void PosicionaObservador(void)
{
	glMatrixMode (GL_MODELVIEW); // Especifica sistema de coordenadas do modelo
	glLoadIdentity (); // Inicializa sistema de coordenadas do modelo
	glTranslatef (-obsX,-obsY,-obsZ); // Posiciona e orienta o observador
	glRotatef (rotX,1,0,0);
	glRotatef (rotY,0,1,0);
}

void AlteraJanela (GLsizei largura, GLsizei altura) {
	if ( altura == 0 ) altura = 1;
	GLfloat fAspecto = (GLfloat)largura/(GLfloat)altura;
	glViewport (0, 0, largura, altura);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (angulo,fAspecto,0.5,500);
	PosicionaObservador ();
}

void Teclado (unsigned char tecla, int x, int y) {
	if (tecla == 27) exit(0);
}
              
void GerenciaMouse (int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		// Salva os par�metros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button; // Para conrole do movimento do mouse
	} else bot = -1;
}

#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0
void GerenciaMovimento (int x, int y) {
	// Calcula diferen�as
	int deltax = x_ini - x;
	int deltay = y_ini - y;
	int deltaz = y_ini - y;
	
	if (bot == GLUT_LEFT_BUTTON) { // Bot�o esquerdo ?
		// Modifica �ngulos de rota��o
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	} else if (bot == GLUT_RIGHT_BUTTON) { // Bot�o direito ?
		// Modifica dist�ncia do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	} else if (bot == GLUT_MIDDLE_BUTTON) { // Bot�o do meio ?
		// E modifica posi��es
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

/*Programa principal */

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize (650, 450);
	glutInitWindowPosition (5, 5);
	glutCreateWindow ("Casa: Paredes, Telhado, Aberturas em cada lado e no cordao");
	glutKeyboardFunc (Teclado);
	glutMouseFunc (GerenciaMouse);
	glutMotionFunc (GerenciaMovimento);
	glutDisplayFunc (Desenha);
	glutReshapeFunc (AlteraJanela);
	Inicializa ();
	glutMainLoop();
	return 0;
}


