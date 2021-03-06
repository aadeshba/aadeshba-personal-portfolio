/*
  DIY Lighty + SD + OLED + 5 way joystick + WS2812B RGB LED
  Dirk Essl 2020
  based on Digital Light Wand by Michael Ross

  Lighty is for use in specialized Light Painting Photography
  Applications.

  The functionality that is included in this code is as follows:

  Menu System
  1 - File select
  2 - Brightness
  3 - Initial Delay
  4 - Frame Delay
  5 - Repeat Times (The number of times to repeat the current file playback)
  6 - Repeat Delay (if you want a delay between repeated files)

  This code supports direct reading of a 24bit Windows BMP from the SD card.
  BMP images must be rotated 90 degrees clockwise and the width of the image should match the
  number of pixels you have on your LED strip.  The bottom of the tool will be the INPUT
  end of the strips where the Arduino is connected and will be the left side of the input
  BMP image.

*/

// Library initialization
#include <Adafruit_NeoPixel.h>           // Library for the WS2812 Neopixel Strip
#include <SD.h>                          // Library for the SD Card
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 lcd(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin assignments for the Arduino (Make changes to these if you use different Pins)
#define SDssPin 53                        // SD card CS pin
int NPPin = 6;                            // Data Pin for the NeoPixel LED Strip
int AuxButton = 4;                        // Aux Select Button Pin
int AuxButtonGND = 5;                     // Aux Select Button Ground Pin
int g = 0;                                // Variable for the Green Value
int b = 0;                                // Variable for the Blue Value
int r = 0;                                // Variable for the Red Value

// Intial Variable declarations and assignments (Make changes to these if you want to change defaults)
#define STRIP_LENGTH 288                  // Set the number of LEDs on the LED Strip
int frameDelay = 15;                      // default for the frame delay
int menuItem = 1;                         // Variable for current main menu selection
int initDelay = 0;                        // Variable for delay between button press and start of light sequence
int repeat = 0;                           // Variable to select auto repeat (until select button is pressed again)
int repeatDelay = 0;                      // Variable for delay between repeats
int updateMode = 0;                       // Variable to keep track of update Modes
int repeatTimes = 1;                      // Variable to keep track of number of repeats
int brightness = 50;                      // Variable and default for the Brightness of the strip

// EEPROM setup. saves all values in eeprom. the mega has 4kb of eeprom storage

#include <EEPROM.h>
// the current address in the EEPROM (i.e. which byte we're going to write to next)

// set addresses for save
int addrframeDelay = 0;                        // default for the frame delay
int addrinitDelay = 20;                        // Variable for delay between button press and start of light sequence
int addrrepeat = 30;                           // Variable to select auto repeat (until select button is pressed again)
int addrrepeatDelay = 400;                     // Variable for delay between repeats
int addrupdateMode = 50;                       // Variable to keep track of update Modes
int addrrepeatTimes = 60;                      // Variable to keep track of number of repeats
int addrbrightness = 70;                       // Variable and default for the Brightness of the strip

// Other program variable declarations, assignments, and initializations
byte x;

// Declaring the two LED Strips and pin assignments to each
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_LENGTH, NPPin, NEO_GRB + NEO_KHZ800);

int key = -1;
int oldkey = -1;

// SD Card Variables and assignments
File root;
File dataFile;
String m_CurrentFilename = "";
int m_FileIndex = 0;
int m_NumberOfFiles = 0;
String m_FileNames[200];
long buffer[STRIP_LENGTH];

// Setup 5 way joystick

int uppin = 22;
int downpin = 23;
int leftpin = 24;
int rightpin = 25;
int entpin = 26;

