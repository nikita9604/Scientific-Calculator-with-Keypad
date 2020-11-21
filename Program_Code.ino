// Scientific Calculator using Arduino Uno code written by Nikita Rath

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <math.h>

LiquidCrystal lcd(13, 12, A2, A3, A4, A5);
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {7, 6, 5, 4};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String show_val = "";
int prev_val = 0;
bool status = false;
char oper_vector[5] = {'+','-','*','/','%'};

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  operation_information();
  lcd.print("Sci-Calculator");
  delay(1000);
  lcd.clear();
}

//Option No. for Operations
void operation_information()
{
  Serial.println("Options :");
  Serial.println("	 1. Addition");
  Serial.println("	 2. Subtraction");
  Serial.println("	 3. Multiply");
  Serial.println("	 4. Division");
  Serial.println("	 5. Sin");
  Serial.println("	 6. Cos");
  Serial.println("	 7. Sqrt of number");
  Serial.println("	 8. Log10");
  Serial.println("	 9. Exp");
  Serial.println("	10. Square of number");
  Serial.println("	11. BODMAS Operation");
  Serial.println("  ");
}

void loop()
{
  status = false;
  int enter_val = getNumber();
  Serial.print("Option chosen :");
  Serial.print(enter_val);
  Serial.println();
  lcd.clear();
  lcd.print("Option chosen :");
  lcd.setCursor(0,2);
  lcd.print(enter_val);
  delay(2000);
  //Call BODMAS function
  if(enter_val == 11){
    BODMAS();
  }
  else{
    show_val = "";
    prev_val = process(enter_val,status);
    
    while(1){
      status = true;
      //New computation
      Serial.println("Press D to start new computation.");
      show_val = "";
      int enter_val1 = getNumber();
      if(enter_val1==0){
        Serial.println("Starting new computation.");
        break;
      }
      else{
        Serial.print("Option chosen :");
        Serial.println(enter_val);
        lcd.clear();
        show_val = "";
        String myString = String(prev_val);
        getshow_val(myString);
        lcd.print(show_val);
        prev_val = process(enter_val1,status);
      }
   	}
  }
  delay(3000);
  lcd.clear();
  show_val = "";
}

//Display Operation
String operation(int num1)
{
  String ret_val = "";
  while(1){
    if (num1==1){
      ret_val = "+";
    }
    else if (num1==2){
      ret_val = "-";
    }
    else if (num1==3){
      ret_val = "*";
    }
    else if (num1==4){
      ret_val = "/";
    }
    else if (num1==5){
      ret_val = "sin :";
    }
    else if (num1==6){
      ret_val = "cos :";
    }
    else if (num1==7){
      ret_val = "Sqrt :";
    }
    else if (num1==8){
      ret_val = "Log10 :";
    }
    else if (num1==9){
      ret_val = "exp :";
    }
    else if(num1==10){
      ret_val = "Square :";
    }
    break;
  }
  getshow_val(ret_val);
  return ret_val;
}

