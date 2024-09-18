#include <MAVLinkHandler.h>

mavlink_message_t msg;
mavlink_status_t status;

// Message #0  HEARTHBEAT
uint8_t ap_type;
uint8_t ap_autopilot;
uint8_t ap_base_mode;
uint32_t ap_custom_mode;
uint8_t ap_system_status;
uint8_t ap_mavlink_version;

// Message #1  SYS_STATUS
uint16_t voltage_battery;
int16_t current_battery;
int8_t battery_remaining;
uint16_t drop_rate_comm;

// Message #24  GPS_RAW_INT
uint8_t ap_fixtype;
uint8_t ap_sat_visible;

// Message #33 GLOBAL_POSITION_INT
int32_t ap_lat;
int32_t ap_lon;
int32_t ap_alt_ag;

void MAVLink_receive(BluetoothSerial &SerialBT)
{

    while (SerialBT.available())
    {
        uint8_t c = SerialBT.read();
        if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status))
        {
            switch (msg.msgid)
            {

            case MAVLINK_MSG_ID_HEARTBEAT:
                ap_type = mavlink_msg_heartbeat_get_type(&msg);
                ap_autopilot = mavlink_msg_heartbeat_get_autopilot(&msg);
                ap_base_mode = mavlink_msg_heartbeat_get_base_mode(&msg);
                ap_custom_mode = mavlink_msg_heartbeat_get_custom_mode(&msg);
                ap_system_status = mavlink_msg_heartbeat_get_system_status(&msg);
                ap_mavlink_version = mavlink_msg_heartbeat_get_mavlink_version(&msg);
                break;

            case MAVLINK_MSG_ID_SYS_STATUS:
                voltage_battery = mavlink_msg_sys_status_get_voltage_battery(&msg);
                current_battery = mavlink_msg_sys_status_get_current_battery(&msg);
                battery_remaining = mavlink_msg_sys_status_get_battery_remaining(&msg);
                drop_rate_comm = mavlink_msg_sys_status_get_drop_rate_comm(&msg);
                break;

            case MAVLINK_MSG_ID_GPS_RAW_INT:
                ap_fixtype = mavlink_msg_gps_raw_int_get_fix_type(&msg);
                ap_sat_visible = mavlink_msg_gps_raw_int_get_satellites_visible(&msg);
                break;

            case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
                ap_lat = mavlink_msg_global_position_int_get_lat(&msg);
                ap_lon = mavlink_msg_global_position_int_get_lon(&msg);
                ap_alt_ag = mavlink_msg_global_position_int_get_relative_alt(&msg);
            }
        }
    }
}