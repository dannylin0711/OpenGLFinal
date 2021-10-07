//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define PI acos(-1)
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GLCtrl"
#pragma resource "*.dfm"

#define AXES 0
#define GAXES 1
#define CUBE 2

TForm1 *Form1;
typedef double point[3];
typedef int color[3];

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
static bool singleMode = true;
static bool flag = true;
static int count = 0;
double translateX = 0.0;
double translateY = 0.0;
double translateZ = 0.0;
double scaleX = 1.0;
double scaleY = 1.0;
double scaleZ = 1.0;
double rotateX = 0;
double rotateY = 0;
double rotateZ = 0;
double prev_rotateX = 0;
double prev_rotateY = 0;
double prev_rotateZ = 0;
double rad = PI/180.0 ;
float matrix[16];
float matrix_temp[16];
bool rotateFlag = true;
bool scaleFlag = false;
float scaleFactor = 1.0;
String fileName = "";
bool redLight = true;
bool blueLight = true;
bool greenLight = true;
double totalScaleFactor = 1.0;
bool renderFlat = false;
bool renderLine = false;



GLfloat colors[][3] = {
{0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},
{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,1.0},
{1.0,1.0,1.0},{0.0,1.0,1.0}
};


bool modelInput = false;


struct simpleTriangle {
    int triangleNumber;
    int vertexIndex[3];
};

struct colorTriangle {
    int triangleNumber;
    int vertexIndex[3];
    int frontcolor[3];
    int backcolor[3];
};

struct vertex{
    int vertexIndex;
    double xyz[3];
    double normalxyz[3];
};

typedef struct simpleTriangle simpleTriangle;
typedef simpleTriangle* simpleTrianglePointer;
typedef struct colorTriangle colorTriangle;
typedef colorTriangle* colorTrianglePointer;
typedef struct vertex vertex;
typedef vertex* vertexPointer;

simpleTrianglePointer simpleTriangleArray;
colorTrianglePointer colorTriangleArray;
vertexPointer vertexArray;

unsigned int triangleCount = 0;
unsigned int vertexCount = 0;


void triangle(point a, point b, point c){

     glVertex3dv(a);
     glVertex3dv(b);
     glVertex3dv(c);

}


void drawTriangle(point a,point b,point c,point na,point nb,point nc){
    glBegin(GL_TRIANGLES);
        glColor3f(0.3,0.3,0.3);
        glNormal3dv(na);
        glVertex3dv(a);

        glNormal3dv(nb);
        glVertex3dv(b);

        glNormal3dv(nc);
        glVertex3dv(c);


    glEnd();
}

void drawTriangleWithColor(point a,point b,point c,point na,point nb,point nc,color cf,color cb){
    double cfdouble[3] = {cf[0]/255.0,cf[1]/255.0,cf[2]/255.0};
    glBegin(GL_TRIANGLES);
        glColor3dv(cfdouble);


        
        glNormal3dv(na);
        glVertex3dv(a);
        glNormal3dv(nb);
        glVertex3dv(b);
        glNormal3dv(nc);
        glVertex3dv(c);

    glEnd();

}

