// Iftekhar Hyder ID: 011163012

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>



using namespace std;




double angle = 0;
double incx=0, incy;
bool gameOver = false;
int state;
int lastscore = 0;
int points[120][2];
double colorx = 0.0, colory = 1.0, colorz = 0.0;
double px, py, rx = -100, ry=150, bx=100, by=150;
double playerx=0, playery=0;
double b_angle = 90;
bool coin_enlarge = true;
int global_it = 0;
bool blastNow = false;
double last_hx, last_hy;
int hp = 12;
int hp_width = 100;
string playerColor;
double b_s = 0;
int back_freq = 0;
double cx, cy, c2x, c2y, c3x, c3y, c4x, c4y, c5x, c5y, c6x, c6y, c7x, c7y, hx, hy;
double _px = 0;
double _py = 0;
double c_a, c2_a, c3_a, c4_a, c5_a, c6_a, c7_a;
double c_s, c2_s, c3_s, c4_s, c5_s, c6_s, c7_s, h_s;
bool blast = false;
double blx, bly;
double h_a;
double coin_size = 0;
double coinx, coiny;
bool homing = false;
double co_s;
double coin_a;
int score = 0;
int level = 1;
int timer_time = 0;
bool keyUp, keyLeft, keyRight, keyDown;
bool pause = false;
int high_score = 0;
int timx = 0;

float getColor(int x){
    //cout << (float)x/255 << endl;
    return (float)x/255;

}
void* currentFont;
void timer(int x){
    timx += 1;
    blast = false;
    blastNow = false;
    cout << timx << endl;
    glutPostRedisplay();
}

void timer2(int x){

    blast = false;
    glutPostRedisplay();
}

void loadHighScore(){
	FILE *file = fopen("score.txt", "r");
	if(file == NULL){
	  printf("Highscore file not found");
	  FILE *file2 = fopen("score.txt", "w");
	  fprintf(file2, "%d", high_score);
	  fclose(file2);
	}else{
		fscanf(file, "%d", &high_score);
	}

	fclose(file);
}
void writeHighScore(){
	FILE *file = fopen("score.txt", "w");

	if(file == NULL){
	  printf("Highscore file not found");
	}else{
		fprintf(file, "%d", high_score);
	}

	fclose(file);

}


void setFont(void* font) {
  currentFont = font;
}

void drawString(float x, float y, float z, char *string) {
  glRasterPos3f(x, y, z);

  for (char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(currentFont, *c);  // Updates the position
  }
}

int rectCollision(int rectx, int recty, int rectwidth, int rectheight, int rect2x, int rect2y, int rect2width, int rect2height){

	if (rectx < rect2x + rect2width &&
      rectx + rectwidth > rect2x &&
      recty < rect2y + rect2height &&
      rectheight + recty > rect2y) {
		  return true;

   }else{
	   return false;
	}
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
        case 32:
            //score += 5;
            if(gameOver){
                gameOver = false;
            }
            break;
        case 'r':
            break;
        case 'b':
            break;
        case 'g':
            break;
        case 'w':
            incx+=1;
            break;
        case 'd':
            //code
            break;

		default:
			break;
	}
}
void specialKeyUp(int key, int x, int y){
    switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
		    keyDown = false;
            break;
		case GLUT_KEY_UP:
		    keyUp = false;
			break;
		case GLUT_KEY_RIGHT:
		    keyRight = false;
			break;
		case GLUT_KEY_LEFT:
           keyLeft = false;
           break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
		    //code
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}
void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
		    keyDown = true;
            break;
		case GLUT_KEY_UP:
		    keyUp = true;
			break;
		case GLUT_KEY_RIGHT:
		    keyRight = true;
			break;
		case GLUT_KEY_LEFT:
           keyLeft = true;
           break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
		    //code
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void draw_tri()
{
    glBegin(GL_POLYGON);
        glVertex2f(10, 10);
        glVertex2f(10, 0);
        glVertex2f(-10, 0);
    glEnd();
}


void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glVertex3f( 250,0,0);
        glVertex3f(-250,0,0);

        glVertex3f(0,-250,0);
        glVertex3f(0, 250,0);

        glVertex3f(0,0, 250);
        glVertex3f(0,0,-2);
    }glEnd();

}


