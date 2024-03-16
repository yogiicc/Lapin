#include <GL/freeglut.h>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <cstdio>

char presse;
int anglex,angley,x,y,xold,yold;
int zoom = 20;

float mouvement = -1;
float mouvement2 = 0.80;
bool mouvementBool = true;
bool mouvementBool2 = false;

bool animationEncours = false;
int etape = 0;
int rotation = 0;
int rotation2 = 90;

/* Prototype des fonctions */
void affichage();

void idle();
void animationOreilles();
void reshape(int x,int y);
void clavier(unsigned char touche, int x, int y);
void cameraFleches(int touche, int x, int y);
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);

void piedPt1();
void piedPt2();
void coussinetPiedPt1();
void coussinetPiedPt2();
void corps();
void bras();
void coussinetBras();
void tete();
void oreillePt1();
void oreillePt2();
void coussinetOreillePt1();
void coussinetOreillePt2();
void museau();
void nez();
void sourcil();

int main(int argc,char **argv)
{
    // initialisation de glut et creation de la fenetre
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(800,800);
    glutCreateWindow("Lapin");

    // Initialisation d'OpenGL
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);

    //enregistrement des fonctions de rappel
    glutDisplayFunc(affichage);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutSpecialFunc(cameraFleches);
    glutKeyboardFunc(clavier);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);

    //Entree dans la boucle principale glut
    glutMainLoop();
    return 0;
}

void idle()
{
    if(mouvement <= -1.0){
        mouvementBool=true;
    }
    if(mouvementBool){
        mouvement += 0.01;
    }else{
        mouvement -=0.01;
    }
    if(mouvement >= -0.80){
        mouvementBool=false;
    }

    if(mouvement2 >= 1.0){
        mouvementBool2=true;
    }
    if(mouvementBool2){
        mouvement2 -= 0.01;
    }else{
        mouvement2 +=0.01;
    }
    if(mouvement2 <=0.80){
        mouvementBool2=false;
    }
    glutPostRedisplay();

}

void animationOreilles(int etape)
{
    if(etape<=180){
         if(etape <=90){
            rotation +=1;
            rotation2 -=1;
            glutPostRedisplay();
            glutTimerFunc(10,animationOreilles,etape+1);
         }
         else if(etape>90){
            rotation -=1;
            rotation2 +=1;
            glutPostRedisplay();
            glutTimerFunc(10,animationOreilles,etape+1);
        }
    }
    else{
        animationEncours=false;
    }
}

