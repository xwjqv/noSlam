int Sensorrechts=2;
int Sensorlinks=3;

int Motorrechts=4;
int Motorlinks=5;

void setup() 
{
pinMode(Sensorrechts, INPUT);
pinMode(Sensorlinks, INPUT);

attachInterrupt(digitalPinToInterrupt(Sensorlinks), Lenkunglinks, CHANGE);
attachInterrupt(digitalPinToInterrupt(Sensorrechts), Lenkungrechts, CHANGE);

pinMode(Motorrechts, OUTPUT);
pinMode(Motorlinks, OUTPUT);
}

void loop()
{

}

void Lenkunglinks()
{
	if(digitalRead(Sensorlinks)== HIGH){
		digitalWrite(Motorrechts, HIGH);
	}else{
		digitalWrite(Motorrechts, LOW);
	}

	if(digitalRead(Sensorrechts)== HIGH){
		digitalWrite(Motorlinks, HIGH);
	}else{
		digitalWrite(Motorlinks, LOW);
	}
}

void Lenkungrechts()
{
	if(digitalRead(Sensorrechts)== HIGH){
		digitalWrite(Motorlinks, HIGH);
	}else{
		digitalWrite(Motorlinks, LOW);
	}

	if(digitalRead(Sensorlinks)== HIGH){
		digitalWrite(Motorrechts, HIGH);
	}else{
		digitalWrite(Motorrechts, LOW);
	}
}
