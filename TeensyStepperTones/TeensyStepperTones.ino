


float octave = 6;
float keyNote = 261.63 * octave;
float divider = 600.0;
int minor = 4;

float gcode [] = {
  0, 0, 0, 0
};

float justScale[] = {
  1.0, 25. / 24, 9. / 8, 6. / 5, 5. / 4, 4. / 3, 45. / 32, 3. / 2, 8. / 5, 5. / 3, 9. / 5, 15. / 8, 2.0
};

void setup() {
  Serial1.begin(115200);
  pinMode(18, INPUT);
}

void loop() {
  float sensor = analogRead(A0);
  //Serial.println(sensor);
  if (sensor >  20.0) {
    keyNote = map(sensor, 0, 1023, 261.63 * octave, 493.88 * octave);
    Serial.println(keyNote / octave);
    if (digitalRead(18) == HIGH) {
      minor = 3;
    }
    else minor = 4;
    Serial.println(minor);
    freq2Gcode(keyNote * justScale[0], keyNote * justScale[minor], keyNote * justScale[7]);
    Serial1.println("G21");
    Serial1.println("G91");
    Serial1.print("G1 X");
    Serial1.print(gcode[0] / divider);
    Serial1.print(" Y");
    Serial1.print(gcode[1] / divider);
    Serial1.print(" Z");
    Serial1.print(gcode[2] / divider);
    Serial1.print(" F");
    Serial1.println(gcode[3]);
    delay(108);       //108-100 works well
  }
}

void freq2Gcode (float xNote, float yNote, float zNote) {
  gcode[0] = xNote;
  gcode[1] = yNote;
  gcode[2] = zNote;
  gcode[3] = sqrt(sq(xNote) + sq(yNote) + sq(zNote));
}

