#include <CurieIMU.h>
#include <MadgwickAHRS.h>

Madgwick gyroScope;
//Variables for Accel and Gyro
int ax,ay,az;
int gx,gy,gz;
float yaw;
float pitch;
float roll;

int divider = 800;   //Variables in which divides average for Gyroscope value
int autoCalibrate = 1;   // 0 = off & 1 = on for AutoCalibration

unsigned long timer_1;  //Timer -> gyroReading
unsigned long timer_2;  //Timer -> accelReading
unsigned long timer_3;  //Timer -> motionReding

uint16_t delay_1 = 500;
uint16_t delay_2 = 2000;
uint16_t delay_3 = 3000;
void setup(){
  Serial.begin(9600);
  timer_1 = millis();
  timer_2 = timer_1;
  timer_3 = timer_2;
  autoGyroBoot();
  delay(3000);
  
}
void loop(){
  unsigned long now = millis();

 if(now-timer_1 > delay_1){
  gyroRead();
  timer_1 = now;
 }
 if(now - timer_2 > delay_2){
  accelRead();
  timer_2 = now;
 }
 if(now - timer_3 > delay_3){
  motionRead();
  timer_3 = now;
 }
}
void autoGyroBoot(){
  CurieIMU.begin();
  if (autoCalibrate == 1){
    Serial.println("Internal Sensors will offset Before Calibration....");
    Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS));
    Serial.print("\t");
    Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS));
    Serial.print("\t");
    Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS));
    Serial.print("\t");
    Serial.print(CurieIMU.getGyroOffset(X_AXIS));
    Serial.print("\t");
    Serial.print(CurieIMU.getGyroOffset(Y_AXIS));
    Serial.print("\t");
    Serial.print(CurieIMU.getGyroOffset(Z_AXIS));
    Serial.print("\t");
  }
  Serial.print("Starting Calibration of Gyro!!");
  CurieIMU.autoCalibrateGyroOffset();
  Serial.println("Done!");
  Serial.print("Starting Calibration of Acceleration!!");
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);\
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
  Serial.println("Done!");
  
  Serial.println("Internal Sensors will offset After Calibration....");
  Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS));
  Serial.print("\t");
  Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS));
  Serial.print("\t");
  Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS));
  Serial.print("\t");
  Serial.print(CurieIMU.getGyroOffset(X_AXIS));
  Serial.print("\t");
  Serial.print(CurieIMU.getGyroOffset(Y_AXIS));
  Serial.print("\t");
  Serial.print(CurieIMU.getGyroOffset(Z_AXIS));
  Serial.print("\t");

  Serial.println("SETUP IS COMPLETE");
}
void manuelGyroBoot(){
      // To manually configure offset compensation values, use the following methods instead of the autoCalibrate...() methods below
     CurieIMU.setGyroOffset(X_AXIS, 220);
     CurieIMU.setGyroOffset(Y_AXIS, 76);
     CurieIMU.setGyroOffset(Z_AXIS, -85);
     CurieIMU.setAccelerometerOffset(X_AXIS, -76);
     CurieIMU.setAccelerometerOffset(Y_AXIS, -235);
     CurieIMU.setAccelerometerOffset(Z_AXIS, 168);
}
void gyroRead(){
  CurieIMU.readMotionSensor(ax,ay,az,gx,gy,gz);
  gyroScope.updateIMU(gx/divider,gy/divider,gz/divider,ax,ay,az);

  Serial.print("Gyro Read Gx: ");
  Serial.print(gx);
  Serial.print("\t");
  Serial.print("Gyro Read Gy: ");
  Serial.print(gy);
  Serial.print("\t");
  Serial.print("Gyro Read Gz: ");
  Serial.print(gz);
  Serial.println("\t"); 
}
void accelRead(){
  CurieIMU.readMotionSensor(ax,ay,az,gx,gy,gz);
  Serial.print("Acclerometer Read Ax: ");
  Serial.print(ax);
  Serial.print("\t");
  Serial.print("Acclerometer Read Ay: ");
  Serial.print(ay);
  Serial.print("\t");
  Serial.print("Acclerometer Read Az: ");
  Serial.print(az);
  Serial.println("\t"); 
}
void motionRead(){ 
  yaw = gyroScope.getYaw();
  roll = gyroScope.getRoll();
  pitch = gyroScope.getPitch();
  Serial.print("Yaw:  ");
  Serial.print(yaw);
  Serial.print('\t');
  Serial.print("Pitch:  ");
  Serial.print(pitch);
  Serial.print('\t');
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.println('\t');

}