// Setup loop to get everything ready.  This is only run once at power on or reset
void setup() {

  pinMode(downpin, INPUT_PULLUP);
  pinMode(leftpin, INPUT_PULLUP);
  pinMode(rightpin, INPUT_PULLUP);
  pinMode(entpin, INPUT_PULLUP);
  pinMode(uppin, INPUT_PULLUP);

  // check if values in eeprom make sense, otherwise set default value
  if (EEPROM.read(addrbrightness) >= 1 && EEPROM.read(addrbrightness) <= 100) {
    brightness = EEPROM.read(addrbrightness);
  } else {
    brightness = 50;
  }

  //Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    //Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  lcd.display();
  delay(100);

  // Clear the buffer
  lcd.clearDisplay();
  lcd.setTextSize(2);
  lcd.setTextColor(SSD1306_WHITE);
  lcd.setCursor(0, 0);
  lcd.println(F("LIGHTY"));
  lcd.setTextSize(1);
  lcd.println(F("(c) Dirk Essl 2020"));
  lcd.println(F("V0.9.20200314"));
  lcd.display();
  delay(1000);
  lcd.clearDisplay();
  lcd.println(F(" "));
  lcd.println(F("..Initializing.."));
  lcd.println("Please wait");
  lcd.display();
  delay(1000);

  pinMode(AuxButton, INPUT_PULLUP);
  digitalWrite(AuxButton, INPUT_PULLUP);
  pinMode(AuxButtonGND, INPUT_PULLUP);
  digitalWrite(AuxButtonGND, INPUT_PULLUP);

  setupLEDs();
//  serial.print("Setup ledss done")
  setupSDcard();
//  serial.print("Setup sdccard done")

  ClearStrip(0);
}

// The Main Loop for the program starts here...
// This will loop endlessly looking for a key press to perform a function
void loop() {

  switch (menuItem) {
    case 1:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("1:File Select "));
      lcd.println(m_CurrentFilename);
      lcd.display();
      break;
    case 2:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("2:Brightness "));
      lcd.println(brightness);
      lcd.display();
      break;
    case 3:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("3:Init Delay "));
      lcd.println(initDelay);
      lcd.display();
      break;
    case 4:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("4:Frame Delay"));
      lcd.println(frameDelay);
      lcd.display();
      break;
    case 5:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("5:Repeat Times"));
      lcd.println(repeatTimes);
      lcd.display();
      break;
    case 6:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("6:Repeat Delay"));
      lcd.println(repeatDelay);
      lcd.display();
      break;
  }

  int keypress = ReadKeypad();
  delay(50);

  if ((keypress == 4) || (digitalRead(AuxButton) == LOW)) {   // The select key was pressed

    lcd.clearDisplay();
    lcd.setTextSize(2);
    lcd.setTextColor(SSD1306_WHITE);
    lcd.setCursor(0, 0);
    lcd.println(F(" "));
    lcd.setTextSize(1);
    lcd.println(F("Now Playing"));
    lcd.println(m_CurrentFilename);
    lcd.display();
    delay(initDelay);
    if (repeatTimes > 1) {
      for (int x = repeatTimes; x > 0; x--) {
        SendFile(m_CurrentFilename);
        delay(repeatDelay);
      }
    }
    else {
      SendFile(m_CurrentFilename);
    }
    ClearStrip(0);
  }
  if (keypress == 0) {                    // The Right Key was Pressed
    switch (menuItem) {
      case 1:                             // Select the Next File
        //BackLightOn();
        if (m_FileIndex < m_NumberOfFiles - 1) {
          m_FileIndex++;
        }
        else {
          m_FileIndex = 0;                // On the last file so wrap round to the first file
        }
        DisplayCurrentFilename();
        break;
      case 2:                             // Adjust Brightness
        if (brightness < 100) {
          brightness += 1;
        }
        break;
      case 3:                             // Adjust Initial Delay + 1 second
        initDelay += 1000;
        break;
      case 4:                             // Adjust Frame Delay + 1 milliseconds
        frameDelay += 1;
        break;
      case 5:                             // Adjust Repeat Times + 1
        repeatTimes += 1;
        break;
      case 6:                             // Adjust Repeat Delay + 100 milliseconds
        repeatDelay += 100;
        break;
    }
  }

  if (keypress == 3) {                    // The Left Key was Pressed
    switch (menuItem) {                   // Select the Previous File
      case 1:
        //BackLightOn();
        if (m_FileIndex > 0) {
          m_FileIndex--;
        }
        else {
          m_FileIndex = m_NumberOfFiles - 1;   // On the last file so wrap round to the first file
        }
        DisplayCurrentFilename();
        delay(500);
        break;
      case 2:                             // Adjust Brightness
        //BackLightOn();
        if (brightness > 1) {
          brightness -= 1;
          EEPROM.put(addrbrightness, brightness);
        }
        break;
      case 3:                             // Adjust Initial Delay - 1 second
        if (initDelay > 0) {
          initDelay -= 1000;
          EEPROM.put(addrinitDelay, initDelay);
        }
        break;
      case 4:                             // Adjust Frame Delay - 1 millisecond
        if (frameDelay > 0) {
          frameDelay -= 1;
          EEPROM.put(addrframeDelay, frameDelay);
        }
        break;
      case 5:                             // Adjust Repeat Times - 1
        if (repeatTimes > 1) {
          repeatTimes -= 1;
          EEPROM.put(addrrepeatTimes, repeatTimes);
        }
        break;
      case 6:                             // Adjust Repeat Delay - 100 milliseconds
        if (repeatDelay > 0) {
          repeatDelay -= 100;
          EEPROM.put(addrrepeatDelay, repeatDelay);
        }
        break;
    }
  }

  //if (digitalRead(uppin) == LOW) key = 1;
  if (digitalRead(uppin) == LOW) {                 // The up key was pressed
    delay(50);
    if (menuItem == 1) {
      menuItem = 6;
    }
    else {
      menuItem -= 1;
    }
  }
  if (( keypress == 2)) {                 // The down key was pressed
    if (menuItem == 6) {
      menuItem = 1;
    }
    else {
      menuItem += 1;
    }
  }
}

