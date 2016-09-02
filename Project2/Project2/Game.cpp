#define _CRT_SECURE_NO_DEPRECATE
#include <SDL.h>
#include <glew.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>
#undef main
//CONTROLS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//W,A,S,D TO MOVE
//ARROW KEYS TO CHANGE DIRECTION
//SPACEBAR TO FIRE (USE LEFT THUMB FOR EASIEST CONTROLS)
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//HW3-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//There is collision detection between player and walls, and enemies and bullets
//only the sprites on screen are being drawn
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//HW4-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//The player will collide with the walls surrounding the map
//Kill all of the space sharks to win
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//HW5-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//The Space Sharks have three different ai behaviors
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

char shouldExit = 0;
GLuint spaceship0;
GLuint spaceship1;
unsigned char kbPrevState[SDL_NUM_SCANCODES] = { 0 };
const unsigned char* kbState = NULL;
int map[40][40] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
//clock_t start, current;
int current;
struct Camera {
	struct AABB;
};

struct wall {
	char *type;
	struct AABB;
};

struct AABB {
	double x, y, w, h;
};

struct gameObj {
	char* name;
	struct AABB aabb;
	GLuint frames[30];
	int currentFrame;
	int totalFrames;
	float frameTime;
	float timeTillFrameChange;
	char* state;
	double prevX;
	double prevY;
	int walltype;
	int direction;
	int bulletTime;
	bool draw;
	GLuint left[3];
	GLuint right[3];
	GLuint up[3];
	GLuint down[3];
	int behavior;
	bool moving;
	int moveTime;
	bool dead;
	int moves;
};

struct player{
	gameObj playerObj;
	double velocity;
};

void animUpdate(gameObj* obj, float dt){
	obj->timeTillFrameChange -= dt;
	int temp = obj->timeTillFrameChange;
	if (obj->timeTillFrameChange < 0){
		obj->currentFrame++;
		if (obj->currentFrame > obj->totalFrames - 1){
			obj->currentFrame = 0;
		}
		obj->timeTillFrameChange = obj->frameTime - temp;
	}
	//printf("Obj Name: %s\n", obj->name);
	//printf("currentFrame: %d\n", obj->currentFrame);
	//printf("timeTillFrameChange: %f\n", obj->timeTillFrameChange);
	//printf("deltatime: %f\n", dt);
	//printf("frametime: %f\n", obj->frameTime);

}

bool AABBIntersect(const AABB* box1, const AABB* box2)
{
	// box1 to the right
	if (box1->x > box2->x + box2->w) {
		return false;
	}
	// box1 to the left
	if (box1->x + box1->w < box2->x) {
		return false;
	}
	// box1 below
	if (box1->y > box2->y + box2->h) {
		return false;
	}
	// box1 above
	if (box1->y + box1->h < box2->y) {
		return false;
	}
	return true;
}
/* Load a file into an OpenGL texture, and return that texture. */

