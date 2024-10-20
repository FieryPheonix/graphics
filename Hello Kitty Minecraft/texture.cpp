#include "TextureBuilder.h"
#include <glut.h>
#include <string>
#include <sstream>

#define GLUT_KEY_ESCAPE 27

//questions
// add texture to background and animation
//can i do upon colliding with an obsticles, loses a life and then automatically character goes down to avoid obstacle and continue game

// Variables

//to make sure my variables update every second
float counter = 0;
//Window and Ortho Sizes
int windowX = 1000;
int windowY = 500;

//How many times to repeat in the X axis
int rep = 4;

//pictures
GLuint grassPtr;
GLuint playerBodyPtr;
GLuint playerArmsPtr;
GLuint LightPinkPtr;

//background colors
double backRed = 1.0f;
double backGreen = 0.47f;
double backBlue = 0.6f;
int colorTimer = 1;

//time and score and health
int gameTime = 121; //2 minutes
int health = 5;
int score = 0;




//speed
int gameSpeed = 1;
//controls
int duckY = 0; //controlls ducking
int jumpY = 0; //controlls jumping
int jumpingTime = 2;
bool isJumping = false; //to make sure i dont duck and jump at the same time

//collision character
int topYplayer = 200 - duckY + jumpY;
int bottomYplayer = 100 + jumpY;
int rightXplayer = 100;
int leftXplayer = 50;

//collision obstacle
int topYObstacle;
int bottomYObstacle = 180;
int rightXObstacle;
int leftXObstacle = 1000;
int scaleObstacle = 1;

int topYObstacle2;
int bottomYObstacle2 = 180;
int rightXObstacle2;
int leftXObstacle2 = 1000;
int scaleObstacle2 = 2;


int obstacleStartTime = 117;
int obstacle2StartTime = 100;



//collision strawberry
int topYberry = 120;
int bottomYberry = 100;
int rightXberry = 1010;
int leftXberry = 1000;
int randomTranslation = 120;  //random spawn of strawberry


//collision potion
int topYpu1 = 350;
int bottomYpu1 = 335;
int rightXpu1 = 1015;
int leftXpu1 = 1000;
int randomTranslationPu1 = 350;
int potionStartTime = 112;


int scoreIncrease = 1;
int scoreIncreaseTime = 10;
bool isScorePowerup = false;

// collision magnet
int topYpu2 = 170;
int bottomYpu2 = 150;
int rightXpu2 = 920;
int leftXpu2 = 900;
int randomTranslationPu2 = 170;
bool isMagnetPowerup = false;
int magnetStartTime = 100;
int magnetTime = 10;

//game over?
bool gameOver = false;

//-----------------




//  Methods Signatures
void Keyboard(unsigned char key, int x, int y);
void Display();
void time(int val);
void key(unsigned char k, int x, int y);
void keyUp(unsigned char k, int x, int y);
void createObstacle();
//-----------------


// Main
void main(int argc, char** argv) {

	//Initialize Window
	glutInit(&argc, argv);

	glutInitWindowSize(windowX, windowY);
	glutInitWindowPosition(250, 175);

	glutCreateWindow("Hello Kitty Run!");

	glutDisplayFunc(Display);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);

	//time
	glutTimerFunc(0, time, 0);

	//clear color white and pixels modes
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //clear color white

	//include 2D textures
	glEnable(GL_TEXTURE_2D);

	//initialize ortho size
	gluOrtho2D(0, windowX, 0, windowY);

	//Loading pictures
	loadBMP(&grassPtr, "textures/grass.bmp", true);
	loadBMP(&playerBodyPtr, "textures/body.bmp", true);
	loadBMP(&playerArmsPtr, "textures/arm.bmp", true);
	loadBMP(&LightPinkPtr, "textures/lightpink.bmp", true);
	//loadPPM(&skyPtr, "textures/sky.ppm", 200, 200, false);
	
	glutMainLoop();
}
//----------------------------------------------------------------





//Creating the game using shapes

//Animate background
void createBackground() {
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

	// Bind the background texture
	glBindTexture(GL_TEXTURE_2D, LightPinkPtr);

	// Enable texturing
	glEnable(GL_TEXTURE_2D);

	glColor3f(backRed, backGreen, backBlue);
	// Draw a full-screen quad
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); // Bottom-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 500.0f, 0.0f);  // Bottom-right
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1000.0f, 500.0f, 0.0f);   // Top-right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1000.0f, 0.0f, 0.0f);  // Top-left
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	
}
//given a string, it diplays it
void RenderString(GLdouble x, GLdouble y, const std::string& string)
{
	//const std::string &string
	//n<string.size()
	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(x, y);
	for (size_t n = 0; n < string.length(); ++n) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[n]);
	}
}

