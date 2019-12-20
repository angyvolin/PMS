/*
PMS Advanced example using SoftwareSerial printing out
- standard particles (CF=1)
- atmospheric environment particles
- raw numbers of particle numbers measured by device

NOTE: For measuring/comparing data atmospheric environment particles should be used all the time!
*/

#include "PMS.h"
#include <SoftwareSerial.h> // using SoftwareSerial can create problems with sleep mode

SoftwareSerial serialDust(11, 12); // RX, TX
PMS pms(serialDust);
PMS::DATA data;

void setup()
{
  // Serial Port setups
  Serial.begin(9600);   // used for print output
  serialDust.begin(9600); // software serial for dust sensor

  pms.passiveMode();    // Switch to passive mode
}

void loop()
{
  Serial1.println("Waking up, wait 30 seconds for stable readings...");
  pms.wakeUp();
  delay(30000);

  Serial1.println("Send read request...");
  pms.requestRead();

  Serial1.println("Wait max. 1 second for read...");
  if (pms.readUntil(data)) {
    Serial.print("PM 1.0 (ug/m3) CF=1: ");
    Serial.println(data.PM_SP_UG_1_0);

    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3) CF=1: ");
    Serial.println(data.PM_SP_UG_2_5);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3) CF=1: ");
    Serial.println(data.PM_SP_UG_10_0);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    // raw particle counts
    Serial.print("P > 0.3 (count/0.1l): ");
    Serial.println(data.PM_RAW_0_3);

    Serial.print("P > 0.5 (count/0.1l): ");
    Serial.println(data.PM_RAW_0_5);

    Serial.print("P > 1.0 (count/0.1l): ");
    Serial.println(data.PM_RAW_1_0);

    Serial.print("P > 2.5 (count/0.1l): ");
    Serial.println(data.PM_RAW_2_5);

    Serial.print("P > 5.0 (count/0.1l): ");
    Serial.println(data.PM_RAW_5_0);

    Serial.print("P > 10.0 (count/0.1l): ");
    Serial.println(data.PM_RAW_10_0);
  } else {
    Serial1.println("No data.");
  }

  Serial1.println("Going to sleep for 60 seconds.");
  Serial.flush(); // IMPORTANT when using software serial
  pms.sleep();
  delay(60000);
}