void drawGrid()
{
	int i;

    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-8;i<=8;i++){

            if(i==0)
                continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*10, 0);
            glVertex3f( 90, i*10, 0);
        }
    }glEnd();

}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}



void rec_animation()
{
    glColor3f(0,1,0);
    //glRotatef(5*angle,0,0,1);

    glTranslatef(incx,incy,0);

    glRotatef(50*angle,0,0,1);
    drawSquare(1);

}
void draw_rec()
{

    drawSquare(5);

}
void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);
    //glPushMatrix();
    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);
    //glPopMatrix();

    glRotatef(angle,0,0,1);
    glTranslatef(60,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,0,1);
    drawSquare(10);




}

void simple_trans()
{


    glTranslatef(0, 20, 0);
    glRotatef(45, 0, 0, 1);

    glColor3f(0.0, 0.0, 1.0);
    draw_rec();


    glPushMatrix();
        glTranslatef(-20, 0, 0);
        glRotatef(45, 0, 0, 1);
        glColor3f(0.0, 1.0, 0.0);
        draw_rec();
    glPopMatrix();


    glTranslatef(20, 0, 0);
    //glRotatef(45, 0, 0, 1);

    glColor3f(1.0, 0.0, 0.0);
    draw_rec();

}
double curve_by_points()
{
    ///
}
double func(double x)
{
    return x*x;
}
void curve()
{
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    for(double i =-180; i<180;i+=.5)
    {
        glVertex2d(i,10*func(i));
        glVertex2d(i+.5, 10*func(i+.5));
    }
     // It can be any type Gl_POINT,_LINE
    glEnd();

}

void drawPlayer(){
    if(playerColor == "blue"){
        glColor3f(getColor(0), getColor(0), getColor(255));
    }else if(playerColor == "yellow"){
        glColor3f(getColor(255), getColor(255), getColor(0));
    }else if(playerColor == "orange"){
        glColor3f(getColor(204), getColor(102), getColor(0));
    }else if(playerColor == "red"){
        glColor3f(getColor(255), getColor(0), getColor(0));
    }

     glBegin(GL_QUADS);
		glVertex3f(-5, 5, 0);
		glVertex3f(5, 5, 0);
		glVertex3f(5,-5,0);
		glVertex3f(-5, -5,0);
	glEnd();
}
void drawCap(){
    if(playerColor == "blue"){
        glColor3f(getColor(148), getColor(0), getColor(211));
    }else if(playerColor == "yellow"){
        glColor3f(getColor(255), getColor(255), getColor(0));
    }else if(playerColor == "orange"){
        glColor3f(getColor(204), getColor(102), getColor(0));
    }else if(playerColor == "red"){
        glColor3f(getColor(255), getColor(0), getColor(0));
    }

    glBegin(GL_POLYGON);
        glVertex2f(-5, 5);
        glVertex2f(5, 5);
        glVertex2f(0, 10);
    glEnd();
}
void drawWings(){
    if(playerColor == "blue"){
        glColor3f(getColor(255), getColor(0), getColor(127));
    }else if(playerColor == "yellow"){
        glColor3f(getColor(255), getColor(255), getColor(0));
    }else if(playerColor == "orange"){
        glColor3f(getColor(204), getColor(102), getColor(0));
    }else if(playerColor == "red"){
        glColor3f(getColor(255), getColor(0), getColor(0));
    }

    glBegin(GL_POLYGON);
        glVertex2f(-5, 5);
        glVertex2f(-5, -5);
        glVertex2f(-10, -5);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(5, 5);
        glVertex2f(5, -5);
        glVertex2f(10, -5);
    glEnd();
}
void drawBorder(){
    glColor3f(1, 1, 1);
     glBegin(GL_QUADS);
		glVertex3f(-250, 200, 0);
		glVertex3f(250, 200, 0);
		glVertex3f(250 ,200-10,0);
		glVertex3f(-250, 200-10, 0);
	glEnd();
}
void pointStars(){

    int x = 0;
    int y = 0;
    for(int i = 0; i <= 120; i ++){
        if(i >= 0 && i <= 30){
            points[i][y] = rand()%250;
            points[i][y+1] = rand()%250;
        }else if(i >= 30 && i <= 60){
            points[i][y] = -(rand()%250);
            points[i][y+1] = rand()%250;
        }else if(i >= 60 && i <= 90){
            points[i][y] = -(rand()%250);
            points[i][y+1] = -(rand()%250);
        }else if(i >= 90 && i <= 120){
            points[i][y] = rand()%250;
            points[i][y+1] = -(rand()%250);
        }else{

        }

        if(y >= 1){
            y = 0;
        }else{
          y += 1;
        }

    }


}


