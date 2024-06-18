#pragma once
class Ball {
protected:
	float x, y;
	float speedX, speedY;
	float radius;

public:
	Ball(float x, float y, float rad, float sX = 300, float sY = 300);
	void draw();
	void move(float velocity);
	void checkLimits();
	void checkCollisions(Rectangle playerSX, Rectangle playerDX, Sound fx);
	const char* handleWinner();
};

