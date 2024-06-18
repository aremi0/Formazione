#include "raylib.h"
#include "Ball.h"

Ball::Ball(float x, float y, float rad, float sX, float sY) {
	this->x = x;
	this->y = y;
	this->radius = rad;
	this->speedX = sX;
	this->speedY = sY;
}

void Ball::draw() {
	DrawCircle((int) x, (int) y, radius, WHITE);
}

void Ball::move(float velocity) {
	this->x += this->speedX * velocity;
	this->y += this->speedY * velocity;
	Ball::checkLimits();
}

void Ball::checkLimits() {
	if(this->y < 0) {
		this->y = 0;
		this->speedY *= -1;
	}
	if(this->y > GetScreenHeight()) {
		this->y = GetScreenHeight();
		this->speedY *= -1;
	}
}

void Ball::checkCollisions(Rectangle playerSX, Rectangle playerDX, Sound fx) {

	if(CheckCollisionCircleRec(Vector2 { this->x, this->y }, this->radius, playerSX)) {
		if(this->speedX < 0) {
			this->speedX *= -1.1f;
			this->speedY = (this->y - playerSX.y) / (playerSX.height / 2) * this->speedX;
		}
		PlaySound(fx);
	}

	if(CheckCollisionCircleRec(Vector2 { this->x, this->y }, this->radius, playerDX)) {
		if(this->speedX > 0) {
			this->speedX *= -1.1f;
			this->speedY = (this->y - playerDX.y) / (playerDX.height / 2) * -(this->speedX);
		}
		PlaySound(fx);
	}
}

const char* Ball::handleWinner() {
	if(this->x < 0)
		return "Right Player Wins!";

	if(this->x > GetScreenWidth())
		return "Left Player Wins!";

	return nullptr;
}