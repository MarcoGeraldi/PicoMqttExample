/* -------------------------------------------------------------------------- */
/*                                Include Files                               */
/* -------------------------------------------------------------------------- */

#include "IoT_device.h"
#include <ctype.h> 


/* ----------------------- Initialize all the entities ---------------------- */
err_t IoT_device_config_pub_init(mqtt_client_t *client, void *arg){
    
    err_t err;

    IoT_device_config_pub_generic(IoT_device_config_pub_grid_U1, client, arg);

    return err;
}

/* ----------------------- Initialize a generic entity ---------------------- */
err_t IoT_device_config_pub_generic(JSON_Status (*IoT_entityDeclaration)(JSON_Object*),mqtt_client_t *client, void *arg)
{
    err_t err;
    char *serialized_string = NULL;
    char publishTopic[128];

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    
    /* ----------------------------- Add device info ---------------------------- */
    IoT_deviceDeclaration(root_object);

    /* ----------------------------- Declare Entity ----------------------------- */
    IoT_entityDeclaration(root_object);

    /* ---------------------- Convert JSON Object to string --------------------- */
    serialized_string = json_serialize_to_string_pretty(root_value);

    /* -------------------------- Calculate State Topic ------------------------- */
    snprintf(publishTopic, sizeof(publishTopic), "homeassistant/%s/%s/%s/config",DEVICE_GRID_U_ENTITY_TYPE,DEVICE_ID,DEVICE_GRID_U1_ENTITY_NAME);
    
    /* ---------------------- Publish Entity Configuration ---------------------- */
    mqtt_publish(client, publishTopic, serialized_string, strlen(serialized_string), 2, 0, mqtt_pub_request_cb, arg);

    return err;
}

/* ----------------------- Entity Specific Definition ----------------------- */
JSON_Status IoT_device_config_pub_grid_U1 (JSON_Object *object){
    JSON_Status JSON_Status = JSONSuccess; 

    char valueTemplate[64];

    snprintf(valueTemplate, sizeof(valueTemplate), "{{value_json.%s}}",DEVICE_GRID_U1_ENTITY_NAME);
    
    for (int i = 0; valueTemplate[i] != '\0'; i++) {
        // Convert to lowercase if it's a letter
        valueTemplate[i] = tolower(valueTemplate[i]);
        
        // Replace space with underscore
        if (valueTemplate[i] == ' ') {
            valueTemplate[i] = '_';
        }
    }

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_number                                                                                                (object, "enabled_by_default",   DEVICE_GRID_U_ENABLE_DEFAULT);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "entity_category",      DEVICE_GRID_U_ENTITY_CATEGORY);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "icon",                 DEVICE_GRID_U_ICON);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "name",                 DEVICE_GRID_U1_ENTITY_NAME);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "state_class",          DEVICE_GRID_U_STATE_CLASS);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "state_topic",          DEVICE_STATE_TOPIC );
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "unit_of_measurement",  DEVICE_GRID_U_UNIT);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "value_template",       valueTemplate);    
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "unique_id",            DEVICE_ID);
        
    return JSON_Status;
}

JSON_Status IoT_deviceDeclaration(JSON_Object *object)
{
    JSON_Status JSON_Status = JSONSuccess;

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_dotset_string(object, "device.identifiers", DEVICE_IDENTIFIER);

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_dotset_string(object, "device.manufacturer", DEVICE_MANUFACTURER);

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_dotset_string(object, "device.model", DEVICE_MODEL);

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_dotset_string(object, "device.name", DEVICE_NAME);

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_dotset_string(object, "device.sw_version", DEVICE_SW_VERS);

    return JSON_Status;
}



static void libraryExample(mqtt_client_t *client, void *arg)
{

    err_t err;

    u8_t qos = 2;    /* 0 1 or 2, see MQTT specification */
    u8_t retain = 0; /* No don't retain such crappy payload... */

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    json_object_set_string(root_object, "name", "John Smith");
    json_object_set_number(root_object, "age", 25);
    json_object_dotset_string(root_object, "address.city", "Cupertino");
    json_object_dotset_value(root_object, "contact.emails", json_parse_string("[\"email@example.com\",\"email2@example.com\"]"));
    serialized_string = json_serialize_to_string_pretty(root_value);
    puts(serialized_string);

    printf("%s", serialized_string);

    mqtt_publish(client, "pub_topic", serialized_string, strlen(serialized_string), qos, retain, mqtt_pub_request_cb, arg);
}