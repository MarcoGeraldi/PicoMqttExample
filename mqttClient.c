/* -------------------------------------------------------------------------- */
/*                                Include Files                               */
/* -------------------------------------------------------------------------- */
#include "mqttExample.h"
#include "mqttClient.h"

/* -------------------------------------------------------------------------- */
/*                              Method Definition                             */
/* -------------------------------------------------------------------------- */

/* Called when publish is complete either with sucess or failure */
void mqtt_pub_request_cb(void *arg, err_t result){
  if(result != ERR_OK) {
    printf("Publish result: %d\n", result);
  }
}

 void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
    
    MQTT_CLIENT_DATA_T* mqtt_client = (MQTT_CLIENT_DATA_T*)arg;
    LWIP_UNUSED_ARG(data);
    strncpy((char*)mqtt_client->data, (char*)data, len);

    mqtt_client->len=len;
    mqtt_client->data[len]='\0';
  
    /* ------------------------- Callback for iot device ------------------------ */
    IoT_device_cb(mqtt_client);
   
}

 void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len) {
  MQTT_CLIENT_DATA_T* mqtt_client = (MQTT_CLIENT_DATA_T*)arg;
  
  strcpy((char*)mqtt_client->topic, (char*)topic);

}

 void mqtt_request_cb(void *arg, err_t err) {
  MQTT_CLIENT_DATA_T* mqtt_client = ( MQTT_CLIENT_DATA_T*)arg;

  LWIP_PLATFORM_DIAG(("MQTT client \"%s\" request cb: err %d\n", mqtt_client->mqtt_client_info.client_id, (int)err));
}

 void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
  MQTT_CLIENT_DATA_T* mqtt_client = (MQTT_CLIENT_DATA_T*)arg;
  LWIP_UNUSED_ARG(client);

  LWIP_PLATFORM_DIAG(("MQTT client \"%s\" connection cb: status %d\n", mqtt_client->mqtt_client_info.client_id, (int)status));

  if (status == MQTT_CONNECT_ACCEPTED) {
    printf("MQTT_CONNECT_ACCEPTED\n");

    //example_publish(client, arg);
    //mqtt_disconnect(client);
    mqtt_sub_unsub(client, "start", 0, mqtt_request_cb, arg, 1);
    mqtt_sub_unsub(client, "stop", 0,  mqtt_request_cb, arg, 1);
        
  }
}

void mqtt_sub_request_cb(void *arg, err_t result)
{
  /* Just print the result code here for simplicity,
     normal behaviour would be to take some action if subscribe fails like
     notifying user, retry subscribe or disconnect from server */
  printf("Subscribe result: %d\n", result);
}