void affichage()
{
    //effacement de l'image avec la couleur de fond
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-zoom,zoom,-5, zoom,-zoom,zoom);
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    //Repère
    //axe x en rouge
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(10, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(0, 10,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(0, 0,10);
    glEnd();

    //Coussinet Pied Gauche
    glPushMatrix();
    glTranslatef(-1.5,0,0);
    glRotatef(90,1,0,0);
    coussinetPiedPt2();
    glRotatef(-90,1,0,0);
    glTranslatef(0,0,-0.5);
    glRotatef(180,0,1,0);
    glRotatef(90,1,0,0);
    coussinetPiedPt1();
    glPopMatrix();

    //pied gauche
    glPushMatrix();
    glTranslatef(-1.5,0,0);
    glRotatef(180,0,1,0);
    glRotatef(90,0,0,1);
    glRotatef(-90,0,1,0);
    piedPt2();
    glRotatef(90,0,1,0);
    piedPt1();
    glPopMatrix();

    //Coussinet Pied Droit
    glPushMatrix();
    glTranslatef(1.5,0,0);
    glRotatef(90,1,0,0);
    coussinetPiedPt2();
    glRotatef(-90,1,0,0);
    glTranslatef(0,0,-0.5);
    glRotatef(180,0,1,0);
    glRotatef(90,1,0,0);
    coussinetPiedPt1();
    glPopMatrix();

    //pied droite
    glPushMatrix();
    glTranslatef(1.5,0,0);
    glRotatef(180,0,1,0);
    glRotatef(90,0,0,1);
    glRotatef(-90,0,1,0);
    piedPt2();
    glRotatef(90,0,1,0);
    piedPt1();
    glPopMatrix();

    //Corps Bas
    glPushMatrix();
    glTranslatef(0,3,-0.75);
    glRotatef(-90,1,0,0);
    corps();
    glPopMatrix();

    //Corps Haut
    glPushMatrix();
    glTranslatef(0,3,-0.75);
    glRotatef(-90,1,0,0);
    glColor3f(1,1,1);
    glutSolidCone(3,2,10,6);
    glPopMatrix();

    //Queue
    glPushMatrix();
    glTranslatef(0,3,-3.5);
    glColor3f(1,1,1);
    glutSolidSphere(1,100,100);
    glPopMatrix();

    //Bras Gauche
    glPushMatrix();
    glTranslatef(-1.25,3,2);
    glRotatef(90,0,1,0);
    glRotatef(45,1,0,0);
    bras();
    coussinetBras();
    glPopMatrix();

    //Bras Droit
    glPushMatrix();
    glTranslatef(1.25,3,2);
    glRotatef(-90,0,1,0);
    glRotatef(45,1,0,0);
    bras();
    coussinetBras();
    glPopMatrix();

    //Tete
    glPushMatrix();
    glTranslatef(0,6,0);
    glColor3f(1,1,1);
    glutSolidSphere(2.5,100,100);
    glTranslatef(0,-0.75,0);
    tete();
    glPopMatrix();

    //coussinet oreille gauche
    glPushMatrix();
    glTranslatef(-2,10.5,0);
    glRotatef(180,1,0,0);
    coussinetOreillePt1();
    glRotatef(-180,1,0,0);
    glTranslatef(0,0.5,0);
    glRotatef(rotation,1,0,0); //ici la rotation
    coussinetOreillePt2();
    glPopMatrix();

    //oreille gauche
    glPushMatrix();
    glTranslatef(-2,11,0);
    glRotatef(90,1,0,0);
    glRotatef(-90,0,0,1);
    oreillePt1();
    glRotatef(-rotation2,0,1,0); //ici la rotation
    oreillePt2();
    glPopMatrix();

    //coussinet oreille Droite
    glPushMatrix();
    glTranslatef(2,10.5,0);
    glRotatef(180,1,0,0);
    coussinetOreillePt1();
    glRotatef(-180,1,0,0);
    glTranslatef(0,0.5,0);
    glRotatef(rotation2,1,0,0);//ici la rotation
    coussinetOreillePt2();
    glPopMatrix();

    //oreille Droite
    glPushMatrix();
    glTranslatef(2,11,0);
    glRotatef(90,1,0,0);
    glRotatef(-90,0,0,1);
    oreillePt1();
    glRotatef(-rotation,0,1,0); //ici a rotation
    oreillePt2();
    glPopMatrix();

    //Museau gauche
    glPushMatrix();
    glTranslatef(-0.15,5.25,3);
    glScalef(0.25,0.25,0.25);
    museau();
    glPopMatrix();

    //Museau Droit
    glPushMatrix();
    glTranslatef(0.15,5.25,3);
    glScalef(0.25,0.25,0.25);
    museau();
    glPopMatrix();

    //Nez
    glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(0.15,5.55,3);
    glRotatef(90,0,1,0);
    glRotatef(-45,1,0,0);
    glScalef(0.5,0.5,0.5);
    nez();
    glPopMatrix();

    //Dents
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-0.10,4.75,3);
    glutSolidCube(0.20);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0.10,4.75,3);
    glutSolidCube(0.20);
    glPopMatrix();

    //Bouche
    glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(0,4.5,1.75);
    glutSolidCylinder(0.5,1,10,6);
    glPopMatrix();

    //Sourcil Gauche
    glPushMatrix();
    glTranslatef(-0.80,6.5,2.15);
    glRotated(90,1,0,0);
    glScalef(0.5,0.5,0.5);
    sourcil();
    glPopMatrix();

    //Sourcil Droit
    glPushMatrix();
    glTranslatef(0.80,6.5,2.15);
    glRotated(90,1,0,0);
    glScalef(0.5,0.5,0.5);
    sourcil();
    glPopMatrix();

    //oeil Gauche
    glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(-0.80,6.25,2.15);
    glRotated(90,1,0,0);
    glutSolidSphere(0.45,10,6);
    glPopMatrix();

    //oeil Droit
    glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(0.80,6.25,2.15);
    glRotated(90,1,0,0);
    glutSolidSphere(0.45,10,6);
    glPopMatrix();

    //pupille Gauche
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(mouvement,0,0);
    glTranslatef(0,6.25,2.50);
    glutSolidSphere(0.15,10,6);
    glPopMatrix();

    //mouvement de -1 a -80 et mouvement 2 de 0.80 a 1

    //pupille Droite
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(mouvement2,6.25,2.50);
    glRotated(90,1,0,0);
    glutSolidSphere(0.15,10,6);
    glPopMatrix();

    glFlush();

    //On echange les buffers
    glutSwapBuffers();
}

