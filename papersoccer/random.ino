#include <math.h>

String incomingCommand = ""; 
long timeout = INFINITY;
bool flag ;
int l = 10;
int w = 8;
bool createArray = false;
String arr [8] ={"0","1", "2", "3", "4", "5", "6" ,"7"};


String nextMove();



void setup() {
  Serial.begin(115200); 
  Serial.setTimeout(timeout);
  Serial.println("Hello Arduino\n");
}

void loop() {
  if (Serial.available() > 0) {
    incomingCommand = Serial.readStringUntil('\n'); 
    if (incomingCommand.startsWith("c")) {
      int equalsPosition = incomingCommand.indexOf('c');
      String periodValue = incomingCommand.substring(equalsPosition + 1);
      if(periodValue == "r"){
        flag = true;
        //Serial.print("red");
      }
      else if(periodValue == "b"){
        flag = false;
        //Serial.print("blue");
      }
      //  Serial.print(flag);
    }else if (incomingCommand.endsWith("}")) {
      if(flag == true){
        Serial.println(nextMove());
        // nextMove();
        // Serial.println("{4}\n");
      }
      else if(flag == false){
        // nextMove();
        Serial.println(nextMove());
        // Serial.println("{0}\n");
      }
    }else if (incomingCommand.startsWith("w")) {
      int equalsPosition = incomingCommand.indexOf('w');
      String value = incomingCommand.substring(equalsPosition + 1);
      // w =  value.toInt();
      // Serial.println(w);
      // measureAndTestField(w, l);

    }else if (incomingCommand.startsWith("l")) {
      int equalsPosition = incomingCommand.indexOf('l');
      String value = incomingCommand.substring(equalsPosition + 1);
      // l = value.toInt();
      //Serial.println(l);
      //measureAndTestField(w, l);
    } 

    if((w != 0) && (l != 0) && (createArray == false)){
      createArray = true;
    }
  } 
    
}

String nextMove() {
  int random = (rand() % 8);
  String s = "{" + arr[random] + "}" + "\n";
  return s;
}

