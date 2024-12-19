#include "mqtt.h"
#include <iostream>

// Define the static member variable
esp_mqtt_client_handle_t PubSubClient::mqtt_client = nullptr;

// MQTT Event Handler
void PubSubClient::mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            std::cout << "MQTT_EVENT_CONNECTED\n";
            break;
        case MQTT_EVENT_DISCONNECTED:
            std::cout << "MQTT_EVENT_DISCONNECTED\n";
            break;
        case MQTT_EVENT_PUBLISHED:
            std::cout << "MQTT_EVENT_PUBLISHED, msg_id=" << event->msg_id << "\n";
            break;
        case MQTT_EVENT_DATA:
            std::cout << "MQTT_EVENT_DATA\n";
            std::cout << "Received data: " << std::string(event->data, event->data_len) << "\n";
            break;
        case MQTT_EVENT_ERROR:
            std::cout << "MQTT_EVENT_ERROR\n";
            break;
        default:
            std::cout << "Unhandled MQTT event: " << event->event_id << "\n";
            break;
    }
}

static esp_mqtt_client_handle_t mqtt_client; // Handle for the MQTT client

  esp_err_t PubSubClient::init(){
    return _init();
  }

 
 
 esp_err_t PubSubClient::_init()
 {
    
    std::cout << "initialize MQTT\n";
    // MQTT Client Configuration for ESP-IDF v5.x
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {
            .address = {
                       .uri = "mqtt://broker.hivemq.com",
                       .port = 1883 // Default MQTT port
                    },
            },
    .credentials = {},  // Initialize optional fields
    .network = {},      // Example of initializing unused fields
    // Add other initializations if needed
    };

    // Create and initialize the MQTT client
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);

    // Register the MQTT event handler
    esp_mqtt_client_register_event(mqtt_client, static_cast<esp_mqtt_event_id_t>(ESP_EVENT_ANY_ID), mqtt_event_handler, NULL);

    // Start the MQTT client
    esp_mqtt_client_start(mqtt_client);

    std::cout << "MQTT Client Started" << std::endl;
        
    return ESP_OK; // Ensure function has a return statement

}