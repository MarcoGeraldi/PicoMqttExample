#ifndef mqttClientH
#define mqttClientH

/* -------------------------------------------------------------------------- */
/*                                Include Files                               */
/* -------------------------------------------------------------------------- */
#include "lwip/apps/mqtt.h"


/* -------------------------------------------------------------------------- */
/*                               Data Structures                              */
/* -------------------------------------------------------------------------- */
static struct mqtt_connect_client_info_t mqtt_client_info =
{
 "picow",
 "homeassistant", /* user */
 "root", /* pass */
 0, /* keep alive */
 NULL, /* will_topic */
 NULL, /* will_msg */
 0, /* will_qos */
 0 /* will_retain */
#if LWIP_ALTCP && LWIP_ALTCP_TLS
 , NULL
#endif
};

/* -------------------------------------------------------------------------- */
/*                                   Macros                                   */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                  Typedefs                                  */
/* -------------------------------------------------------------------------- */

typedef struct MQTT_CLIENT_DATA_T {
 mqtt_client_t *mqtt_client_inst;
 struct mqtt_connect_client_info_t mqtt_client_info;
 uint8_t data[MQTT_OUTPUT_RINGBUF_SIZE];
 uint8_t topic[100];
 uint32_t len;
} MQTT_CLIENT_DATA_T;

/* -------------------------------------------------------------------------- */
/*                                Enumerations                                */
/* -------------------------------------------------------------------------- */



/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

void mqtt_pub_request_cb(void *arg, err_t result);
void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags);
void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
void mqtt_request_cb(void *arg, err_t err) ;
void mqtt_connection_cbb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);

#endif