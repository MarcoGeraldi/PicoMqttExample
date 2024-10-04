#ifndef IoTdeviceH
#define IoTdeviceH

/* -------------------------------------------------------------------------- */
/*                                Include Files                               */
/* -------------------------------------------------------------------------- */

#include "mqttClient.h"
#include "utils/parson/parson.h"
#include "IoT_device_config.h"
#include <string.h>

/* -------------------------------------------------------------------------- */
/*                                   Macros                                   */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                                  Variables                                 */
/* -------------------------------------------------------------------------- */
static int IoT_entity_voltage_l1_value;
static int IoT_entity_voltage_l2_value;
static int IoT_entity_voltage_l3_value;

static char IoT_entity_output1_state_value[8] = ENTITY_SWITCH_PAYLOAD_OFF;
/* -------------------------------------------------------------------------- */
/*                               Data Structures                              */
/* -------------------------------------------------------------------------- */
// Define a structure to hold the parameters
typedef struct {
    double enableByDefault;
    const char *category;
    const char *icon;
    const char *entityName;
    const char *stateClass;
    const char *stateTopic;
    const char *unit;
    const char *uniqueID;
    const char *entityType;
    const char *command_topic;
} EntityParams;
/* -------------------------------------------------------------------------- */
/*                                  Typedefs                                  */
/* -------------------------------------------------------------------------- */
// Define a function pointer type that accepts a variable number of arguments
typedef JSON_Status (*IoT_entityDeclaration_t)(JSON_Object*, ...);
/* -------------------------------------------------------------------------- */
/*                                Enumerations                                */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

err_t IoT_device_config_pub_generic(IoT_entityDeclaration_t IoT_entityDeclaration,mqtt_client_t *client, void *arg, EntityParams *params);
err_t IoT_device_state_update_pub(mqtt_client_t *client, void *arg);
err_t IoT_device_update_sub();
err_t IoT_device_config_pub_init(mqtt_client_t *client, void *arg);

JSON_Status IoT_deviceDeclaration(JSON_Object *object);
JSON_Status IoT_entity_sensor_definition(JSON_Object *object, EntityParams *params);
JSON_Status IoT_entity_switch_definition(JSON_Object *object, EntityParams *params);

void IoT_device_cb(MQTT_CLIENT_DATA_T* mqtt_client);
static char *stringValueTemplate(const char *entityName);
static char *stringSnakeCase (const char *entityName);
#endif
