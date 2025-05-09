#pragma once
class MediaPlayerBase
{
protected:

	int x;
	int y;
	int width;
	int height;

public:
	MediaPlayerBase(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {

	}

	virtual ~MediaPlayerBase() {
	
	}

	virtual void draw() = 0;



};

