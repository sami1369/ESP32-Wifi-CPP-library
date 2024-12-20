#include "main.h"
#include "mqtt.h"






Main App;
PubSubClient mqttClient;
void Main::run(void) {
  wifiState = Wifi.GetState();

  switch (wifiState) {
  case WIFI::Wifi::state_e::READY_TO_CONNECT:
    std::cout << "Wifi Status: READY_TO_CONNECT\n";
    Wifi.Begin();
    break;
  case WIFI::Wifi::state_e::DISCONNECTED:
    std::cout << "Wifi Status: DISCONNECTED\n";
    Wifi.Begin();
    break;
  case WIFI::Wifi::state_e::CONNECTING:
    std::cout << "Wifi Status: CONNECTING\n";
    break;
  case WIFI::Wifi::state_e::WAITING_FOR_IP:
    std::cout << "Wifi Status: WAITING_FOR_IP\n";
    break;
  case WIFI::Wifi::state_e::ERROR:
    std::cout << "Wifi Status: ERROR\n";
    break;
  case WIFI::Wifi::state_e::CONNECTED:
    std::cout << "Wifi Status: CONNECTED\n";
    break;
  case WIFI::Wifi::state_e::NOT_INITIALIZED:
    std::cout << "Wifi Status: NOT_INITIALIZED\n";
    break;
  case WIFI::Wifi::state_e::INITIALIZED:
    std::cout << "Wifi Status: INITIALIZED\n";
    break;
  }
}

void Main::setup(void) {
  esp_event_loop_create_default();
  nvs_flash_init();

  Wifi.SetCredentials("Saeid", "12345678");
  Wifi.Init();
}



extern "C" void app_main(void) {
  App.setup();
    vTaskDelay(pdMS_TO_TICKS(10000));
    App.run();
    vTaskDelay(pdMS_TO_TICKS(10000));

    mqttClient.init();

    // mqttClient.subscribe("test/topic", 1);

    mqttClient.publish("test/topic", "Hello, MQTT!", 1, false);


    while (true) {
    vTaskDelay(pdMS_TO_TICKS(5000));
    App.run();
    mqttClient.publish("test/topic", "Hello, MQTT!", 1, false);


   }
}