void vertexNormalization(){
    double xBase = vertexArray[0].xyz[0];
    double yBase = vertexArray[0].xyz[1];
    double zBase = vertexArray[0].xyz[2];
    double totalX = 0;
    double totalY = 0;
    double totalZ = 0;
    double maxX = INT_MIN;
    double maxY = INT_MIN;
    double maxZ = INT_MIN;
    double minX = INT_MAX;
    double minY = INT_MAX;
    double minZ = INT_MAX;
    double maxSize = INT_MIN;
    for(size_t i = 0;i<vertexCount;i++){
        totalX += vertexArray[i].xyz[0] - xBase;
        totalY += vertexArray[i].xyz[1] - yBase;
        totalZ += vertexArray[i].xyz[2] - zBase;
    }
    totalX /= vertexCount;
    totalY /= vertexCount;
    totalZ /= vertexCount;

    for(size_t i = 0;i<vertexCount;i++){
        vertexArray[i].xyz[0] -= totalX+ xBase;
        vertexArray[i].xyz[1] -= totalY+ yBase;
        vertexArray[i].xyz[2] -= totalZ+ zBase;
    }


    for(size_t i = 0;i<vertexCount;i++){

        if(vertexArray[i].xyz[0] > maxX){
            maxX = vertexArray[i].xyz[0];
        }else if(vertexArray[i].xyz[0] < minX){
            minX = vertexArray[i].xyz[0];
        }
        if(vertexArray[i].xyz[1] > maxY){
            maxY = vertexArray[i].xyz[1];
        }else if(vertexArray[i].xyz[2] < minY){
            minY = vertexArray[i].xyz[1];
        }
        if(vertexArray[i].xyz[2] > maxZ){
            maxZ = vertexArray[i].xyz[2];
        }else if(vertexArray[i].xyz[2] < minZ){
            minZ = vertexArray[i].xyz[2];
        }
    }
    xBase = maxX-minX;
    yBase = maxY-minY;
    zBase = maxZ-minZ;

    if(xBase>yBase){
        if(xBase>zBase){
            maxSize = xBase;
        }else{
            maxSize = zBase;
        }
    }else{
        if(yBase>zBase){
            maxSize = yBase;
        }else{
            maxSize = zBase;
        }
    }
    maxSize = fabs(maxSize);
    int digit = 0;
    while(maxSize >= 1){
        maxSize /= 10.0;
        digit++;
    }
    totalScaleFactor = pow(10.0,(digit-1));
    int p =0;
}

int modelType = -1;
void readModel(){
    FILE *f;
    f = fopen(fileName.c_str(),"r");
    if( NULL == f ){
        printf( "open failure" );
        return;
    }else{

        char typeChar[8] = {0} ;
        char tempChar[2]={0};


        fscanf( f, "%s",typeChar );

        modelType = (strcmp("Simple:",typeChar));
        if(modelType != 0){
            modelType = 1;
        }

        if(!modelType){

            fscanf( f, "%d",&triangleCount );
            fscanf( f, "%s %d",tempChar,&vertexCount );
            printf( "%d\n",triangleCount);
            printf( "%d\n",vertexCount);
            simpleTriangleArray = (simpleTrianglePointer)malloc(triangleCount * sizeof(simpleTriangle));
            vertexArray = (vertexPointer)malloc(vertexCount * sizeof(vertex));
            for (size_t i = 0; i < triangleCount; i++){
                fscanf( f, "%d %d %d %d",&simpleTriangleArray[i].triangleNumber,&simpleTriangleArray[i].vertexIndex[0],&simpleTriangleArray[i].vertexIndex[1],&simpleTriangleArray[i].vertexIndex[2]);
            }
            for (size_t i = 0; i < vertexCount; i++){
                fscanf( f, "%d %lf %lf %lf %lf %lf %lf",&vertexArray[i].vertexIndex,&vertexArray[i].xyz[0],&vertexArray[i].xyz[1],&vertexArray[i].xyz[2],&vertexArray[i].normalxyz[0],&vertexArray[i].normalxyz[1],&vertexArray[i].normalxyz[2]);
            }
        }else{

            fscanf( f, "%d",&triangleCount );
            fscanf( f, "%s %d",tempChar,&vertexCount );
            printf( "%d\n",triangleCount);
            printf( "%d\n",vertexCount);
            colorTriangleArray = (colorTrianglePointer)malloc(triangleCount * sizeof(colorTriangle));
            vertexArray = (vertexPointer)malloc(vertexCount * sizeof(vertex));
            for (size_t i = 0; i < triangleCount; i++){
                fscanf( f, "%d",&colorTriangleArray[i].triangleNumber);
                for (size_t j = 0; j <3;j++){
                     fscanf( f, "%d",&colorTriangleArray[i].vertexIndex[j]);
                }
                for (size_t j = 0; j <3;j++){
                     fscanf( f, "%d",&colorTriangleArray[i].frontcolor[j]);
                }
                for (size_t j = 0; j <3;j++){
                     fscanf( f, "%d",&colorTriangleArray[i].backcolor[j]);
                }
            }
            //int p = 0;
            for (size_t i = 0; i < vertexCount; i++){
                fscanf( f, "%d %lf %lf %lf %lf %lf %lf",&vertexArray[i].vertexIndex,&vertexArray[i].xyz[0],&vertexArray[i].xyz[1],&vertexArray[i].xyz[2],&vertexArray[i].normalxyz[0],&vertexArray[i].normalxyz[1],&vertexArray[i].normalxyz[2]);
            }
        }
    }
    fclose(f);
    vertexNormalization();

}


