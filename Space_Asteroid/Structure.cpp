#include "Structure.h"
#pragma once
#include <iostream>

Asted::Asted(double x, double y, double z, Movement_type m, double b, double ship_x, double ship_y) : start_x(x), start_y(y), redius(z), movement(m), final(b), outside(false)

{
	if (start_x < 0) {
		direction = 1;
	}
	else {
		direction = -1;
	}
	switch (movement)
	{
	case LINEAR:
		speed_x = -x + ship_x;
		speed_y = -y + ship_y;
		start_x += ship_x;
		start_y += ship_y;
		x_pos = start_x;
		y_pos = start_y;
		break;
	
	case PARABOLIC:
		speed_x = -x + ship_x;
		speed_y = start_y + ship_y;
		start_x = ship_x;
		start_y = ship_y;
		x_pos = start_x;
		y_pos = start_y;
		std::cout << "X: " << start_x << "Y: " << start_y << "FinX: " << speed_x << "SPP " << speed_y << std::endl;
		break;
	}
}

Asted::~Asted(){}

bool Asted::operator==(const Asted& a)
{	
	if (x_pos == a.x_pos && y_pos == a.y_pos) {
		return true;
	}
	return false;
}

Firearm::Firearm(double x, double y, double ship_x, double ship_y) : speed_x(x), speed_y(y), x_pos(ship_x), y_pos(ship_y), start_x(ship_x), start_y(ship_y) {
	if (speed_x > ship_x) {
		direction = 1;
	}
	else {
		direction = -1;
	}
}


bool Firearm::operator==(const Firearm& b)
{
	if (x_pos == b.x_pos && y_pos == b.y_pos) {
		return true;
	}
	return false;
}

Firearm::~Firearm(){}