class Point{
    public :
        //coordonnées x, y et z du point
        double x;
        double y;
        double z;
        // couleur r, v et b du point
        float r;
        float g;
        float b;
};
//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////***********PIEDS***********///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int fPiedPt1[10*6][4];
Point pPiedPt1[10*6];

void piedPt1()
{
    //Création du demi-Cone
    int rayon = 1;
    int hauteur = 2;
    int NM = 10;
    int NP = 6;
    float PI = 3.14159265359;

    float theta = PI/NM;
    float phi = (PI/2)/(NP-1);

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP; j++){
            pPiedPt1[i+NM*j].x = rayon*cos(i*theta + PI/2)*cos(j*phi + PI/2);
            pPiedPt1[i+NM*j].y = rayon*sin(i*theta + PI/2)*cos(j*phi + PI/2);
            pPiedPt1[i+NM*j].z = hauteur*rayon*sin(j*phi + PI/2);
        }
    }

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP-1; j++){
            fPiedPt1[i+NM*j][0] = i+NM*j;
            fPiedPt1[i+NM*j][1] = (i+1)%NM+NM*j;
            fPiedPt1[i+NM*j][2] = (i+1)%NM+NM*(j+1);
            fPiedPt1[i+NM*j][3] = i+NM*(j+1);
        }
    }

    //Affichage du demi-Cone
    for(int i=0;i<10*6;i++){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_POLYGON);
        for(int j=0;j<6;j++){
            glColor3f(0.5, 0.5, 0.5);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
            glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 1.0);
            glTexCoord2f(0.0,0.0);   glVertex3f(pPiedPt1[fPiedPt1[i][0]].x, pPiedPt1[fPiedPt1[i][0]].y, pPiedPt1[fPiedPt1[i][0]].z);
            glTexCoord2f(0.0,-2);   glVertex3f(pPiedPt1[fPiedPt1[i][1]].x, pPiedPt1[fPiedPt1[i][1]].y, pPiedPt1[fPiedPt1[i][1]].z);
            glTexCoord2f(-2,-2);   glVertex3f(pPiedPt1[fPiedPt1[i][2]].x, pPiedPt1[fPiedPt1[i][2]].y, pPiedPt1[fPiedPt1[i][2]].z);
            glTexCoord2f(-2,0.0);   glVertex3f(pPiedPt1[fPiedPt1[i][3]].x, pPiedPt1[fPiedPt1[i][3]].y, pPiedPt1[fPiedPt1[i][3]].z);
            glEnd();

            //glVertex3f(pSphere[fSphere[i][j]].x,pSphere[fSphere[i][j]].y,pSphere[fSphere[i][j]].z);
            glutPostRedisplay();
        }
        glEnd();
    }
}

int fPiedPt2[10*6][4];
Point pPiedPt2[10*6];

