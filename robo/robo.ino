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

bool fullstep[4][4] = {
  {1,1,0,0},
  {1,0,0,1},
  {0,0,1,1},
  {0,1,1,0}
};

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

int i = 0;

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
  
}

void step(bool forward, bool halfstep, int frequency) {
  int delta = halfstep ? 1 : i % 2 == 1 ? 1 : 2;
  if (!forward) delta *= -1;
  int i = (i + delta) % 8;
  digitalWrite(transmissionDirection, 0);
  digitalWrite(d3, halfstep[i][0]);
  digitalWrite(d2, halfstep[i][1]);
  digitalWrite(d1, halfstep[i][2]);
  digitalWrite(d0, halfstep[i][3]);
  delay(1000/frequency);
}