//updates time per second
void time(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{
	if (std::floor(counter) == counter)
	{
		//changes timer
		gameTime = gameTime - 1;
		colorTimer = colorTimer - 1;
		//----------------------------------------------------------------

		//display background animation
		// pink light(/256) : 255, 209(0.82), 220(0.86) , darker pink:255, 120(0.47), 152(0.6)
		if (colorTimer < 0) {
			if (backGreen == 0.82f)
				backGreen = 0.47f;
			else
				backGreen = 0.82f;

			if (backBlue == 0.86f)
				backBlue = 0.6f;
			else
				backBlue = 0.86f;
			colorTimer = 1;
		}
		//----------------------------------------------------------------

		//controls jumping and ducking
		if (isJumping) {
			jumpingTime = jumpingTime - 1;
		}
		//----------------------------------------------------------------


	//PowerUp timer
		if (isScorePowerup)
		{
			scoreIncrease = 2;
			scoreIncreaseTime--;
		}
		if (scoreIncreaseTime == 0)
		{
			scoreIncreaseTime = 15;
			isScorePowerup = false;
			scoreIncrease = 1;
		}
		//----------------------------------------------------------------
		


		//magnet time
		if (isMagnetPowerup)
		{
			magnetTime--;
			randomTranslation = 150;
		}
		if (magnetTime == 0)
		{
			magnetTime = 10;
			isMagnetPowerup = false;
		}
		


		//----------------------------------------------------------------

	



		
		//resets timers if done
		if (gameTime <= 0 || health == 0)
		{
			gameOver = true;
		}
		if (jumpingTime <= 0)
		{
			jumpingTime = 2;
			jumpY = 0;
			isJumping = false;
		}
		//----------------------------------------------------------------

		//controls game speed
		if (gameTime > 90) {
			gameSpeed = 2;
		}
		else if (gameTime > 60) {
			gameSpeed = 4;
		}
		else if (gameTime > 30) {
			gameSpeed = 8;
		}
		else {
			gameSpeed = 12;
		}

		//----------------------------------------------------------------

		

	}
	else
	{
		//control speed

		leftXberry -= (5 * gameSpeed);
		rightXberry -= (5 * gameSpeed);

		if (gameTime <= potionStartTime)
		{
			leftXpu1 -= (5 * gameSpeed);
			rightXpu1 -= (5 * gameSpeed);
		}
		if (gameTime <= magnetStartTime)
		{
			leftXpu2 -= (5 * gameSpeed);
			rightXpu2 -= (5 * gameSpeed);
		}
		if (gameTime <= obstacleStartTime)
		{
			leftXObstacle -= (5 * gameSpeed);
			rightXObstacle -= (5 * gameSpeed);
		}
		if (gameTime <= obstacle2StartTime)
		{
			leftXObstacle2 -= (5 * gameSpeed);
			rightXObstacle2 -= (5 * gameSpeed);
		}
	}
	
	counter += 0.25;
	glutPostRedisplay();							// redraw,go to display 		
	glutTimerFunc(250, time, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}

//display remaining time
void displayTimeLeft() {
	std::ostringstream dispTime; // Create an output string stream
	dispTime << "Time Left: " << gameTime; // Append the score to the string
	RenderString(1, 410, dispTime.str()); // Render the complete string
	//RenderString(1, 410, "Time Left:");
}

//display score
void displayScore() {
	std::ostringstream dispScore; // Create an output string stream
	dispScore << "Score: " << score; // Append the score to the string
	RenderString(1, 440, dispScore.str()); // Render the complete string
	//RenderString(1, 440, "Score: ");
}

//heart skeleton
void createHeart(int count) {
	int distance = 0;
	
	
	for (int i = 0; i < count; i++) {
		glColor3f(1.0f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, grassPtr);

		// Draw the heart shape
		glBegin(GL_POLYGON);

		// Define texture coordinates before vertices
		glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f + distance, 480.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f + distance, 483.0f, 0.0f);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(12.0f + distance, 485.0f, 0.0f);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(15.0f + distance, 485.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(17.0f + distance, 480.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(19.0f + distance, 485.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(22.0f + distance, 485.0f, 0.0f);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(24.0f + distance, 483.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(24.0f + distance, 480.0f, 0.0f);

		glEnd();

		glBegin(GL_TRIANGLES);

		// Define texture coordinates for triangles
		glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f + distance, 480.0f, 0.0f);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(17.0f + distance, 470.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(24.0f + distance, 480.0f, 0.0f);

		glEnd();

		distance += 30;
		glColor3f(1.0f, 1.0f, 1.0f);
	}
}

//display the lives
void displayRemainingLives() {

}

//creates the background
void drawBow(float translateX, float translateY) {
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, grassPtr);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f + translateX, 0.0f + translateY, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f + translateX, 10.0f + translateY, 0.0f);
	glTexCoord2f(1.0f, 0.5f); glVertex3f(10.0f + translateX, 5.0f + translateY, 0.0f);
	glEnd();

	// Draw the polygon with texture
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(10.0f + translateX, 5.0f + translateY, 0.0f);
	glTexCoord2f(0.2f, 0.7f); glVertex3f(12.0f + translateX, 7.0f + translateY, 0.0f);
	glTexCoord2f(0.4f, 0.7f); glVertex3f(14.0f + translateX, 7.0f + translateY, 0.0f);
	glTexCoord2f(0.6f, 0.5f); glVertex3f(16.0f + translateX, 5.0f + translateY, 0.0f);
	glTexCoord2f(0.4f, 0.3f); glVertex3f(14.0f + translateX, 3.0f + translateY, 0.0f);
	glTexCoord2f(0.2f, 0.3f); glVertex3f(12.0f + translateX, 3.0f + translateY, 0.0f);
	glEnd();

	// Draw the second triangle with texture
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.8f, 0.0f); glVertex3f(26.0f + translateX, 0.0f + translateY, 0.0f);
	glTexCoord2f(0.8f, 1.0f); glVertex3f(26.0f + translateX, 10.0f + translateY, 0.0f);
	glTexCoord2f(1.0f, 0.5f); glVertex3f(16.0f + translateX, 5.0f + translateY, 0.0f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void drawStrawberryLine(float translateX, float translateY) {


	glBegin(GL_LINE_LOOP);
	glVertex3f(10.0f + translateX, 25.0f + translateY, 0.0f);
	glVertex3f(10.0f + translateX, 20.0f + translateY, 0.0f);
	glVertex3f(0.0f + translateX, 20.0f + translateY, 0.0f);
	glVertex3f(0.0f + translateX, 10.0f + translateY, 0.0f);
	glVertex3f(10.0f + translateX, 0.0f + translateY, 0.0f);
	glVertex3f(20.0f + translateX, 10.0f + translateY, 0.0f);
	glVertex3f(20.0f + translateX, 20.0f + translateY, 0.0f);
	glVertex3f(10.0f + translateX, 20.0f + translateY, 0.0f);
	glEnd();
}

void drawClouds(float translateX, float translateY) {


	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f + translateX, 0.0f + translateY, 0.0f);
	glVertex3f(0.0f + translateX, 10.0f + translateY, 0.0f);
	glVertex3f(10.0f + translateX, 10.0f + translateY, 0.0f);
	glVertex3f(10.0f + translateX, 20.0f + translateY, 0.0f);
	glVertex3f(30.0f + translateX, 20.0f + translateY, 0.0f);
	glVertex3f(30.0f + translateX, 10.0f + translateY, 0.0f);
	glVertex3f(40.0f + translateX, 10.0f + translateY, 0.0f);
	glVertex3f(40.0f + translateX, 0.0f + translateY, 0.0f);
	glEnd();
}

void createEnvironment() {

	//create lower border
	//1)Create Bows(triangle and polygon)
		glColor3f(1.0f, 0.0f, 0.0f);
		drawBow(30, 30);
		drawBow(240, 50);
		drawBow(500, 10);
		drawBow(750, 30);
		drawBow(950, 50);
		glColor3f(1.0f, 0.0f, 0.0f);
	//2)create strawberry (Lines)
		drawStrawberryLine(150, 30);
		drawStrawberryLine(375, 30);
		drawStrawberryLine(680, 30);
		drawStrawberryLine(860, 30);
	//3)Create grass(Quad)
		glBindTexture(GL_TEXTURE_2D, grassPtr);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 70, 0);
			glTexCoord2f(rep, 0.0f); glVertex3f(1000, 70, 0);
			glTexCoord2f(rep, 1); glVertex3f(1000, 100, 0);
			glTexCoord2f(0.0f, 1); glVertex3f(0, 100, 0);
		glEnd();
		glColor3f(1.0f, 0.0f, 0.0f);
	//----------------------------------------------------------------
	

	//create upper border
	//1)Create Bows(triangle and polygon)
		glColor3f(1.0f, 0.0f, 0.0f);
		drawBow(240, 450);
		drawBow(500, 410);
		drawBow(750, 430);
		drawBow(950, 450);
		glColor3f(1.0f, 0.0f, 0.0f);
	//2)create clouds(Lines)
		drawClouds(300,430);
		drawClouds(530, 475);
		drawClouds(600, 430);
		drawClouds(850, 450);
	//3)create line(quad)
		glBindTexture(GL_TEXTURE_2D, grassPtr);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 380, 0);
			glTexCoord2f(rep, 0.0f); glVertex3f(1000, 380, 0);
			glTexCoord2f(rep, 1); glVertex3f(1000, 400, 0);
			glTexCoord2f(0.0f, 1); glVertex3f(0, 400, 0);
		glEnd();

	
		glColor3f(1.0f, 1.0f, 1.0f);
			
	
}



//creates and displays the player
void createPlayer() {
	//to make sure character isnt tinted
	glColor3f(1.0f, 1.0f, 1.0f);

	topYplayer = 200 - duckY + jumpY;
	bottomYplayer = 100 + jumpY;

	//Create Player's body
	glBindTexture(GL_TEXTURE_2D, playerBodyPtr);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(60, 100 + jumpY, 0);
		glTexCoord2f(1, 0.0f); glVertex3f(90, 100 + jumpY, 0);
		glTexCoord2f(1, 1); glVertex3f(90, 200 - duckY + jumpY, 0);
		glTexCoord2f(0.0f, 1); glVertex3f(60, 200 - duckY + jumpY, 0);
	glEnd();

	//Create Player's arms
	glBindTexture(GL_TEXTURE_2D, playerArmsPtr);
	glBegin(GL_POLYGON);
		//left arm
		glTexCoord2f(0.0f, 0.0f); glVertex3f(50, 135 + jumpY, 0);
		glVertex3f(54, 135 + jumpY, 0);
		glVertex3f(53, 130 + jumpY, 0);
		glVertex3f(58, 130 + jumpY, 0);
		glVertex3f(58, 135 + jumpY, 0);
		glTexCoord2f(1, 0.0f); glVertex3f(60, 135 + jumpY, 0);
		glTexCoord2f(1, 1); glVertex3f(60, 178 - duckY + jumpY, 0);
		glTexCoord2f(0.0f, 1); glVertex3f(50, 178 - duckY + jumpY, 0);
	glEnd();

	glBegin(GL_POLYGON);
		//right arm
		glTexCoord2f(0.0f, 0.0f); glVertex3f(90, 135 + jumpY, 0);
		glVertex3f(94, 135 + jumpY, 0);
		glVertex3f(93, 130 + jumpY, 0);
		glVertex3f(98, 130 + jumpY, 0);
		glVertex3f(98, 135 + jumpY, 0);
		glTexCoord2f(1, 0.0f); glVertex3f(100, 135 + jumpY, 0);
		glTexCoord2f(1, 1); glVertex3f(100, 178 - duckY + jumpY, 0);
		glTexCoord2f(0.0f, 1); glVertex3f(90, 178 - duckY + jumpY, 0);
	glEnd();

	//Create Player's ears (3ady no texture?)
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(60.0f, 200.0f - duckY + jumpY, 0.0f);
		glColor3f(1.0f, 0.55f, 0.63f);
		glVertex3f(63.0f, 210.0f - duckY + jumpY, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(69.0f, 200.0f - duckY + jumpY, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(83.0f, 200.0f - duckY + jumpY, 0.0f);
		glColor3f(1.0f, 0.55f, 0.63f);
		glVertex3f(86.0f, 210.0f - duckY + jumpY, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(90.0f, 200.0f - duckY + jumpY, 0.0f);
	glEnd();

	//Create Player's whiskers (3ady overlap?)
	glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(80.0f, 181.0f - duckY + jumpY, 0.0f);
		glVertex3f(90.0f, 183.0f - duckY + jumpY, 0.0f);

		glVertex3f(80.0f, 179.0f - duckY + jumpY, 0.0f);
		glVertex3f(90.0f, 177.0f - duckY + jumpY, 0.0f);

		glVertex3f(70.0f, 181.0f - duckY + jumpY, 0.0f);
		glVertex3f(60.0f, 183.0f - duckY + jumpY, 0.0f);

		glVertex3f(70.0f, 179.0f - duckY + jumpY, 0.0f);
		glVertex3f(60.0f, 177.0f - duckY + jumpY, 0.0f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
}

//upon keyboard key press
void key(unsigned char k, int x, int y)
{
	// k is the key pressed from the keyboard
	// x and y are mouse postion when the key was pressed.

	//duckY==0 ensures i dont duck again or jump if im already ducking
	//!isJumping ensures i dont duck again or jump if im already jumping
	if (k == 'w' && duckY == 0 && !isJumping)//if the letter w is pressed, then the object will be translated in the y axis by 10. (moving upwords)
	{
		jumpY += 170;
		isJumping = true;
	}
	if (k == 's' && duckY == 0 && !isJumping)//if the letter w is pressed, then the object will shrink
	{
		duckY = 40;
	}
		
	
	glutPostRedisplay();//redisplay to update the screen with the changes
}

//Active Release of the keyboard letters
void keyUp(unsigned char k, int x, int y)
{
	if (k == 's')//if the letter q is pressed, then the object will go back to it's original color.
		duckY = 0;
	glutPostRedisplay();//redisplay to update the screen with the changed
}

//creates the obstacles
void createObstacle() {



	// Draw the three tiers of the cake using polygons


	topYObstacle = bottomYObstacle + 6 * scaleObstacle;
	rightXObstacle = leftXObstacle + 6 * scaleObstacle;
	// Base tier (bottom layer)
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.2f, 0.1f); // Dark brown color
	glVertex3f(leftXObstacle + 0 * scaleObstacle, bottomYObstacle + 0 * scaleObstacle, 0);                     // Bottom left
	glVertex3f(leftXObstacle + 6 * scaleObstacle, bottomYObstacle + 0 * scaleObstacle, 0);                     // Bottom right
	glVertex3f(leftXObstacle + 5 * scaleObstacle, bottomYObstacle + 2 * scaleObstacle, 0);                     // Right peak
	glVertex3f(leftXObstacle + 1 * scaleObstacle, bottomYObstacle + 2 * scaleObstacle, 0);                     // Left peak
	glEnd();

	// Middle tier
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.25f, 0.1f); // Medium brown color
	glVertex3f(leftXObstacle + 1 * scaleObstacle, bottomYObstacle + 2 * scaleObstacle, 0);                     // Bottom left
	glVertex3f(leftXObstacle + 5 * scaleObstacle, bottomYObstacle + 2 * scaleObstacle, 0);                     // Bottom right
	glVertex3f(leftXObstacle + 4 * scaleObstacle, bottomYObstacle + 4 * scaleObstacle, 0);                     // Right peak
	glVertex3f(leftXObstacle + 2 * scaleObstacle, bottomYObstacle + 4 * scaleObstacle, 0);                     // Left peak
	glEnd();

	// Top tier
	glBegin(GL_POLYGON);
	glColor3f(0.6f, 0.3f, 0.1f); // Light brown color
	glVertex3f(leftXObstacle + 2 * scaleObstacle, bottomYObstacle + 4 * scaleObstacle, 0);                     // Bottom left
	glVertex3f(leftXObstacle + 4 * scaleObstacle, bottomYObstacle + 4 * scaleObstacle, 0);                     // Bottom right
	glVertex3f(leftXObstacle + 3.5 * scaleObstacle, bottomYObstacle + 6 * scaleObstacle, 0);                   // Right peak
	glVertex3f(leftXObstacle + 2.5 * scaleObstacle, bottomYObstacle + 6 * scaleObstacle, 0);                   // Left peak
	glEnd();

	// Draw an outline around each tier using lines
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for outline

	// Outline for base tier
	glBegin(GL_LINE_LOOP);
	glVertex3f(leftXObstacle + 0 * scaleObstacle, bottomYObstacle + 0 * scaleObstacle, 0);                     // Bottom left
	glVertex3f(leftXObstacle + 6 * scaleObstacle, bottomYObstacle + 0 * scaleObstacle, 0);                     // Bottom right
	glVertex3f(leftXObstacle + 5 * scaleObstacle, bottomYObstacle + 2 * scaleObstacle, 0);                     // Right peak
	glVertex3f(leftXObstacle + 1 * scaleObstacle, bottomYObstacle + 2 * scaleObstacle, 0);                     // Left peak
	glEnd();

	// Outline for middle tier
	glBegin(GL_LINE_LOOP);
	glVertex3f(leftXObstacle + 1 * scaleObstacle, bottomYObstacle + 2 * scaleObstacle, 0);                     // Bottom left
	glVertex3f(leftXObstacle + 5 * scaleObstacle, bottomYObstacle + 2 * scaleObstacle, 0);                     // Bottom right
	glVertex3f(leftXObstacle + 4 * scaleObstacle, bottomYObstacle + 4 * scaleObstacle, 0);                     // Right peak
	glVertex3f(leftXObstacle + 2 * scaleObstacle, bottomYObstacle + 4 * scaleObstacle, 0);                     // Left peak
	glEnd();

	// Outline for top tier
	glBegin(GL_LINE_LOOP);
	glVertex3f(leftXObstacle + 2 * scaleObstacle, bottomYObstacle + 4 * scaleObstacle, 0);                     // Bottom left
	glVertex3f(leftXObstacle + 4 * scaleObstacle, bottomYObstacle + 4 * scaleObstacle, 0);                     // Bottom right
	glVertex3f(leftXObstacle + 3.5 * scaleObstacle, bottomYObstacle + 6 * scaleObstacle, 0);                   // Right peak
	glVertex3f(leftXObstacle + 2.5 * scaleObstacle, bottomYObstacle + 6 * scaleObstacle, 0);                   // Left peak
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
}


void createObstacle2() {


	// Scale factor
	// Seed the random number generator
	std::srand(static_cast<unsigned int>(std::time(0)));

	// Generate a random scale between 3 and 8
	//float scale = 3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (8.0f - 3.0f)));
	
	// Draw the three tiers of the cake using polygons


	topYObstacle2 = bottomYObstacle2 + 6 * scaleObstacle2;
	rightXObstacle2 = leftXObstacle2 + 6 * scaleObstacle2;
	// Base tier (bottom layer)
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.2f, 0.1f); // Dark brown color
	glVertex3f(leftXObstacle2 + 0 * scaleObstacle2, bottomYObstacle2 + 0 * scaleObstacle2, 0);                     // Bottom left
	glVertex3f(leftXObstacle2 + 6 * scaleObstacle2, bottomYObstacle2 + 0 * scaleObstacle2, 0);                     // Bottom right
	glVertex3f(leftXObstacle2 + 5 * scaleObstacle2, bottomYObstacle2 + 2 * scaleObstacle2, 0);                     // Right peak
	glVertex3f(leftXObstacle2 + 1 * scaleObstacle2, bottomYObstacle2 + 2 * scaleObstacle2, 0);                     // Left peak
	glEnd();

	// Middle tier
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.25f, 0.1f); // Medium brown color
	glVertex3f(leftXObstacle2 + 1 * scaleObstacle2, bottomYObstacle2 + 2 * scaleObstacle2, 0);                     // Bottom left
	glVertex3f(leftXObstacle2 + 5 * scaleObstacle2, bottomYObstacle2 + 2 * scaleObstacle2, 0);                     // Bottom right
	glVertex3f(leftXObstacle2 + 4 * scaleObstacle2, bottomYObstacle2 + 4 * scaleObstacle2, 0);                     // Right peak
	glVertex3f(leftXObstacle2 + 2 * scaleObstacle2, bottomYObstacle2 + 4 * scaleObstacle2, 0);                     // Left peak
	glEnd();

	// Top tier
	glBegin(GL_POLYGON);
	glColor3f(0.6f, 0.3f, 0.1f); // Light brown color
	glVertex3f(leftXObstacle2 + 2 * scaleObstacle2, bottomYObstacle2 + 4 * scaleObstacle2, 0);                     // Bottom left
	glVertex3f(leftXObstacle2 + 4 * scaleObstacle2, bottomYObstacle2 + 4 * scaleObstacle2, 0);                     // Bottom right
	glVertex3f(leftXObstacle2 + 3.5 * scaleObstacle2, bottomYObstacle2 + 6 * scaleObstacle2, 0);                   // Right peak
	glVertex3f(leftXObstacle2 + 2.5 * scaleObstacle2, bottomYObstacle2 + 6 * scaleObstacle2, 0);                   // Left peak
	glEnd();

	// Draw an outline around each tier using lines
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for outline

	// Outline for base tier
	glBegin(GL_LINE_LOOP);
	glVertex3f(leftXObstacle2 + 0 * scaleObstacle2, bottomYObstacle2 + 0 * scaleObstacle2, 0);                     // Bottom left
	glVertex3f(leftXObstacle2 + 6 * scaleObstacle2, bottomYObstacle2 + 0 * scaleObstacle2, 0);                     // Bottom right
	glVertex3f(leftXObstacle2 + 5 * scaleObstacle2, bottomYObstacle2 + 2 * scaleObstacle2, 0);                     // Right peak
	glVertex3f(leftXObstacle2 + 1 * scaleObstacle2, bottomYObstacle2 + 2 * scaleObstacle2, 0);                     // Left peak
	glEnd();

	// Outline for middle tier
	glBegin(GL_LINE_LOOP);
	glVertex3f(leftXObstacle2 + 1 * scaleObstacle2, bottomYObstacle2 + 2 * scaleObstacle2, 0);                     // Bottom left
	glVertex3f(leftXObstacle2 + 5 * scaleObstacle2, bottomYObstacle2 + 2 * scaleObstacle2, 0);                     // Bottom right
	glVertex3f(leftXObstacle2 + 4 * scaleObstacle2, bottomYObstacle2 + 4 * scaleObstacle2, 0);                     // Right peak
	glVertex3f(leftXObstacle2 + 2 * scaleObstacle2, bottomYObstacle2 + 4 * scaleObstacle2, 0);                     // Left peak
	glEnd();

	// Outline for top tier
	glBegin(GL_LINE_LOOP);
	glVertex3f(leftXObstacle2 + 2 * scaleObstacle2, bottomYObstacle2 + 4 * scaleObstacle2, 0);                     // Bottom left
	glVertex3f(leftXObstacle2 + 4 * scaleObstacle2, bottomYObstacle2 + 4 * scaleObstacle2, 0);                     // Bottom right
	glVertex3f(leftXObstacle2 + 3.5 * scaleObstacle2, bottomYObstacle2 + 6 * scaleObstacle2, 0);                   // Right peak
	glVertex3f(leftXObstacle2 + 2.5 * scaleObstacle2, bottomYObstacle2 + 6 * scaleObstacle2, 0);                   // Left peak
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void isObstacleCollision() {
	if (
		//check for character and collectible collision
		(topYObstacle >= bottomYplayer && topYObstacle <= topYplayer) &&
		((leftXObstacle >= leftXplayer && leftXObstacle <= rightXplayer)
			|| (rightXObstacle >= leftXplayer && rightXObstacle <= rightXplayer))
		||
		(bottomYObstacle >= bottomYplayer && bottomYObstacle <= topYplayer) &&
		((leftXObstacle >= leftXplayer && leftXObstacle <= rightXplayer)
			|| (rightXObstacle >= leftXplayer && rightXObstacle <= rightXplayer))
		)
	{
		//if collision then health decreases
		health--;

		//make player jump if collided

		jumpY += 170;
		isJumping = true;
		

		
	}
	else if (rightXObstacle <= 0) {
		/// Seed the random number generator
		std::srand(static_cast<unsigned int>(std::time(0)));

		scaleObstacle = 1.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (3.0f - 1.0f)));

		leftXObstacle = 1000;
	}
}

