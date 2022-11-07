String letters[] = {
".-", 
"-...",
"-.-.",
"-..",
".",
"..-.",
"--.",
"....",
"..",
".---",
"-.-",
".-..",
"--",
"-.",
"---",
".--.",
"--.-",
".-.",
"...",
"-",
"..-",
"...-",
".--",
"-..-",
"-.--",
"--.."
};

String numbers[] = {
"-----",
".----",
"..---",
"...--",
"....-",
".....",
"-....",
"--...",
"---..",
"----."};

int buzzerPin = 5;
int ledPin = 12;

int freq = 1000;
int pause = 200;
int tPoint = 50;
int tLine = 200;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);


  Serial.println("Morse: ");
}

void loop() {
  
  //Ascolto dell'input
  if (Serial.available()) {
    char ch = Serial.read();
    
  //Nel caso i caratteri inseriti siano spazi o a capi fai una pausa 
    if ((ch == '\n') || (ch == '\r')) {
      delay(pause * 7);
    } 
    else if (ch == ' ') {
      delay(pause * 7);
    } 
    else {
      doMorse(int(ch));  
    }
  }
}

//Passa dal ASCII al morse
void doMorse(int i) {
  String code = "";
  //Se la lettere inserita si trova nel delta di numeri in cui è decodificato l'alfabeto in ASCII, togli a n 97 (97 = a) così facendo ottengo posizione della lettera secondo l'array Letters
  
  if ((i >= 97) && (i <= 122)) {
    code = letters[i-97];
  } 
  else if ((i >= 48) && (i <= 57)) {
    code = numbers[i-48];
  } 
  else {
    code = "?"; 
  }
  Serial.println(code);
  if (code != "?") {
  
     for (int n = 0; n < code.length(); n++){
       char t = code.charAt(n); 
     //Definizione dei millisecondi per punto e linea
       if (t == '.') {
         digitalWrite(ledPin, HIGH);
         tone(buzzerPin, freq, tPoint);
         delay(tPoint);
         digitalWrite(ledPin, LOW);
         delay(pause);
       } else if (t == '-') {
        digitalWrite(ledPin, HIGH);
         tone(buzzerPin, freq, tLine);
         delay(tLine);
         digitalWrite(ledPin, LOW);
         delay(pause);
       } 
     }
     delay(pause);
  }
}
