//Các chân của L298N
#define ENA 6
#define IN1 11
#define IN2 10
#define IN3 9
#define IN4 8
#define ENB 5

//Cảm biến siêu âm trước
#define TRIG_FRONT 7
#define ECHO_FRONT 4

//Cảm biến siêu âm phải
#define TRIG_RIGHT 13
#define ECHO_RIGHT 12

//Cảm biến siêu âm trái
#define TRIG_LEFT 3
#define ECHO_LEFT 2

const int MinDistance = 15; //Khoảng cách tối thiểu để bám tường 15cm
const int Turn = 20; //Ngưỡng để phát hiện ngã rẽ
const int Speed = 255; //Tốc độ bánh xe
const int K = 5; //Hằng số K để điều chỉnh tốc độ bánh

bool Turning = false; //Kiểm tra xem robot có đang rẽ hay không
unsigned long Last = 0; //Thời gian chạy của vòng loop trước
const unsigned long Delay = 30; //Thời gian delay 30ms giữa các vòng lặp
unsigned long TurnStart = 0; //Thời gian robot bắt đầu rẽ
const unsigned long TurnDuration = 118; //Thời gian robot rẽ: 118ms

const int Exit = 40; //Ngưỡng để robot biết nó đã thoát khỏi mê cung
//Hàm đọc khoảng cách
int GetDis(int Trig, int Echo){
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  int time = pulseIn(Echo, HIGH);
  int distance = time / 2 / 29.412;
  return distance;
}

//Kiểm tra xem đã thoát mê cung hay chưa
bool isExit(int DisFront, int DisRight, int DisLeft){
  if(DisFront > Exit && DisRight > Exit && DisLeft > Exit) return true;
  return false;
}

// Hàm điều khiển động cơ
void Motor(int LeftSpeed, int RightSpeed, int leftDirection, int rightDirection) {
  digitalWrite(IN1, leftDirection);
  digitalWrite(IN2, !leftDirection);
  digitalWrite(IN3, rightDirection);
  digitalWrite(IN4, !rightDirection);
  analogWrite(ENA, LeftSpeed);
  analogWrite(ENB, RightSpeed);
}

// Rẽ trái
void Left() {
  Turning = true;
  TurnStart = millis();
  Motor(255, 255, LOW, HIGH);
}

// Rẽ phải
void Right() {
  Turning = true;
  TurnStart = millis();
  Motor(255, 255, HIGH, LOW);
}

// Dừng lại
void Stop() {
  Motor(0, 0, LOW, LOW);
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);

  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);

  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
}

void loop() {
  unsigned long CurrentTime = millis();

  if(CurrentTime - Last < Delay) return; //Giới hạn vòng lặp
  int DisFront = GetDis(TRIG_FRONT, ECHO_FRONT); //Lấy khoảng cách trước
  int DisLeft = GetDis(TRIG_LEFT, ECHO_LEFT); //Lấy khoảng cách trái
  int DisRight = GetDis(TRIG_RIGHT, ECHO_RIGHT); //lấy khoảng cách phải
  
  if(isExit(DisFront, DisRight, DisLeft)){
    Stop();
    return;
  }

  if(Turning){ //Nếu robot đang rẽ
    if(CurrentTime - TurnStart >= TurnDuration){ //Nếu đủ thời gian rẽ
      Stop();
      Turning = false;
    }
    return;
  }
  if(DisFront < MinDistance){ //Nếu phía trước có vật cản
    if(DisLeft > Turn) Left(); //Nếu trái có đường thì quay sang trái
    else Right(); //Nếu không thì quay sang phải
  }
  else{ //Nếu phía trước không có vật cản, sử dụng công thức tổng quát của điều khiển PID
    if(DisLeft > Turn) Left(); //Nếu có ngã rẽ phía bên trái thì rẽ
    else{ //Nếu không duy trì khoảng cách cố định với tường
      int Error = DisLeft - MinDistance; //Sai số giữa khoảng cách của xe với giá trị ban đầu
      int Adj = K * Error; //Giá trị để điều chỉnh xe

      //Tính tốc độ mỗi bánh 
      int LeftSpeed = Speed + Adj;
      int RightSpeed = Speed - Adj;

      //Giới hạn tốc độ
      LeftSpeed = constrain(LeftSpeed, 0, 255);
      RightSpeed = constrain(RightSpeed, 0, 255);

      Motor(LeftSpeed, RightSpeed, HIGH, HIGH);
    }
  }
    Last = CurrentTime;
}
