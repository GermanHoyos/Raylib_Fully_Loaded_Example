#include "raylib_and_all_headers_wrapper.h"
#pragma once

class TimeUtils {
public:
	static int seconds;
	static int minutes;
	static float deltaTime;

	static float getDeltaTime();
	static int getFPS();
	static void displaySystemTime();
};