void piedPt2()
{
    //Création de la demi-sphère
    int rayon = 1;
    int NM = 10;
    int NP = 6;
    float PI = 3.14159265359;

    float theta = 2*PI/NM;
    float phi = (PI/2)/(NP-1) ;

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP; j++){
            pPiedPt2[i+NM*j].x = rayon*cos(i*theta)*cos(j*phi - PI/2);
            pPiedPt2[i+NM*j].y = rayon*sin(i*theta)*cos(j*phi - PI/2);
            pPiedPt2[i+NM*j].z = rayon*sin(j*phi - PI/2);
        }
    }

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP-1; j++){
            fPiedPt2[i+NM*j][0] = i+NM*j;
            fPiedPt2[i+NM*j][1] = (i+1)%NM+NM*j;
            fPiedPt2[i+NM*j][2] = (i+1)%NM+NM*(j+1);
            fPiedPt2[i+NM*j][3] = i+NM*(j+1);
        }
    }

    //Affichage de la demi-sphère
    for(int i=0;i<10*6;i++){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_POLYGON);
        for(int j=0;j<6;j++){
            glColor3f(0.5, 0.5, 0.5);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 1.0);
            glTexCoord2f(0.0,0.0);   glVertex3f(pPiedPt2[fPiedPt2[i][0]].x, pPiedPt2[fPiedPt2[i][0]].y, pPiedPt2[fPiedPt2[i][0]].z);
            glTexCoord2f(0.0,-2);   glVertex3f(pPiedPt2[fPiedPt2[i][1]].x, pPiedPt2[fPiedPt2[i][1]].y, pPiedPt2[fPiedPt2[i][1]].z);
            glTexCoord2f(-2,-2);   glVertex3f(pPiedPt2[fPiedPt2[i][2]].x, pPiedPt2[fPiedPt2[i][2]].y, pPiedPt2[fPiedPt2[i][2]].z);
            glTexCoord2f(-2,0.0);   glVertex3f(pPiedPt2[fPiedPt2[i][3]].x, pPiedPt2[fPiedPt2[i][3]].y, pPiedPt2[fPiedPt2[i][3]].z);
            glEnd();

            //glVertex3f(pSphere[fSphere[i][j]].x,pSphere[fSphere[i][j]].y,pSphere[fSphere[i][j]].z);
            glutPostRedisplay();
        }
        glEnd();
    }
}

void coussinetPiedPt1()
{
    glBegin(GL_TRIANGLES);
        glColor3f( 1, 0, 1 );
        glVertex2f( -0.8, -0.8 );
        glColor3f( 1, 0, 1 );
        glVertex2f( 0.8, -0.8 );
        glColor3f( 1, 0, 1 );
        glVertex2f( 0, 1 );
    glEnd();
}

void coussinetPiedPt2()
{
    glBegin( GL_TRIANGLE_FAN );
        glVertex2f( 0, 0 );
        glColor3f(1,0,1);
        for( float i = 0; i <= 2 * 3.14 + 0.1; i += 0.1 )
            {
                glVertex2f( x + sin( i ) * 0.75, y + cos( i ) * 0.75 );
            }
    glEnd();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////***********CORPS***********///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int fCorps[10*6][4];
Point pCorps[10*6];

void corps()
{
    //Création de la demi-sphère
    int rayon = 3;
    int NM = 10;
    int NP = 6;
    float PI = 3.14159265359;

    float theta = 2*PI/NM;
    float phi = (PI/2)/(NP-1) ;

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP; j++){
            pCorps[i+NM*j].x = rayon*cos(i*theta)*cos(j*phi - PI/2);
            pCorps[i+NM*j].y = rayon*sin(i*theta)*cos(j*phi - PI/2);
            pCorps[i+NM*j].z = rayon*sin(j*phi - PI/2);
        }
    }

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP-1; j++){
            fCorps[i+NM*j][0] = i+NM*j;
            fCorps[i+NM*j][1] = (i+1)%NM+NM*j;
            fCorps[i+NM*j][2] = (i+1)%NM+NM*(j+1);
            fCorps[i+NM*j][3] = i+NM*(j+1);
        }
    }

    //Affichage de la demi-sphère
    for(int i=0;i<10*6;i++){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_POLYGON);
        for(int j=0;j<6;j++){
            glColor3f(0.5, 0.5, 0.5);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 1.0);
            glTexCoord2f(0.0,0.0);   glVertex3f(pCorps[fCorps[i][0]].x, pCorps[fCorps[i][0]].y, pCorps[fCorps[i][0]].z);
            glTexCoord2f(0.0,-2);   glVertex3f(pCorps[fCorps[i][1]].x, pCorps[fCorps[i][1]].y, pCorps[fCorps[i][1]].z);
            glTexCoord2f(-2,-2);   glVertex3f(pCorps[fCorps[i][2]].x, pCorps[fCorps[i][2]].y, pCorps[fCorps[i][2]].z);
            glTexCoord2f(-2,0.0);   glVertex3f(pCorps[fCorps[i][3]].x, pCorps[fCorps[i][3]].y, pCorps[fCorps[i][3]].z);
            glEnd();

            //glVertex3f(pSphere[fSphere[i][j]].x,pSphere[fSphere[i][j]].y,pSphere[fSphere[i][j]].z);
            glutPostRedisplay();
        }
        glEnd();
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////***********BRAS***********///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int fBras[10*6][4];
Point pBras[10*6];

