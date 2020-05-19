#define RED_LED 11
#define GREEN_LED 10
#define BLUE_LED 9

#define DIAL A0

struct Colour {
  int red;
  int green;
  int blue; 
};

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor = analogRead(DIAL);
  double hue = (double) sensor  * 360.0 / 1024.0;
  Colour colour = hsvToRgb(hue, 1, 0.5);

  analogWrite(RED_LED, colour.red);
  analogWrite(GREEN_LED, colour.green);
  analogWrite(BLUE_LED, colour.blue);
}

/*******************************************************************************
 * Converts HSV to RGB. Requires Colour struct definition
 *
 * @date 19 May 2020
 * @author Jacob Vartanian
 *
 * @param hue The hue angle from 0 to 360
 * @param saturation The saturation from 0 to 1
 * @param value The value from 0 to 1
 ******************************************************************************/
Colour hsvToRgb(double hue, double saturation, double value) {
  double red = 0;
  double green = 0;
  double blue = 0;

  double chroma = saturation * value;
  double hue_index = hue / 60.0;

  double intermediate = chroma * (1 - abs(fmod(hue_index, 2.0) - 1));

  switch ((int) hue_index)
  {
  case 0:
    red = chroma;
    green = intermediate;
    break;
  case 1:
    green = chroma;
    red = intermediate;
    break;
  case 2:
    green = chroma;
    blue = intermediate;
    break;
  case 3:
    blue = chroma;
    green = intermediate;
    break;
  case 4:
    blue = chroma;
    red = intermediate;
    break;
  case 5: 
    red = chroma;
    blue = intermediate;
    break;
  }

  double value_match = value - chroma;
  Colour colour;
  colour.red = (int) ((red + value_match) * 255);
  colour.green = (int) ((green + value_match) * 255);
  colour.blue = (int) ((blue + value_match) * 255);
  return colour;
}
