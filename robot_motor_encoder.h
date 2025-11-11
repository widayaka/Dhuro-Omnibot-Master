#ifndef __ROBOT_MOTOR_ENCODER_H__
#define __ROBOT_MOTOR_ENCODER_H__

#include <stdint.h>

#define ENCODER1A   36
#define ENCODER1B   39
#define ENCODER2A   34
#define ENCODER2B   35
#define PWM_PIN_1A  23  
#define PWM_PIN_1B  19
#define PWM_PIN_2A  18
#define PWM_PIN_2B  4
#define NUM_OF_MOTORS 2

#define CW 0
#define CCW 1

extern int frequency;
extern int resolution;
extern int pwmChannel1;
extern int pwmChannel2;

extern int VAL_ENC_1A;
extern int VAL_ENC_1B;
extern int VAL_ENC_2A;
extern int VAL_ENC_2B;

extern int16_t encoder_cnt[NUM_OF_MOTORS];
extern int16_t encoder_prev_cnt[NUM_OF_MOTORS];
extern int16_t encoder_last_cnt[NUM_OF_MOTORS];
extern int16_t encoder_velocity[NUM_OF_MOTORS];
extern int16_t encoder_velocity_monitor[NUM_OF_MOTORS];

extern float error[NUM_OF_MOTORS]; 
extern float error_w[NUM_OF_MOTORS];
extern float lastError[NUM_OF_MOTORS];
extern float lastError_w[NUM_OF_MOTORS];
extern float P[NUM_OF_MOTORS];
extern float P_w[NUM_OF_MOTORS];
extern float I[NUM_OF_MOTORS];
extern float I_w[NUM_OF_MOTORS];
extern float D[NUM_OF_MOTORS];
extern float D_w[NUM_OF_MOTORS];
extern float PID[NUM_OF_MOTORS];
extern float PID_w[NUM_OF_MOTORS];

extern float motor_p;
extern float motor_i;
extern float motor_d;

extern float motor_pid_min;
extern float motor_pid_max;

extern float motor[NUM_OF_MOTORS];
extern float motor_setPoint[NUM_OF_MOTORS];
extern float pwm_motor[NUM_OF_MOTORS];

extern unsigned long currentTime;
extern unsigned long previousTime;
              
extern int interval;

void encoder1_ISR(void);
void encoder2_ISR(void);
void encoder1_RPM(void);
void encoder2_RPM(void);
void encoderAll_RPM(void);
void robotMotorEncoder_init(void);
void robotDisplayEncoderSlave(void);
void robotDisplayEncoderMaster(void);

#endif