void bras()
{
    //Création de la demi-sphère
     int rayon = 1;
    int NM = 10;
    int NP = 6;
    float PI = 3.14159265359;

    float theta = 2*PI/NM;
    float phi = (PI/2)/(NP-1) ;

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP; j++){
            pBras[i+NM*j].x = rayon*cos(i*theta)*cos(j*phi - PI/2);
            pBras[i+NM*j].y = rayon*sin(i*theta)*cos(j*phi - PI/2);
            pBras[i+NM*j].z = rayon*sin(j*phi - PI/2);
        }
    }

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP-1; j++){
            fBras[i+NM*j][0] = i+NM*j;
            fBras[i+NM*j][1] = (i+1)%NM+NM*j;
            fBras[i+NM*j][2] = (i+1)%NM+NM*(j+1);
            fBras[i+NM*j][3] = i+NM*(j+1);
        }
    }

    //Affichage de la demi-Sphère
    for(int i=0;i<10*6;i++){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_POLYGON);
        for(int j=0;j<6;j++){
            glColor3f(0.5, 0.5, 0.5);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 1.0);
            glTexCoord2f(0.0,0.0);   glVertex3f(pBras[fBras[i][0]].x, pBras[fBras[i][0]].y, pBras[fBras[i][0]].z);
            glTexCoord2f(0.0,-2);   glVertex3f(pBras[fBras[i][1]].x, pBras[fBras[i][1]].y, pBras[fBras[i][1]].z);
            glTexCoord2f(-2,-2);   glVertex3f(pBras[fBras[i][2]].x, pBras[fBras[i][2]].y, pBras[fBras[i][2]].z);
            glTexCoord2f(-2,0.0);   glVertex3f(pBras[fBras[i][3]].x, pBras[fBras[i][3]].y, pBras[fBras[i][3]].z);
            glEnd();

            //glVertex3f(pSphere[fSphere[i][j]].x,pSphere[fSphere[i][j]].y,pSphere[fSphere[i][j]].z);
            glutPostRedisplay();
        }
        glEnd();
    }
}

void coussinetBras()
{
    glBegin( GL_TRIANGLE_FAN );
        glVertex2f( 0, 0 );
        glColor3f(1,0,1);
        for( float i = 0; i <= 2 * 3.14 + 0.1; i += 0.1 )
            {
                glVertex2f( x + sin( i ) * 0.75, y + cos( i ) * 0.75 );
            }
    glEnd();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////***********TETE***********///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int fTete[10*6][4];
Point pTete[10*6];

void tete()
{
    //Création de l'ellispoide
     int rayon = 3;
     int rayon2 = 2;
     int NM = 10;
     int NP = 6;
     float PI = 3.14159265359;

     float theta = 2*PI/NM;
     float phi = PI/(NP-1) ;

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP; j++){
            pTete[i+NM*j].x = rayon*cos(i*theta)*cos(j*phi - PI/2);
            pTete[i+NM*j].y = rayon2*sin(i*theta)*cos(j*phi - PI/2);
            pTete[i+NM*j].z = rayon*sin(j*phi - PI/2);
        }
    }

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP-1; j++){
            fTete[i+NM*j][0] = i+NM*j;
            fTete[i+NM*j][1] = (i+1)%NM+NM*j;
            fTete[i+NM*j][2] = (i+1)%NM+NM*(j+1);
            fTete[i+NM*j][3] = i+NM*(j+1);
        }
    }

    //Affichage de l'ellipsoide
    for(int i=0;i<10*6;i++){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_POLYGON);
        for(int j=0;j<6;j++){
            glColor3f(0.5, 0.5, 0.5);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 1.0);
            glTexCoord2f(0.0,0.0);   glVertex3f(pTete[fTete[i][0]].x, pTete[fTete[i][0]].y, pTete[fTete[i][0]].z);
            glTexCoord2f(0.0,-2);   glVertex3f(pTete[fTete[i][1]].x, pTete[fTete[i][1]].y, pTete[fTete[i][1]].z);
            glTexCoord2f(-2,-2);   glVertex3f(pTete[fTete[i][2]].x, pTete[fTete[i][2]].y, pTete[fTete[i][2]].z);
            glTexCoord2f(-2,0.0);   glVertex3f(pTete[fTete[i][3]].x, pTete[fTete[i][3]].y, pTete[fTete[i][3]].z);
            glEnd();

            //glVertex3f(pSphere[fSphere[i][j]].x,pSphere[fSphere[i][j]].y,pSphere[fSphere[i][j]].z);
            glutPostRedisplay();
        }
        glEnd();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////***********OREILLES***********///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int fOreillePt1[10*6][4];
