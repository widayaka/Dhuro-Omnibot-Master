#ifndef __ROBOT_PROGRAM_MODE_H__
#define __ROBOT_PROGRAM_MODE_H__

extern float compass;

extern float dataYaw;
extern float eepromYaw;
extern float setPointYaw;
extern float errorYaw;
extern float lastErrorYaw;
extern float P_Yaw;
extern float I_Yaw; 
extern float D_Yaw;
extern float PID_Yaw;

extern float dataPitch;
extern float eepromPitch;
extern float setPointPitch; 
extern float errorPitch; 
extern float lastErrorPitch;
extern float P_Pitch;
extern float I_Pitch;
extern float D_Pitch;
extern float PID_Pitch;

extern float dataRoll;
extern float eepromRoll;
extern float setPointRoll;
extern float errorRoll;
extern float lastErrorRoll;
extern float P_Roll;
extern float I_Roll;
extern float D_Roll;
extern float PID_Roll;

extern float KP_Yaw;
extern float KI_Yaw;
extern float KD_Yaw;

extern float KP_Pitch;
extern float KI_Pitch;
extern float KD_Pitch;

extern float KP_Roll;
extern float KI_Roll;
extern float KD_Roll;

void setPIDGainYaw(float kp, float ki, float kd);
void setPIDGainPitch(float kp, float ki, float kd);
void setPIDGainRoll(float kp, float ki, float kd);
void setPIDGainRPM(float kp, float ki, float kd);
void setPIDMinMax(int min, int max);

void robotHoldPosition(void);
void robotJoystickControl(void);
void robotOdometry(void);
void robotROS2Navigation(void);
void robotROS2ObjectTracking(void);
void robotROS2LineFollowing(void);
void robotROS2WallFollowing(void);

void onConnect(void);

#endif