GLuint glTexImageTGAFile(const char* filename, int* outWidth, int* outHeight){
	const int BPP = 4;

	/* open the file */
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		fprintf(stderr, "File: %s -- Could not open for reading.\n", filename);
		return 0;
	}

	/* skip first two bytes of data we don't need */
	fseek(file, 2, SEEK_CUR);

	/* read in the image type.  For our purposes the image type should
	* be either a 2 or a 3. */
	unsigned char imageTypeCode;
	fread(&imageTypeCode, 1, 1, file);
	if (imageTypeCode != 2 && imageTypeCode != 3) {
		fclose(file);
		fprintf(stderr, "File: %s -- Unsupported TGA type: %d\n", filename, imageTypeCode);
		return 0;
	}

	/* skip 9 bytes of data we don't need */
	fseek(file, 9, SEEK_CUR);

	/* read image dimensions */
	int imageWidth = 0;
	int imageHeight = 0;
	int bitCount = 0;
	fread(&imageWidth, sizeof(short), 1, file);
	fread(&imageHeight, sizeof(short), 1, file);
	fread(&bitCount, sizeof(unsigned char), 1, file);
	fseek(file, 1, SEEK_CUR);

	/* allocate memory for image data and read it in */
	unsigned char* bytes = (unsigned char*)calloc(imageWidth * imageHeight * BPP, 1);

	/* read in data */
	if (bitCount == 32) {
		int it;
		for (it = 0; it != imageWidth * imageHeight; ++it) {
			bytes[it * BPP + 0] = fgetc(file);
			bytes[it * BPP + 1] = fgetc(file);
			bytes[it * BPP + 2] = fgetc(file);
			bytes[it * BPP + 3] = fgetc(file);
		}
	}
	else {
		int it;
		for (it = 0; it != imageWidth * imageHeight; ++it) {
			bytes[it * BPP + 0] = fgetc(file);
			bytes[it * BPP + 1] = fgetc(file);
			bytes[it * BPP + 2] = fgetc(file);
			bytes[it * BPP + 3] = 255;
		}
	}

	fclose(file);

	/* load into OpenGL */
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, bytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	free(bytes);

	if (outWidth) {
		*outWidth = imageWidth;
	}
	if (outHeight) {
		*outHeight = imageHeight;
	}
	return tex;
}

/* Draw the sprite */
void glDrawSprite(GLuint tex, int x, int y, int w, int h, int angle){
	glRotatef( angle, 0.0, 0.0, 1.0 );
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
	{
		glColor3ub(255, 255, 255);
		glTexCoord2i(0, 1);
		//glVertex2i(x, y);
		glVertex3f(x, y, 0);
		glTexCoord2i(1, 1);
		//glVertex2i(x + w, y);
		glVertex3f(x+w, y, 0);
		glTexCoord2i(1, 0);
		//glVertex2i(x + w, y + h);
		glVertex3f(x+w, y+h, 0);
		glTexCoord2i(0, 0);
		//glVertex2i(x, y + h);
		glVertex3f(x, y+h, 0);
	}
	glEnd();
}

void enemyBulletCollision(gameObj *bullets, gameObj *enemies){
	int i, j;
	for (i = 0; i < 20; i++){
		if (bullets[i].direction != -1){
			for (j = 0; j < 30; j++){
				if (!enemies[j].dead){
					if (AABBIntersect(&bullets[i].aabb, &enemies[j].aabb)){
						bullets[i].direction = -1;
						enemies[j].dead = true;
					}
				}
			}
		}
	}
}