Point pOreillePt1[10*6];

void oreillePt1()
{
    //Création du demi-Cone
    int rayon = 1;
    int hauteur = 4;
    int NM = 10;
    int NP = 6;
    float PI = 3.14159265359;

    float theta = PI/NM;
    float phi = (PI/2)/(NP-1);

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP; j++){
            pOreillePt1[i+NM*j].x = rayon*cos(i*theta + PI/2)*cos(j*phi + PI/2);
            pOreillePt1[i+NM*j].y = rayon*sin(i*theta + PI/2)*cos(j*phi + PI/2);
            pOreillePt1[i+NM*j].z = hauteur*rayon*sin(j*phi + PI/2);
        }
    }

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP-1; j++){
            fOreillePt1[i+NM*j][0] = i+NM*j;
            fOreillePt1[i+NM*j][1] = (i+1)%NM+NM*j;
            fOreillePt1[i+NM*j][2] = (i+1)%NM+NM*(j+1);
            fOreillePt1[i+NM*j][3] = i+NM*(j+1);
        }
    }

    //Affichage du demi-Cone
    for(int i=0;i<10*6;i++){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_POLYGON);
        for(int j=0;j<6;j++){
            glColor3f(0.5, 0.5, 0.5);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 1.0);
            glTexCoord2f(0.0,0.0);   glVertex3f(pOreillePt1[fOreillePt1[i][0]].x, pOreillePt1[fOreillePt1[i][0]].y, pOreillePt1[fOreillePt1[i][0]].z);
            glTexCoord2f(0.0,-2);   glVertex3f(pOreillePt1[fOreillePt1[i][1]].x, pOreillePt1[fOreillePt1[i][1]].y, pOreillePt1[fOreillePt1[i][1]].z);
            glTexCoord2f(-2,-2);   glVertex3f(pOreillePt1[fOreillePt1[i][2]].x, pOreillePt1[fOreillePt1[i][2]].y, pOreillePt1[fOreillePt1[i][2]].z);
            glTexCoord2f(-2,0.0);   glVertex3f(pOreillePt1[fOreillePt1[i][3]].x, pOreillePt1[fOreillePt1[i][3]].y, pOreillePt1[fOreillePt1[i][3]].z);
            glEnd();

            //glVertex3f(pSphere[fSphere[i][j]].x,pSphere[fSphere[i][j]].y,pSphere[fSphere[i][j]].z);
            glutPostRedisplay();
        }
        glEnd();
    }
}


int fOreillePt2[10*6][4];
Point pOreillePt2[10*6];

void oreillePt2()
{
    //Création de la demi-sphère
    int rayon = 1;
    int NM = 10;
    int NP = 6;
    float PI = 3.14159265359;

    float theta = 2*PI/NM;
    float phi = (PI/2)/(NP-1) ;

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP; j++){
            pOreillePt2[i+NM*j].x = rayon*cos(i*theta)*cos(j*phi - PI/2);
            pOreillePt2[i+NM*j].y = rayon*sin(i*theta)*cos(j*phi - PI/2);
            pOreillePt2[i+NM*j].z = rayon*sin(j*phi - PI/2);
        }
    }

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP-1; j++){
            fOreillePt2[i+NM*j][0] = i+NM*j;
            fOreillePt2[i+NM*j][1] = (i+1)%NM+NM*j;
            fOreillePt2[i+NM*j][2] = (i+1)%NM+NM*(j+1);
            fOreillePt2[i+NM*j][3] = i+NM*(j+1);
        }
    }

    //Affichage de la demi-sphère
    for(int i=0;i<10*6;i++){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_POLYGON);
        for(int j=0;j<6;j++){
            glColor3f(0.5, 0.5, 0.5);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 1.0);
            glTexCoord2f(0.0,0.0);   glVertex3f(pOreillePt2[fOreillePt2[i][0]].x, pOreillePt2[fOreillePt2[i][0]].y, pOreillePt2[fOreillePt2[i][0]].z);
            glTexCoord2f(0.0,-2);   glVertex3f(pOreillePt2[fOreillePt2[i][1]].x, pOreillePt2[fOreillePt2[i][1]].y, pOreillePt2[fOreillePt2[i][1]].z);
            glTexCoord2f(-2,-2);   glVertex3f(pOreillePt2[fOreillePt2[i][2]].x, pOreillePt2[fOreillePt2[i][2]].y, pOreillePt2[fOreillePt2[i][2]].z);
            glTexCoord2f(-2,0.0);   glVertex3f(pOreillePt2[fOreillePt2[i][3]].x, pOreillePt2[fOreillePt2[i][3]].y, pOreillePt2[fOreillePt2[i][3]].z);
            glEnd();

            //glVertex3f(pSphere[fSphere[i][j]].x,pSphere[fSphere[i][j]].y,pSphere[fSphere[i][j]].z);
            glutPostRedisplay();
        }
        glEnd();
    }
}

