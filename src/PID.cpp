#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->p_error = 0;
  this->i_error = 0;
  this->d_error = 0;
  this->Kp = Kp;
  this->Kd = Kd;
  this->Ki = Ki;

}

void PID::UpdateError(double cte, double speed_factor) {

  this->d_error = (cte - this->p_error);
  this->i_error += cte;
  this->p_error = cte;
}

double PID::TotalError() {
  double ControlFeedback = -this->Kp * this->p_error - this->Kd * this->d_error - this->Ki * this->i_error;

  return ControlFeedback;
}