void drawStars(){
    glColor3f(getColor(236), getColor(252), getColor(5));
    glPointSize(2.0);
    glBegin(GL_POINTS);
    int j = 0;
    int index = 0;
    for(int i = 0; i < 120; i ++){

        glVertex3f(points[i][j], points[i][j+1], 0);
        if(j == 0){
            j += 1;
        }else{
            j = 0;
        }
    }
    glEnd();
}
void drawBackground(){


    drawStars();


    glColor3f(0, 0, 0);
     glBegin(GL_QUADS);
		glVertex3f(-250, -250, 0);
		glVertex3f(-250, 250, 0);
		glVertex3f(250 , 250,0);
		glVertex3f(250, -250, 0);
	glEnd();


}
void drawHP(){

    glColor3f(1, 0, 0);
     glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(hp_width, 0, 0);
		glVertex3f(hp_width , 20,0);
		glVertex3f(0, 20, 0);
	glEnd();

	glColor3f(0, 0, 1);
     glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(100, 0, 0);
		glVertex3f(100, 20,0);
		glVertex3f(0, 20, 0);
	glEnd();


}
void drawRed(){
glColor3f(1, 0, 0);
     glBegin(GL_QUADS);
		glVertex3f(rx, ry, 0);
		glVertex3f(rx+10, ry, 0);
		glVertex3f(rx+10,ry-10,0);
		glVertex3f(rx, ry-10, 0);
	glEnd();

}
void drawBlue(){
glColor3f(0, 0, 1);
     glBegin(GL_QUADS);
		glVertex3f(bx, by, 0);
		glVertex3f(bx+10, by, 0);
		glVertex3f(bx+10,by-10,0);
		glVertex3f(bx, by-10, 0);
	glEnd();

}

void drawStar(){
    glColor3f(getColor(255), getColor(0), getColor(0));
    glBegin(GL_POLYGON);
    /*
        glVertex2f(cx, cy+5);
        glVertex2f(cx-5, cy-5);
        glVertex2f(cx+5, cy-5);
    */
    /*
        glVertex2f(0, 5);
        glVertex2f(-5, -5);
        glVertex2f(5, -5);
    */
    glVertex2f(0, 5);
    glVertex2f(5, 2);
    glVertex2f(5, -2);
    glVertex2f(0, -5);
    glVertex2f(-5, -2);
    glVertex2f(-5, 2);
    glEnd();
}
void drawStar2(){
    glColor3f(getColor(236), getColor(252), getColor(5));
    glBegin(GL_POLYGON);
    /*
        glVertex2f(c2x, c2y+5);
        glVertex2f(c2x-5, c2y-5);
        glVertex2f(c2x+5, c2y-5);
    */
       glVertex2f(0, 5);
    glVertex2f(5, 2);
    glVertex2f(5, -2);
    glVertex2f(0, -5);
    glVertex2f(-5, -2);
    glVertex2f(-5, 2);
    glEnd();
}
void drawStar3(){
    glColor3f(getColor(0), getColor(0), getColor(255));
    glBegin(GL_POLYGON);
    /*
        glVertex2f(c3x, c3y+5);
        glVertex2f(c3x-5, c3y-5);
        glVertex2f(c3x+5, c3y-5);
        */
        glVertex2f(0, 5);
    glVertex2f(5, 2);
    glVertex2f(5, -2);
    glVertex2f(0, -5);
    glVertex2f(-5, -2);
    glVertex2f(-5, 2);
    glEnd();
}
void drawStar4(){
    glColor3f(getColor(100), getColor(130), getColor(80));
    glBegin(GL_POLYGON);
    /*
        glVertex2f(c3x, c3y+5);
        glVertex2f(c3x-5, c3y-5);
        glVertex2f(c3x+5, c3y-5);
        */
        glVertex2f(0, 5);
    glVertex2f(5, 2);
    glVertex2f(5, -2);
    glVertex2f(0, -5);
    glVertex2f(-5, -2);
    glVertex2f(-5, 2);
    glEnd();
}
void drawStar5(){
    glColor3f(getColor(200), getColor(200), getColor(210));
    glBegin(GL_POLYGON);
    /*
        glVertex2f(c3x, c3y+5);
        glVertex2f(c3x-5, c3y-5);
        glVertex2f(c3x+5, c3y-5);
        */
        glVertex2f(0, 5);
    glVertex2f(5, 2);
    glVertex2f(5, -2);
    glVertex2f(0, -5);
    glVertex2f(-5, -2);
    glVertex2f(-5, 2);
    glEnd();
}
void drawStar6(){
    glColor3f(getColor(200), getColor(200), getColor(210));
    glBegin(GL_POLYGON);
    /*
        glVertex2f(c3x, c3y+5);
        glVertex2f(c3x-5, c3y-5);
        glVertex2f(c3x+5, c3y-5);
        */
        glVertex2f(0, 5);
    glVertex2f(5, 2);
    glVertex2f(5, -2);
    glVertex2f(0, -5);
    glVertex2f(-5, -2);
    glVertex2f(-5, 2);
    glEnd();
}
void drawStar7(){
    glColor3f(getColor(200), getColor(200), getColor(210));
    glBegin(GL_POLYGON);
    /*
        glVertex2f(c3x, c3y+5);
        glVertex2f(c3x-5, c3y-5);
        glVertex2f(c3x+5, c3y-5);
        */
        glVertex2f(0, 5);
    glVertex2f(5, 2);
    glVertex2f(5, -2);
    glVertex2f(0, -5);
    glVertex2f(-5, -2);
    glVertex2f(-5, 2);
    glEnd();
}