void coussinetOreillePt1()
{
    glBegin(GL_TRIANGLES);
        glColor3f( 1, 0, 1 );
        glVertex2f( -0.8, -0.8 );
        glColor3f( 1, 0, 1 );
        glVertex2f( 0.8, -0.8 );
        glColor3f( 1, 0, 1 );
        glVertex2f( 0, 2.5 );
    glEnd();
}

void coussinetOreillePt2()
{
    glBegin( GL_TRIANGLE_FAN );
        glVertex2f( 0, 0 );
        glColor3f(1,0,1);
        for( float i = 0; i <= 2 * 3.14 + 0.1; i += 0.1 )
            {
                glVertex2f( x + sin( i ) * 0.75, y + cos( i ) * 0.75 );
            }
    glEnd();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////***********VISAGE***********///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int fMuseau[10*6][4];
Point pMuseau[10*6];

void museau()
{
    //Création de l'ellispoide
     int rayon = 1;
     int rayon2 = 2;
     int rayon3 = 1;
     int NM = 10;
     int NP = 6;
     float PI = 3.14159265359;

     float theta = 2*PI/NM;
     float phi = PI/(NP-1) ;

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP; j++){
            pTete[i+NM*j].x = rayon*cos(i*theta)*cos(j*phi - PI/2);
            pTete[i+NM*j].y = rayon2*sin(i*theta)*cos(j*phi - PI/2);
            pTete[i+NM*j].z = rayon3*sin(j*phi - PI/2);
        }
    }

    for(int i=0; i<NM; i++){
        for(int j=0; j<NP-1; j++){
            fTete[i+NM*j][0] = i+NM*j;
            fTete[i+NM*j][1] = (i+1)%NM+NM*j;
            fTete[i+NM*j][2] = (i+1)%NM+NM*(j+1);
            fTete[i+NM*j][3] = i+NM*(j+1);
        }
    }

    //Affichage de l'ellipsoide
    for(int i=0;i<10*6;i++){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_POLYGON);
        for(int j=0;j<6;j++){
            glColor3f(0.5, 0.5, 0.5);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glColor3f(0.0, 1.0, 1.0);
            glTexCoord2f(0.0,0.0);   glVertex3f(pTete[fTete[i][0]].x, pTete[fTete[i][0]].y, pTete[fTete[i][0]].z);
            glTexCoord2f(0.0,-2);   glVertex3f(pTete[fTete[i][1]].x, pTete[fTete[i][1]].y, pTete[fTete[i][1]].z);
            glTexCoord2f(-2,-2);   glVertex3f(pTete[fTete[i][2]].x, pTete[fTete[i][2]].y, pTete[fTete[i][2]].z);
            glTexCoord2f(-2,0.0);   glVertex3f(pTete[fTete[i][3]].x, pTete[fTete[i][3]].y, pTete[fTete[i][3]].z);
            glEnd();

            //glVertex3f(pSphere[fSphere[i][j]].x,pSphere[fSphere[i][j]].y,pSphere[fSphere[i][j]].z);
            glutPostRedisplay();
        }
        glEnd();
    }
}


