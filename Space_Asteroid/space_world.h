#pragma once
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Structure.h"
#include <string>
#include <algorithm>
#include <list>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240
#define DIFFICULTY 10
#define GAME_SP 20 // Game Speed
#define BULL_SP 10 // bullet speed 

//Importing Images

std::string path_img1 = "..\\imgs\\asteroid.png";
std::string path_img2 = "..\\imgs\\up-arrow.png";
std::string path_img3 = "..\\imgs\\background.png";

olc::Sprite* aster = new olc::Sprite(path_img1);
olc::Sprite* up_ar = new olc::Sprite(path_img2);
olc::Sprite* bkg = new olc::Sprite(path_img3);


int difficulty = 100;
int last_changement = 0;
class Game : public olc::PixelGameEngine
{
public:
	
	int ship_x_position;
	int ship_y_position;
	std::list<Asted> asted;
	std::list<Firearm> fire;
	int score;
	bool game_over;
	
	Game() :
		ship_x_position(SCREEN_WIDTH / 2),
		ship_y_position(SCREEN_WIDTH / 2),
		score(0),
		game_over(false)
	{
		sAppName = "Asted_Ybenel";
	}
	
	bool OnUserCreate() override
	{
		SetPixelMode(olc::Pixel::MASK);
		DrawCircle(ship_x_position, ship_y_position, 5, olc::Pixel(olc::DARK_GREY));
		// Takes 6 Arguments i passed only 5 That's why it caused the issue.
		Asted first(100.0, 100, 10, LINEAR, 5, ship_x_position, ship_y_position);
		asted.push_back(first);
		return true;
	}
	
	bool OnUserUpdate(float fElapsedTime) override
	{
		
		olc::HWButton key_enter = GetKey(olc::Key::ENTER);
		if (key_enter.bPressed) {
			game_over = false,
				asted.clear();
			fire.clear();
			score = 0;
			difficulty = 100;
			OnUserCreate();
		}
		
		if (game_over) {
			return true;
		}

		olc::HWButton key_mouse = GetMouse(0);
		
		if (key_mouse.bPressed) {
			Firearm novi(GetMouseX(), GetMouseY(), ship_x_position, ship_y_position);
			fire.push_back(novi);
		}
		
		if (score % DIFFICULTY == 0 && difficulty > 150 && score != last_changement) {
			difficulty -= 50;
			last_changement = score;
		}
		
		int respawn_change = rand() % difficulty;
		int direction_x = 1, direction_y = 1;
		int speed = 5;
		Movement_type movement = LINEAR;
		
		if(respawn_change == 1) 
		{
			if (rand() % 2 == 1) { direction_y = -1; }
			if (rand() % 2 == 1) { direction_x = -1; }
			if (rand() % 3 == 1) { movement = PARABOLIC; speed = 2; }
			Asted novi(((rand() % 100) + 150) * direction_x, ((rand() % 100) + 150) * direction_y, 10, movement, speed, ship_x_position, ship_y_position);
			asted.push_back(novi);
		}
		
		//DrawSprite(0, 0, , 1);
		//DrawSprite(0, 0, aster, 1);
		DrawCircle(ship_x_position, ship_y_position, 5, olc::Pixel(olc::DARK_CYAN));
		DrawString(0, 0, "Score:" + std::to_string(score), olc::Pixel(olc::DARK_BLUE), 1);
	}

	// Star Ship Position Calculation 


private:
	void calculate_aste_pos(float time)
	{
		for (Asted& as : asted) {
			double x1 = as.x_pos;
			double y1 = as.y_pos;
			as.x_pos += (time * GAME_SP) * as.speed_x * as.direction;
			switch (as.movement) {
			case LINEAR:
				return;
			}
		}
	}

	// Asteroid Calculation 

	void cacl_fire_pos(float time)
	{
		for (Firearm& b : fire) {
			double angle = abs(ship_y_position - b.speed_y) / 2;
			double x1 = b.x_pos;
			b.x_pos += (time * GAME_SP) * BULL_SP * b.direction;
			double y1 = b.y_pos;
			if (abs(b.y_pos - y1) > 1.3) {
				std::cout << abs(b.y_pos - y1) << std::endl;
				b.x_pos = x1 + (time * GAME_SP) * (BULL_SP / (abs(b.y_pos - y1))) * b.direction;
			}
		}
	}

	bool out_of_bounds(const Firearm& b) {
		if (b.y_pos < 500 && b.y_pos > 0 && b.x_pos > 0 && b.x_pos < 500) { return false; }
		return true;
	}

	template<typename Y>
	void range_lin_interpolation(Y& a) {
		double y = (a.start_y * (a.x_pos - a.speed_y) / (a.start_x - a.speed_x)) + (a.speed_y * ((a.x_pos - a.start_x) / (a.speed_x - a.start_x))
		a.y_pos = y
	}
};
