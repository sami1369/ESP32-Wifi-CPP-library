#pragma once
#include "wifi.h"
#include "mqtt_client.h"


class PubSubClient{
   public: 
//    PubSubClient();
   esp_err_t init();

   private:
   // Define the static member variable
   static esp_mqtt_client_handle_t mqtt_client; // MQTT client handle
   static esp_err_t _init();  //static to restrict access to it only within the class

   // Private static event handler
   static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

};