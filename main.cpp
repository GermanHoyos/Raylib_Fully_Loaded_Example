#include "raylib_and_all_headers_wrapper.h"
#include "TimeManager.h"
#include "InputManager.h"
#include <cstdio>
#include <bitset>
using namespace std;

//only convert to radians below if not already converted
	Vector2 angleToDirection(float angle, Vector2 origin, float radius){
		angle = angle * 3.14f / 180; //converted to radians
		Vector2 direction = {(origin.x + radius * cosf(angle)),(origin.y + radius * sinf(angle))};
		return direction;
		//TroubleShoot above with:
		//string dir_str = to_string(direction.x) + " " + to_string(direction.y);
		//DrawText(dir_str.c_str(), 0, 0, 20, GREEN);
	}
//remember y is down so convert to conventional : (origin.y - direction.y,direction.x - origin.x)
	//         90
	//         |
	//  180 -------- 0     
	//         |
	//        270
	float directionToAngle(Vector2 origin ,Vector2 direction) {

		float angle = atan2(origin.y - direction.y,direction.x - origin.x) * 180 / PI;
		if (angle < 0)
			angle += 360;
		string angle_str = "Angle: " + to_string((int)angle);
		DrawText(angle_str.c_str(), origin.x - 50, origin.y - 75, 20, GREEN);
		return angle;
	}
//EaseIn
	float easeIn(float t) { //BLUE
		return t * t; //x^2 {0<x<1}
	}
	Vector2 easeInApply(Vector2 start, Vector2 end, float t, bool flip) {
		float factor = easeIn(t); // 0.0 -> 1.0
		Vector2 xy_returned;
			if (!flip) //right 
			{
				float x = start.x + (end.x - start.x) * factor;
				float y = start.y + (end.y - start.y) * factor;
				xy_returned = { x, y };
			}
			if (flip) //left
			{
				float x = start.x - (start.x - end.x) * factor;
				float y = start.y + (end.y - start.y) * factor;
				xy_returned = { x, y };
			}
		return xy_returned;
	}
//EaseOut
	float easeOut(float t) { //GREEN
		return 1 - (1 - t) * (1 - t); //1-(x-1)^2 {0<x<1}
	}
	Vector2 easeOutApply(Vector2 start, Vector2 end, float t, bool flip) {
		float factor = easeOut(t);
		Vector2 xy_returned;

		if (!flip) //right
		{
			float x = start.x + (end.x - start.x) * factor;
			float y = start.y + (end.y - start.y) * factor;
			xy_returned = { x, y };
		}
		if (flip) //left
		{
			float x = start.x - (start.x - end.x) * factor;
			float y = start.y + (end.y - start.y) * factor;
			xy_returned = { x, y };
		}
		return xy_returned;
	}
// "tweeny" lib inits