void isObstacle2Collision() {
	if (
		//check for character and collectible collision
		(topYObstacle2 >= bottomYplayer && topYObstacle2 <= topYplayer) &&
		((leftXObstacle2 >= leftXplayer && leftXObstacle2 <= rightXplayer)
			|| (rightXObstacle2 >= leftXplayer && rightXObstacle2 <= rightXplayer))
		||
		(bottomYObstacle2 >= bottomYplayer && bottomYObstacle2 <= topYplayer) &&
		((leftXObstacle2 >= leftXplayer && leftXObstacle2 <= rightXplayer)
			|| (rightXObstacle2 >= leftXplayer && rightXObstacle2 <= rightXplayer))
		)
	{
		//if collision then health decreases
		health--;
		

		//make player jump if collided
		
		jumpY += 170;
		isJumping = true; 


	}
	else if (rightXObstacle2 <= 0) {
		/// Seed the random number generator
		std::srand(static_cast<unsigned int>(std::time(0)));

		scaleObstacle = 1.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (3.0f - 1.0f)));

		leftXObstacle2 = 1000;
	}
}

//creates collectibles
void createCollectibles() {
	if (gameTime % 2 == 0) {
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else {
		glColor3f(1.0f, 1.0f, 0.0f);
	}
	glBindTexture(GL_TEXTURE_2D, LightPinkPtr);
	topYberry = randomTranslation;
	bottomYberry = randomTranslation - 10;

	// Draw lines (optional to texture, as lines usually don't have textures)
	glBegin(GL_LINES);
	glVertex3f(leftXberry + 5, topYberry, 0.0f);
	glVertex3f(leftXberry + 5, topYberry + 3, 0.0f);
	glEnd();

	// Draw the quad with texture
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(leftXberry, topYberry - 5, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(leftXberry, topYberry, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(rightXberry, topYberry, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(rightXberry, topYberry - 5, 0);
	glEnd();

	// Draw the triangle with texture
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(leftXberry, bottomYberry + 5, 0.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(leftXberry + 5, bottomYberry, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(rightXberry, bottomYberry + 5, 0.0f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void isCollectibleCollision() {
	if (
		//check for character and collectible collision
		(topYberry>= bottomYplayer && topYberry <= topYplayer) &&
				((leftXberry >= leftXplayer && leftXberry <= rightXplayer)
					|| (rightXberry >= leftXplayer && rightXberry <= rightXplayer))
		||
		(bottomYberry >= bottomYplayer && bottomYberry <= topYplayer) &&
			((leftXberry >= leftXplayer && leftXberry <= rightXplayer)
				|| (rightXberry >= leftXplayer && rightXberry <= rightXplayer))
		)
	{
		//if collision then increase score
		score+= scoreIncrease;
		//randomize y position when it respawns
		  
			//random y
			std::srand(static_cast<unsigned int>(std::time(0))); // Seed for random number generation

			// Randomly decide between the two ranges
			do{
				if (std::rand() % 2 == 0) {
					// Generate a number between 120 and 200
					randomTranslation = std::rand() % 101 + 120; // [120, 200]
				}
				else {
					// Generate a number between 270 and 370
					randomTranslation = std::rand() % 101 + 270; // [270, 370]
				}
			}while (randomTranslation == 180);
			rightXberry = 1010;
			leftXberry = 1000;
	}
	else if(rightXberry<=0){
		//random y
		std::srand(static_cast<unsigned int>(std::time(0))); // Seed for random number generation

		// Randomly decide between the two ranges
		do{
			if (std::rand() % 2 == 0) {
				// Generate a number between 120 and 200
				randomTranslation = std::rand() % 101 + 120; // [120, 200]
			}
			else {
				// Generate a number between 270 and 370
				randomTranslation = std::rand() % 101 + 270; // [270, 370]
			}
		}while (randomTranslation == 180);
		rightXberry = 1010;
		leftXberry = 1000;
	}
}

//creates powerups
void createPowerup1() {

	topYpu1 = randomTranslationPu1;
	bottomYpu1 = randomTranslationPu1 - 15;

	if (gameTime % 2 == 0) {
		// Dark green
		glColor3f(0.0f, 0.5f, 0.0f); // RGB: (0, 0.5, 0)
	}
	else {
		// Dark red
		glColor3f(0.5f, 0.0f, 0.0f); // RGB: (0.5, 0, 0)
	}

	glBindTexture(GL_TEXTURE_2D, LightPinkPtr);
	glBegin(GL_LINES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(leftXpu1, topYpu1, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(rightXpu1, topYpu1, 0.0f);
	glEnd();

	// Draw the quad with texture
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(leftXpu1 + 4, topYpu1 - 7, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(leftXpu1 + 4, topYpu1, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(rightXpu1 - 4, topYpu1, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(rightXpu1 - 4, topYpu1 - 7, 0);
	glEnd();

	// Draw the triangle with texture
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(leftXpu1, topYpu1 - 7, 0.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(leftXpu1 + 7, bottomYpu1, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(rightXpu1, topYpu1 - 7, 0.0f);
	glEnd();

	glPointSize(3.0f);
	glBegin(GL_POINTS);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		//glVertex3f(leftXpu1, topYpu1 - 10, 0.0f);
		//glVertex3f(leftXpu1 + 15, topYpu1 - 20, 0.0f);
		glVertex3f(leftXpu1 + 7, topYpu1 - 10, 0.0f);
		
	glEnd();
	glPointSize(1.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
}

void isPowerUp1Collision() {
	if (

		//check for character and collectible collision
		(topYpu1 >= bottomYplayer && topYpu1 <= topYplayer) &&
		((leftXpu1 >= leftXplayer && leftXpu1 <= rightXplayer)
			|| (rightXpu1 >= leftXplayer && rightXpu1 <= rightXplayer))
		||
		(bottomYpu1 >= bottomYplayer && bottomYpu1 <= topYplayer) &&
		((leftXpu1 >= leftXplayer && leftXpu1 <= rightXplayer)
			|| (rightXpu1 >= leftXplayer && rightXpu1 <= rightXplayer))
		)
	{
		//if collision then for 15 seconds, strawberries give u + 2 instead of                                                                                   
		isScorePowerup = true;
		//randomize y position when it respawns

		//random y
		std::srand(static_cast<unsigned int>(std::time(0))); // Seed for random number generation

		// Randomly decide between the two ranges
		do {
			if (std::rand() % 2 == 0) {
				// Generate a number between 120 and 200
				randomTranslationPu1 = std::rand() % 101 + 120; // [120, 200]
			}
			else {
				// Generate a number between 270 and 370
				randomTranslationPu1 = std::rand() % 101 + 270; // [270, 370]
			}
		}while (randomTranslationPu1 == 180);
		
		rightXpu1 = 1015;
		leftXpu1 = 1000;
	}
	else if (rightXpu1 <= 0) {
		//random y
		std::srand(static_cast<unsigned int>(std::time(0))); // Seed for random number generation

		// Randomly decide between the two ranges
		do{
			if (std::rand() % 2 == 0) {
				// Generate a number between 120 and 200
				randomTranslationPu1 = std::rand() % 101 + 120; // [120, 200]
			}
			else {
				// Generate a number between 270 and 370
				randomTranslationPu1 = std::rand() % 101 + 270; // [270, 370]
			}
		}while (randomTranslationPu1 == 180);
		rightXpu1 = 1015;
		leftXpu1 = 1000;
	}
}

void createPowerup2() {
	topYpu2 = randomTranslationPu2;
	bottomYpu2 = randomTranslationPu2 - 20;

	glColor3f(0.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, grassPtr);

	// First Polygon
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(leftXpu2 + 3, topYpu2, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(leftXpu2, topYpu2 - 2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(leftXpu2, topYpu2 - 15, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(leftXpu2 + 6, topYpu2 - 15, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(leftXpu2 + 6, topYpu2 - 2, 0);
	glEnd();

	// Second Polygon
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(leftXpu2 + 17, topYpu2, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(leftXpu2 + 14, topYpu2 - 2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(leftXpu2 + 14, topYpu2 - 15, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(leftXpu2 + 20, topYpu2 - 15, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(leftXpu2 + 20, topYpu2 - 2, 0);
	glEnd();

	// Draw Bottom Quad
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(leftXpu2, bottomYpu2 + 5, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(leftXpu2, bottomYpu2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(rightXpu2, bottomYpu2, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(rightXpu2, bottomYpu2 + 5, 0);
	glEnd();

	// Draw Triangle
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(leftXpu2 + 8, bottomYpu2 + 5, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(leftXpu2 + 10, bottomYpu2 + 7, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(leftXpu2 + 12, bottomYpu2 + 5, 0.0f);
	glEnd();


	if (gameTime % 2 == 0) {
		glBegin(GL_LINES);

		// Top glow lines
		glVertex3f(leftXpu2 + 3, topYpu2 + 2, 0); // Top left glow
		glVertex3f(leftXpu2 + 3, topYpu2 + 5, 0); // Top left higher glow

		glVertex3f(leftXpu2 + 17, topYpu2 + 2, 0); // Top right glow
		glVertex3f(leftXpu2 + 17, topYpu2 + 5, 0); // Top right higher glow

		// Bottom glow lines
		glVertex3f(leftXpu2, bottomYpu2 - 5, 0); // Bottom left glow
		glVertex3f(leftXpu2, bottomYpu2 - 2, 0); // Bottom left higher glow

		glVertex3f(rightXpu2, bottomYpu2 - 5, 0); // Bottom right glow
		glVertex3f(rightXpu2, bottomYpu2 - 2, 0); // Bottom right higher glow

		glEnd();
	}
	else {
		glBegin(GL_LINES);

		// Top glow line
		glVertex3f(leftXpu2 + 10, topYpu2 + 2, 0); // Top left glow
		glVertex3f(leftXpu2 + 10, topYpu2 + 5, 0); // Top left higher glow

		// Bottom glow line
		glVertex3f(leftXpu2 + 10, bottomYpu2 - 5, 0); // Bottom left glow
		glVertex3f(leftXpu2 + 10, bottomYpu2 - 2, 0); // Bottom left higher glow

		// Right glow lines
		glVertex3f(rightXpu2 + 2, bottomYpu2 + 10, 0); // Top right glow
		glVertex3f(rightXpu2 + 5, bottomYpu2 + 10, 0); // Top right higher glow

		//Left glow lines
		glVertex3f(leftXpu2 - 2, bottomYpu2 + 10, 0); // Bottom right glow
		glVertex3f(leftXpu2 - 5, bottomYpu2 + 10, 0); // Bottom right higher glow

		glEnd();
	}

	


	glColor3f(1.0f, 1.0f, 1.0f);
}

void isPowerUp2Collision() {
	if (

		//check for character and collectible collision
		(topYpu2 >= bottomYplayer && topYpu2 <= topYplayer) &&
		((leftXpu2 >= leftXplayer && leftXpu2 <= rightXplayer)
			|| (rightXpu2 >= leftXplayer && rightXpu2 <= rightXplayer))
		||
		(bottomYpu2 >= bottomYplayer && bottomYpu2 <= topYplayer) &&
		((leftXpu2 >= leftXplayer && leftXpu2 <= rightXplayer)
			|| (rightXpu2 >= leftXplayer && rightXpu2 <= rightXplayer))
		)
	{
		//if collision then strawberry magnet                                                                                  
		isMagnetPowerup = true;
		//randomize y position when it respawns

		//random y
		std::srand(static_cast<unsigned int>(std::time(0))); // Seed for random number generation

		// Randomly decide between the two ranges
		do{
			if (std::rand() % 2 == 0) {
				// Generate a number between 120 and 200
				randomTranslationPu2 = std::rand() % 101 + 120; // [120, 200]
			}
			else {
				// Generate a number between 270 and 370
				randomTranslationPu2 = std::rand() % 101 + 270; // [270, 370]
			}
			rightXpu2 = 1020;
			leftXpu2 = 1000;
		} while (randomTranslationPu2 == 180);
	}
	else if (rightXpu2 <= 0) {
		//random y
		std::srand(static_cast<unsigned int>(std::time(0))); // Seed for random number generation

		// Randomly decide between the two ranges
		do{
			if (std::rand() % 2 == 0) {
				// Generate a number between 120 and 200
				randomTranslationPu2 = std::rand() % 101 + 120; // [120, 200]
			}
			else {
				// Generate a number between 270 and 370
				randomTranslationPu2 = std::rand() % 101 + 270; // [270, 370]
			}
		} while (randomTranslationPu2 == 180);
		rightXpu2 = 1020;
		leftXpu2 = 1000;
	}
}


//creates game end screen
void gameEnd() {
	std::ostringstream gameover; // Create an output string stream

	if (health == 0)
	{
		gameover << "Game Over! No Lives Remaining.  score:" << score; // Append the score to the string
	}
	else {
		gameover << "Game Over! No time Remaining  score:" << score; // Append the score to the string
	}

	RenderString(325, 250, gameover.str()); // Render the complete string
	
}
//------------------------------------------------------




void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(backRed, backGreen, backBlue, 0.0f);

	if (!gameOver) 
	{
		glPushMatrix();
		createBackground();
		displayTimeLeft();
		displayScore();
		createCollectibles();
		isCollectibleCollision();
		createHeart(health);
		createEnvironment();
		createPlayer();
		if (gameTime <= potionStartTime)
		{
			createPowerup1();
			isPowerUp1Collision();
		}
		if (gameTime <= magnetStartTime)
		{
			createPowerup2();
			isPowerUp2Collision();
		}
		if (gameTime <= obstacleStartTime)
		{
			createObstacle();
			isObstacleCollision();
			
		}
		if (gameTime <= obstacle2StartTime) {
			createObstacle2();
			isObstacle2Collision();
		}
		
		glPopMatrix();
		
	}
	else
	{
		glPushMatrix();
			gameEnd();
		glPopMatrix();
	}

	




	glFlush();
}


