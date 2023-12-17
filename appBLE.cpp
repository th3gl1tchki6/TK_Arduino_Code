/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/appBLE/src/appBLE.ino"
void setup();
void loop();
#line 1 "d:/appBLE/src/appBLE.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
const size_t UART_TX_BUF_SIZE = 20;
void onDataReceived(const uint8_t *data, size_t len, const BlePeerDevice &peer, void *context);
const BleUuid serviceUuid("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid rxUuid("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid txUuid("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");
BleCharacteristic txCharacteristic("tx", BleCharacteristicProperty::NOTIFY, txUuid, serviceUuid);
BleCharacteristic rxCharacteristic("rx", BleCharacteristicProperty::WRITE_WO_RSP, rxUuid, serviceUuid, onDataReceived, NULL);

void setup()
{
   RGB.control(true);
   BLE.on();
   BLE.addCharacteristic(txCharacteristic);
   BLE.addCharacteristic(rxCharacteristic);
   BleAdvertisingData data;
   data.appendServiceUUID(serviceUuid);
   data.appendLocalName("Gaming");
   BLE.advertise(&data);
   pinMode(D7, OUTPUT);
}

void loop()
{

   if (BLE.connected())
   {
      digitalWrite(D7, HIGH);
      RGB.color(0, 0, 0);
   }
   else
   {
      digitalWrite(D7, LOW);
      RGB.color(255, 200, 0);
   }
}
void onDataReceived(const uint8_t *data, size_t len, const BlePeerDevice &peer, void *context)
{
}