//Main computation (Option 1 to 10)
float process(int num,bool status){
  float val1 = prev_val;
  if(num==1){
    if(status==true){
    }
    else{
    	lcd.clear();
    	Serial.println("Enter the first number.");
    	val1 = (float)getNumber();
    	Serial.println(val1);
    }
    String oper = operation(num);
    lcd.clear();
    lcd.print(show_val);
  	Serial.println(oper);
  	Serial.println("Enter second number.");
  	float val2 = (float)getNumber();
 	Serial.println(val2);
  	lcd.clear();
  	lcd.print(show_val);
    lcd.setCursor(0,2);
    //Addition
    float result = val1 + val2;
    lcd.print(result);
    Serial.println("Result :");
    Serial.println(result);
    return result;
  }
  else if(num==2){
    if(status==true){
    }
    else{
       lcd.clear();
       Serial.println("Enter the first number.");
       val1 = (float)getNumber();
  	   Serial.println(val1);
    }
    String oper = operation(num);
  	lcd.clear();
  	lcd.print(show_val);
  	Serial.println(oper);
  	Serial.println("Enter second number.");
  	float val2 = (float)getNumber();
  	Serial.println(val2);
  	lcd.clear();
  	lcd.print(show_val);
    lcd.setCursor(0,2);
    //Subtraction
    float result = val1 - val2;
    lcd.print(result);
    Serial.println("Result :");
    Serial.println(result);
    return result;
  }
  else if(num==3){
    if(status==true){
    }
    else{
      lcd.clear();
      Serial.println("Enter the first number.");
      val1 = (float)getNumber();
  	  Serial.println(val1);
    }
    String oper = operation(num);
  	lcd.clear();
  	lcd.print(show_val);
  	Serial.println(oper);
  	Serial.println("Enter second number.");
  	float val2 = (float)getNumber();
  	Serial.println(val2);
  	lcd.clear();
  	lcd.print(show_val);
    lcd.setCursor(0,2);
    //Multiplication
    float result = val1 * val2;
    lcd.print(result);
    Serial.println("Result :");
    Serial.println(result);
    return result;
  }
   else if(num==4){
    if(status==true){
    }
    else{
      lcd.clear();
      Serial.println("Enter the first number.");
      val1 = getNumber();
  	  Serial.println(val1);
    }
    String oper = operation(num);
  	lcd.clear();
  	lcd.print(show_val);
  	Serial.println(oper);
  	Serial.println("Enter second number.");
  	int val2 = getNumber();
  	Serial.println(val2);
  	lcd.clear();
  	lcd.print(show_val);
    lcd.setCursor(0,2);
    
//Division
    float result = val1 / val2;
    lcd.print(result);
    Serial.println("Result :");
    Serial.println(result);
     return result;
  }
  else if(num==5){
    lcd.clear();
    show_val = "";
    String oper = operation(num);
  	lcd.clear();
  	Serial.println(oper);
    if(status==true){
      String myString = String(val1);
      getshow_val(myString);
      lcd.print(show_val);
    }
    else{
      Serial.println("Enter the number.");
      val1 = (float)getNumber();
  	  Serial.println(val1);
    }
    lcd.setCursor(0,2);
   


 //Sine function
    float result = sin(val1);
    lcd.print(result);
    Serial.println("Result :");
    Serial.println(result);
    return result;
  }
   else if(num==6){
    lcd.clear();
    show_val = "";
    String oper = operation(num);
  	lcd.clear();
  	Serial.println(oper);
    if(status==true){
      String myString = String(val1);
      getshow_val(myString);
      lcd.print(show_val);
    }
    else{
      Serial.println("Enter the number.");
      val1 = (float)getNumber();
  	  Serial.println(val1);
    }
    lcd.setCursor(0,2);
   


 //Cosine function
    float result = cos(val1);
    lcd.print(result);
    Serial.println("Result :");
    Serial.println(result);
     return result;
  }
   else if(num==7){
    lcd.clear();
    show_val = ""; 
    String oper = operation(num);
  	lcd.clear();
  	Serial.println(oper);
    if(status==true){
      String myString = String(val1);
      getshow_val(myString);
      lcd.print(show_val);
    }
    else{
      Serial.println("Enter the number.");
      val1 = (float)getNumber();
  	  Serial.println(val1);
    }
    lcd.setCursor(0,2);
   


 //Square root of a number
    float result = sqrt(val1);
    lcd.print(result);
    Serial.println("Result :");
    Serial.println(result);
     return result;
  }
  else if(num==8){
    lcd.clear();
    show_val = ""; 
    String oper = operation(num);
  	lcd.clear();
  	Serial.println(oper);
    if(status==true){
      String myString = String(val1);
      getshow_val(myString);
      lcd.print(show_val);
    }
    else{
      Serial.println("Enter the number.");
      val1 = getNumber();
  	  Serial.println(val1);
    }
    lcd.setCursor(0,2);
    //log10(number)
    float result = log10((float)val1);
    lcd.print(result);
    Serial.println("Result :");
    Serial.println(result);
     return result;
  }
  else if(num==9){
    lcd.clear();
    show_val = ""; 
    String oper = operation(num);
  	lcd.clear();
  	Serial.println(oper);
    if(status==true){
      String myString = String(val1);
      getshow_val(myString);
      lcd.print(show_val);
    }
    else{
      Serial.println("Enter the number.");
      val1 = getNumber();
  	  Serial.println(val1);
    }
    lcd.setCursor(0,2);
    //e^number
    float result = exp((float)val1);
    lcd.print(result);
    Serial.println("Result :");
    Serial.println(result);
     return result;
  }
  else if(num==10){
    lcd.clear();
    show_val = ""; 
    String oper = operation(num);
  	lcd.clear();
  	Serial.println(oper);
    if(status==true){
      String myString = String(val1);
      getshow_val(myString);
      lcd.print(show_val);
    }
    else{
      Serial.println("Enter the number.");
      val1 = getNumber();
  	  Serial.println(val1);
    }
    lcd.setCursor(0,2);
    //Square of a number
    float result = square((float)val1);
    lcd.print(result);
    Serial.println("Result :");
    Serial.println(result);
     return result;
  }
}

