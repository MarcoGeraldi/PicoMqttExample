/* -------------------------------------------------------------------------- */
/*                                Include Files                               */
/* -------------------------------------------------------------------------- */

#include "IoT_device.h"



err_t IoT_device_config_pub(mqtt_client_t *client, void *arg){
    err_t err;

    u8_t qos = 2; /* 0 1 or 2, see MQTT specification */
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

    printf ("%s", serialized_string);

    mqtt_publish(client, "pub_topic", serialized_string, strlen(serialized_string), qos, retain, mqtt_pub_request_cb, arg);



    return err;
}


err_t IoT_device_update_pub(){
    err_t err;

    return err;
}

