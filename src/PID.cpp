#include "PID.h"
#include <algorithm>
#include <math.h>
//using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;

	p_error = 0.0;
	i_error = 0.0;
	d_error = 0.0;
	
	pre_cte = 0.0;
	min_error = std::numeric_limits<double>::max();
	max_error = std::numeric_limits<double>::min();
}

void PID::UpdateError(double cte) {
	// propagate error
	p_error = pre_cte;
	d_error = cte - pre_cte;
	i_error += cte;
	pre_cte = cte;
	
	if (fabs(cte) > max_error) {
		max_error = fabs(cte);
	}
	if (fabs(cte) < min_error) {
		min_error = fabs(cte);
	}
}

double PID::TotalError() {
	double total_err = Kp*p_error + Kd*d_error + Ki*i_error;
	return total_err;
}

