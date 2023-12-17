#include "Wire.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include "Particle.h"
#include "LIS3DH.h"
#include "Adafruit_Fingerprint.h"
#include "blynk.h"

// declaring variables, devices, etc
//int getFingerprintIDez();
//const int red_led_pin = 2, green_led_pin = 3;
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);
VCNL4040 proximitySensor;
bool lock = false;
bool value = FALSE;
int x;
long previousMillis = 0;
long interval = 1000;
bool lockOpen = false;
//bool doorUnLocked = false;
bool doorOpen = false;

const BleUuid serviceUuid("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid rxUuid("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid txUuid("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");

const size_t UART_TX_BUF_SIZE = 20;
const size_t SCAN_RESULT_COUNT = 20;

BleScanResult scanResults[SCAN_RESULT_COUNT];

BleCharacteristic peerTxCharacteristic;
BleCharacteristic peerRxCharacteristic;
BlePeerDevice peer;

uint8_t txBuf[UART_TX_BUF_SIZE];
size_t txLen = 0;

const unsigned long SCAN_PERIOD_MS = 2000;
unsigned long lastScan = 0;

const unsigned long PRINT_SAMPLE_PERIOD = 100;
LIS3DHSPI accel(SPI, D3, WKP);
unsigned long lastPrintSample = 0;
// receiving data
void onDataReceived(const uint8_t *data, size_t len, const BlePeerDevice &peer, void *context)
{
  for (size_t i = 0; i < len; i++)
  {
    if (String(data[i]).equals("49"))
    {
      Serial.println("1 received");
    }
  }
}

// setup
void setup()
{
  Blynk.begin("9xVQdlyZEUR91QYEiNZ9-PAgldvD5uP_", IPAddress(167, 172, 234, 162), 8080);
  pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);

  Serial.begin(9600);

  //finger.begin(57600);

  Wire.begin();

  BLE.on();

  RGB.control(true);

  /*if (finger.verifyPassword())
  {
    Serial.println("Found fingerprint sensor!");
  }
  else
  {
    Serial.println("Did not find fingerprint sensor :(");
    while (1)
      ;
  }
  Serial.println("Waiting for valid finger...");*/

  LIS3DHConfig config;
  config.setAccelMode(LIS3DH::RATE_100_HZ);
  accel.setup(config);

  if (proximitySensor.begin() == false)
  {
    Serial.println("Device not found. Please check wiring.");
    while (1)
      ; // Freeze!
  }
#if SYSTEM_VERSION == SYSTEM_VERSION_v310
  // This is required with 3.1.0 only
  BLE.setScanPhy(BlePhy::BLE_PHYS_AUTO);
#endif
  peerTxCharacteristic.onDataReceived(onDataReceived, &peerTxCharacteristic);
}

void loop()
{
  Blynk.run();
  //if (doorUnLocked == false)
  //{
    if (value == true)
    {
      lock == false;
    }
    if (lock == false) {
      unsigned int proxValue = proximitySensor.getProximity();
      if (proxValue > 4)
      {
        digitalWrite(D7, HIGH);
        delay(5000);
        digitalWrite(D7, LOW);
      }
    } else if (lock == true) {
      digitalWrite(D7, LOW);
    }
    unsigned long currentMillis = millis();
    if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD)
    {
      lastPrintSample = millis();

      LIS3DHSample sample;

      if (accel.getSample(sample))
      {
        x = sample.x;
        Serial.println(x);
      }
      else
      {
        Serial.println("no sample");
      }
    }
    if (x > 1500)
    {
      if (lock == true)
      {
        digitalWrite(D6, HIGH);
      } else {
        digitalWrite(D6, LOW);
      }
    }
    else if (x < 0)
    {
      if (lock == true)
      {
        digitalWrite(D6, HIGH);
      }
      else
      {
        digitalWrite(D6, LOW);
      }
//ble connecting
      if (BLE.connected())
      {
        lock = false;

        RGB.color(255, 255, 0);

        
      }
      else
      {
        lock = true;
        RGB.color(255, 0, 0);
        if (millis() - lastScan >= SCAN_PERIOD_MS)
        {
          // Time to scan
          lastScan = millis();
          size_t count = BLE.scan(scanResults, SCAN_RESULT_COUNT);
          if (count > 0)
          {
            for (uint8_t ii = 0; ii < count; ii++)
            {
              // Our serial peripheral only supports one service, so we only look for one here.
              // In some cases, you may want to get all of the service UUIDs and scan the list
              // looking to see if the serviceUuid is anywhere in the list.
              BleUuid foundServiceUuid;
              size_t svcCount = scanResults[ii].advertisingData().serviceUUID(&foundServiceUuid, 1);
              if (svcCount > 0 && foundServiceUuid == serviceUuid)
              {

                if (Serial.println(String(scanResults[ii].advertisingData().deviceName()).equals("Gaming")))
                {
                  Serial.println("Device Found!");
                  peer = BLE.connect(scanResults[ii].address());
                }
                else
                {
                  Serial.println("Device not found");
                }
                if (peer.connected())
                {
                  peer.getCharacteristicByUUID(peerTxCharacteristic, txUuid);
                  peer.getCharacteristicByUUID(peerRxCharacteristic, rxUuid);
                  // Could do this instead, but since the names are not as standardized, UUIDs are better
                  // peer.getCharacteristicByDescription(peerTxCharacteristic, "tx");
                }
                break;
              }
            }
          }
        }
      }
    }
  }
BLYNK_WRITE(V0)
{   
  if (value == TRUE) 
  {
    value = FALSE;
  } 
  else
  {
    value = TRUE;
  }
}