gameObj collision(gameObj* obj1, gameObj walls[][40]){
	int i;
	int j;
	for (i = 0; i < 40; i++){
		for (j = 0; j < 40; j++){
			while (AABBIntersect(&obj1->aabb, &walls[i][j].aabb))
			{
				//printf("walltype: %d\n", walls[i][j].walltype);
				//printf("player X: %lf\n", obj1->aabb.x);
				//printf("player y: %lf\n", obj1->aabb.y);
				//printf("previous player X: %lf\n", obj1->prevX);
				//printf("previous player Y: %lf\n", obj1->prevY);
				if (walls[i][j].walltype == 2){
					if (obj1->prevX > obj1->aabb.x){
						obj1->aabb.x = obj1->aabb.x + .1;
						//printf("on change player X: %d\n", obj1->aabb.x);
					}
					if (obj1->prevX < obj1->aabb.x){
						obj1->aabb.x = obj1->aabb.x - .1;
						//printf("on change player X: %d\n", obj1->aabb.x);
					}
				}
				if (walls[i][j].walltype == 1){
					if (obj1->prevY > obj1->aabb.y){
						obj1->aabb.y = obj1->aabb.y + .1;
						//printf("on change player Y: %d\n", obj1->aabb.y);
					}
					if (obj1->prevY < obj1->aabb.y){
						obj1->aabb.y = obj1->aabb.y - .1;
						//printf("on change player Y: %d\n", obj1->aabb.y);
					}
				}
				//printf("collision!");
				//int midXp = obj1->aabb.x + obj1->aabb.w/2;
				//int midYp = obj1->aabb.y + obj1->aabb.h/2;
				//int midXw = walls[i][j].aabb.x + walls[i][j].aabb.w / 2;
				//int midYw = walls[i][j].aabb.y + walls[i][j].aabb.h / 2;
			}
		}
	}
	//printf("doen with collision!");
	return *obj1;
}
//struct gameObj walls[40][40];
//player pchar;
int main(void){
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_Window* window = SDL_CreateWindow("TestSDL",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1280, 720, SDL_WINDOW_OPENGL);
	if (!window){
		fprintf(stderr, "Could not create window. ErrorCode=%\n",
			SDL_GetError());
		SDL_Quit();
		return 1;
	}
	SDL_GL_CreateContext(window);

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK){
		fprintf(stderr, "Could not initialize glew. ErrorCode=%s\n",
			glewGetErrorString(glewError));
		SDL_Quit();
		return 1;
	}
	if (!GLEW_VERSION_3_0){
		fprintf(stderr, "OpenGL max supported version is too low.\n");
		SDL_Quit();
		return 1;
	}
	float x = 0;
	float y = 0;
	//struct AABB cam{ x = 640 - 180, y =  480 - 180};
	float camx = 640 - 180;
	float camx2 = 640 + 180;
	float camy = 360 - 60;
	float camy2 = 360 + 60;
	glViewport(0, 0, 1280, 720);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 1280, 720, 0, 0, 100);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	kbState = SDL_GetKeyboardState(NULL);

	int imgAngle = 0;
	spaceship0 = glTexImageTGAFile("CrabSpr_0.tga", NULL, NULL);
	spaceship1 = glTexImageTGAFile("CrabSpr_1.tga", NULL, NULL);
	GLuint shark0 = glTexImageTGAFile("SharkCircleSpr_0.tga", NULL, NULL);
	GLuint shark1 = glTexImageTGAFile("SharkCircleSpr_1.tga", NULL, NULL);
	GLuint shark2 = glTexImageTGAFile("SharkCircleSpr_2.tga", NULL, NULL);
	GLuint shark3 = glTexImageTGAFile("SharkCircleSpr_3.tga", NULL, NULL);
	GLuint p_up = glTexImageTGAFile("SpaceShip_down.tga", NULL, NULL);
	GLuint p_left = glTexImageTGAFile("SpaceShip_left.tga", NULL, NULL);
	GLuint p_down = glTexImageTGAFile("SpaceShip_up.tga", NULL, NULL);
	GLuint p_right = glTexImageTGAFile("SpaceShip_right.tga", NULL, NULL);
	GLuint lazer = glTexImageTGAFile("FilledCircle_0.tga", NULL, NULL);
	GLuint e_up_0 = glTexImageTGAFile("CrazySharkSpr_0.tga", NULL, NULL);
	GLuint e_up_1 = glTexImageTGAFile("CrazySharkSpr_1.tga", NULL, NULL);
	GLuint e_up_2 = glTexImageTGAFile("CrazySharkSpr_2.tga", NULL, NULL);
	GLuint e_right_0 = glTexImageTGAFile("CrazySharkSpr_0_right.tga", NULL, NULL);
	GLuint e_right_1 = glTexImageTGAFile("CrazySharkSpr_1_right.tga", NULL, NULL);
	GLuint e_right_2 = glTexImageTGAFile("CrazySharkSpr_2_right.tga", NULL, NULL);
	GLuint e_left_0 = glTexImageTGAFile("CrazySharkSpr_0_left.tga", NULL, NULL);
	GLuint e_left_1 = glTexImageTGAFile("CrazySharkSpr_1_left.tga", NULL, NULL);
	GLuint e_left_2 = glTexImageTGAFile("CrazySharkSpr_2_left.tga", NULL, NULL);
	GLuint e_down_0 = glTexImageTGAFile("CrazySharkSpr_0_down.tga", NULL, NULL);
	GLuint e_down_1 = glTexImageTGAFile("CrazySharkSpr_1_down.tga", NULL, NULL);
	GLuint e_down_2 = glTexImageTGAFile("CrazySharkSpr_2_down.tga", NULL, NULL);
	GLuint youwin = glTexImageTGAFile("youwin.tga", NULL, NULL);
	int n, m;
	struct AABB cammy;
	cammy.x = x;
	cammy.y = y;
	cammy.w = 1280;
	cammy.h = 720;
	struct gameObj walls[40][40];
	for (n = 0; n < 40; n++){
		for (m = 0; m < 40; m++){
			printf("map num: %d\n", map[m][n]);
			if (map[m][n] != 0){
				printf("map num: %d!!!!!!!!!!\n", map[m][n]);
				walls[m][n].currentFrame = 0;
				walls[m][n].frames[0] = spaceship0;
				walls[m][n].frames[1] = spaceship1;
				walls[m][n].frameTime = 150;
				walls[m][n].name = "wall";
				walls[m][n].timeTillFrameChange = 150;
				walls[m][n].totalFrames = 2;
				walls[m][n].aabb.x = n * 64;
				walls[m][n].aabb.y = m * 64;
				walls[m][n].aabb.w = 64;
				walls[m][n].aabb.h = 64;
				walls[m][n].walltype = map[m][n];
			}
		}
	}
	//start = clock();
	int deltaTime;
	//current = clock();
	current = SDL_GetTicks();
	double gravity = .05;
	player pchar;
	pchar.playerObj.currentFrame = 0;
	//pchar.playerObj.frameTime = 150;
	//pchar.playerObj.totalFrames = 4;
	//pchar.playerObj.timeTillFrameChange = 150;
	pchar.playerObj.aabb.x = 400;
	pchar.playerObj.aabb.y = 400;
	pchar.playerObj.aabb.w = 64;
	pchar.playerObj.aabb.h = 64;
	pchar.playerObj.frames[0] = p_up;
	pchar.playerObj.frames[1] = p_right;
	pchar.playerObj.frames[2] = p_down;
	pchar.playerObj.frames[3] = p_left;
	pchar.playerObj.name = "player";
	pchar.velocity = 0;
	double maxvelocity = 3;

	struct gameObj bullets[20];
	int p;
	int bulletNum = 0;
	for (p = 0; p < 20; p++){
		bullets[p].aabb.h = 64;
		bullets[p].aabb.w = 64;
		bullets[p].aabb.x = -500;
		bullets[p].aabb.y = -500;
		bullets[p].direction = -1;
		bullets[p].bulletTime = 300;
		bullets[p].frames[0] = lazer;
		bullets[p].draw = false;
	}
	int it, no;
	time_t t;

	no = 5;

	/* Intializes random number generator */
	srand((unsigned)time(&t));

	/* Print 5 random numbers from 0 to 49 */
	//for (it = 0; it < no; it++)
	//{
	//	printf("%d\n", rand() % 10);
	//}
	int spawn;
	struct gameObj enemies[30];
	for (p = 0; p < 30; p++){
		spawn = rand() % 8;
		if (spawn == 0 || spawn == 1){
			enemies[p].aabb.x = -200;
			enemies[p].aabb.y = -200;
		}
		if (spawn == 2){
			enemies[p].aabb.x = 1280;
			enemies[p].aabb.y = -200;
		}
		if (spawn == 3){
			enemies[p].aabb.x = 2760;
			enemies[p].aabb.y = -200;
		}
		if (spawn == 4){
			enemies[p].aabb.x = -200;
			enemies[p].aabb.y = 1280;
		}
		if (spawn == 5){
			enemies[p].aabb.x = 2760;
			enemies[p].aabb.y = 1280;
		}
		if (spawn == 6){
			enemies[p].aabb.x = -200;
			enemies[p].aabb.y = 2760;
		}
		if (spawn == 7){
			enemies[p].aabb.x = 1280;
			enemies[p].aabb.y = 2760;
		}
		if (spawn == 8){
			enemies[p].aabb.x = 2760;
			enemies[p].aabb.y = 2760;
		}
		enemies[p].aabb.h = 64;
		enemies[p].aabb.w = 64;
		enemies[p].up[0] = e_up_0;
		enemies[p].up[1] = e_up_1;
		enemies[p].up[2] = e_up_2;
		enemies[p].down[0] = e_down_0;
		enemies[p].down[1] = e_down_1;
		enemies[p].down[2] = e_down_2;
		enemies[p].left[0] = e_left_0;
		enemies[p].left[1] = e_left_1;
		enemies[p].left[2] = e_left_2;
		enemies[p].right[0] = e_right_0;
		enemies[p].right[1] = e_right_1;
		enemies[p].right[2] = e_right_2;
		enemies[p].direction = 0;
		enemies[p].moves = 10;
		enemies[p].moveTime = 1000;
		enemies[p].behavior = 1;
		enemies[p].dead = false;
		enemies[p].totalFrames = 3;
		enemies[p].currentFrame = 0;
		enemies[p].frameTime = 150;
		enemies[p].timeTillFrameChange = 150;
	}
	while (!shouldExit){
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_QUIT:
				shouldExit = 1;
			}
		}

		//memcpy(kbPrevState, kbState, sizeof(kbPrevState));

		//spaceship = glTexImageTGAFile("SpaceShip_0.png", NULL, NULL);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		int future = SDL_GetTicks();

		deltaTime = future - current;
		//printf("DeltaTime: %d\n", deltaTime);
		//current = clock();
		current = future;
		int i;
		int j;
		for (i = 0; i < 40; i++){
			for (j = 0; j < 40; j++){
				if (map[i][j] != 0){
					gameObj* temp = &walls[i][j];
					animUpdate(temp, deltaTime);
					if (AABBIntersect(&temp->aabb, &cammy)){
						glDrawSprite(temp->frames[temp->currentFrame], temp->aabb.x - x, temp->aabb.y - y, 64, 64, imgAngle);
					}
				}
			}
		}
		//pchar.playerObj.aabb.y += pchar.velocity;
		//pchar.velocity += gravity;
		if (pchar.velocity >= maxvelocity)
		{
			pchar.velocity = maxvelocity;
		}
		//animUpdate(&pchar.playerObj, deltaTime);
		//printf("Obj Name: %s\n", pchar.playerObj.name);
		//printf("currentFrame: %d\n", pchar.playerObj.currentFrame);
		//printf("timeTillFrameChange: %f\n", pchar.playerObj.timeTillFrameChange);
		//printf("deltatime: %f\n", deltaTime);
		//printf("frametime: %f\n", pchar.playerObj.frameTime);
		//printf("player x: %d\n", pchar.playerObj.aabb.x);
		//printf("playe y: %d\n", pchar.playerObj.aabb.y);
		//glDrawSprite(pchar.playerObj.frames[pchar.playerObj.currentFrame], pchar.playerObj.aabb.x -x, pchar.playerObj.aabb.y -y, 64, 64, imgAngle);
		int e;
		//printf("test rand: %d\n", rand() % 2);
		for (e = 0; e < 30; e++){
			if (!enemies[e].dead){
				gameObj* temp = &enemies[e];
				animUpdate(temp, deltaTime);
				if (enemies[e].moveTime <= 0){
					enemies[e].moveTime = 1000;
					enemies[e].moves--;
				}
				if (enemies[e].moves < 1){
					enemies[e].behavior = rand() % 3;
					enemies[e].moves = 10;
					//printf("behavior = : %d\n", enemies[e].behavior);
				}
				int xD = pchar.playerObj.aabb.x - enemies[e].aabb.x;
				int yD = pchar.playerObj.aabb.y - enemies[e].aabb.y;
				if (enemies[e].moveTime == 1000){
					//printf("new move time! %d\n", rand() % 9);
					if (enemies[e].behavior == 0){
							if (abs(xD) > abs(yD)){
								if (xD > 0){
									enemies[e].direction = 1;
								}
								else {
									enemies[e].direction = 3;
								}
							}
							else{
								if (yD > 0){
									enemies[e].direction = 0;
								}
								else {
									enemies[e].direction = 2;
								}
							}
					}
					if (enemies[e].behavior == 2){
						enemies[e].direction = rand() % 4;
					}
				}
				if (enemies[e].behavior == 1){
					if (abs(xD) > abs(yD)){
						if (xD > 0){
							enemies[e].direction = 1;
						}
						else {
							enemies[e].direction = 3;
						}
					}
					else{
						if (yD > 0){
							enemies[e].direction = 0;
						}
						else {
							enemies[e].direction = 2;
						}
					}
					//printf("enemies direction: %d\n", enemies[e].direction);
				}
				if (enemies[e].direction == 0){
					enemies[e].aabb.y += .4;
				}
				if (enemies[e].direction == 1){
					enemies[e].aabb.x += .4;
				}
				if (enemies[e].direction == 2){
					enemies[e].aabb.y -= .4;
				}
				if (enemies[e].direction == 3){
					enemies[e].aabb.x -= .4;
				}
				enemies[e].moveTime -= deltaTime;
				if (AABBIntersect(&enemies[e].aabb, &cammy)){
					if (enemies[e].direction == 0){
						glDrawSprite(temp->up[temp->currentFrame], temp->aabb.x - x, temp->aabb.y - y, 64, 64, imgAngle);
					}
					if (enemies[e].direction == 1){
						glDrawSprite(temp->right[temp->currentFrame], temp->aabb.x - x, temp->aabb.y - y, 64, 64, imgAngle);
					}
					if (enemies[e].direction == 2){
						glDrawSprite(temp->down[temp->currentFrame], temp->aabb.x - x, temp->aabb.y - y, 64, 64, imgAngle);
					}
					if (enemies[e].direction == 3){
						glDrawSprite(temp->left[temp->currentFrame], temp->aabb.x - x, temp->aabb.y - y, 64, 64, imgAngle);
					}
				}
			}
		}
		//glDrawSprite(shark0, x, y, 32, 32, imgAngle);
		pchar.playerObj = collision(&pchar.playerObj, walls);
		pchar.playerObj.prevX = pchar.playerObj.aabb.x;
		pchar.playerObj.prevY = pchar.playerObj.aabb.y;
		enemyBulletCollision(bullets, enemies);
		if (pchar.playerObj.aabb.x < camx +x){
			//x -= .6;
			x = pchar.playerObj.aabb.x - camx;
			cammy.x = x;
			//printf("camera's x: %f\n", x);
		}
		if (pchar.playerObj.aabb.x > camx2 + x){
			//x += .6;
			x = pchar.playerObj.aabb.x - camx2;
			cammy.x = x;
			//printf("camera's x: %f\n", x);
		}
		if (pchar.playerObj.aabb.y < camy + y){
			//y -= .6;
			y = pchar.playerObj.aabb.y - camy;
			cammy.y = y;
			//printf("camera's y: %f\n", y);
		}
		if (pchar.playerObj.aabb.y > camy2+ y){
			//y += .6;
			y = pchar.playerObj.aabb.y - camy2;
			cammy.y = y;
			//printf("camera's y: %f\n", y);
		}
		//pchar.playerObj = collision(&pchar.playerObj, walls);
		if (kbState[SDL_SCANCODE_J]){
			//x-=.6;
		}
		if (kbState[SDL_SCANCODE_L]){
			//x+=.6;
		}
		if (kbState[SDL_SCANCODE_I]){
			//y-=.6;
		}
		if (!kbPrevState[SDL_SCANCODE_K])
		{
			if (kbState[SDL_SCANCODE_K]){
				printf("test rand: %d\n", rand() % 2);
			}
		}
		if (kbState[SDL_SCANCODE_A]){
			pchar.playerObj.aabb.x -= .6;
			//animUpdate(&pchar.playerObj, deltaTime);
			//pchar.playerObj.currentFrame = 3;
		}
		if (kbState[SDL_SCANCODE_D]){
			pchar.playerObj.aabb.x += .6;
			//animUpdate(&pchar.playerObj, deltaTime);
			//pchar.playerObj.currentFrame = 1;
		}
		if (kbState[SDL_SCANCODE_W]){
			pchar.playerObj.aabb.y -= .6;
			//pchar.playerObj.currentFrame = 0;
		}
		if (kbState[SDL_SCANCODE_S]){
			pchar.playerObj.aabb.y += .6;
			//pchar.playerObj.currentFrame = 2;
		}
		/*if (kbState[SDL_SCANCODE_C]){
			imgAngle += 1;
		}
		if (kbState[SDL_SCANCODE_V]){
			imgAngle += -1;
		}*/
		if (kbState[SDL_SCANCODE_UP]){
			pchar.playerObj.currentFrame = 0;
		}
		if (kbState[SDL_SCANCODE_LEFT]){
			pchar.playerObj.currentFrame = 3;
		}
		if (kbState[SDL_SCANCODE_DOWN]){
			pchar.playerObj.currentFrame = 2;
		}
		if (kbState[SDL_SCANCODE_RIGHT]){
			pchar.playerObj.currentFrame = 1;
		}
		if (!kbPrevState[SDL_SCANCODE_SPACE])
		{
			//printf("nor pressing spacebar\n");
			if (kbState[SDL_SCANCODE_SPACE]){
				printf("pressed spacebar\n");
				bullets[bulletNum].direction = pchar.playerObj.currentFrame;
				bullets[bulletNum].aabb.x = pchar.playerObj.aabb.x;
				bullets[bulletNum].aabb.y = pchar.playerObj.aabb.y;
				bullets[bulletNum].bulletTime = 300;
				bulletNum++;
				if (bulletNum >= 19){
					bulletNum = 0;
				}
			}
		}
		int q;
		for (q = 0; q < 20; q++){
			if (bullets[q].direction != -1) {
				if (bullets[q].bulletTime < 0){
					bullets[q].direction = -1;
				}
				else {
					bullets[q].bulletTime--;
					if (bullets[q].direction == 0) {
						bullets[q].aabb.y -= 2;
					}
					if (bullets[q].direction == 1) {
						bullets[q].aabb.x += 2;
					}
					if (bullets[q].direction == 2) {
						bullets[q].aabb.y += 2;
					}
					if (bullets[q].direction == 3) {
						bullets[q].aabb.x -= 2;
					}
					//printf("DRAW BULLET\n");
					if (AABBIntersect(&bullets[q].aabb, &cammy)){
						glDrawSprite(bullets[q].frames[0], bullets[q].aabb.x - x, bullets[q].aabb.y - y, 64, 64, imgAngle);
					}
				}
			}
		}
		int deathCount = 0;
		for (q = 0; q < 30; q++){
			if (enemies[q].dead){
				deathCount++;
			}
		}
		if (deathCount > 29){
			glDrawSprite(youwin, cammy.x - x + 320, cammy.y - y + 272 / 2, 640, 480, imgAngle);
		}
		//glDrawSprite(youwin, cammy.x -  x + 320,cammy.y - y + 272/2, 640, 480, imgAngle);
		/*int v;
		for (v = 40; i < 40; i++){
			if ()
		}*/
		glDrawSprite(pchar.playerObj.frames[pchar.playerObj.currentFrame], pchar.playerObj.aabb.x - x, pchar.playerObj.aabb.y - y, 64, 64, imgAngle);
		memcpy(kbPrevState, kbState, sizeof(kbPrevState));
		SDL_GL_SwapWindow(window);
	}

	SDL_Quit();

	return 0;
};