void light(){

    GLfloat global_ambient[]  = { 0.1f,  0.1f,  0.1f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    GLfloat light1_ambient[]  = { 0.5f,  0.2f,  0.2f, 1.0f};
    GLfloat light1_diffuse[]  = { 0.5f,  0.2f,  0.2f, 1.0f};
    GLfloat light1_specular[] = { 0.3f,  0.3f,  0.3f, 1.0f};
    GLfloat light1_position[] = { 800.0, 0.0f,   0.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);





    GLfloat light2_ambient[]  = { 0.2f,  0.5f,  0.2f, 1.0f};
    GLfloat light2_diffuse[]  = { 0.2f,  0.5f,  0.2f, 1.0f};
    GLfloat light2_specular[] = { 0.5,  0.5f,  0.5f, 1.0f};
    GLfloat light2_position[] = { 0.0f,  800.0, 0.0f, 1.0f};

    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);



    GLfloat light3_ambient[]  = { 0.2f,  0.2f,  0.5f, 1.0f};
    GLfloat light3_diffuse[]  = { 0.2f,  0.2f,  0.5f, 1.0f};
    GLfloat light3_specular[] = { 0.5f,  0.5f,  0.5f, 1.0f};
    GLfloat light3_position[] = { 0.0f,  0.0f,  800.0f, 1.0f};

    glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);



}

void drawAxis(){
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1000.0,0.0,0.0);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,1000.0,0.0);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,1000.0);
    glEnd();
}
void drawAxis2(){
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(2.5,0.0,0.0);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,0,0.0);
    glVertex3f(0.0,2.5,0.0);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,2.5);
    glEnd();
}
void renderModel(){
    if(!modelType){
        for(size_t i=0;i<triangleCount;i++){
            drawTriangle(vertexArray[simpleTriangleArray[i].vertexIndex[0]].xyz,
                         vertexArray[simpleTriangleArray[i].vertexIndex[1]].xyz,
                         vertexArray[simpleTriangleArray[i].vertexIndex[2]].xyz,
                         vertexArray[simpleTriangleArray[i].vertexIndex[0]].normalxyz,
                         vertexArray[simpleTriangleArray[i].vertexIndex[1]].normalxyz,
                         vertexArray[simpleTriangleArray[i].vertexIndex[2]].normalxyz);
        }
    }else{
        for(size_t i=0;i<triangleCount;i++){
            drawTriangleWithColor(vertexArray[colorTriangleArray[i].vertexIndex[0]].xyz,
                                  vertexArray[colorTriangleArray[i].vertexIndex[1]].xyz,
                                  vertexArray[colorTriangleArray[i].vertexIndex[2]].xyz,
                                  vertexArray[colorTriangleArray[i].vertexIndex[0]].normalxyz,
                                  vertexArray[colorTriangleArray[i].vertexIndex[1]].normalxyz,
                                  vertexArray[colorTriangleArray[i].vertexIndex[2]].normalxyz,
                                  colorTriangleArray[i].frontcolor,
                                  colorTriangleArray[i].backcolor
                                  );
        }
    }

}
GLfloat vertices[][3] = {
{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},{1.0,1.0,-1.0},
{-1.0,1.0,-1.0},{-1.0,-1.0,1.0},{1.0,-1.0,1.0},
{1.0,1.0,1.0},{-1.0,1.0,1.0}
};

