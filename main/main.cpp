#include "main.h"
#include "mqtt_client.h"

static esp_mqtt_client_handle_t mqtt_client; // Handle for the MQTT client

// MQTT Event Handler
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;

    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            std::cout << "MQTT Connected" << std::endl;
            break;

        case MQTT_EVENT_DISCONNECTED:
            std::cout << "MQTT Disconnected, retrying..." << std::endl;
            break;

        case MQTT_EVENT_ERROR:
            std::cout << "MQTT Event Error" << std::endl;
            break;

        default:
            std::cout << "Unhandled MQTT Event ID: " << event_id << std::endl;
            break;
    }
}

Main App;

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

      std::cout << "initialize MQTT\n";
    // MQTT Client Configuration for ESP-IDF v5.x
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {
            .address = {
                       .uri = "mqtt://broker.hivemq.com",
                       .port = 1883 // Default MQTT port
                    }
            }
        };

    // Create and initialize the MQTT client
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);

    // Register the MQTT event handler
    esp_mqtt_client_register_event(mqtt_client, static_cast<esp_mqtt_event_id_t>(ESP_EVENT_ANY_ID), mqtt_event_handler, NULL);

    // Start the MQTT client
    esp_mqtt_client_start(mqtt_client);

    std::cout << "MQTT Client Started" << std::endl;

    while (true) {
    vTaskDelay(pdMS_TO_TICKS(10000));
    App.run();

   }
}
