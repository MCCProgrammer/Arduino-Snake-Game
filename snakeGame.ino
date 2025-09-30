#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3

const byte rows[] = {ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8};
const byte col[]  = {COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8};

struct Point { byte x; byte y; };
Point snake[64];
int snakeLength = 3;
Point food;

// Botões
#define BTN_UP    A5
#define BTN_LEFT  A4

// 0=RIGHT, 1=DOWN, 2=LEFT, 3=UP
byte direction = 3; // começa subindo

unsigned long lastMove = 0;
unsigned long moveDelay = 400; // tempo entre movimentos
unsigned long lastButtonPress = 0;
unsigned long debounceDelay = 150;

void setup() {
  for (byte i = 2; i <= 13; i++) pinMode(i, OUTPUT);
  pinMode(A0, OUTPUT); pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT); pinMode(A3, OUTPUT);

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);

  // cobra inicia no meio
  snake[0] = {3, 4};
  snake[1] = {2, 4};
  snake[2] = {1, 4};

  spawnFood();
}

void loop() {
  // botões
  if (digitalRead(BTN_UP) == LOW && millis() - lastButtonPress > debounceDelay) {
    changeDirection(3); // UP
    lastButtonPress = millis();
  }
  if (digitalRead(BTN_LEFT) == LOW && millis() - lastButtonPress > debounceDelay) {
    changeDirection(2); // LEFT
    lastButtonPress = millis();
  }

  // movimento automático
  if (millis() - lastMove > moveDelay) {
    moveSnake(direction);
    lastMove = millis();
  }

  drawSnake();
}

// muda direção ou inverte cobra se direção oposta
void changeDirection(byte newDir) {
  // detecta direção oposta
  if ((direction == 0 && newDir == 2) || (direction == 2 && newDir == 0) ||
      (direction == 1 && newDir == 3) || (direction == 3 && newDir == 1)) {
    // inverter a cobra: cauda vira cabeça
    for (int i = 0; i < snakeLength / 2; i++) {
      Point temp = snake[i];
      snake[i] = snake[snakeLength - 1 - i];
      snake[snakeLength - 1 - i] = temp;
    }
  }
  direction = newDir;
}

// move a cobra em 1 passo
void moveSnake(byte dir) {
  Point newHead = snake[0];

  if (dir == 0) newHead.x = (newHead.x + 1) % 8;       // RIGHT
  if (dir == 2) newHead.x = (newHead.x + 7) % 8;       // LEFT (wrap-around)
  if (dir == 1) newHead.y = (newHead.y + 1) % 8;       // DOWN
  if (dir == 3) newHead.y = (newHead.y + 7) % 8;       // UP (wrap-around)

  // colisão com corpo
  for (int i = 0; i < snakeLength; i++) {
    if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
      resetGame();
      return;
    }
  }

  // shift corpo
  for (int i = snakeLength; i > 0; i--) {
    snake[i] = snake[i - 1];
  }
  snake[0] = newHead;

  // comida
  if (newHead.x == food.x && newHead.y == food.y) {
    snakeLength++;
    spawnFood();
  }
}

void drawSnake() {
  byte buffer[8] = {0};
  for (int i = 0; i < snakeLength; i++) {
    buffer[snake[i].y] |= (1 << snake[i].x);
  }
  buffer[food.y] |= (1 << food.x);

  drawScreen(buffer);
}

void drawScreen(byte buffer2[]) {
  for (byte i = 0; i < 8; i++) {
    digitalWrite(rows[i], HIGH);
    for (byte a = 0; a < 8; a++) {
      digitalWrite(col[a], ((~buffer2[i]) >> a) & 0x01);
      delayMicroseconds(100);
      digitalWrite(col[a], 1);
    }
    digitalWrite(rows[i], LOW);
  }
}

void spawnFood() {
  food.x = random(0, 8);
  food.y = random(0, 8);
}

void resetGame() {
  snakeLength = 3;
  snake[0] = {3, 4};
  snake[1] = {2, 4};
  snake[2] = {1, 4};
  direction = 3; // começa subindo
  spawnFood();
}