void polygon(int a,int b, int c,int d){
    glBegin(GL_POLYGON);
        glColor3fv(colors[a]);
        glVertex3fv(vertices[a]);
        glColor3fv(colors[b]);
        glVertex3fv(vertices[b]);
        glColor3fv(colors[c]);
        glVertex3fv(vertices[c]);
        glColor3fv(colors[d]);
        glVertex3fv(vertices[d]);
    glEnd();
}

void drawline(int a,int b){
    glBegin(GL_LINES);
        glColor3fv(colors[a]);
        glVertex3fv(vertices[a]);
        glColor3fv(colors[b]);
        glVertex3fv(vertices[b]);
    glEnd();
}


void colorCubeLine(){
    drawline(0,4);
    drawline(7,6);
    drawline(5,1);
    drawline(1,0);

    drawline(4,7);
    drawline(6,5);
    drawline(2,1);
    drawline(3,0);

    drawline(3,2);
    drawline(7,3);
    drawline(4,5);
    drawline(6,2);
    //drawline(7,3);

}



void colorCube(){
    polygon(0,3,2,1);//031 321

    polygon(2,3,7,6);//236 376

    polygon(0,4,7,3);//043 473

    polygon(1,2,6,5);//125 265

    polygon(4,5,6,7);//457 567

    polygon(0,1,5,4);//014 154


}


void MatrixMult(float *mat1, float *mat2, float *result)
{
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			result[i*4+j] = 0;
			for(int k=0; k<4; k++){
				result[i*4+j] += mat1[i*4+k]*mat2[k*4+j];
			}
		}
	}
}

void MatrixRotateX(float *mat, float angle){
	angle = angle/180*3.141592653589793238;
	float rot[] = {
		1,0,0,0,
		0,cos(angle),-sin(angle),0,
		0,sin(angle),cos(angle),0,
		0,0,0,1
	};
	float res[16];
	MatrixMult(rot,mat,res);
	for(int i=0; i<16; i++) mat[i] = res[i];
}

void MatrixRotateY(float *mat, float angle){
	angle = angle/180*3.141592653589793238;
	float rot[] = {
		cos(angle),0,sin(angle),0,
		0,1,0,0,
		-sin(angle),0,cos(angle),0,
		0,0,0,1
	};
	float res[16];
	MatrixMult(rot,mat,res);
	for(int i=0; i<16; i++) mat[i] = res[i];
}

void MatrixRotateZ(float *mat, float angle){
	angle = angle/180*3.141592653589793238;
	float rot[] = {
		cos(angle),-sin(angle),0,0,
		sin(angle),cos(angle),0,0,
		0,0,1,0,
		0,0,0,1
	};
	float res[16];
	MatrixMult(rot,mat,res);
	for(int i=0; i<16; i++) mat[i] = res[i];
}

void MatrixIdentity(float *mat)
{
	for(int i=0; i<16; i++) mat[i] = 0;
	for(int i=0; i<4; i++){
		mat[i*4+i] = 1;
	}
}
void MatrixCopy(float *src, float *dest){
	for(int i=0; i<16; i++) dest[i] = src[i];
}

void MatrixTranspose(float *mat)
{
	float temp;
	for(int i=0; i<4; i++){
		for(int j=i+1; j<4; j++){
			temp = mat[i*4+j];
			mat[i*4+j] = mat[j*4+i];
			mat[j*4+i] = temp;
		}
	}
}

void rotate(){
    float trans[16];
	float temp[16];

	MatrixIdentity(temp);
    if(rotateFlag){
        if(prev_rotateX-rotateX)
            MatrixRotateX(temp, rotateX-prev_rotateX);
	    if(prev_rotateY-rotateY)
            MatrixRotateY(temp, rotateY-prev_rotateY);
        if(prev_rotateZ-rotateZ)
            MatrixRotateZ(temp, rotateZ-prev_rotateZ);
	    MatrixMult(matrix,temp,trans);
	    MatrixCopy(trans,matrix);
	    MatrixTranspose(trans);


        prev_rotateX = rotateX;
        prev_rotateY = rotateY;
        prev_rotateZ = rotateZ;

        glMultMatrixf(trans);
    }else{
        rotateFlag = true;

    }

}

