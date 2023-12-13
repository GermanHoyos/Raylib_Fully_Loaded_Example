#include "raylib_and_all_headers_wrapper.h"
#include "TimeManager.h"

using namespace std;

//Must define static variables outside the class with initialization
int gameTotalSeconds = GetTime();
int TimeUtils::seconds = 0;
int TimeUtils::minutes = 0;
float TimeUtils::deltaTime = 0;

float TimeUtils::getDeltaTime() {
	return GetFrameTime();
};

int TimeUtils::getFPS() {
	return GetFPS();
};

void TimeUtils::displaySystemTime() {

	//count the seconds and minutes
	deltaTime = GetFrameTime();
	int currentTime = GetTime();
	if (gameTotalSeconds != currentTime) {
		seconds++;
		if (seconds == 60) {
			seconds = 0;
			minutes++;
		}
		gameTotalSeconds = currentTime;
	}

	//stringify seconds and minutes
	int FPS = GetFPS();
	string seconds_str = "Seconds: " + to_string(seconds);
	string minutes_str = "Minutes: " + to_string(minutes);
	string deltaTime_str = "Delta Time: " + to_string(deltaTime);
	string fps_str = "Fps: " + to_string(FPS);

	//display seconds and minutes
	DrawLine(210, 0, 210, 600, GREEN); //x,y x,y
	//DrawLine(210, 100, 0, 100, GREEN);

	DrawText(fps_str.c_str(), 2, 2, 20, GREEN);
	DrawText(seconds_str.c_str(), 2, 20, 20, GREEN);
	DrawText(minutes_str.c_str(), 2, 40, 20, GREEN);
	DrawText(deltaTime_str.c_str(), 2, 60, 20, GREEN);
}