void setupLEDs() {
  strip.begin();
  strip.show();
}

void setupSDcard() {
  pinMode(SDssPin, OUTPUT);

  while (!SD.begin(SDssPin)) {
    lcd.println("SD init failed! ");
    lcd.display();
    delay(2000);
    lcd.clearDisplay();
    delay(500);
  }
  
  //lcd.clearDisplay();
  lcd.print("SD init done.   ");
  delay(1000);
  root = SD.open("/");
  lcd.clearDisplay();
  lcd.print("Scanning files  ");
  delay(500);
  GetFileNamesFromSD(root);
  isort(m_FileNames, m_NumberOfFiles);
  m_CurrentFilename = m_FileNames[0];
  DisplayCurrentFilename();
}

int ReadKeypad() {
  {
    if (digitalRead(uppin) == LOW) key = 1;
    else key = -1;
  }
  {
    if (digitalRead(downpin) == LOW) key = 2;
    else key = -1;
  }
  {
    if (digitalRead(leftpin) == LOW) key = 3;
    //else key = oldkey;
  }
  {
    if (digitalRead(rightpin) == LOW) key = 0;
    //else key = oldkey;
  }
  {
    if (digitalRead(entpin) == LOW) key = 4;
    //else key = oldkey;
  }

  if (key != oldkey) {                    // if keypress is detected
    delay(250);                            // wait for debounce time
    key = key;
    if (key != oldkey) {
      oldkey = key;
      if (key >= 0) {
        return key;
      }
    }
  }
  return key;
}

void SendFile(String Filename) {
  char temp[14];
  Filename.toCharArray(temp, 14);
  dataFile = SD.open(temp);

  // if the file is available send it to the LED's
  if (dataFile) {
    ReadTheFile();
    dataFile.close();
  }
  else {
    lcd.clearDisplay();
    lcd.print("  Error reading ");
    lcd.setCursor(4, 1);
    lcd.print("file");
    delay(1000);
    lcd.clearDisplay();
    setupSDcard();
    return;
  }
}

void DisplayCurrentFilename() {
  m_CurrentFilename = m_FileNames[m_FileIndex];
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(m_CurrentFilename);
}

void GetFileNamesFromSD(File dir) {
  int fileCount = 0;
  String CurrentFilename = "";
  while (1) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      m_NumberOfFiles = fileCount;
      entry.close();
      break;
    }
    else {
      if (entry.isDirectory()) {
        //GetNextFileName(root);
      }
      else {
        CurrentFilename = entry.name();
        if (CurrentFilename.endsWith(".bmp") || CurrentFilename.endsWith(".BMP") ) { //find files with our extension only
          m_FileNames[fileCount] = entry.name();
          fileCount++;
        }
      }
    }
    entry.close();
  }
}

void latchanddelay(int dur) {
  strip.show();
  delay(dur);
}

void ClearStrip(int duration) {
  int x;
  for (x = 0; x < STRIP_LENGTH; x++) {
    strip.setPixelColor(x, 0);
  }
  strip.show();
}

uint32_t readLong() {
  uint32_t retValue;
  byte incomingbyte;

  incomingbyte = readByte();
  retValue = (uint32_t)((byte)incomingbyte);

  incomingbyte = readByte();
  retValue += (uint32_t)((byte)incomingbyte) << 8;

  incomingbyte = readByte();
  retValue += (uint32_t)((byte)incomingbyte) << 16;

  incomingbyte = readByte();
  retValue += (uint32_t)((byte)incomingbyte) << 24;

  return retValue;
}