int materialType = 1;
    GLfloat polished_silver_ambient[] = {0.23125,0.23125,0.23125,1.0f};
    GLfloat polished_silver_diffuse[] = {0.2775,0.2775,0.2775,1.0f};
    GLfloat polished_silver_specular[] = {0.773911,0.773911,0.773911,1.0f};
    GLfloat polished_silver_shininess[] = {128};
    GLfloat polished_silver_emission[] = {0.069375,0.069375,0.069375,1.0f};

    GLfloat pewter_ambient[] = {0.10588,0.058824,0.113725,1.0f};
    GLfloat pewter_diffuse[] = {0.427451,0.470588,0.541176,1.0f};
    GLfloat pewter_specular[] = {0.3333,0.3333,0.521569,1.0f};
    GLfloat pewter_shininess[] = {9.84615};
    GLfloat pewter_emission[] = {0.106862,0.117647,0.135294,1.0f};

    GLfloat gold_ambient[] = {0.24725,0.1995,0.0745,1.0f};
    GLfloat gold_diffuse[] = {0.75164,0.60648,0.22648,1.0f};
    GLfloat gold_specular[] = {0.628281,0.555802,0.366065,1.0f};
    GLfloat gold_shininess[] = {51.2};
    GLfloat gold_emission[] = {0.18791,0.15162,0.05662,1.0f};

    GLfloat d_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat d_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat d_specular[] = {0, 0, 0, 1};
    GLfloat d_shininess[] = {0};
    GLfloat d_emission[] = {0, 0, 0, 1};


    bool enableMaterial = true;
void material(){



    switch(materialType){
        case 1:
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,gold_ambient);
            glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,gold_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,gold_specular);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,gold_shininess);
            glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gold_emission);
            break;
        case 2:
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,pewter_ambient);
            glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,pewter_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,pewter_specular);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,pewter_shininess);
            glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,pewter_emission);
            break;
        case 3:
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,polished_silver_ambient);
            glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,polished_silver_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,polished_silver_specular);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,polished_silver_shininess);
            glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,polished_silver_emission);
            break;
        default:
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,d_ambient);
            glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,d_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,d_specular);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,d_shininess);
            glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,d_emission);
            break;
    }



}



void render(){

        if(redLight)
            glEnable(GL_LIGHT1);
        else
            glDisable(GL_LIGHT1);
        if(greenLight)
            glEnable(GL_LIGHT2);
        else
            glDisable(GL_LIGHT2);
        if(blueLight)
           glEnable(GL_LIGHT3);
        else
            glDisable(GL_LIGHT3);








        if(renderLine){
            glPolygonMode(GL_FRONT,GL_LINE);
            glPolygonMode(GL_BACK,GL_LINE);
        }else{
            glPolygonMode(GL_FRONT,GL_FILL);
            glPolygonMode(GL_BACK,GL_FILL);
        }
        if(renderFlat){
            glShadeModel(GL_FLAT);
        }else{
            glShadeModel(GL_SMOOTH);
        }

        if(enableMaterial){
            glDisable(GL_COLOR_MATERIAL);
        }else{
            glEnable(GL_COLOR_MATERIAL);
        }
        drawAxis();
        glTranslated(translateX,translateY,translateZ);
        rotate();
        glScaled(scaleX,scaleY,scaleZ);
        if(scaleFlag){
            glScaled(scaleFactor,scaleFactor,scaleFactor);
        }

        if(modelInput){

            glPushMatrix();
            glScaled(totalScaleFactor,totalScaleFactor,totalScaleFactor);
            drawAxis2();
            glPopMatrix();
            if(modelType){
                glRotatef(-90,1.0,0.0,0.0);
            }

            renderModel();
        }else{
            //glCallList(CUBE);
            drawAxis2();
            if(renderLine)
                glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            colorCube();
        }

}





void __fastcall TForm1::init(TObject *Sender){


        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1,0.1,0.1,1.0);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
        MatrixIdentity(matrix);

        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_LIGHTING);
        //glEnable(GL_COLOR_MATERIAL);

}