//Main**************************
	//**************************
	//**************************
	int main() 
	{
	// Screen Dimensions
		Vector2 screen = {800,600};
	// Init window function
		InitWindow(screen.x, screen.y, "C++ Raylib");
	// Inkscape color pallete
		Color myGreen = {0, 255, 0, 255};
		Color myBlue = {0, 255, 255, 255};
		Color myRed = {255, 0, 0, 255};
		Color myPurple = {255, 0, 255, 255};
	// Textures must be loaded after the InitWindow and before the while game loop
		Texture2D ships = LoadTexture("BgLilgShips.png");
		int textureW = ships.width / 2; //split the image into 2 equal parts
		int textureH = ships.height;
	// Source rectangle (part of the texture to use for drawing)
		Rectangle sourceRec = { 0.0f, 0.0f, (float)textureW, (float)textureH };
	// Destination rectangle (screen rectangle where drawing part of texture)
		Rectangle destRec = { 260, 80, textureW * 5.0f, textureH * 5.0f };
	// Origin of the texture (rotation/scale point), it's relative to destination rectangle size
		Vector2 origin = { (float)textureW * 5.0f  / 2, (float)textureH * 5.0f / 2 };
	// Change this to rotate textures
		int rotation = 0;
	// Black circle:
		float angle = 0;
	// EaseIn
		float t1 = 0.0f;
		float t2 = 0.0f;
		Vector2 position1 = {540, 35};
		bool pos1Switch = false; 
	// EaseOut
		Vector2 position2 = {540, 60};
		bool	flip = false;
		bool	flip0= false;
	// Using tweeny
		// float tweenAcceleration = 2.f;
		// Vector2 boxPosition = { 100, 300 };
		// Vector2 boxSize = { 50, 50 };
		// auto tween1 = tweeny::from(0).to(10).during(10); 
		

	// Set FPS
		SetTargetFPS(60);
	//Start Game Loop **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP**
	while (WindowShouldClose() == false) 
	{
		BeginDrawing();
		ClearBackground({22,22,80,225});
	// Time mechanics
		TimeUtils::displaySystemTime();	
	//Input mechanics
		InputUtils::printKey();
	// Draw object and move object
		DrawTexturePro(ships, sourceRec, destRec, origin, (float)rotation, WHITE);
		rotation++;
	//black circle:
	//Test functions using circle, take an angle and display it on a circle
		angle++;
		Vector2 origin = {370,80};
		DrawCircleV(origin,50,BLACK);
		Vector2 direction = angleToDirection(angle,origin,50);
		DrawCircleV({direction.x,direction.y},4, myRed);
		directionToAngle(origin,direction);
	//easeIn //float t = 0.0f; //Vector2 position1 = { 500, 300 }; <- outside of while loop
		DrawText("EaseIn:",450,30,20,myGreen);
		DrawRectangleV(position1,{10,10},myBlue);
		float animationSpeedFactor = 0.05f;
		if (t1 <= 1.0f &&  flip == false) {
			Vector2 endPosition1 = { 750, 35 };
			position1 = easeInApply(position1, endPosition1, t1, flip);
			t1 += animationSpeedFactor * TimeUtils::getDeltaTime();
			if (position1.x > endPosition1.x - 1){
				flip = true;
				t1 = 0.0f;
			}
		}
		if (t1 <= 1.0f && flip == true) {
			Vector2 endPosition1 = { 540,35 };
			position1 = easeInApply(position1, endPosition1, t1, flip);
			t1 += animationSpeedFactor * TimeUtils::getDeltaTime();
			if (position1.x < endPosition1.x + 1) {
				flip = false;
				t1 = 0.0f;
			}
		}
	//easeOut //float t = 0.0f //Vector2 position2 = {500, 340}; <-outside of while loop
		DrawText("EaseOut:", 450, 55, 20, myGreen);
		DrawRectangleV(position2,{10,10},myGreen);
	//animationSpeedFactor
		if (t2 <= 1.0f && flip0 == false) {
			Vector2 endPosition2 = { 750, 60 };
			position2 = easeOutApply(position2, endPosition2, t2, flip0);
			t2 += animationSpeedFactor * TimeUtils::getDeltaTime();
			if (position2.x > endPosition2.x - 1 ) {
				flip0 = true;
				t2 = 0.0f;
			}
		} 
		if (t2 <= 1.0f && flip0 == true) {
			Vector2 endPosition2 = { 540, 60 };
			position2 = easeOutApply(position2, endPosition2, t2, flip0);
			t2 += animationSpeedFactor * TimeUtils::getDeltaTime();
			if (position2.x < endPosition2.x + 1) {
				flip0 = false;
				t2 = 0.0f;
			}
		}
	//	"tweeny.h" library experiments
	//	Tween 1
		//if (tween1.progress() < 1.0f) 
		//{
		//	// auto tween1 = tweeny::from(0).to(100).during(10);
		//	//float returnedValue = tween1.step((1.0f / GetFPS()) * TimeUtils::deltaTime * tweenAcceleration);
		//	float returnedValue = tween1.step(1.0f / 30.f);
		//	DrawText(to_string(returnedValue).c_str(),0,100,20,GREEN);
		//} else {
		//	tween1 = tweeny::from(0).to(10).during(10); // Recreate the tween1 params to reset it
		//}
	//	Tween 2
		DrawText("BackInOut:", 450, 80, 20, myGreen);
		//if (tween2.progress() < 1.0f) 
		//{
		//	float interpolatedValue = tween2.step((1.0f / 60.0f) * .1f); // Step by 1/60th of a second
		//	Vector2 boxPosition = { interpolatedValue, 300 };
		//	DrawRectangleV(boxPosition, { 10, 10 }, RED);
		//} else {
		//	tween2 = tweeny::from(0).to(600).during(2000).via(easing::backInOut);
		//}

		//while(true)
		//{
		//	auto tween2 = tweeny::from(100).to(400).during(2000).via(easing::backInOut);
		//}
	
	

	//additional console debuging information displays
		//DrawText("Tween 1: ",0,100,20,GREEN);
		DrawText("Debug 2:",0,120,20,GREEN);
		DrawText("Debug 3:",0,140,20,GREEN);
		DrawText("Debug 4:",0,160,20,GREEN);
		DrawText("Debug 5:",0,180,20,GREEN);
		DrawText("Debug 6:",0,200,20,GREEN);
		DrawText("Debug 7:",0,220,20,GREEN);
		DrawText("Debug 8:",0,240,20,GREEN);
		DrawText("Debug 9:",0,260,20,GREEN);


	// end drawing context
		EndDrawing();
	} // End Game Loop **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP** **LOOP**
	
	//unload textures, close window and end game
		UnloadTexture(ships);
		CloseWindow();
		return 0;
	
	}



