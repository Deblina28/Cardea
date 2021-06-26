#define alpha 0.2
#define alpha2 0.01
 
#define n 250


int data[n];

void setup() {

  pinMode(A0, INPUT_PULLUP);
  Serial.begin(38400);

  for (int i = 0; i < n; i++)
     data[i] = 0;
}

float x, y, raw, sum = 0, avg = 0, max = 0, bpm = 0.0, dRaw = 0;
int idx = 0;
int f = 1, ct = 0;
long ls=0, ps=0,cs=0;

void loop() 
{
  dRaw = calcRaw();
  //Serial.println (dRaw);
  if (dRaw > 1.5 && f)
  {
    ps = millis() - ls;
    ls = millis();
    f = 0;
    bpm = (1000.0 / ps) * 60.0;  
    Serial.println (bpm);
  }

  else if (dRaw < -1)
  {
    f = 1;
  }
    /*Serial.println(calcRaw());
    Serial.print(" ");
    Serial.println(bpm);
    delay(1);
    Serial.print(zt*6);
    Serial.print(" ");  
    Serial.println(bpmavg/11);*/
}

  float calcRaw()
  {
    raw = analogRead(A0);
    x  = alpha * raw + (1 - alpha) * x;
    y  = alpha2 * x + (1 - alpha2) * y;

    sum -= data[idx];
    data[idx] = raw;
    sum += raw;

    idx = (idx + 1) % n;

    avg = sum / n;

    return (avg-y)*(-1);
  }