//---------------------------------------------------------------------------
void __fastcall TForm1::graphicDraw(TObject *Sender){

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-8*totalScaleFactor,8*totalScaleFactor,-5*totalScaleFactor,5*totalScaleFactor,-100*totalScaleFactor,100*totalScaleFactor);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    light();
    material();
    glDisable(GL_COLOR_MATERIAL);

    if(!singleMode){
        glPushMatrix();

        glViewport(0,0,GLBox1->Width/2,GLBox1->Height/2);
        render();
        glPopMatrix();

        glViewport(0,GLBox1->Height/2,GLBox1->Width/2,GLBox1->Height/2);
        glPushMatrix();
        gluLookAt(0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,-1.0);
        render();
        glPopMatrix();

        glViewport(GLBox1->Width/2,0,GLBox1->Width/2,GLBox1->Height/2);
        glPushMatrix();
        gluLookAt(1.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0);
        render();
        glPopMatrix();

        glViewport(GLBox1->Width/2,GLBox1->Height/2,GLBox1->Width/2,GLBox1->Height/2);
        glPushMatrix();
        gluLookAt(1,1,1,0.0,0.0,0.0,0.0,1.0,0.0);
        render();
        glPopMatrix();
    }else{
        glViewport(0,0,GLBox1->Width,GLBox1->Height);
        glPushMatrix();
        gluLookAt(8*totalScaleFactor,8*totalScaleFactor,8*totalScaleFactor,0.0,0.0,0.0,0.0,1.0,0.0);

        render();
        glPopMatrix();
    }
     glFlush();


}
//---------------------------------------------------------------------------


