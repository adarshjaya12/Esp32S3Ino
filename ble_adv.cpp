#include<Arduino.h>
#include<BLEDevice.h>
#include<BLEUtils.h>
#include<BLEServer.h>
#include"ble_adv.h"

#define SERVICE_UUID "ca78875a-8065-11ee-b962-0242ac120002"
#define CHARACTERISTIC_UUID "57bda5cb-1764-485f-85de-afe8a11f17b4"

//Flags stating if should begin connecting and if the connection is up
static boolean deviceConnected = false;
static boolean oldDeviceConnected = false;
static boolean doScan = false;
unit32_t value=0;

class MyClientCallback : public BLEClientCallbacks 
{
  void onConnect(BLEClient* pclient) 
  {
    deviceConnected=True;
    Serial.println("BLE Connected");
  }
  void onDisconnect(BLEClient* pclient) 
  {
    deviceConnected=False;
    Serial.println("BLE Disconnected");
  }
};

//Create a BLE Device
void ble_advert()
{
  Serial.println("Advertising BLE");
  BLEDevice::init("PandaCat");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
          CHARACTERISTIC_UUID,
          BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE|
          BLECharacteristic::PROPERTY_NOTIFY|
          BLECharacteristic::PROPERTY_INDICATE 
  );
  pCharacteristic->setValue("Hello World!");
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Waiting for connection");
  if(deviceConnected)
  {
    pCharacteristic->setValue(unit8_t*)&value,4);
    pCharacteristic->notify();
    value++;
    delay(5000);
  }
}

