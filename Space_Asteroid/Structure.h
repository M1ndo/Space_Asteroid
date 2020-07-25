#pragma once


enum Movement_type { PARABOLIC, LINEAR };

struct Asted {
	double x_pos;
	double y_pos;
	double redius;
	double start_x;
	double start_y;
	double speed_x;
	double speed_y;
	double final;
	int direction;
	bool outside;
	Movement_type movement;

	Asted(double x, double y, double z, Movement_type m, double b, double ship_x, double ship_y);
	~Asted();
	bool operator==(const Asted& a);
};


struct Firearm {


	double x_pos;
	double y_pos;
	double start_x;
	double start_y;
	double speed_x;
	double speed_y;
	double final;
	int direction;
	Firearm(double x, double y, double ship_x, double ship_y);
	bool operator==(const Firearm& b);
	~Firearm();
};	


