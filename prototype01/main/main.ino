int DIG[4]={10,11,12,13};  //pins relating to each digit
int LOOPTIME = 12000;  // 1 minute (in 5ms chunks)

void setup()
{
  // set all pins as outputs and turn off
 DDRD=0xff; // all pins 0-7 OUTPUTs
 DDRB=0xff; // all pins 8-13 OUTPUTs even though we only use pins 8-12
 PORTD=0x00; // make pins 0-7 LOWs
 PORTB=0x00; // make pins 8-13 LOWs
}

void loop()
{
  removeDecimal(); // turn off decimal place once as it will never need to be on.
  int dig1value;
  int dig2value;
  int dig3value;
  int dig4value;
  int i;
  int ticker = -5;

  for (i=0;i<LOOPTIME;i++)
  {
    ticker = ticker + 5; // test ticker += 5;
    dig1value = digitOneScript(ticker);
    dig2value = digitTwoScript(ticker);
    dig3value = digitThreeScript(ticker);
    dig4value = digitFourScript(ticker);
    
    activateDigit(0);
    displayDigit(dig1value);
    delay(1);
    activateDigit(1);
    displayDigit(dig2value);
    delay(1);
    activateDigit(2);
    displayDigit(dig3value);
    delay(1);
    activateDigit(3);
    displayDigit(dig4value);
    delay(1);
  }
  delay(1);

}

void activateDigit(int digit) {
  int i;
  for (i=0;i<4;i++)
  {
    if (i == digit) {
      digitalWrite(DIG[i], HIGH);
    } else {
      digitalWrite(DIG[i], LOW);
    }
  }
}

int digitOneScript(int tick) {
  int digNum = 0;
  // Script for 1st digit. This will show nothing for 50ms, then 1 for 200ms, then 2 for 200ms etc...
  int startDelay = 50; // start counting 50ms after loop begins
  int countSpeed = 800; // change number every 200ms
  // normalize tick to speed
  // int normalTick = tick - startDelay
  if (tick < startDelay) {
    return 0;
  } else {
    int result = (tick - startDelay)/countSpeed;
    if (result == 0) {
      return 10;
    } else if (result < 10) {
      // digitalWrite(DIG[digNum],HIGH);
      return result;
    } else {
      return result % 10;
    }
  }
}

int digitTwoScript(int tick) {
  int startDelay = 2000;
  int countSpeed = 2000;
  if (tick < startDelay) {
    return 0;
  } else {
    int result = (tick - startDelay)/countSpeed;
    if (result < 10) {
      return result;
    } else {
      return result % 10;
    }
  }
}

int digitThreeScript(int tick) {
  int startDelay = 5000;
  int countSpeed = 4000;
  if (tick < startDelay) {
    return 0;
  } else {
    int result = (tick - startDelay)/countSpeed;
    if (result < 10) {
      return result;
    } else {
      return result % 10;
    }
  }
}

int digitFourScript(int tick) {
  int startDelay = 0;
  int countSpeed = 1000;
  if (tick < startDelay) {
    return 0;
  } else {
    int result = (tick - startDelay)/countSpeed;
    if (result < 10) {
      return result;
    } else {
      return result % 10;
    }
  }
}


void turnOff(int digit) {
  digitalWrite(DIG[digit],LOW);
}

void removeDecimal() {
  digitalWrite(9,HIGH);
}

void displayDigit(int num)
{
   switch(num)
   {
     case 0:
      PORTD=B11111111;
      digitalWrite(8,HIGH);
     break;
     case 1:
      PORTD=B11100111; // only pins 2 and 3 are on
      digitalWrite(8,HIGH); // turn off pin 8
     break;
     case 2:
      PORTD=B10010011; // only pins 2,3,5 and 6 on
      digitalWrite(8,LOW); // segment g on
     break;
     case 3:
      PORTD=B11000011; // only pins 2,3,4 and 5 on
      digitalWrite(8,LOW); // segment g on
     break;
     case 4:
      PORTD=B01100111; // only pins 3,4 and 7 on
      digitalWrite(8,LOW); // segment g on
     break;
     case 5:
      PORTD=B01001011; //B10110100; // only pins 2,4,5 and 7 on
      digitalWrite(8,LOW); // segment g on
     break;
     case 6:
      PORTD=B00001011; //B11110100; // only pins 2,4,5,6 and 7 on
      digitalWrite(8,LOW); // segment g on
     break;
     case 7:
      PORTD=B11100011; // only pins 2,3 and 4 on
      digitalWrite(8,HIGH); // segment g off
     break;
     case 8:
      PORTD=B00000011; // pins 2-7 on
      digitalWrite(8,LOW); // turn on pin 8
     break;
     case 9:
      PORTD=B01000011; // only pins 2,3, 4 and 5 on
      digitalWrite(8,LOW); // segment g on
     break;
     case 10: // blank case
      PORTD=B11111111;
      digitalWrite(8,HIGH);
     break;
   }
}
