int ip = A0;

int val = 1;

int led = 13;

void setup() {

  Serial.begin(9600);

  pinMode (ip, INPUT);

  pinMode (led, OUTPUT);

}

void loop() {

  val = analogRead(ip);

  Serial.println(val);

  if(val >0)

  {

    digitalWrite(led, HIGH);

  }

  else

  {

    digitalWrite(led, LOW);

  }

  
}