uint16_t readInt() {
  byte incomingbyte;
  uint16_t retValue;
  incomingbyte = readByte();
  retValue += (uint16_t)((byte)incomingbyte);
  incomingbyte = readByte();
  retValue += (uint16_t)((byte)incomingbyte) << 8;
  return retValue;
}

int readByte() {
  int retbyte = -1;
  while (retbyte < 0) retbyte = dataFile.read();
  return retbyte;
}

void getRGBwithGamma() {
  g = gamma(readByte()) / (101 - brightness);
  b = gamma(readByte()) / (101 - brightness);
  r = gamma(readByte()) / (101 - brightness);
}

void ReadTheFile() {
#define MYBMP_BF_TYPE           0x4D42
#define MYBMP_BF_OFF_BITS       54
#define MYBMP_BI_SIZE           40
#define MYBMP_BI_RGB            0L
#define MYBMP_BI_RLE8           1L
#define MYBMP_BI_RLE4           2L
#define MYBMP_BI_BITFIELDS      3L

  uint16_t bmpType = readInt();
  uint32_t bmpSize = readLong();
  uint16_t bmpReserved1 = readInt();
  uint16_t bmpReserved2 = readInt();
  uint32_t bmpOffBits = readLong();
  bmpOffBits = 54;

  /* Check file header */
  if (bmpType != MYBMP_BF_TYPE || bmpOffBits != MYBMP_BF_OFF_BITS) {
    lcd.setCursor(0, 0);
    lcd.print("not a bitmap");
    delay(1000);
    return;
  }

  /* Read info header */
  uint32_t imgSize = readLong();
  uint32_t imgWidth = readLong();
  uint32_t imgHeight = readLong();
  uint16_t imgPlanes = readInt();
  uint16_t imgBitCount = readInt();
  uint32_t imgCompression = readLong();
  uint32_t imgSizeImage = readLong();
  uint32_t imgXPelsPerMeter = readLong();
  uint32_t imgYPelsPerMeter = readLong();
  uint32_t imgClrUsed = readLong();
  uint32_t imgClrImportant = readLong();

  /* Check info header */
  if ( imgSize != MYBMP_BI_SIZE || imgWidth <= 0 ||
       imgHeight <= 0 || imgPlanes != 1 ||
       imgBitCount != 24 || imgCompression != MYBMP_BI_RGB ||
       imgSizeImage == 0 )
  {
    lcd.setCursor(0, 0);
    lcd.print("Unsupported");
    lcd.setCursor(0, 1);
    lcd.print("Bitmap Use 24bpp");
    delay(1000);
    return;
  }

  int displayWidth = imgWidth;
  if (imgWidth > STRIP_LENGTH) {
    displayWidth = STRIP_LENGTH;           //only display the number of led's we have
  }

  /* compute the line length */
  uint32_t lineLength = imgWidth * 3;
  if ((lineLength % 4) != 0)
    lineLength = (lineLength / 4 + 1) * 4;

  // Note:
  // The x,r,b,g sequence below might need to be changed if your strip is displaying
  // incorrect colors.  Some strips use an x,r,b,g sequence and some use x,r,g,b
  // Change the order if needed to make the colors correct.

  for (int y = imgHeight; y > 0; y--) {
    int bufpos = 0;
    for (int x = 0; x < displayWidth; x++) {
      uint32_t offset = (MYBMP_BF_OFF_BITS + (((y - 1) * lineLength) + (x * 3))) ;
      dataFile.seek(offset);

      getRGBwithGamma();

      strip.setPixelColor(x, r, b, g);

    }
    latchanddelay(frameDelay);
  }
}

// Sort the filenames in alphabetical order
void isort(String * filenames, int n) {
  for (int i = 1; i < n; ++i) {
    String j = filenames[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < filenames[k]); k--) {
      filenames[k + 1] = filenames[k];
    }
    filenames[k + 1] = j;
  }
}

PROGMEM const unsigned char gammaTable[]  = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,
  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,
  4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,
  7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9, 10, 10, 10, 10, 11,
  11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15, 16, 16,
  16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22,
  23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30,
  30, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39,
  40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50,
  50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 58, 58, 59, 60, 61, 62,
  62, 63, 64, 65, 66, 67, 67, 68, 69, 70, 71, 72, 73, 74, 74, 75,
  76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
  92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 104, 105, 106, 107, 108,
  109, 110, 111, 113, 114, 115, 116, 117, 118, 120, 121, 122, 123, 125, 126, 127
};

inline byte gamma(byte x) {
  return pgm_read_byte(&gammaTable[x]);
}