void drawHoming(){
    glColor3f(getColor(255), getColor(0), getColor(0));
    glBegin(GL_TRIANGLES);
    /*
        glVertex2f(c3x, c3y+5);
        glVertex2f(c3x-5, c3y-5);
        glVertex2f(c3x+5, c3y-5);
        */
    glVertex2f(0, 15);
    glVertex2f(10, 0);
    glVertex2f(-10, 0);
    glEnd();
}

void drawBlast(float radius_x, float radius_y){
int i = 0;
	float angle = 0.0;



	glBegin(GL_POLYGON);
    {
		for(i = 0; i < 100; i++)
		{
			angle = 2 * 3.1416 * i / 100;

			glColor3f(getColor(236), getColor(252), getColor(5));

			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);

		}

    }
	glEnd();
}
void drawCoin(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;



	glBegin(GL_POLYGON);
    {
		for(i = 0; i < 100; i++)
		{
			angle = 2 * 3.1416 * i / 100;

			glColor3f(getColor(236), getColor(252), getColor(5));

			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);

		}

    }
	glEnd();
}

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();


	gluLookAt(0,0,250,	0,0,0,	0,1,0);



	//glMatrixMode(GL_MODELVIEW);

	//drawAxes();
	//drawGrid();


    if(gameOver){
        glColor3f(1, 1, 1);
        char str[80];
        sprintf(str, "Score: %d", lastscore);

        drawString(-10, 10, 0, str);



        glColor3f(1, 1, 1);
        char str2[80];
        sprintf(str2, "Game OVER! :'|");

        drawString(-30, -10, 0, str2);

        glColor3f(1, 1, 1);
        char str3[80];
        sprintf(str3, "Press SPACEBAR to restart");

        drawString(-50, -30, 0, str3);

        glColor3f(1, 1, 1);
        char str4[80];
        sprintf(str4, "High Score: %d", high_score);

        drawString(-20, 30, 0, str4);




        glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
		glVertex3f(-250, -250, 0);
		glVertex3f(-250, 250, 0);
		glVertex3f(250 , 250,0);
		glVertex3f(250, -250, 0);
        glEnd();
    }
    glColor3f(0, 1, 0);
    char str0[80];
    sprintf(str0, "HP: %d%%", hp_width);

    drawString(100+(100/2 - 20), 130.5+6, 0, str0);


    glPushMatrix();
        glTranslatef(100, 130.5, 0);
        drawHP();

    glPopMatrix();

    glColor3f(1, 1, 1);

    /*
    ostringstream str;
    str << 'Score: ' << score;
    const char *text = str.str().c_str();

    */


    char str[80];
    sprintf(str, "Score: %d", score);

    drawString(130, 180, 0, str);
    glColor3f(0, 0, 1);
    char str2[80];
    sprintf(str2, "Level: %d", level);

    drawString(130, 160, 0, str2);

    glColor3f(0, 1, 0);
    char str3[80];
    sprintf(str3, "High Score: %d", high_score);

    drawString(100, 100, 0, str3);

    glPushMatrix();
        glTranslatef(coinx, coiny, 0);
        glScalef(coin_size, coin_size, 0);
        drawCoin(5, 5);

        glPopMatrix();

        if(homing){

           glPushMatrix();
        glTranslatef(hx, hy, 0);
        glScalef(coin_size, coin_size, 0);
        glRotatef(h_a, 0, 0, 1);

        drawHoming();

        glPopMatrix();
        }

        if(blast == true){
            glPushMatrix();
        glTranslatef(blx, bly, 0);

        drawBlast(b_s, b_s);

        glPopMatrix();
        }

        glPushMatrix();
        glTranslatef(cx, cy, 0);
        glRotatef(c_a, 0, 0, 1);

        drawStar();

        glPopMatrix();

        glPushMatrix();
        glTranslatef(c2x, c2y, 0);
        glRotatef(c2_a, 0, 0, 1);

        drawStar2();

        glPopMatrix();

        glPushMatrix();
        glTranslatef(c3x, c3y, 0);
        glRotatef(c3_a, 0, 0, 1);

        drawStar3();

        glPopMatrix();

        glPushMatrix();
        glTranslatef(c4x, c4y, 0);
        glRotatef(c4_a, 0, 0, 1);

        drawStar4();

        glPopMatrix();

        glPushMatrix();
        glTranslatef(c5x, c5y, 0);
        glRotatef(c5_a, 0, 0, 1);

        drawStar5();

        glPopMatrix();

        glPushMatrix();
        glTranslatef(c6x, c6y, 0);
        glRotatef(c6_a, 0, 0, 1);

        drawStar6();

        glPopMatrix();

        glPushMatrix();
        glTranslatef(c7x, c7y, 0);
        glRotatef(c7_a, 0, 0, 1);

        drawStar7();

        glPopMatrix();



     glPushMatrix();

     glTranslatef(0, 0, 0);
     //cout << "X: " << "(" << player.x << ", Y: " << player.y << ")" << endl;


        glPushMatrix();
            glTranslatef(playerx, playery, 0);
            glRotatef(angle, 0, 0, 1);
            drawWings();
            drawCap();
            drawPlayer();
        glPopMatrix();


    glPopMatrix();


        glPushMatrix();
            glRotatef(b_angle, 0, 0, 1);
            drawBackground();
        glPopMatrix();


    //glPopMatrix();





    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){



   if(keyUp){
    py += 0.2;
    playery = py;
   }if(keyDown){
    py -= 0.2;
    playery = py;
   }if(keyLeft){
    px -= 0.2;
    playerx = px;
   }if(keyRight){
    px += 0.2;
    playerx = px;
   }
  // cout << playerx << ", " << playery << endl;
   if(playerx <= -204){
    //cout << "Border" << endl;
    playerx = -204;
   }
   if(playerx >= 204){
    //cout << "Border" << endl;
    playerx = 204;
   }

   if(playery >= 204){
    //cout << "Border" << endl;
    playery = 204;
   }
   if(playery <= -204){
    //cout << "Bordery" << endl;
    playery = -204;
   }

    if(score == 5){
        level = 2;
    }else if(score == 10){
        level = 3;
    }else if(score == 15){
        level = 4;
    }else if(score == 20){
        level = 5;
    }else if(score == 25){
        level = 6;
    }else if(score == 30){
        level = 7;
    }else if(score == 35){
        level = 8;
    }else if(score == 40){
        level = 9;
    }else if(score == 45){
        level = 10;
    }else{

    }

    if(level == 1){

        c_s = 0.02;
        c2_s = 0.05;
        c3_s = 0.01;
        c4_s = 0.02;
        c5_s = 0.06;
        c6_s = 0.04;
        c7_s = 0.12;
        h_s = 0.02;

    }else if(level == 2){
        c_s = 0.07;
        c2_s = 0.10;
        c3_s = 0.05;
        c4_s = 0.08;
        c5_s = 0.14;
        c6_s = 0.22;
        c7_s = 0.20;

        homing = true;



        h_s = 0.08;
    }else if(level == 3){


        c_s = 0.15;
        c2_s = 0.17;
        c3_s = 0.10;
        c4_s = 0.14;
        c5_s = 0.13;
        c6_s = 0.30;
        c7_s = 0.26;
        homing = false;
        if(global_it == 0){
            blx = hx;
            bly = hy;
            blast = true;

            global_it += 1;
        }else{
            global_it = 1;
        }
        glutTimerFunc(300, timer2, 0);
        h_s = 0.02;

    }else if(level == 4){
        c_s = 0.15;
        c2_s = 0.17;
        c3_s = 0.10;
        c4_s = 0.14;
        c5_s = 0.13;
        c6_s = 0.30;
        c7_s = 0.26;
        homing = false;
        global_it = 0;

        h_s = 0.13;

    }else if(level == 5){
        c_s = 0.15;
        c2_s = 0.17;
        c3_s = 0.10;
        c4_s = 0.14;
        c5_s = 0.13;
        c6_s = 0.30;
        c7_s = 0.26;

        homing = true;

        h_s = 0.13;

    }else if(level == 6){

        c_s = 0.15;
        c2_s = 0.17;
        c3_s = 0.10;
        c4_s = 0.14;
        c5_s = 0.13;
        c6_s = 0.30;
        c7_s = 0.26;
        homing = false;
        if(global_it == 0){
            blx = hx;
            bly = hy;
            blast = true;
            global_it += 1;
        }else{
            global_it = 1;
        }
        glutTimerFunc(300, timer2, 0);

        h_s = 0.13;

    }else if(level == 7){
        c_s = 0.15;
        c2_s = 0.17;
        c3_s = 0.10;
        c4_s = 0.14;
        c5_s = 0.13;
        c6_s = 0.30;
        c7_s = 0.26;
        h_s = 0.13;
        homing = true;
        global_it = 0;



    }else if(level == 8){

        c_s = 0.15;
        c2_s = 0.17;
        c3_s = 0.10;
        c4_s = 0.14;
        c5_s = 0.13;
        c6_s = 0.30;
        c7_s = 0.26;
        h_s = 0.13;
        homing = false;
        if(global_it == 0){
            blx = hx;
            bly = hy;
            blast = true;
            global_it += 1;
        }else{
            global_it = 1;
        }
        glutTimerFunc(300, timer2, 0);


    }else if(level == 9){
        c_s = 0.15;
        c2_s = 0.17;
        c3_s = 0.10;
        c4_s = 0.14;
        c5_s = 0.13;
        c6_s = 0.30;
        c7_s = 0.26;

        homing = true;
        global_it = 0;


        h_s = 0.13;


    }else if(level == 10){


        c_s = 0.15;
        c2_s = 0.17;
        c3_s = 0.10;
        c4_s = 0.14;
        c5_s = 0.13;
        c6_s = 0.30;
        c7_s = 0.26;
        h_s = 0.13;
        homing = false;
        if(global_it == 0){
            blx = hx;
            bly = hy;
            blast = true;
            global_it += 1;
        }else{
            global_it = 1;
        }
        glutTimerFunc(300, timer2, 0);


    }else{

    }

    if(gameOver){

        cx =  -204 + rand() % ( 204 - (-204) + 1 );
        cy = 204;

        c2x = -204 + rand() % ( 204 - (-204) + 1 );
        c2y = 204;

        c3x = -204 + rand() % ( 204 - (-204) + 1 );
        c3y =  204;

        c4x = -204 + rand() % ( 204 - (-204) + 1 );
        c4y =  204;

        c5x = -204 + rand() % ( 204 - (-204) + 1 );
        c5y =  204;

        c6x = -204 + rand() % ( 204 - (-204) + 1 );
        c6y =  250;

        c7x = -204 + rand() % ( 204 - (-204) + 1 );
        c7y =  204;

        c_s = 0.02;
        c2_s = 0.05;
        c3_s = 0.01;
        c4_s = 0.02;
        c5_s = 0.06;
        c6_s = 0.04;
        c7_s = 0.12;
        h_s = 0.13;

        score = 0;
        level = 1;
        hp = 12;
        hp_width = 100;
        playerColor = "blue";
        homing = false;

    }

     if(hp == 0){
        gameOver= true;
        lastscore = score;
    }else if(hp == 9){
      playerColor = "yellow";
    }else if(hp == 6){
      playerColor = "orange";
    }else if(hp == 3){
      playerColor = "red";
    }

    if(score > high_score){
        high_score = score;
        writeHighScore();
    }

    cy -= c_s;
    c2y -= c2_s;
    c3y -= c3_s;
    c4y -= c4_s;
    c5y -= c5_s;
    c6y -= c6_s;
    c7y -= c7_s;
    coiny -= co_s;

    // rotation
    c_a += 0.10;
    c2_a += 0.10;
    c3_a += 0.10;
    c4_a += 0.10;
    c5_a += 0.10;
    c6_a += 0.10;
    c7_a += 0.10;
    h_a  += 0.10;
    coin_a += 0.10;

    if(cy <= -204){
        cx =  -204 + rand() % ( 204 - (-204) + 1 );
        cy = 204;
    }
    if(c2y <= -204){
        c2x =  -204 + rand() % ( 204 - (-204) + 1 );
        c2y = 204;
    }

    if(c3y <= -204){
        c3x =  -204 + rand() % ( 204 - (-204) + 1 );
        c3y = 204;
    }

    if(c4y <= -204){
        c4x =  -204 + rand() % ( 204 - (-204) + 1 );
        c4y = 204;
    }
    if(c5y <= -204){
        c5x =  -204 + rand() % ( 204 - (-204) + 1 );
        c5y = 204;
    }
     if(coiny <= -204){
        coinx =  -204 + rand() % ( 204 - (-204) + 1 );
        coiny = 204;
    }

    if(homing){
        double dirx = playerx  - hx;
        double diry = playery - hy;
        double hyp = sqrt(dirx * dirx + diry * diry);
        dirx /= hyp;
        diry /= hyp;
        hx += dirx * h_s;
        hy += diry * h_s;

    }





    if(blast == true){
        b_s += 0.1;
    }else{
        b_s = 0;
    }




    if(rectCollision(playerx, playery, 15, 10, coinx, coiny, 5, 5)){
        score += 1;
        coinx =  -204 + rand() % ( 204 - (-204) + 1 );
        coiny = 204;

        PlaySound(TEXT("eat.wav"), NULL, SND_FILENAME | SND_ASYNC);

    }else{

    }

    if(rectCollision(playerx, playery, 15, 10, cx, cy, 5, 5)){
        cx =  -204 + rand() % ( 204 - (-204) + 1 );
        cy = 204;
        hp -= 3;
        hp_width -= 25;
        PlaySound(TEXT("hit1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }else{

    }

    if(rectCollision(playerx, playery, 15, 10, c2x, c2y, 5, 5)){
        c2x =  -204 + rand() % ( 204 - (-204) + 1 );
        c2y = 204;
        hp -= 3;
        hp_width -= 25;
        PlaySound(TEXT("hit1.wav"), NULL, SND_FILENAME | SND_ASYNC);

    }else{

    }
    if(rectCollision(playerx, playery, 15, 10, c3x, c3y, 5, 5)){

        c3x =  -204 + rand() % ( 204 - (-204) + 1 );
        c3y = 204;
        hp -= 3;
        hp_width -= 25;
        PlaySound(TEXT("hit1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }else{

    }
    if(rectCollision(playerx, playery, 15, 10, c4x, c4y, 5, 5)){

        c4x =  -204 + rand() % ( 204 - (-204) + 1 );
        c4y = 204;
        hp -= 3;
        hp_width -= 25;
        PlaySound(TEXT("hit1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }else{

    }
    if(rectCollision(playerx, playery, 15, 10, c5x, c5y, 5, 5)){

        c5x =  -204 + rand() % ( 204 - (-204) + 1 );
        c5y = 204;
        hp -= 3;
        hp_width -= 25;
        PlaySound(TEXT("hit1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }else{

    }
    if(rectCollision(playerx, playery, 15, 10, c6x, c6y, 5, 5)){

        c6x =  -204 + rand() % ( 204 - (-204) + 1 );
        c6y = 204;
        hp -= 3;
        hp_width -= 25;
        PlaySound(TEXT("hit1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }else{

    }
    if(rectCollision(playerx, playery, 15, 10, c7x, c7y, 5, 5)){

        c7x =  -204 + rand() % ( 204 - (-204) + 1 );
        c7y = 204;
        hp -= 3;
        hp_width -= 25;
        PlaySound(TEXT("hit1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }else{

    }
    if(rectCollision(playerx, playery, 15, 10, hx, hy, 5, 5)){
        blast = true;
        blx = playerx;
        bly = playery;
        glutTimerFunc(300.0, timer, 0);


        hx =  -204 + rand() % ( 204 - (-204) + 1 );
        int d = rand() % 2;
        if(d == 0){
            hy = -204;
        }else{
            hy = 204;
        }
        hp -= 3;
        hp_width -= 25;
        PlaySound(TEXT("hit2.wav"), NULL, SND_FILENAME | SND_ASYNC);


    }else{

    }







    if(coin_size <= 0){
        coin_enlarge = true;
    }else if(coin_size >= 2){
        coin_enlarge = false;
    }

    if(coin_enlarge){
        coin_size += 1;
    }else{
        coin_size -= 1;
    }


    /*
    */

    b_angle += 0.02;

    if(b_angle > 360){
        b_angle = -360;
    }

    if(c_a > 360){
        c_a = 0;
    }

    if(c2_a > 360){
        c2_a = 0;
    }

    if(c3_s > 360){
        c3_s = 0;
    }

    if(c4_a > 360){
        c4_a = 0;
    }

    if(c5_a > 360){
        c5_a = 0;
    }

    if(c6_a > 360){
        c6_a = 0;
    }
    if(c7_a > 360){
        c7_a = 0;
    }

    if(coin_a > 360){
        coin_a = 0;
    }
     if(h_a > 360){
        h_a = 0;
    }






	glutPostRedisplay();
}
void printPoints(){
 for(int i=0; i<120; i++)
        {
                for(int j=0; j<2; j++)
                {
                        cout<<" "<<points[i][j]<<" ";
                }
                cout<<"\n";
        }
}

void initStars(){

}
void init(){
	//codes for initialization


    srand (time(NULL));
    gameOver = false;
    playerColor = "blue";
    homing = false;
    b_s = 10;
    hp = 12;
    hp_width = 100;
    blast = false;



    _px = playerx;
    _py = playery;

    cx =  -204 + rand() % ( 204 - (-204) + 1 );
    cy = 204;

    c2x = -204 + rand() % ( 204 - (-204) + 1 );
    c2y = 204;

    c3x = -204 + rand() % ( 204 - (-204) + 1 );
    c3y =  204;

    c4x = -204 + rand() % ( 204 - (-204) + 1 );
    c4y =  204;

    c5x = -204 + rand() % ( 204 - (-204) + 1 );
    c5y =  204;

    c6x = -204 + rand() % ( 204 - (-204) + 1 );
    c6y =  204;

    c7x = -204 + rand() % ( 204 - (-204) + 1 );
    c7y =  204;
    hx = -204 + rand() % ( 204 - (-204) + 1 );
    int d = rand() % 2;
    if(d == 0){
        hy = -204;
    }else{
        hy = 204;
    }


    c_s = 0.02;
    c2_s = 0.05;
    c3_s = 0.01;
    c4_s = 0.02;
    c5_s = 0.06;
    c6_s = 0.04;
    c7_s = 0.12;

    coinx = -250 + rand() % ( 250 - (-250) + 1 );
    coiny = 250;
    co_s = 0.14;
    coin_size = 0;
    coin_enlarge = true;

    //printPoints();

	glClearColor(0,0,0,0);


	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	setFont(GLUT_BITMAP_HELVETICA_18);

}

int main(int argc, char **argv){
    loadHighScore();
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Road To The End Of Galaxy : ~");
	pointStars();

	init();
	initStars();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutSpecialUpFunc(specialKeyUp);
	//glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}

