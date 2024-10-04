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
JSON_Status IoT_device_config_pub_grid_U1 (JSON_Object *object);
JSON_Status IoT_deviceDeclaration(JSON_Object *object);
JSON_Status IoT_entity_sensor_definition(JSON_Object *object, EntityParams *params);
JSON_Status IoT_entity_switch_definition(JSON_Object *object, EntityParams *params);
static char *stringValueTemplate(const char *entityName);
static char *stringSnakeCase (const char *entityName);
#endif
