#ifndef INPUT_H
#define INPUT_H

class Input
{
private:
	struct Mouse
	{
		int x, y;
		bool left, right;
	};

	bool keys[256]{ false };
	Mouse mouse;

public:
	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);

	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMouseXY(int lx, int ly);
	int getMouseX();
	int getMouseY();

	void setMouseLeftDown(bool b);
	bool isLeftDown();

	void setMouseRightDown(bool b);
	bool isRightDown();
};

#endif // INPUT_H
