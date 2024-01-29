#include <math.h>

String incomingCommand = "";
long timeout = INFINITY;
bool flag;
int l = 10;
int w = 8;
bool table[10][8];
bool createArray = false;
int index = 0;

int initialX;
int initialY;

String actionMoves [200] ;

void update(int action);
void moveBall(String moves);
String randomAction();

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(timeout);
  Serial.print("Hello Arduino\n");
}

void loop() {
  if (Serial.available() > 0) {
    incomingCommand = Serial.readStringUntil('\n');
    if (incomingCommand.startsWith("c")) {
      int equalsPosition = incomingCommand.indexOf('c');
      String periodValue = incomingCommand.substring(equalsPosition + 1);
      if (periodValue == "r") {
        flag = true;
        // Serial.println("red");
      } else if (periodValue == "b") {
        flag = false;
        // Serial.println("blue");
      }
      //  Serial.print(flag);

    } else if (incomingCommand.startsWith("w")) {
      int equalsPosition = incomingCommand.indexOf('w');
      String value = incomingCommand.substring(equalsPosition + 1);
      // w = value.toInt();
      // Serial.println(w);
    } else if (incomingCommand.startsWith("l")) {
      int equalsPosition = incomingCommand.indexOf('l');
      String value = incomingCommand.substring(equalsPosition + 1);
      // l = value.toInt();
      // Serial.println(l);
    } else if (incomingCommand.startsWith("{")) {
      int startBrace = incomingCommand.indexOf('{');
      int endBrace = incomingCommand.indexOf('}');
      String moves = incomingCommand.substring(startBrace + 1, endBrace);
      // Serial.println(moves);
      moveBall(moves);
      findNextMove();

    }
    if ((w != 0) && (l != 0) && (createArray == false)) {
      createVisitedArray(l, w);
      initialX = l/2;
      initialY = w/2;
      // Serial.println(initialX);
      // Serial.println(initialY);
      createArray = true;
    }

    
  }
}
void moveBall(String moves) {
  //Serial.println(index);
  String temp = "";
  String revTemp = "";
  String s = "";
  int tempx , tempy;
  int numMoves = moves.length();
  //Serial.println(moves);
  //Serial.println(numMoves);
  if (numMoves == 0){
    // فقط یه حرکتی بکن مهم نیست چیه مثلا بالا یا پایین
    if(flag == false){// blue
      temp += String(initialX);
      temp += String(initialY);
      temp += String(initialX+=1);
      temp += String(initialY);
      actionMoves[index] = temp;
      index++;
      tempx = initialX;
      revTemp += String(tempx);
      revTemp += String(initialY);
      revTemp += String(tempx-=1);
      revTemp += String(initialY);
      actionMoves[index] = revTemp;
      index++;
      // Serial.print("{0}\n");
      // findNextMove();
    }else{//red
      temp += String(initialX);
      temp += String(initialY);
      temp += String(initialX-=1);
      temp += String(initialY);
      actionMoves[index] = temp;
      index++;
      tempx = initialX;
      tempy = initialY;
      revTemp += String(tempx);
      revTemp += String(initialY);
      revTemp += String(tempx+=1);
      revTemp += String(tempy);
      actionMoves[index] = revTemp;
      index++;
      // Serial.print("{4}\n");
      // findNextMove();

    }
  }
  for (int i = 0; i < numMoves; ++i) {
    temp = "";
    revTemp = "";
    char move = moves.charAt(i);
    int nextAction = 0;
    switch (move) {
      case '0': //MOVE_UP
        temp += String(initialX);
        temp += String(initialY);
        temp += String(initialX+=1);
        temp += String(initialY);
        actionMoves[index] = temp;
        index++;
        tempx = initialX;
        revTemp += String(tempx);
        revTemp += String(initialY);
        revTemp += String(tempx-=1);
        revTemp += String(initialY);
        actionMoves[index] = revTemp;
        index++;

        table[initialX][initialY] = true;
        // findNextMove();
        break;
        
      case '1': //MOVE_UP_RIGHT
        temp += String(initialX);
        temp += String(initialY);
        temp += String(initialX+=1);
        temp += String(initialY+=1);
        actionMoves[index] = temp;
        index++;
        tempx = initialX;
        tempy = initialY;
        revTemp += String(tempx);
        revTemp += String(initialY);
        revTemp += String(tempx-=1);
        revTemp += String(tempy-=1);
        actionMoves[index] = revTemp;
        index++;
        
        table[initialX][initialY] = true;
        // findNextMove();
        break;
        
      case '2': //MOVE_RIGHT
        temp += String(initialX);
        temp += String(initialY);
        temp += String(initialX);
        temp += String(initialY+=1);
        actionMoves[index] = temp;
        index++;
        tempy = initialY;
        tempx = initialX;
        revTemp += String(tempx);
        revTemp += String(initialY);
        revTemp += String(tempx);
        revTemp += String(tempy-=1);
        actionMoves[index] = revTemp;
        index++;
        
        table[initialX][initialY] = true;
        // findNextMove();
        break;
      case '3': //MOVE_DOWN_RIGHT
        temp += String(initialX);
        temp += String(initialY);
        temp += String(initialX-=1);
        temp += String(initialY+=1);
        actionMoves[index] = temp;
        index++;
        tempx = initialX;
        tempy = initialY;
        revTemp += String(tempx);
        revTemp += String(initialY);
        revTemp += String(tempx+=1);
        revTemp += String(tempy-=1);
        actionMoves[index] = revTemp;
        index++;
        
        table[initialX][initialY] = true;
        // findNextMove();
        break;
      case '4': //MOVE_DOWN
        temp += String(initialX);
        temp += String(initialY);
        temp += String(initialX-=1);
        temp += String(initialY);
        actionMoves[index] = temp;
        index++;
        tempx = initialX;
        tempy = initialY;
        revTemp += String(tempx);
        revTemp += String(initialY);
        revTemp += String(tempx+=1);
        revTemp += String(tempy);
        actionMoves[index] = revTemp;
        index++;
        
        table[initialX][initialY] = true;
        // findNextMove();
        break;
      case '5': //MOVE_DOWN_LEFT
        temp += String(initialX);
        temp += String(initialY);
        temp += String(initialX-=1);
        temp += String(initialY-=1);
        actionMoves[index] = temp;
        index++;
        tempx = initialX;
        tempy = initialY;
        revTemp += String(tempx);
        revTemp += String(initialY);
        revTemp += String(tempx+=1);
        revTemp += String(tempy+=1);
        actionMoves[index] = revTemp;
        index++;
        
        table[initialX][initialY] = true;
        // findNextMove();     
        break;
      case '6': //MOVE_LEFT
        temp += String(initialX);
        temp += String(initialY);
        temp += String(initialX);
        temp += String(initialY-=1);
        actionMoves[index] = temp;
        index++;
        tempx = initialX;
        tempy = initialY;
        revTemp += String(tempx);
        revTemp += String(initialY);
        revTemp += String(tempx);
        revTemp += String(tempy+=1);
        actionMoves[index] = revTemp;
        index++;
        
        table[initialX][initialY] = true;
        // findNextMove();      
        break;
      case '7': //MOVE_UP_LEFT
        temp += String(initialX);
        temp += String(initialY);
        temp += String(initialX+=1);
        temp += String(initialY-=1);
        actionMoves[index] = temp;
        index++;
        tempx = initialX;
        tempy = initialY;
        revTemp += String(tempx);
        revTemp += String(initialY);
        revTemp += String(tempx-=1);
        revTemp += String(tempy+=1);
        actionMoves[index] = revTemp;
        index++;
        
        table[initialX][initialY] = true;
        // findNextMove();
        break;
      default:
        break;
    }
  }
  
}
String randomAction(){
  String posibleActions[8];
  String up = "";
  up += String(initialX);
  up += String(initialY);
  up += String(initialX+=1);
  up += String(initialY);
  initialX-=1;
  posibleActions[0] = up;


  String topRight = "";
  topRight += String(initialX);
  topRight += String(initialY);
  topRight += String(initialX+=1);
  topRight += String(initialY+=1);
  initialX-=1;
  initialY-=1;
  posibleActions[1] = topRight;

  String right = "";
  right += String(initialX);
  right += String(initialY);
  right += String(initialX);
  right += String(initialY+=1);
  initialY-=1;
  posibleActions[2] = right;


  String downRight = "";
  downRight += String(initialX);
  downRight += String(initialY);
  downRight += String(initialX-=1);
  downRight += String(initialY+=1);
  initialX+=1;
  initialY-=1;
  posibleActions[3] = downRight;


  String down = "";
  down += String(initialX);
  down += String(initialY);
  down += String(initialX-=1);
  down += String(initialY);
  initialX+=1;
  posibleActions[4] = down;


  String downLeft = "";
  downLeft += String(initialX);
  downLeft += String(initialY);
  downLeft += String(initialX-=1);
  downLeft += String(initialY-=1);
  initialX+=1;
  initialY+=1;
  posibleActions[5] = downLeft;


  String left = "";
  left += String(initialX);
  left += String(initialY);
  left += String(initialX);
  left += String(initialY-=1);
  initialY+=1;
  posibleActions[6] = left;


  String upLeft = "";
  upLeft += String(initialX);
  upLeft += String(initialY);
  upLeft += String(initialX+=1);
  upLeft += String(initialY-=1);
  initialX-=1;
  initialY+=1;
  posibleActions[7] = upLeft;

  for(int i = 0; i < index; i++){
    if(up == actionMoves[i]){
      posibleActions[0] = -1;
    }
    if(topRight == actionMoves[i]){
      posibleActions[1] = -1;
    }
    if(right == actionMoves[i]){
      posibleActions[2] = -1;
    }
    if(downRight == actionMoves[i]){
      posibleActions[3] = -1;
    }
    if(down == actionMoves[i]){
      posibleActions[4] = -1;
    }
    if(downLeft == actionMoves[i]){
      posibleActions[5] = -1;
    }
    if(left == actionMoves[i]){
      posibleActions[6] = -1;
    }
    if(upLeft == actionMoves[i]){
      posibleActions[7] = -1;
    }
  }

  String allMoves = "";
  int random ;
  bool reward = true;
  while(reward == true){
    reward = false;
    while(posibleActions[random] == -1){
      random = (rand() % 8);
    }
    allMoves += String(random);
    // Serial.println("allMoves:");
    // Serial.println(allMoves);

    switch (random) {
      case '0':
        initialX+=1;
        if(table[initialX][initialY] == true){
          reward = true;
        }
        initialX-=1;
        break;
      case '1':
        initialX+=1;
        initialY+=1;  
        if(table[initialX][initialY] == true){
          reward = true;
        }
        initialX-=1; 
        initialY-=1;  
        break;
      case '2':
        initialY+=1; 
        if(table[initialX][initialY] == true){
          reward = true;
        }
        initialY-=1;
        break;
      case '3':
        initialX-=1;  
        initialY+=1; 
        if(table[initialX][initialY] == true){
          reward = true;
        }
        initialX+=1; 
        initialY-=1;
        break;
      case '4':
        initialX-=1; 
        if(table[initialX][initialY] == true){
          reward = true;
        }
        initialX+=1; 
        break;
      case '5':
        initialX-=1; 
        initialY-=1; 
        if(table[initialX][initialY] == true){
          reward = true;
        }
        initialX+=1; 
        initialY+=1;
        break;
      case '6':
        initialY-=1; 
        if(table[initialX][initialY] == true){
          reward = true;
        }
        initialY+=1;
        break;
      case '7':
        initialX+=1;
        initialY-=1;  
        if(table[initialX][initialY] == true){
          reward = true;
        }
        initialX-=1; 
        initialY+=1;
        break;
      defult:
        break;
    }
  }
  return allMoves;
}