//BODMAS Computation - Option 11
void BODMAS(){
  String input_takers[16];
  show_val = "";
  Serial.println("Start inserting input");
  int i = 0;
  while(1){
    char Key = keypad.getKey();
    Serial.println(Key);
    if (Key != NO_KEY){
      if(Key == 'B'){
        Serial.println("Stop taking input");
        break;
      }
      if(Key=='C'){
        String prev_show1 = show_val;
        int value = getNumber();
        Serial.print("Got the operation value");
        show_val = prev_show1;
        Serial.println(value);
        if(value == 1){
          //Add
          String myString1 = String(oper_vector[value-1]);
          getshow_val(myString1);
          lcd.clear();
          lcd.print(show_val);
          input_takers[i] = myString1;
          i++;
        }
        else if(value == 2){
          //Subtract
          String prev_show2 = show_val;
          String myString2 = String(oper_vector[value-1]);
          show_val = prev_show2;
          getshow_val(myString2);
          lcd.clear();
          lcd.print(show_val);
          input_takers[i] = myString2;
          i++;
        }
        else if(value == 3){
          //Multiply
          String prev_show3 = show_val;
          String myString3 = String(oper_vector[value-1]);
          show_val = prev_show3;
          getshow_val(myString3);
          lcd.clear();
          lcd.print(show_val);
          input_takers[i] = myString3;
          i++;
        }
        else if(value == 4){
          //Divide
          String prev_show4 = show_val;
          String myString4 = String(oper_vector[value-1]);
          show_val = prev_show4;
          getshow_val(myString4);
          lcd.clear();
          lcd.print(show_val);
          input_takers[i] = myString4;
          i++;
        }
        else if(value == 5){
          //Modulo
          String prev_show5 = show_val;
          String myString5 = String(oper_vector[value-1]);
          show_val = prev_show5;
          getshow_val(myString5);
          lcd.clear();
          lcd.print(show_val);
          input_takers[i] = myString5;
          i++;
        }
      }
      else{
        int value1 = getNumber();
        Serial.print("Got numeric value");
        Serial.println(value1);
        lcd.clear();
        lcd.print(show_val);
        String myString = String(value1);
        input_takers[i] = myString;
        i++;
      }
    }
  }
  int p = 0;
  while(p<=16){
    //Display Operands and Operations
    Serial.print(input_takers[p]);
    Serial.print(" ");
    p++;
  }
  //Computation
  while(i!=1){
    int j = 0;
    bool found1 = true;
    bool found2 = true;
    bool found3 = true;
    while(j<i && i>1){
      if(input_takers[j] == "/"){
        //Division
      	int val1 = input_takers[j-1].toInt();
        int val2 = input_takers[j+1].toInt();
        float res = val1 / val2;
        input_takers[j] = ".";
        input_takers[j+1] = ".";
        String myString = String(res);
        input_takers[j-1] = myString;
        found1 = false;
       	break;
      }
      j++;
    }
    j = 0;
    while(j<i && i>1 && found1 == true){
      if(input_takers[j] == "*"){
        //Multiplication
      	float val1 = input_takers[j-1].toFloat();
        float val2 = input_takers[j+1].toFloat();
        float res = val1 * val2;
        input_takers[j] = ".";
        input_takers[j+1] = ".";
        String myString = String(res);
        input_takers[j-1] = myString;
        found2 = false;
       	break;
      }
      j++;
    }
    j = 0;
    while(j<i && i>1 && found1==true && found2 == true){
      if(input_takers[j] == "-"){
        //Subtraction
      	float val1 = input_takers[j-1].toFloat();
        float val2 = input_takers[j+1].toFloat();
        float res = val1 - val2;
        input_takers[j] = ".";
        input_takers[j+1] = ".";
        String myString = String(res);
        input_takers[j-1] = myString;
        found3 = false;
       	break;
      }
      j++;
    }
    j = 0;
    while(j<i && i>1 && found1==true && found2==true && found3 == true){
      if(input_takers[j] == "+"){
        //Addition
      	float val1 = input_takers[j-1].toFloat();
        float val2 = input_takers[j+1].toFloat();
        float res = val1 + val2;
        input_takers[j] = ".";
        input_takers[j+1] = ".";
        String myString = String(res);
        input_takers[j-1] = myString;
       	break;
      }
      j++;
    }
    int d = 0;
    while(d<i-2){
      if(input_takers[d] == "."){
        String temp = input_takers[d];
        input_takers[d] = input_takers[d+2];
        input_takers[d+2] = temp;
      }
      d++;
    }
    i = i-2;
  }
  //Final result
  float result = input_takers[0].toFloat();
  lcd.setCursor(0,2);
  lcd.print(result);
  Serial.println(result);
  delay(3000);
}

void getshow_val(String str){
  show_val = show_val + str;
}

//Taking input
int getNumber()
{
  int second = 0;
  while(1)
  {
    char Key = keypad.getKey();
    if(Key >= '0' && Key <= '9')
    {
      second = second * 10 + (Key - '0');
      lcd.clear();
      String myString = String(Key);
      getshow_val(myString);
      lcd.print(show_val);
    }
    if(Key == 'D') {
      break;
    }
  }
  return second;
}