int transmissionDirection = 0;

int m0 = 1;
int m1 = 2;
int m2 = 3;
// m0 | m1 | m2 | Motorbits
// 0  | 0  | 0  | no motor moves, but all motors will receive current, which results in heating up the motors very quicly
// 0  | 0  | 1  | wrist right
// 0  | 1  | 0  | upper arm
// 0  | 1  | 1  | gripper
// 1  | 0  | 0  | shoulder rotate
// 1  | 0  | 1  | wrist left
// 1  | 1  | 0  | under arm
// 1  | 1  | 1  | no motor moves, an no motor will receive current, this is best for idle.
int d0 = 4;
int d1 = 5;
int d2 = 6;
int d3 = 7;

bool halfstep[8][4] = {
  {1,1,0,0},
  {1,1,0,1},
  {1,0,0,1},
  {1,0,1,1},
  {0,0,1,1},
  {0,1,1,1},
  {0,1,1,0},
  {1,1,1,0}
};

// save i of each motor
int im[] = {
  0,
  0,
  0,
  0,
  0,
  0
};

void setup() {
  pinMode(transmissionDirection, OUTPUT);
  pinMode(m0, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
}

void loop() {
  step(1, true, true, 100);
  step(5, true, true, 100);
}

// Moves the given motor one step. 
// The direction, if it should be a halfstep and the frequency can be given.
//
// The motor is addressed as follows:
// # | binary | axis
// 0 | 0b000  | no motor moves, but all motors will receive current, which results in heating up the motors very quicly, NOT RECOMMENDED!
// 1 | 0b001  | wrist right
// 2 | 0b010  | upper arm
// 3 | 0b011  | gripper
// 4 | 0b100  | shoulder rotate
// 5 | 0b101  | wrist left
// 6 | 0b110  | under arm
// 7 | 0b111  | no motor moves, an no motor will receive current, this is best for idle.
// 
// If forward is true, the motor will rotate forward.
//
// If halfstep is false, the motor tries to make a fullstep (equal to 2 halfsteps). 
// But if the motor is still in a half step which does not match a fullstep, it will only make a halfstep, 
// the position will then match a full step.
//
// The frequency determines how many steps the robot performs per minute.
void step(int motor, bool isForward, bool isHalfstep, int frequency) {
  int i = im[motor - 1];
  
  int delta = isHalfstep ? 1 : i % 2 == 1 ? 1 : 2;
  if (!isForward) { 
    delta *= -1; 
  }
  i = (i + delta) % 8;
  
  digitalWrite(transmissionDirection, 0);
  
  digitalWrite(m0, (motor & ( 1 << 2 )) >> 2);
  digitalWrite(m1, (motor & ( 1 << 1 )) >> 1);
  digitalWrite(m2, (motor & ( 1 << 0 )) >> 0);
  
  digitalWrite(d3, halfstep[i][0]);
  digitalWrite(d2, halfstep[i][1]);
  digitalWrite(d1, halfstep[i][2]);
  digitalWrite(d0, halfstep[i][3]);

  // write back i
  im[motor - 1] = i;
  delay(1000/frequency);
}
