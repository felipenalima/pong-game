#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <string>

class Example : public olc::PixelGameEngine
{
	public: 
			Example()
			{
				sAppName = "Example";
			}

	private:
		float leftPaddleOffset = 0.0f;
		float rightPaddleOffset = 0.0f;
		float paddleSpeed = 200.0f;
		char incPoint[11] = "0123456789";
		int indexPointRight = 1;
		int indexPointLeft = 1;

		std::string incPointStringRight;
		std::string incPointStringLeft;

		olc::vf2d posBall = { ScreenWidth() / 2, ScreenHeight() / 2 };
		olc::vf2d velBall = { 200.0f, -100.0f };

		typedef enum 
		{
			Menu,
			Play,
			EndGame
		}States_t;

		States_t state = Menu;

	public:
		bool OnUserCreate() override
		{
			return true;
		}
		bool OnUserUpdate(float fElapsedTime) override
		{
			switch (state)
			{
				case Menu:
				{
					Clear(olc::BLACK);

					incPointStringLeft = incPoint[0];
					incPointStringRight = incPoint[0];
					indexPointRight = 1;
					indexPointLeft = 1;
					
					DrawString(ScreenWidth()/2 - 190, ScreenHeight() / 2, "Left Mouse Click to Start", olc::WHITE, 2);
					DrawString(ScreenWidth() / 2 - 36, 6, "Pong Game", olc::WHITE);

					//Paddle
					DrawRect(40, 40, ScreenWidth() - 80, ScreenHeight() - 80, olc::WHITE);
					FillRect(45, (ScreenHeight() / 2 - 25) + (int)leftPaddleOffset, 10, 50, olc::WHITE); //Left Paddle
					FillRect(ScreenWidth() - 55, (ScreenHeight() / 2 - 25) + (int)rightPaddleOffset, 10, 50, olc::WHITE); //Right Paddle

					//Lines
					DrawLine(20, 20, ScreenWidth() - 20, 20, olc::WHITE); //Up Line
					DrawLine(20, 20, 20, ScreenHeight() - 20, olc::WHITE);//Left Line
					DrawLine(20, ScreenHeight() - 20, ScreenWidth() - 20, ScreenHeight() - 20, olc::WHITE); //Down Line
					DrawLine(ScreenWidth() - 20, 20, ScreenWidth() - 20, ScreenHeight() - 20, olc::WHITE); //Right Line
					DrawLine(ScreenWidth() / 2, 40, ScreenWidth() / 2, ScreenHeight() - 40, olc::DARK_GREY); //Middle Line

					if (GetMouse(0).bPressed)
					{
						state = Play;
					}

				}break;
				case Play:
				{
					//Left Movement
					if (GetKey(olc::Key::W).bHeld && leftPaddleOffset > (float)(-ScreenHeight() / 2) + 67.0f)
						leftPaddleOffset -= paddleSpeed * fElapsedTime;

					if (GetKey(olc::Key::S).bHeld && leftPaddleOffset < (float)(ScreenHeight() / 2) - 67.0f)
						leftPaddleOffset += paddleSpeed * fElapsedTime;

					//Right Movement
					if (GetKey(olc::Key::UP).bHeld && rightPaddleOffset > (float)(-ScreenHeight() / 2) + 67.0f)
						rightPaddleOffset -= paddleSpeed * fElapsedTime;

					if (GetKey(olc::Key::DOWN).bHeld && rightPaddleOffset < (float)(ScreenHeight() / 2) - 67.0f)
						rightPaddleOffset += paddleSpeed * fElapsedTime;

					// Limit Detection
					if (posBall.y <= 42.0f)
						velBall.y *= -1.0f;
					
					if (posBall.y >= (float)(ScreenHeight()) - 42.0f)
						velBall.y *= -1.0f;

					if (posBall.x <= 42.0f)
					{
						velBall.x *= -1.0f;

						float  fAngle = (float(rand()) / float(RAND_MAX)) * 8.0f * 3.14159f;

						if (fAngle <= 45.0f || fAngle >= 135.0f || fAngle <= 225.0f || fAngle >= 315.0f)
						{
							fAngle = (float(rand()) / float(RAND_MAX)) * 8.0f * 3.14159f;
						}
						else velBall = { 300.0f * cos(fAngle), 300.0f * sin(fAngle) };

						posBall = { (float)ScreenWidth() / 2,(float)ScreenHeight() / 2 };


						if (indexPointRight >= 6)
						{
							indexPointRight = 0;
							incPointStringRight = incPoint[0];
						}
						else
							incPointStringRight = incPoint[indexPointRight++];
					}

					if (posBall.x >= (float)(ScreenWidth()) - 42.0f)
					{
						velBall.x *= -1.0f;

						float  fAngle = (float(rand()) / float(RAND_MAX)) * 8.0f * 3.14159f;

						if (fAngle <= 45.0f || fAngle >= 135.0f || fAngle <= 225.0f || fAngle >= 315.0f)
						{
							fAngle = (float(rand()) / float(RAND_MAX)) * 8.0f * 3.14159f;
						}
						else velBall = { 300.0f * cos(fAngle), 300.0f * sin(fAngle) };
						
						posBall = { (float)ScreenWidth() / 2,(float)ScreenHeight() / 2 };

						if (indexPointLeft >= 6)
						{
							indexPointLeft = 0;
							incPointStringLeft = incPoint[0];
						}
						else
							incPointStringLeft = incPoint[indexPointLeft++];
					}

					if (indexPointRight == 6 || indexPointLeft == 6)
					{
						state = EndGame;
					}

					//Check Paddle Collision
					if ((posBall.x <= 55.0f) && (posBall.y > ((float)(ScreenHeight() / 2 - 25.0f) + leftPaddleOffset)) && (posBall.y < ((float)(ScreenHeight() / 2 - 25.0f) + leftPaddleOffset + 50.0f)))
					{
						velBall.x *= -1.0f;
					}
					if ((posBall.x >= ((float)ScreenWidth() - 55.0f)) && (posBall.y > ((ScreenHeight() / 2 - 25) + rightPaddleOffset)) && (posBall.y < ((ScreenHeight() / 2 - 25) + rightPaddleOffset + 50.0f)))
					{
						velBall.x *= -1.0f;
					}

					Clear(olc::DARK_BLUE);

					//Lines
					DrawLine(20, 20, ScreenWidth() - 20, 20, olc::WHITE); //Up Line
					DrawLine(20, 20, 20, ScreenHeight() - 20, olc::WHITE);//Left Line
					DrawLine(20, ScreenHeight() - 20, ScreenWidth() - 20, ScreenHeight() - 20, olc::WHITE); //Down Line
					DrawLine(ScreenWidth() - 20, 20, ScreenWidth() - 20, ScreenHeight() - 20, olc::WHITE); //Right Line
					DrawLine(ScreenWidth() / 2, 40, ScreenWidth() / 2, ScreenHeight() - 40, olc::DARK_GREY); //Middle Line

					//Rects
					DrawRect(40, 40, ScreenWidth() - 80, ScreenHeight() - 80, olc::WHITE);
					FillRect(45, (ScreenHeight() / 2 - 25) + (int)leftPaddleOffset, 10, 50, olc::WHITE); //Left Paddle
					FillRect(ScreenWidth() - 55, (ScreenHeight() / 2 - 25) + (int)rightPaddleOffset, 10, 50, olc::WHITE); //Right Paddle

					//Strings
					DrawString(ScreenWidth() / 2 - 36, 6, "Pong Game", olc::WHITE);
					DrawString(ScreenWidth() / 2 - 35, 60, incPointStringLeft, olc::WHITE, 3);
					DrawString(ScreenWidth() / 2 + 11, 60, incPointStringRight, olc::WHITE, 3);

					//Ball
					posBall += velBall * fElapsedTime;
					FillCircle(posBall, 5, olc::WHITE);

				}break;
				case EndGame:
				{

					if (indexPointRight == 6)
					{
						DrawString(ScreenWidth() / 2 - 200, ScreenHeight() / 2 + 30, "Press Left Click To Continue", olc::WHITE, 2);
						DrawString(ScreenWidth() / 2 - 115, ScreenHeight() / 2 - 30, "Right Paddle Wins", olc::DARK_RED, 2);
						DrawString(ScreenWidth() / 2 - 88, ScreenHeight() / 2, "END GAME", olc::WHITE, 3);
						indexPointRight = 0;
						indexPointLeft = 0;
					}
					if (indexPointLeft == 6)
					{
						DrawString(ScreenWidth() / 2 - 200, ScreenHeight() / 2 + 30, "Press Left Click To Continue", olc::WHITE, 2);
						DrawString(ScreenWidth() / 2 - 115, ScreenHeight() / 2 - 30, "Left Paddle Wins", olc::DARK_RED, 2);
						DrawString(ScreenWidth() / 2 - 88, ScreenHeight() / 2, "END GAME", olc::WHITE, 3);
						indexPointRight = 0;
						indexPointLeft = 0;
					}
					if (GetMouse(0).bPressed)
					{
						state = Menu;
					}
				}break;
				default:break;
			}		
			return true;
		}
};

int main()
{
	Example demo;

	if(demo.Construct(720, 480, 2, 2))
		demo.Start();
	return 0;
}