void update(int action){
  switch (action) {
      case '0':
        initialX+=1;
        table[initialX][initialY] = true;
        break;
      case '1':
        initialX+=1;
        initialY+=1;  
        table[initialX][initialY] = true;    
        break;
      case '2':
        initialY+=1; 
        table[initialX][initialY] = true;
        break;
      case '3':
        initialX-=1;  
        initialY+=1; 
        table[initialX][initialY] = true;
        break;
      case '4':
        initialX-=1; 
        table[initialX][initialY] = true;
        break;
      case '5':
        initialX-=1; 
        initialY-=1; 
        table[initialX][initialY] = true;
        break;
      case '6':
        initialY-=1; 
        table[initialX][initialY] = true;
        break;
      case '7':
        initialX+=1;
        initialY-=1;  
        table[initialX][initialY] = true;
        break;
      defult:
        break;
    }
}

void createVisitedArray(int l, int w) {
  for (int i = 0; i < l + 1; i++) {
    for (int j = 0; j < w + 1; j++) {
      if (j == 0 || j == w || i == l / 2 || (i == 0 && j != w / 2)
       || (i == l && j != w / 2)) {
        table[i][j] = true;
      } else {
      table[i][j] = false;
      }
       //Serial.print(table[i][j] ? "1\t" : "0\t");
    }
     //Serial.println();
  }
  // Serial.println("the arr created!");
}
void printTable(int l, int w) {
  for (int i = 0; i < l + 1; i++) {
    for (int j = 0; j < w + 1; j++) {
       Serial.print(table[i][j] ? "1\t" : "0\t");
    }
     Serial.println();
  }
}
void findNextMove(){
  String nextAction = randomAction();
  String s = "{" + nextAction + "}"+"\n";
  int startBrace = s.indexOf('{');
  int endBrace = s.indexOf('}');
  String moves = s.substring(startBrace + 1, endBrace);
  int numMoves = moves.length();

  for (int i = 0; i < numMoves; ++i){
    char move = moves.charAt(i);
    int moveInt = move - '0';
    update(moveInt);
  }
  // Serial.println("******");
  Serial.println(s);
  // printTable(l,w);
}

