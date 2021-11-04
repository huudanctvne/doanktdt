#include "heltec.h"
#include "images.h"

void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0, 0, logo_width, logo_height, (const unsigned char *)logo_bits);
  Heltec.display->display();
}

void fullScr()
{
  Heltec.display->clear();
  Heltec.display->fillRect(0, 0, logo_width, logo_height);
  Heltec.display->display();
}

void twcircle()
{
  Heltec.display->clear();
  Heltec.display->fillCircle(32, 32, 31);
  Heltec.display->fillCircle(96, 32, 31);
  Heltec.display->display();
}

void progressbar(int progress)
{
  Heltec.display->drawProgressBar(0, 45, 126, 7, progress);
  Heltec.display->display();
}