void __fastcall TForm1::XRotateScrollBarChange(TObject *Sender)
{
    XRotateAmount->Caption = XRotateScrollBar->Position;
    rotateX = XRotateScrollBar->Position;

    GLBox1->Invalidate();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::YRotateScrollBarChange(TObject *Sender)
{
    YRotateAmount->Caption = YRotateScrollBar->Position;
    rotateY = YRotateScrollBar->Position;

    GLBox1->Invalidate();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZRotateScrollBarChange(TObject *Sender)
{
    ZRotateAmount->Caption = ZRotateScrollBar->Position;
    rotateZ = ZRotateScrollBar->Position;

    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::XMoveScrollBarChange(TObject *Sender)
{
    XMoveAmount->Caption = XMoveScrollBar->Position;
    translateX = (double)XMoveScrollBar->Position/(100.0 / totalScaleFactor * 10);
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::YMoveScrollBarChange(TObject *Sender)
{
    YMoveAmount->Caption = YMoveScrollBar->Position;
    translateY = (double)YMoveScrollBar->Position/(100.0 / totalScaleFactor * 10);
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZMoveScrollBarChange(TObject *Sender)
{
    ZMoveAmount->Caption = ZMoveScrollBar->Position;
    translateZ = (double)ZMoveScrollBar->Position/(100.0 / totalScaleFactor * 10);
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::XScaleScrollBarChange(TObject *Sender)
{
    XScaleAmount->Caption = XScaleScrollBar->Position;
    if(scaleFlag){
        scaleFactor = (double)XScaleScrollBar->Position/(scaleX*100);
    }else{
        //XScaleAmount->Caption = XScaleScrollBar->Position;
        scaleX = (double)XScaleScrollBar->Position/100.0;
    }
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::YScaleScrollBarChange(TObject *Sender)
{
    YScaleAmount->Caption = YScaleScrollBar->Position;
    scaleY = (double)YScaleScrollBar->Position/100.0;
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZScaleScrollBarChange(TObject *Sender)
{
    ZScaleAmount->Caption = ZScaleScrollBar->Position;
    scaleZ = (double)ZScaleScrollBar->Position/100.0;
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ResetRotateButtonClick(TObject *Sender)
{
    //rotateSpecial();
    prev_rotateX = 0;
    prev_rotateY = 0;
    prev_rotateZ = 0;

    rotateFlag = false;
    XRotateScrollBar->Position = 0;
    YRotateScrollBar->Position = 0;
    ZRotateScrollBar->Position = 0;
    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;
    MatrixIdentity(matrix);
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ResetMoveButtonClick(TObject *Sender)
{
    XMoveScrollBar->Position = 0;
    YMoveScrollBar->Position = 0;
    ZMoveScrollBar->Position = 0;
    XMoveScrollBarChange(Sender);
    YMoveScrollBarChange(Sender);
    ZMoveScrollBarChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ResetScaleGroupClick(TObject *Sender)
{
    XScaleScrollBar->Position = 100;
    YScaleScrollBar->Position = 100;
    ZScaleScrollBar->Position = 100;
    XScaleScrollBarChange(Sender);
    YScaleScrollBarChange(Sender);
    ZScaleScrollBarChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChangeSingleMode(TObject *Sender)
{
    singleMode = true;
    GLBox1->Invalidate();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChangeMultiMode(TObject *Sender)
{
    singleMode = false;
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::checkScale(TObject *Sender)
{

    if(ScaleCheckBox->Checked){
        YScaleScrollBar->Enabled = false;
        ZScaleScrollBar->Enabled = false;
        YScaleAmount->Caption = YScaleScrollBar->Position;
        ZScaleAmount->Caption = ZScaleScrollBar->Position;
        scaleX = (double)XScaleScrollBar->Position/100.0;
        scaleY = (double)YScaleScrollBar->Position/100.0;
        scaleZ = (double)ZScaleScrollBar->Position/100.0;
        scaleFlag = true;
        GLBox1->Invalidate();
    }else{
        YScaleScrollBar->Enabled = true;
        ZScaleScrollBar->Enabled = true;

        scaleX = (double)XScaleScrollBar->Position/100.0;
        scaleY = (double)((YScaleScrollBar->Position/100.0 )*scaleFactor);
        YScaleScrollBar->Position = (int)(scaleY*100);
        scaleZ = (double)((ZScaleScrollBar->Position/100.0 )*scaleFactor);
        ZScaleScrollBar->Position = (int)(scaleZ*100);
        YScaleAmount->Caption = YScaleScrollBar->Position;
        ZScaleAmount->Caption = ZScaleScrollBar->Position;
        scaleFlag = false;

        GLBox1->Invalidate();
    }
    scaleFactor = XScaleScrollBar->Position / (scaleX*100);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::readFileClicked(TObject *Sender){
    modelOpener->Title = "¿ï¾Ü¼Ò«¬ÀÉ";
    if(modelOpener->Execute()){
        fileName = modelOpener->FileName;
        readModel();
    }
    modelInput = true;
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::redLightCheckBoxClick(TObject *Sender)
{
    redLight = (redLightCheckBox->Checked)? true:false;
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::greenLightCheckBoxClick(TObject *Sender)
{
    greenLight = (greenLightCheckBox->Checked)? true:false;
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::blueLightCheckBoxClick(TObject *Sender)
{
    blueLight = (blueLightCheckBox->Checked)? true:false;
    GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::colorcubeRadioClick(TObject *Sender)
{
modelInput = false;
totalScaleFactor = 1.0;
GLBox1->Invalidate();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::disableMaterialRadioClick(TObject *Sender)
{
enableMaterial = false;
materialType = 4;
GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::goldRadioClick(TObject *Sender)
{
glDisable(GL_COLOR_MATERIAL);
enableMaterial = true;
materialType = 1;
GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pewterRadioClick(TObject *Sender)
{
glDisable(GL_COLOR_MATERIAL);
enableMaterial = true;
materialType = 2;
GLBox1->Invalidate();
}

//---------------------------------------------------------------------------

void __fastcall TForm1::silverRadioClick(TObject *Sender)
{
glDisable(GL_COLOR_MATERIAL);
enableMaterial = true;
materialType = 3;
GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::smoothRadioClick(TObject *Sender)
{
renderFlat = false;
GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::flatRadioClick(TObject *Sender)
{
renderFlat = true;
GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::fillRadioClick(TObject *Sender)
{
renderLine = false;
GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::lineRadioClick(TObject *Sender)
{
renderLine = true;
GLBox1->Invalidate();
}
//---------------------------------------------------------------------------

