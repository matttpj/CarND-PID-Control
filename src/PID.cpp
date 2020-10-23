#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
   PID::Kp = Kp_;
   PID::Ki = Ki_;
   PID::Kd = Kd_;

   p_error = 0.0;
   i_error = 0.0;
   d_error = 0.0;

   // Previous cte
   prev_cte = 0.0;

   // Counters
   counter = 0;
   error_sum = 0.0;

}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */

  // Proportional Error
  p_error = cte;

  // Differential Error
  d_error = cte - prev_cte;
  prev_cte = cte;

  // Integral Error
  i_error += cte;

  error_sum += cte;
  counter++;

  if(cte < best_error){
    best_error = cte;
  }

}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  total_error = p_error * Kp + i_error * Ki + d_error * Kd;

  return total_error;  // TODO: Add your total error calc here!
}

double PID::BestError() {

  return best_error;
}
