#include <windows.h>
#include <GL/glut.h>
#include <cmath>

int projectionMode = 0;
int windowWidth = 800, windowHeight = 600;

// Fungsi menggambar sumbu koordinat
void drawAxes() {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    // X (Merah)
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(5, 0, 0);
    // Y (Hijau)
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 5, 0);
    // Z (Biru)
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 5);
    glEnd();
}

// Fungsi untuk menggambar 1 kursi
void drawChair() {
    // Dudukan
    glPushMatrix();
    glColor3f(0.5f, 0.25f, 0.1f);  // Coklat kayu
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Kaki kursi (depan kiri)
    for (float x = -0.45f; x <= 0.45f; x += 0.9f) {
        for (float z = -0.45f; z <= 0.45f; z += 0.9f) {
            glPushMatrix();
            glColor3f(0.3f, 0.15f, 0.05f);
            glTranslatef(x, -0.45f, z);
            glScalef(0.1f, 0.9f, 0.1f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }

    // Sandaran belakang
    glPushMatrix();
    glTranslatef(0, 0.45f, -0.45f);
    glScalef(1.0f, 0.8f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Fungsi untuk menggambar meja makan
void drawTable() {
    // Permukaan meja
    glPushMatrix();
    glColor3f(0.7f, 0.4f, 0.2f);
    glScalef(2.0f, 0.1f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Kaki meja
    for (float x = -0.9f; x <= 0.9f; x += 1.8f) {
        for (float z = -0.9f; z <= 0.9f; z += 1.8f) {
            glPushMatrix();
            glColor3f(0.3f, 0.2f, 0.1f);
            glTranslatef(x, -0.55f, z);
            glScalef(0.1f, 1.0f, 0.1f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }
}

// Fungsi untuk menyusun 4 kursi dan meja
void drawDiningSet() {
    // Meja di tengah
    glPushMatrix();
    glTranslatef(0, 0, 0);
    drawTable();
    glPopMatrix();

    // Kursi depan
    glPushMatrix();
    glTranslatef(0, 0, -1.6f);
    drawChair();
    glPopMatrix();

    // Kursi belakang
    glPushMatrix();
    glTranslatef(0, 0, 1.6f);
    glRotatef(180, 0, 1, 0);
    drawChair();
    glPopMatrix();

    // Kursi kiri
    glPushMatrix();
    glTranslatef(-1.6f, 0, 0);
    glRotatef(90, 0, 1, 0);
    drawChair();
    glPopMatrix();

    // Kursi kanan
    glPushMatrix();
    glTranslatef(1.6f, 0, 0);
    glRotatef(-90, 0, 1, 0);
    drawChair();
    glPopMatrix();
}

// Proyeksi berdasarkan mode
void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)windowWidth / (float)windowHeight;

    switch (projectionMode) {
        case 0: gluPerspective(45.0, aspect, 1.0, 100.0); gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0); break;
        case 1: glOrtho(-5, 5, -5, 5, -20, 20); gluLookAt(0, 5, 0, 0, 0, 0, 0, 0, -1); break;
        case 2: glOrtho(-5, 5, -5, 5, -20, 20); gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0); break;
        case 3: glOrtho(-5, 5, -5, 5, -20, 20); gluLookAt(5, 0, 0, 0, 0, 0, 0, 1, 0); break;
        case 4: glOrtho(-8, 8, -8, 8, -20, 20); gluLookAt(6, 6, 6, 0, 0, 0, 0, 1, 0); break;
        case 5: glOrtho(-8, 8, -8, 8, -20, 20); gluLookAt(6, 4, 6, 0, 0, 0, 0, 1, 0); break;
        case 6: glOrtho(-8, 8, -8, 8, -20, 20); gluLookAt(7, 3, 5, 0, 0, 0, 0, 1, 0); break;
        case 7: gluPerspective(60.0, aspect, 1.0, 100.0); gluLookAt(0, 2, 10, 0, 0, 0, 0, 1, 0); break;
        case 8: gluPerspective(60.0, aspect, 1.0, 100.0); gluLookAt(8, 3, 8, 0, 0, 0, 0, 1, 0); break;
        case 9: gluPerspective(60.0, aspect, 1.0, 100.0); gluLookAt(8, 8, 8, 0, 0, 0, 0, 1, 0); break;
    }

    glMatrixMode(GL_MODELVIEW);
}

// Fungsi pencahayaan
void setupLighting() {
    GLfloat light_position[] = { 5.0, 10.0, 5.0, 1.0 };
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
}

// Display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    setProjection();

    drawAxes();
    drawDiningSet();

    glutSwapBuffers();
}

// Resize window
void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
}

// Keyboard kontrol
void keyboard(unsigned char key, int, int) {
    if (key >= '0' && key <= '9') {
        projectionMode = key - '0';
        glutPostRedisplay();
    }
}

// Inisialisasi awal
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
    setupLighting();
}

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Meja Makan dan Kursi - Proyeksi GKV");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}