void nez()
{
    glBegin(GL_QUADS);
        glVertex3f(0.5, 0, 0.5);
        glVertex3f(0.5, 0, -0.5);
        glVertex3f(-0.5, 0, -0.5);
        glVertex3f(-0.5, 0, 0.5);

        glVertex3f(0.5,0,-0.5);
        glVertex3f(0.5,1,-0.5);
        glVertex3f(-0.5,1,-0.5);
        glVertex3f(-0.5,0,-0.5);

        glVertex3f(0.5,1,-0.5);
        glVertex3f(-0.5,1,-0.5);
        glVertex3f(-0.5,0,0.5);
        glVertex3f(0.5,0,0.5);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(0.5,0,0.5);
        glVertex3f(0.5,1,-0.5);
        glVertex3f(0.5,0,-0.5);

        glVertex3f(-0.5,0,0.5);
        glVertex3f(-0.5,1,-0.5);
        glVertex3f(-0.5,0,-0.5);
    glEnd();
}

int fSourcil[10*6][4];
Point pSourcil[10*6];

void sourcil()
{
        //Création de la demi-sphère
        int rayon = 1;
        int NM = 10;
        int NP = 6;
        float PI = 3.14159265359;

        float theta = 2*PI/NM;
        float phi = (PI/2)/(NP-1) ;

        for(int i=0; i<NM; i++){
            for(int j=0; j<NP; j++){
                pSourcil[i+NM*j].x = rayon*cos(i*theta)*cos(j*phi - PI/2);
                pSourcil[i+NM*j].y = rayon*sin(i*theta)*cos(j*phi - PI/2);
                pSourcil[i+NM*j].z = rayon*sin(j*phi - PI/2);
            }
        }

        for(int i=0; i<NM; i++){
            for(int j=0; j<NP-1; j++){
                fSourcil[i+NM*j][0] = i+NM*j;
                fSourcil[i+NM*j][1] = (i+1)%NM+NM*j;
                fSourcil[i+NM*j][2] = (i+1)%NM+NM*(j+1);
                fSourcil[i+NM*j][3] = i+NM*(j+1);
            }
        }

        //Affichage de la demi-sphère
        for(int i=0;i<10*6;i++){
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glBegin(GL_POLYGON);
            for(int j=0;j<6;j++){
                glColor3f(0.5, 0.5, 0.5);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glBegin(GL_POLYGON);
                glColor3f(0.0, 1.0, 1.0);
                glTexCoord2f(0.0,0.0);   glVertex3f(pSourcil[fSourcil[i][0]].x, pSourcil[fSourcil[i][0]].y, pSourcil[fSourcil[i][0]].z);
                glTexCoord2f(0.0,-2);   glVertex3f(pSourcil[fSourcil[i][1]].x, pSourcil[fSourcil[i][1]].y, pSourcil[fSourcil[i][1]].z);
                glTexCoord2f(-2,-2);   glVertex3f(pSourcil[fSourcil[i][2]].x, pSourcil[fSourcil[i][2]].y, pSourcil[fSourcil[i][2]].z);
                glTexCoord2f(-2,0.0);   glVertex3f(pSourcil[fSourcil[i][3]].x, pSourcil[fSourcil[i][3]].y, pSourcil[fSourcil[i][3]].z);
                glEnd();

                //glVertex3f(pSphere[fSphere[i][j]].x,pSphere[fSphere[i][j]].y,pSphere[fSphere[i][j]].z);
                glutPostRedisplay();
            }
            glEnd();
        }

}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}
void clavier(unsigned char touche, int x, int y)
{
    switch (touche)
    {
        case 'Z': /* ZOOM */
            zoom -= 1;
            if(zoom < 0){
                zoom = 0;
            }
            glutPostRedisplay();
            break;
        case 'z': /* DEZOOM*/
            zoom += 1;
            glutPostRedisplay();
            break;
        case 'a' : /* ANIMATION*/
            if(animationEncours==false){
                animationEncours=true;
                animationOreilles(0);
            }
            break;
        case 'q' : /*la touche 'q' permet de quitter le programme */
            exit(0);
    }
}

void cameraFleches(int touche, int x, int y)
{
    switch(touche){
        case GLUT_KEY_LEFT:
            anglex += 10;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            anglex -= 10;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            angley += 10;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            angley -= 10;
            glutPostRedisplay();
            break;
    }
}
void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y)
{
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
}
