#ifndef __BGLIB_H__
#define __BGLIB_H__

#include "BGLibConfig.h"
#include "inttypes.h"
#include "usart.h"
#include "UsartLib.h"

#pragma region BGLIB_DEFINES
#define BGLIB_SYSTEM_ENDPOINT_API                                   0
#define BGLIB_SYSTEM_ENDPOINT_TEST                                  1
#define BGLIB_SYSTEM_ENDPOINT_SCRIPT                                2
#define BGLIB_SYSTEM_ENDPOINT_USB                                   3
#define BGLIB_SYSTEM_ENDPOINT_UART0                                 4
#define BGLIB_SYSTEM_ENDPOINT_UART1                                 5

#define BGLIB_ATTRIBUTES_ATTRIBUTE_CHANGE_REASON_WRITE_REQUEST      0
#define BGLIB_ATTRIBUTES_ATTRIBUTE_CHANGE_REASON_WRITE_COMMAND      1
#define BGLIB_ATTRIBUTES_ATTRIBUTE_CHANGE_REASON_WRITE_REQUEST_USER 2
#define BGLIB_ATTRIBUTES_ATTRIBUTE_STATUS_FLAG_NOTIFY               1
#define BGLIB_ATTRIBUTES_ATTRIBUTE_STATUS_FLAG_INDICATE             2

#define BGLIB_CONNECTION_CONNECTED                                  1
#define BGLIB_CONNECTION_ENCRYPTED                                  2
#define BGLIB_CONNECTION_COMPLETED                                  4
#define BGLIB_CONNECTION_PARAMETERS_CHANGE                          8

#define BGLIB_ATTCLIENT_ATTRIBUTE_VALUE_TYPE_READ                   0
#define BGLIB_ATTCLIENT_ATTRIBUTE_VALUE_TYPE_NOTIFY                 1
#define BGLIB_ATTCLIENT_ATTRIBUTE_VALUE_TYPE_INDICATE               2
#define BGLIB_ATTCLIENT_ATTRIBUTE_VALUE_TYPE_READ_BY_TYPE           3
#define BGLIB_ATTCLIENT_ATTRIBUTE_VALUE_TYPE_READ_BLOB              4
#define BGLIB_ATTCLIENT_ATTRIBUTE_VALUE_TYPE_INDICATE_RSP_REQ       5

#define BGLIB_SM_BONDING_KEY_LTK                                    0x01
#define BGLIB_SM_BONDING_KEY_ADDR_PUBLIC                            0x02
#define BGLIB_SM_BONDING_KEY_ADDR_STATIC                            0x04
#define BGLIB_SM_BONDING_KEY_IRK                                    0x08
#define BGLIB_SM_BONDING_KEY_EDIVRAND                               0x10
#define BGLIB_SM_BONDING_KEY_CSRK                                   0x20
#define BGLIB_SM_BONDING_KEY_MASTERID                               0x40
#define BGLIB_SM_IO_CAPABILITY_DISPLAYONLY                          0
#define BGLIB_SM_IO_CAPABILITY_DISPLAYYESNO                         1
#define BGLIB_SM_IO_CAPABILITY_KEYBOARDONLY                         2
#define BGLIB_SM_IO_CAPABILITY_NOINPUTNOOUTPUT                      3
#define BGLIB_SM_IO_CAPABILITY_KEYBOARDDISPLAY                      4

#define BGLIB_GAP_ADDRESS_TYPE_PUBLIC                               0
#define BGLIB_GAP_ADDRESS_TYPE_RANDOM                               1
#define BGLIB_GAP_NON_DISCOVERABLE                                  0
#define BGLIB_GAP_LIMITED_DISCOVERABLE                              1
#define BGLIB_GAP_GENERAL_DISCOVERABLE                              2
#define BGLIB_GAP_BROADCAST                                         3
#define BGLIB_GAP_USER_DATA                                         4
#define BGLIB_GAP_NON_CONNECTABLE                                   0
#define BGLIB_GAP_DIRECTED_CONNECTABLE                              1
#define BGLIB_GAP_UNDIRECTED_CONNECTABLE                            2
#define BGLIB_GAP_SCANNABLE_CONNECTABLE                             3
#define BGLIB_GAP_DISCOVER_LIMITED                                  0
#define BGLIB_GAP_DISCOVER_GENERIC                                  1
#define BGLIB_GAP_DISCOVER_OBSERVATION                              2
#define BGLIB_GAP_AD_TYPE_NONE                                      0
#define BGLIB_GAP_AD_TYPE_FLAGS                                     1
#define BGLIB_GAP_AD_TYPE_SERVICES_16BIT_MORE                       2
#define BGLIB_GAP_AD_TYPE_SERVICES_16BIT_ALL                        3
#define BGLIB_GAP_AD_TYPE_SERVICES_32BIT_MORE                       4
#define BGLIB_GAP_AD_TYPE_SERVICES_32BIT_ALL                        5
#define BGLIB_GAP_AD_TYPE_SERVICES_128BIT_MORE                      6
#define BGLIB_GAP_AD_TYPE_SERVICES_128BIT_ALL                       7
#define BGLIB_GAP_AD_TYPE_LOCALNAME_SHORT                           8
#define BGLIB_GAP_AD_TYPE_LOCALNAME_COMPLETE                        9
#define BGLIB_GAP_AD_TYPE_TXPOWER                                   10
#define BGLIB_GAP_ADV_POLICY_ALL                                    0
#define BGLIB_GAP_ADV_POLICY_WHITELIST_SCAN                         1
#define BGLIB_GAP_ADV_POLICY_WHITELIST_CONNECT                      2
#define BGLIB_GAP_ADV_POLICY_WHITELIST_ALL                          3
#define BGLIB_GAP_SCAN_POLICY_ALL                                   0
#define BGLIB_GAP_SCAN_POLICY_WHITELIST                             1

#define PACKED __attribute__((packed))
#define ALIGNED __attribute__((aligned(0x4)))


#pragma endregion
#pragma region BGLIG_STRUCTS
				  

typedef struct bd_addr_t {
    uint8_t addr[6];
} bd_addr;

typedef bd_addr hwaddr;
typedef struct {
    uint8_t len;
    uint8_t data[];
} uint8array;

typedef struct {
    uint8_t len;
    int8_t data[];
} string;

struct ble_header {
    uint8_t  type_hilen;
    uint8_t  lolen;
    uint8_t  cls;
    uint8_t  command;
};

#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_RESET
struct ble_msg_system_reset_cmd_t {
    uint8_t boot_in_dfu;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ADDRESS_GET
struct ble_msg_system_address_get_rsp_t {
    bd_addr address;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_REG_WRITE
struct ble_msg_system_reg_write_cmd_t {
    uint16_t address;
    uint8_t value;
} PACKED;
struct ble_msg_system_reg_write_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_REG_READ
struct ble_msg_system_reg_read_cmd_t {
    uint16_t address;
} PACKED;
struct ble_msg_system_reg_read_rsp_t {
    uint16_t address;
    uint8_t value;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_GET_COUNTERS
struct ble_msg_system_get_counters_rsp_t {
    uint8_t txok;
    uint8_t txretry;
    uint8_t rxok;
    uint8_t rxfail;
    uint8_t mbuf;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_GET_CONNECTIONS
struct ble_msg_system_get_connections_rsp_t {
    uint8_t maxconn;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_READ_MEMORY
struct ble_msg_system_read_memory_cmd_t {
    uint32_t address;
    uint8_t length;
} PACKED;
struct ble_msg_system_read_memory_rsp_t {
    uint32_t address;
    uint8array data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_GET_INFO
struct ble_msg_system_get_info_rsp_t {
    uint16_t major;
    uint16_t minor;
    uint16_t patch;
    uint16_t build;
    uint16_t ll_version;
    uint8_t protocol_version;
    uint8_t hw;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ENDPOINT_TX
struct ble_msg_system_endpoint_tx_cmd_t {
    uint8_t endpoint;
    uint8_t data_len;
    const uint8_t *data_data;
} PACKED;
struct ble_msg_system_endpoint_tx_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_WHITELIST_APPEND
struct ble_msg_system_whitelist_append_cmd_t {
    bd_addr address;
    uint8_t address_type;
} PACKED;
struct ble_msg_system_whitelist_append_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_WHITELIST_REMOVE
struct ble_msg_system_whitelist_remove_cmd_t {
    bd_addr address;
    uint8_t address_type;
} PACKED;
struct ble_msg_system_whitelist_remove_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ENDPOINT_RX
struct ble_msg_system_endpoint_rx_cmd_t {
    uint8_t endpoint;
    uint8_t size;
} PACKED;
struct ble_msg_system_endpoint_rx_rsp_t {
    uint16_t result;
    uint8array data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ENDPOINT_SET_WATERMARKS
struct ble_msg_system_endpoint_set_watermarks_cmd_t {
    uint8_t endpoint;
    uint8_t rx;
    uint8_t tx;
} PACKED;
struct ble_msg_system_endpoint_set_watermarks_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SYSTEM_BOOT
struct ble_msg_system_boot_evt_t {
    uint16_t major;
    uint16_t minor;
    uint16_t patch;
    uint16_t build;
    uint16_t ll_version;
    uint8_t protocol_version;
    uint8_t hw;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SYSTEM_DEBUG
struct ble_msg_system_debug_evt_t {
    uint8array data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SYSTEM_ENDPOINT_WATERMARK_RX
struct ble_msg_system_endpoint_watermark_rx_evt_t {
    uint8_t endpoint;
    uint8_t data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SYSTEM_ENDPOINT_WATERMARK_TX
struct ble_msg_system_endpoint_watermark_tx_evt_t {
    uint8_t endpoint;
    uint8_t data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SYSTEM_SCRIPT_FAILURE
struct ble_msg_system_script_failure_evt_t {
    uint16_t address;
    uint16_t reason;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SYSTEM_PROTOCOL_ERROR
struct ble_msg_system_protocol_error_evt_t {
    uint16_t reason;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_SAVE
struct ble_msg_flash_ps_save_cmd_t {
    uint16_t key;
    uint8_t value_len;
    const uint8_t *value_data;
} PACKED;
struct ble_msg_flash_ps_save_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_LOAD
struct ble_msg_flash_ps_load_cmd_t {
    uint16_t key;
} PACKED;
struct ble_msg_flash_ps_load_rsp_t {
    uint16_t result;
    uint8array value;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_ERASE
struct ble_msg_flash_ps_erase_cmd_t {
    uint16_t key;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_FLASH_ERASE_PAGE
struct ble_msg_flash_erase_page_cmd_t {
    uint8_t page;
} PACKED;
struct ble_msg_flash_erase_page_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_FLASH_WRITE_DATA
struct ble_msg_flash_write_data_cmd_t {
    uint32_t address;
    uint8_t data_len;
    const uint8_t *data_data;
} PACKED;
struct ble_msg_flash_write_data_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_FLASH_READ_DATA
struct ble_msg_flash_read_data_cmd_t {
    uint32_t address;
    uint8_t length;
} PACKED;
struct ble_msg_flash_read_data_rsp_t {
    uint8array data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_FLASH_PS_KEY
struct ble_msg_flash_ps_key_evt_t {
    uint16_t key;
    uint8array value;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_WRITE
struct ble_msg_attributes_write_cmd_t {
    uint16_t handle;
    uint8_t offset;
    uint8_t value_len;
    const uint8_t *value_data;
} PACKED;
struct ble_msg_attributes_write_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_READ
struct ble_msg_attributes_read_cmd_t {
    uint16_t handle;
    uint16_t offset;
} PACKED;
struct ble_msg_attributes_read_rsp_t {
    uint16_t handle;
    uint16_t offset;
    uint16_t result;
    uint8array value;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_READ_TYPE
struct ble_msg_attributes_read_type_cmd_t {
    uint16_t handle;
} PACKED;
struct ble_msg_attributes_read_type_rsp_t {
    uint16_t handle;
    uint16_t result;
    uint8array value;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_USER_READ_RESPONSE
struct ble_msg_attributes_user_read_response_cmd_t {
    uint8_t connection;
    uint8_t att_error;
    uint8_t value_len;
    const uint8_t *value_data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_USER_WRITE_RESPONSE
struct ble_msg_attributes_user_write_response_cmd_t {
    uint8_t connection;
    uint8_t att_error;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_ATTRIBUTES_VALUE
struct ble_msg_attributes_value_evt_t {
    uint8_t connection;
    uint8_t reason;
    uint16_t handle;
    uint16_t offset;
    uint8array value;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_ATTRIBUTES_USER_READ_REQUEST
struct ble_msg_attributes_user_read_request_evt_t {
    uint8_t connection;
    uint16_t handle;
    uint16_t offset;
    uint8_t maxsize;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_ATTRIBUTES_STATUS
struct ble_msg_attributes_status_evt_t {
    uint16_t handle;
    uint8_t flags;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_CONNECTION_DISCONNECT
struct ble_msg_connection_disconnect_cmd_t {
    uint8_t connection;
} PACKED;
struct ble_msg_connection_disconnect_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_CONNECTION_GET_RSSI
struct ble_msg_connection_get_rssi_cmd_t {
    uint8_t connection;
} PACKED;
struct ble_msg_connection_get_rssi_rsp_t {
    uint8_t connection;
    int8_t rssi;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_CONNECTION_UPDATE
struct ble_msg_connection_update_cmd_t {
    uint8_t connection;
    uint16_t interval_min;
    uint16_t interval_max;
    uint16_t latency;
    uint16_t timeout;
} PACKED;
struct ble_msg_connection_update_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_CONNECTION_VERSION_UPDATE
struct ble_msg_connection_version_update_cmd_t {
    uint8_t connection;
} PACKED;
struct ble_msg_connection_version_update_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_CONNECTION_CHANNEL_MAP_GET
struct ble_msg_connection_channel_map_get_cmd_t {
    uint8_t connection;
} PACKED;
struct ble_msg_connection_channel_map_get_rsp_t {
    uint8_t connection;
    uint8array map;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_CONNECTION_CHANNEL_MAP_SET
struct ble_msg_connection_channel_map_set_cmd_t {
    uint8_t connection;
    uint8_t map_len;
    const uint8_t *map_data;
} PACKED;
struct ble_msg_connection_channel_map_set_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_CONNECTION_FEATURES_GET
struct ble_msg_connection_features_get_cmd_t {
    uint8_t connection;
} PACKED;
struct ble_msg_connection_features_get_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_CONNECTION_GET_STATUS
struct ble_msg_connection_get_status_cmd_t {
    uint8_t connection;
} PACKED;
struct ble_msg_connection_get_status_rsp_t {
    uint8_t connection;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_CONNECTION_RAW_TX
struct ble_msg_connection_raw_tx_cmd_t {
    uint8_t connection;
    uint8_t data_len;
    const uint8_t *data_data;
} PACKED;
struct ble_msg_connection_raw_tx_rsp_t {
    uint8_t connection;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_CONNECTION_STATUS
struct ble_msg_connection_status_evt_t {
    uint8_t connection;
    uint8_t flags;
    bd_addr address;
    uint8_t address_type;
    uint16_t conn_interval;
    uint16_t timeout;
    uint16_t latency;
    uint8_t bonding;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_CONNECTION_VERSION_IND
struct ble_msg_connection_version_ind_evt_t {
    uint8_t connection;
    uint8_t vers_nr;
    uint16_t comp_id;
    uint16_t sub_vers_nr;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_CONNECTION_FEATURE_IND
struct ble_msg_connection_feature_ind_evt_t {
    uint8_t connection;
    uint8array features;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_CONNECTION_RAW_RX
struct ble_msg_connection_raw_rx_evt_t {
    uint8_t connection;
    uint8array data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_CONNECTION_DISCONNECTED
struct ble_msg_connection_disconnected_evt_t {
    uint8_t connection;
    uint16_t reason;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_FIND_BY_TYPE_VALUE
struct ble_msg_attclient_find_by_type_value_cmd_t {
    uint8_t connection;
    uint16_t start;
    uint16_t end;
    uint16_t uuid;
    uint8_t value_len;
    const uint8_t *value_data;
} PACKED;
struct ble_msg_attclient_find_by_type_value_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_BY_GROUP_TYPE
struct ble_msg_attclient_read_by_group_type_cmd_t {
    uint8_t connection;
    uint16_t start;
    uint16_t end;
    uint8_t uuid_len;
    const uint8_t *uuid_data;
} PACKED;
struct ble_msg_attclient_read_by_group_type_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_BY_TYPE
struct ble_msg_attclient_read_by_type_cmd_t {
    uint8_t connection;
    uint16_t start;
    uint16_t end;
    uint8_t uuid_len;
    const uint8_t *uuid_data;
} PACKED;
struct ble_msg_attclient_read_by_type_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_FIND_INFORMATION
struct ble_msg_attclient_find_information_cmd_t {
    uint8_t connection;
    uint16_t start;
    uint16_t end;
} PACKED;
struct ble_msg_attclient_find_information_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_BY_HANDLE
struct ble_msg_attclient_read_by_handle_cmd_t {
    uint8_t connection;
    uint16_t chrhandle;
} PACKED;
struct ble_msg_attclient_read_by_handle_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_ATTRIBUTE_WRITE
struct ble_msg_attclient_attribute_write_cmd_t {
    uint8_t connection;
    uint16_t atthandle;
    uint8_t data_len;
    const uint8_t *data_data;
} PACKED;
struct ble_msg_attclient_attribute_write_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_WRITE_COMMAND
struct ble_msg_attclient_write_command_cmd_t {
    uint8_t connection;
    uint16_t atthandle;
    uint8_t data_len;
    const uint8_t *data_data;
} PACKED;
struct ble_msg_attclient_write_command_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_INDICATE_CONFIRM
struct ble_msg_attclient_indicate_confirm_cmd_t {
    uint8_t connection;
} PACKED;
struct ble_msg_attclient_indicate_confirm_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_LONG
struct ble_msg_attclient_read_long_cmd_t {
    uint8_t connection;
    uint16_t chrhandle;
} PACKED;
struct ble_msg_attclient_read_long_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_PREPARE_WRITE
struct ble_msg_attclient_prepare_write_cmd_t {
    uint8_t connection;
    uint16_t atthandle;
    uint16_t offset;
    uint8_t data_len;
    const uint8_t *data_data;
} PACKED;
struct ble_msg_attclient_prepare_write_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_EXECUTE_WRITE
struct ble_msg_attclient_execute_write_cmd_t {
    uint8_t connection;
    uint8_t commit;
} PACKED;
struct ble_msg_attclient_execute_write_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_MULTIPLE
struct ble_msg_attclient_read_multiple_cmd_t {
    uint8_t connection;
    uint8_t handles_len;
    const uint8_t *handles_data;
} PACKED;
struct ble_msg_attclient_read_multiple_rsp_t {
    uint8_t connection;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_INDICATED
struct ble_msg_attclient_indicated_evt_t {
    uint8_t connection;
    uint16_t attrhandle;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_PROCEDURE_COMPLETED
struct ble_msg_attclient_procedure_completed_evt_t {
    uint8_t connection;
    uint16_t result;
    uint16_t chrhandle;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_GROUP_FOUND
struct ble_msg_attclient_group_found_evt_t {
    uint8_t connection;
    uint16_t start;
    uint16_t end;
    uint8array uuid;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_ATTRIBUTE_FOUND
struct ble_msg_attclient_attribute_found_evt_t {
    uint8_t connection;
    uint16_t chrdecl;
    uint16_t value;
    uint8_t properties;
    uint8array uuid;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_FIND_INFORMATION_FOUND
struct ble_msg_attclient_find_information_found_evt_t {
    uint8_t connection;
    uint16_t chrhandle;
    uint8array uuid;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_ATTRIBUTE_VALUE
struct ble_msg_attclient_attribute_value_evt_t {
    uint8_t connection;
    uint16_t atthandle;
    uint8_t type;
    uint8array value;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_READ_MULTIPLE_RESPONSE
struct ble_msg_attclient_read_multiple_response_evt_t {
    uint8_t connection;
    uint8array handles;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SM_ENCRYPT_START
struct ble_msg_sm_encrypt_start_cmd_t {
    uint8_t handle;
    uint8_t bonding;
} PACKED;
struct ble_msg_sm_encrypt_start_rsp_t {
    uint8_t handle;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SM_SET_BONDABLE_MODE
struct ble_msg_sm_set_bondable_mode_cmd_t {
    uint8_t bondable;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SM_DELETE_BONDING
struct ble_msg_sm_delete_bonding_cmd_t {
    uint8_t handle;
} PACKED;
struct ble_msg_sm_delete_bonding_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SM_SET_PARAMETERS
struct ble_msg_sm_set_parameters_cmd_t {
    uint8_t mitm;
    uint8_t min_key_size;
    uint8_t io_capabilities;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SM_PASSKEY_ENTRY
struct ble_msg_sm_passkey_entry_cmd_t {
    uint8_t handle;
    uint32_t passkey;
} PACKED;
struct ble_msg_sm_passkey_entry_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SM_GET_BONDS
struct ble_msg_sm_get_bonds_rsp_t {
    uint8_t bonds;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_SM_SET_OOB_DATA
struct ble_msg_sm_set_oob_data_cmd_t {
    uint8_t oob_len;
    const uint8_t *oob_data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SM_SMP_DATA
struct ble_msg_sm_smp_data_evt_t {
    uint8_t handle;
    uint8_t packet;
    uint8array data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SM_BONDING_FAIL
struct ble_msg_sm_bonding_fail_evt_t {
    uint8_t handle;
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SM_PASSKEY_DISPLAY
struct ble_msg_sm_passkey_display_evt_t {
    uint8_t handle;
    uint32_t passkey;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SM_PASSKEY_REQUEST
struct ble_msg_sm_passkey_request_evt_t {
    uint8_t handle;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_SM_BOND_STATUS
struct ble_msg_sm_bond_status_evt_t {
    uint8_t bond;
    uint8_t keysize;
    uint8_t mitm;
    uint8_t keys;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_SET_PRIVACY_FLAGS
struct ble_msg_gap_set_privacy_flags_cmd_t {
    uint8_t peripheral_privacy;
    uint8_t central_privacy;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_SET_MODE
struct ble_msg_gap_set_mode_cmd_t {
    uint8_t discover;
    uint8_t connect;
} PACKED;
struct ble_msg_gap_set_mode_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_DISCOVER
struct ble_msg_gap_discover_cmd_t {
    uint8_t mode;
} PACKED;
struct ble_msg_gap_discover_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_CONNECT_DIRECT
struct ble_msg_gap_connect_direct_cmd_t {
    bd_addr address;
    uint8_t addr_type;
    uint16_t conn_interval_min;
    uint16_t conn_interval_max;
    uint16_t timeout;
    uint16_t latency;
} PACKED;
struct ble_msg_gap_connect_direct_rsp_t {
    uint16_t result;
    uint8_t connection_handle;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_END_PROCEDURE
struct ble_msg_gap_end_procedure_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_CONNECT_SELECTIVE
struct ble_msg_gap_connect_selective_cmd_t {
    uint16_t conn_interval_min;
    uint16_t conn_interval_max;
    uint16_t timeout;
    uint16_t latency;
} PACKED;
struct ble_msg_gap_connect_selective_rsp_t {
    uint16_t result;
    uint8_t connection_handle;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_SET_FILTERING
struct ble_msg_gap_set_filtering_cmd_t {
    uint8_t scan_policy;
    uint8_t adv_policy;
    uint8_t scan_duplicate_filtering;
} PACKED;
struct ble_msg_gap_set_filtering_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_SET_SCAN_PARAMETERS
struct ble_msg_gap_set_scan_parameters_cmd_t {
    uint16_t scan_interval;
    uint16_t scan_window;
    uint8_t active;
} PACKED;
struct ble_msg_gap_set_scan_parameters_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_SET_ADV_PARAMETERS
struct ble_msg_gap_set_adv_parameters_cmd_t {
    uint16_t adv_interval_min;
    uint16_t adv_interval_max;
    uint8_t adv_channels;
} PACKED;
struct ble_msg_gap_set_adv_parameters_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_SET_ADV_DATA
struct ble_msg_gap_set_adv_data_cmd_t {
    uint8_t set_scanrsp;
    uint8_t adv_data_len;
    const uint8_t *adv_data_data;
} PACKED;
struct ble_msg_gap_set_adv_data_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_GAP_SET_DIRECTED_CONNECTABLE_MODE
struct ble_msg_gap_set_directed_connectable_mode_cmd_t {
    bd_addr address;
    uint8_t addr_type;
} PACKED;
struct ble_msg_gap_set_directed_connectable_mode_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_GAP_SCAN_RESPONSE
struct ble_msg_gap_scan_response_evt_t {
    int8_t rssi;
    uint8_t packet_type;
    bd_addr sender;
    uint8_t address_type;
    uint8_t bond;
    uint8array data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_GAP_MODE_CHANGED
struct ble_msg_gap_mode_changed_evt_t {
    uint8_t discover;
    uint8_t connect;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_IRQ
struct ble_msg_hardware_io_port_config_irq_cmd_t {
    uint8_t port;
    uint8_t enable_bits;
    uint8_t falling_edge;
} PACKED;
struct ble_msg_hardware_io_port_config_irq_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SET_SOFT_TIMER
struct ble_msg_hardware_set_soft_timer_cmd_t {
    uint32_t time;
    uint8_t handle;
    uint8_t single_shot;
} PACKED;
struct ble_msg_hardware_set_soft_timer_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_ADC_READ
struct ble_msg_hardware_adc_read_cmd_t {
    uint8_t input;
    uint8_t decimation;
    uint8_t reference_selection;
} PACKED;
struct ble_msg_hardware_adc_read_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_DIRECTION
struct ble_msg_hardware_io_port_config_direction_cmd_t {
    uint8_t port;
    uint8_t direction;
} PACKED;
struct ble_msg_hardware_io_port_config_direction_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_FUNCTION
struct ble_msg_hardware_io_port_config_function_cmd_t {
    uint8_t port;
    uint8_t function;
} PACKED;
struct ble_msg_hardware_io_port_config_function_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_PULL
struct ble_msg_hardware_io_port_config_pull_cmd_t {
    uint8_t port;
    uint8_t tristate_mask;
    uint8_t pull_up;
} PACKED;
struct ble_msg_hardware_io_port_config_pull_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_WRITE
struct ble_msg_hardware_io_port_write_cmd_t {
    uint8_t port;
    uint8_t mask;
    uint8_t data;
} PACKED;
struct ble_msg_hardware_io_port_write_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_READ
struct ble_msg_hardware_io_port_read_cmd_t {
    uint8_t port;
    uint8_t mask;
} PACKED;
struct ble_msg_hardware_io_port_read_rsp_t {
    uint16_t result;
    uint8_t port;
    uint8_t data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SPI_CONFIG
struct ble_msg_hardware_spi_config_cmd_t {
    uint8_t channel;
    uint8_t polarity;
    uint8_t phase;
    uint8_t bit_order;
    uint8_t baud_e;
    uint8_t baud_m;
} PACKED;
struct ble_msg_hardware_spi_config_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SPI_TRANSFER
struct ble_msg_hardware_spi_transfer_cmd_t {
    uint8_t channel;
    uint8_t data_len;
    const uint8_t *data_data;
} PACKED;
struct ble_msg_hardware_spi_transfer_rsp_t {
    uint16_t result;
    uint8_t channel;
    uint8array data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_I2C_READ
struct ble_msg_hardware_i2c_read_cmd_t {
    uint8_t address;
    uint8_t stop;
    uint8_t length;
} PACKED;
struct ble_msg_hardware_i2c_read_rsp_t {
    uint16_t result;
    uint8array data;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_I2C_WRITE
struct ble_msg_hardware_i2c_write_cmd_t {
    uint8_t address;
    uint8_t stop;
    uint8_t data_len;
    const uint8_t *data_data;
} PACKED;
struct ble_msg_hardware_i2c_write_rsp_t {
    uint8_t written;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SET_TXPOWER
struct ble_msg_hardware_set_txpower_cmd_t {
    uint8_t power;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_TIMER_COMPARATOR
struct ble_msg_hardware_timer_comparator_cmd_t {
    uint8_t timer;
    uint8_t channel;
    uint8_t mode;
    uint16_t comparator_value;
} PACKED;
struct ble_msg_hardware_timer_comparator_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_IRQ_ENABLE
struct ble_msg_hardware_io_port_irq_enable_cmd_t {
    uint8_t port;
    uint8_t enable_bits;
} PACKED;
struct ble_msg_hardware_io_port_irq_enable_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_IRQ_DIRECTION
struct ble_msg_hardware_io_port_irq_direction_cmd_t {
    uint8_t port;
    uint8_t falling_edge;
} PACKED;
struct ble_msg_hardware_io_port_irq_direction_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_HARDWARE_IO_PORT_STATUS
struct ble_msg_hardware_io_port_status_evt_t {
    uint32_t timestamp;
    uint8_t port;
    uint8_t irq;
    uint8_t state;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_HARDWARE_SOFT_TIMER
struct ble_msg_hardware_soft_timer_evt_t {
    uint8_t handle;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_HARDWARE_ADC_RESULT
struct ble_msg_hardware_adc_result_evt_t {
    uint8_t input;
    int16_t value;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_TX
struct ble_msg_test_phy_tx_cmd_t {
    uint8_t channel;
    uint8_t length;
    uint8_t type;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_RX
struct ble_msg_test_phy_rx_cmd_t {
    uint8_t channel;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_END
struct ble_msg_test_phy_end_rsp_t {
    uint16_t counter;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_TEST_GET_CHANNEL_MAP
struct ble_msg_test_get_channel_map_rsp_t {
    uint8array channel_map;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_TEST_DEBUG
struct ble_msg_test_debug_cmd_t {
    uint8_t input_len;
    const uint8_t *input_data;
} PACKED;
struct ble_msg_test_debug_rsp_t {
    uint8array output;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_TEST_CHANNEL_MODE
struct ble_msg_test_channel_mode_cmd_t {
    uint8_t mode;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_DFU_RESET
struct ble_msg_dfu_reset_cmd_t {
    uint8_t dfu;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_DFU_FLASH_SET_ADDRESS
struct ble_msg_dfu_flash_set_address_cmd_t {
    uint32_t address;
} PACKED;
struct ble_msg_dfu_flash_set_address_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_DFU_FLASH_UPLOAD
struct ble_msg_dfu_flash_upload_cmd_t {
    uint8_t data_len;
    const uint8_t *data_data;
} PACKED;
struct ble_msg_dfu_flash_upload_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_COMMAND_DFU_FLASH_UPLOAD_FINISH
struct ble_msg_dfu_flash_upload_finish_rsp_t {
    uint16_t result;
} PACKED;
#endif
#ifdef BGLIB_ENABLE_EVENT_DFU_BOOT
struct ble_msg_dfu_boot_evt_t {
    uint32_t version;
} PACKED;
#endif
#pragma endregion

class BGLib {
    public:
        BGLib(Usart *module=0, Usart *output=0, uint8_t pMode=0);
        uint8_t checkActivity(uint16_t timeout=0);
        uint8_t checkError();
        uint8_t checkTimeout();
        void setBusy(bool busyEnabled);

        uint8_t *getLastCommand();
        uint8_t *getLastResponse();
        uint8_t *getLastEvent();
        void *getLastRXPayload();

        // set/update UART port objects
        void setModuleUART(Usart *module);
        void setOutputUART(Usart *debug);

        uint8_t parse(uint8_t ch, uint8_t packetMode=0);
        uint8_t sendCommand(uint16_t len, uint8_t commandClass, uint8_t commandId, void *payload=0);

        void (*onBusy)();               // special function to run when entering a "busy" state (e.g. mid-packet)
        void (*onIdle)();               // special function to run when returning to idle mode
        void (*onTimeout)();            // special function to run when the parser times out waiting for expected data
        void (*onBeforeTXCommand)();    // special function to run immediately before sending a command
        void (*onTXCommandComplete)();  // special function to run immediately after command transmission is complete

        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_RESET
            uint8_t ble_cmd_system_reset(uint8_t boot_in_dfu);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_HELLO
            uint8_t ble_cmd_system_hello();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ADDRESS_GET
            uint8_t ble_cmd_system_address_get();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_REG_WRITE
            uint8_t ble_cmd_system_reg_write(uint16_t address, uint8_t value);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_REG_READ
            uint8_t ble_cmd_system_reg_read(uint16_t address);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_GET_COUNTERS
            uint8_t ble_cmd_system_get_counters();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_GET_CONNECTIONS
            uint8_t ble_cmd_system_get_connections();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_READ_MEMORY
            uint8_t ble_cmd_system_read_memory(uint32_t address, uint8_t length);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_GET_INFO
            uint8_t ble_cmd_system_get_info();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ENDPOINT_TX
            uint8_t ble_cmd_system_endpoint_tx(uint8_t endpoint, uint8_t data_len, const uint8_t *data_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_WHITELIST_APPEND
            uint8_t ble_cmd_system_whitelist_append(bd_addr address, uint8_t address_type);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_WHITELIST_REMOVE
            uint8_t ble_cmd_system_whitelist_remove(bd_addr address, uint8_t address_type);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_WHITELIST_CLEAR
            uint8_t ble_cmd_system_whitelist_clear();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ENDPOINT_RX
            uint8_t ble_cmd_system_endpoint_rx(uint8_t endpoint, uint8_t size);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ENDPOINT_SET_WATERMARKS
            uint8_t ble_cmd_system_endpoint_set_watermarks(uint8_t endpoint, uint8_t rx, uint8_t tx);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_DEFRAG
            uint8_t ble_cmd_flash_ps_defrag();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_DUMP
            uint8_t ble_cmd_flash_ps_dump();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_ERASE_ALL
            uint8_t ble_cmd_flash_ps_erase_all();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_SAVE
            uint8_t ble_cmd_flash_ps_save(uint16_t key, uint8_t value_len, const uint8_t *value_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_LOAD
            uint8_t ble_cmd_flash_ps_load(uint16_t key);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_ERASE
            uint8_t ble_cmd_flash_ps_erase(uint16_t key);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_ERASE_PAGE
            uint8_t ble_cmd_flash_erase_page(uint8_t page);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_WRITE_DATA
            uint8_t ble_cmd_flash_write_data(uint32_t address, uint8_t data_len, const uint8_t *data_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_READ_DATA
            uint8_t ble_cmd_flash_read_data(uint32_t address, uint8_t length);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_WRITE
            uint8_t ble_cmd_attributes_write(uint16_t handle, uint8_t offset, uint8_t value_len, const uint8_t *value_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_READ
            uint8_t ble_cmd_attributes_read(uint16_t handle, uint16_t offset);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_READ_TYPE
            uint8_t ble_cmd_attributes_read_type(uint16_t handle);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_USER_READ_RESPONSE
            uint8_t ble_cmd_attributes_user_read_response(uint8_t connection, uint8_t att_error, uint8_t value_len, const uint8_t *value_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_USER_WRITE_RESPONSE
            uint8_t ble_cmd_attributes_user_write_response(uint8_t connection, uint8_t att_error);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_DISCONNECT
            uint8_t ble_cmd_connection_disconnect(uint8_t connection);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_GET_RSSI
            uint8_t ble_cmd_connection_get_rssi(uint8_t connection);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_UPDATE
            uint8_t ble_cmd_connection_update(uint8_t connection, uint16_t interval_min, uint16_t interval_max, uint16_t latency, uint16_t timeout);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_VERSION_UPDATE
            uint8_t ble_cmd_connection_version_update(uint8_t connection);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_CHANNEL_MAP_GET
            uint8_t ble_cmd_connection_channel_map_get(uint8_t connection);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_CHANNEL_MAP_SET
            uint8_t ble_cmd_connection_channel_map_set(uint8_t connection, uint8_t map_len, const uint8_t *map_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_FEATURES_GET
            uint8_t ble_cmd_connection_features_get(uint8_t connection);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_GET_STATUS
            uint8_t ble_cmd_connection_get_status(uint8_t connection);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_RAW_TX
            uint8_t ble_cmd_connection_raw_tx(uint8_t connection, uint8_t data_len, const uint8_t *data_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_FIND_BY_TYPE_VALUE
            uint8_t ble_cmd_attclient_find_by_type_value(uint8_t connection, uint16_t start, uint16_t end, uint16_t uuid, uint8_t value_len, const uint8_t *value_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_BY_GROUP_TYPE
            uint8_t ble_cmd_attclient_read_by_group_type(uint8_t connection, uint16_t start, uint16_t end, uint8_t uuid_len, const uint8_t *uuid_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_BY_TYPE
            uint8_t ble_cmd_attclient_read_by_type(uint8_t connection, uint16_t start, uint16_t end, uint8_t uuid_len, const uint8_t *uuid_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_FIND_INFORMATION
            uint8_t ble_cmd_attclient_find_information(uint8_t connection, uint16_t start, uint16_t end);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_BY_HANDLE
            uint8_t ble_cmd_attclient_read_by_handle(uint8_t connection, uint16_t chrhandle);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_ATTRIBUTE_WRITE
            uint8_t ble_cmd_attclient_attribute_write(uint8_t connection, uint16_t atthandle, uint8_t data_len, const uint8_t *data_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_WRITE_COMMAND
            uint8_t ble_cmd_attclient_write_command(uint8_t connection, uint16_t atthandle, uint8_t data_len, const uint8_t *data_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_INDICATE_CONFIRM
            uint8_t ble_cmd_attclient_indicate_confirm(uint8_t connection);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_LONG
            uint8_t ble_cmd_attclient_read_long(uint8_t connection, uint16_t chrhandle);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_PREPARE_WRITE
            uint8_t ble_cmd_attclient_prepare_write(uint8_t connection, uint16_t atthandle, uint16_t offset, uint8_t data_len, const uint8_t *data_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_EXECUTE_WRITE
            uint8_t ble_cmd_attclient_execute_write(uint8_t connection, uint8_t commit);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_MULTIPLE
            uint8_t ble_cmd_attclient_read_multiple(uint8_t connection, uint8_t handles_len, const uint8_t *handles_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_ENCRYPT_START
            uint8_t ble_cmd_sm_encrypt_start(uint8_t handle, uint8_t bonding);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_SET_BONDABLE_MODE
            uint8_t ble_cmd_sm_set_bondable_mode(uint8_t bondable);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_DELETE_BONDING
            uint8_t ble_cmd_sm_delete_bonding(uint8_t handle);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_SET_PARAMETERS
            uint8_t ble_cmd_sm_set_parameters(uint8_t mitm, uint8_t min_key_size, uint8_t io_capabilities);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_PASSKEY_ENTRY
            uint8_t ble_cmd_sm_passkey_entry(uint8_t handle, uint32_t passkey);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_GET_BONDS
            uint8_t ble_cmd_sm_get_bonds();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_SET_OOB_DATA
            uint8_t ble_cmd_sm_set_oob_data(uint8_t oob_len, const uint8_t *oob_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_PRIVACY_FLAGS
            uint8_t ble_cmd_gap_set_privacy_flags(uint8_t peripheral_privacy, uint8_t central_privacy);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_MODE
            uint8_t ble_cmd_gap_set_mode(uint8_t discover, uint8_t connect);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_DISCOVER
            uint8_t ble_cmd_gap_discover(uint8_t mode);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_CONNECT_DIRECT
            uint8_t ble_cmd_gap_connect_direct(bd_addr address, uint8_t addr_type, uint16_t conn_interval_min, uint16_t conn_interval_max, uint16_t timeout, uint16_t latency);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_END_PROCEDURE
            uint8_t ble_cmd_gap_end_procedure();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_CONNECT_SELECTIVE
            uint8_t ble_cmd_gap_connect_selective(uint16_t conn_interval_min, uint16_t conn_interval_max, uint16_t timeout, uint16_t latency);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_FILTERING
            uint8_t ble_cmd_gap_set_filtering(uint8_t scan_policy, uint8_t adv_policy, uint8_t scan_duplicate_filtering);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_SCAN_PARAMETERS
            uint8_t ble_cmd_gap_set_scan_parameters(uint16_t scan_interval, uint16_t scan_window, uint8_t active);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_ADV_PARAMETERS
            uint8_t ble_cmd_gap_set_adv_parameters(uint16_t adv_interval_min, uint16_t adv_interval_max, uint8_t adv_channels);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_ADV_DATA
            uint8_t ble_cmd_gap_set_adv_data(uint8_t set_scanrsp, uint8_t adv_data_len, const uint8_t *adv_data_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_DIRECTED_CONNECTABLE_MODE
            uint8_t ble_cmd_gap_set_directed_connectable_mode(bd_addr address, uint8_t addr_type);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_IRQ
            uint8_t ble_cmd_hardware_io_port_config_irq(uint8_t port, uint8_t enable_bits, uint8_t falling_edge);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SET_SOFT_TIMER
            uint8_t ble_cmd_hardware_set_soft_timer(uint32_t time, uint8_t handle, uint8_t single_shot);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_ADC_READ
            uint8_t ble_cmd_hardware_adc_read(uint8_t input, uint8_t decimation, uint8_t reference_selection);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_DIRECTION
            uint8_t ble_cmd_hardware_io_port_config_direction(uint8_t port, uint8_t direction);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_FUNCTION
            uint8_t ble_cmd_hardware_io_port_config_function(uint8_t port, uint8_t function);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_PULL
            uint8_t ble_cmd_hardware_io_port_config_pull(uint8_t port, uint8_t tristate_mask, uint8_t pull_up);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_WRITE
            uint8_t ble_cmd_hardware_io_port_write(uint8_t port, uint8_t mask, uint8_t data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_READ
            uint8_t ble_cmd_hardware_io_port_read(uint8_t port, uint8_t mask);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SPI_CONFIG
            uint8_t ble_cmd_hardware_spi_config(uint8_t channel, uint8_t polarity, uint8_t phase, uint8_t bit_order, uint8_t baud_e, uint8_t baud_m);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SPI_TRANSFER
            uint8_t ble_cmd_hardware_spi_transfer(uint8_t channel, uint8_t data_len, const uint8_t *data_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_I2C_READ
            uint8_t ble_cmd_hardware_i2c_read(uint8_t address, uint8_t stop, uint8_t length);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_I2C_WRITE
            uint8_t ble_cmd_hardware_i2c_write(uint8_t address, uint8_t stop, uint8_t data_len, const uint8_t *data_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SET_TXPOWER
            uint8_t ble_cmd_hardware_set_txpower(uint8_t power);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_TIMER_COMPARATOR
            uint8_t ble_cmd_hardware_timer_comparator(uint8_t timer, uint8_t channel, uint8_t mode, uint16_t comparator_value);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_IRQ_ENABLE
            uint8_t ble_cmd_hardware_io_port_irq_enable(uint8_t port, uint8_t enable_bits);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_IRQ_DIRECTION
            uint8_t ble_cmd_hardware_io_port_irq_direction(uint8_t port, uint8_t falling_edge);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_TX
            uint8_t ble_cmd_test_phy_tx(uint8_t channel, uint8_t length, uint8_t type);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_RX
            uint8_t ble_cmd_test_phy_rx(uint8_t channel);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_END
            uint8_t ble_cmd_test_phy_end();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_RESET
            uint8_t ble_cmd_test_phy_reset();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_GET_CHANNEL_MAP
            uint8_t ble_cmd_test_get_channel_map();
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_DEBUG
            uint8_t ble_cmd_test_debug(uint8_t input_len, const uint8_t *input_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_CHANNEL_MODE
            uint8_t ble_cmd_test_channel_mode(uint8_t mode);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_DFU_RESET
            uint8_t ble_cmd_dfu_reset(uint8_t dfu);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_DFU_FLASH_SET_ADDRESS
            uint8_t ble_cmd_dfu_flash_set_address(uint32_t address);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_DFU_FLASH_UPLOAD
            uint8_t ble_cmd_dfu_flash_upload(uint8_t data_len, const uint8_t *data_data);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_DFU_FLASH_UPLOAD_FINISH
            uint8_t ble_cmd_dfu_flash_upload_finish();
        #endif

        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_RESET
            void (*ble_rsp_system_reset)(const struct ble_msg_system_reset_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_HELLO
            void (*ble_rsp_system_hello)(const struct ble_msg_system_hello_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ADDRESS_GET
            void (*ble_rsp_system_address_get)(const struct ble_msg_system_address_get_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_REG_WRITE
            void (*ble_rsp_system_reg_write)(const struct ble_msg_system_reg_write_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_REG_READ
            void (*ble_rsp_system_reg_read)(const struct ble_msg_system_reg_read_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_GET_COUNTERS
            void (*ble_rsp_system_get_counters)(const struct ble_msg_system_get_counters_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_GET_CONNECTIONS
            void (*ble_rsp_system_get_connections)(const struct ble_msg_system_get_connections_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_READ_MEMORY
            void (*ble_rsp_system_read_memory)(const struct ble_msg_system_read_memory_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_GET_INFO
            void (*ble_rsp_system_get_info)(const struct ble_msg_system_get_info_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ENDPOINT_TX
            void (*ble_rsp_system_endpoint_tx)(const struct ble_msg_system_endpoint_tx_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_WHITELIST_APPEND
            void (*ble_rsp_system_whitelist_append)(const struct ble_msg_system_whitelist_append_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_WHITELIST_REMOVE
            void (*ble_rsp_system_whitelist_remove)(const struct ble_msg_system_whitelist_remove_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_WHITELIST_CLEAR
            void (*ble_rsp_system_whitelist_clear)(const struct ble_msg_system_whitelist_clear_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ENDPOINT_RX
            void (*ble_rsp_system_endpoint_rx)(const struct ble_msg_system_endpoint_rx_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SYSTEM_ENDPOINT_SET_WATERMARKS
            void (*ble_rsp_system_endpoint_set_watermarks)(const struct ble_msg_system_endpoint_set_watermarks_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_DEFRAG
            void (*ble_rsp_flash_ps_defrag)(const struct ble_msg_flash_ps_defrag_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_DUMP
            void (*ble_rsp_flash_ps_dump)(const struct ble_msg_flash_ps_dump_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_ERASE_ALL
            void (*ble_rsp_flash_ps_erase_all)(const struct ble_msg_flash_ps_erase_all_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_SAVE
            void (*ble_rsp_flash_ps_save)(const struct ble_msg_flash_ps_save_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_LOAD
            void (*ble_rsp_flash_ps_load)(const struct ble_msg_flash_ps_load_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_PS_ERASE
            void (*ble_rsp_flash_ps_erase)(const struct ble_msg_flash_ps_erase_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_ERASE_PAGE
            void (*ble_rsp_flash_erase_page)(const struct ble_msg_flash_erase_page_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_WRITE_DATA
            void (*ble_rsp_flash_write_data)(const struct ble_msg_flash_write_data_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_FLASH_READ_DATA
            void (*ble_rsp_flash_read_data)(const struct ble_msg_flash_read_data_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_WRITE
            void (*ble_rsp_attributes_write)(const struct ble_msg_attributes_write_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_READ
            void (*ble_rsp_attributes_read)(const struct ble_msg_attributes_read_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_READ_TYPE
            void (*ble_rsp_attributes_read_type)(const struct ble_msg_attributes_read_type_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_USER_READ_RESPONSE
            void (*ble_rsp_attributes_user_read_response)(const struct ble_msg_attributes_user_read_response_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTRIBUTES_USER_WRITE_RESPONSE
            void (*ble_rsp_attributes_user_write_response)(const struct ble_msg_attributes_user_write_response_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_DISCONNECT
            void (*ble_rsp_connection_disconnect)(const struct ble_msg_connection_disconnect_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_GET_RSSI
            void (*ble_rsp_connection_get_rssi)(const struct ble_msg_connection_get_rssi_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_UPDATE
            void (*ble_rsp_connection_update)(const struct ble_msg_connection_update_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_VERSION_UPDATE
            void (*ble_rsp_connection_version_update)(const struct ble_msg_connection_version_update_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_CHANNEL_MAP_GET
            void (*ble_rsp_connection_channel_map_get)(const struct ble_msg_connection_channel_map_get_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_CHANNEL_MAP_SET
            void (*ble_rsp_connection_channel_map_set)(const struct ble_msg_connection_channel_map_set_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_FEATURES_GET
            void (*ble_rsp_connection_features_get)(const struct ble_msg_connection_features_get_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_GET_STATUS
            void (*ble_rsp_connection_get_status)(const struct ble_msg_connection_get_status_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_CONNECTION_RAW_TX
            void (*ble_rsp_connection_raw_tx)(const struct ble_msg_connection_raw_tx_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_FIND_BY_TYPE_VALUE
            void (*ble_rsp_attclient_find_by_type_value)(const struct ble_msg_attclient_find_by_type_value_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_BY_GROUP_TYPE
            void (*ble_rsp_attclient_read_by_group_type)(const struct ble_msg_attclient_read_by_group_type_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_BY_TYPE
            void (*ble_rsp_attclient_read_by_type)(const struct ble_msg_attclient_read_by_type_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_FIND_INFORMATION
            void (*ble_rsp_attclient_find_information)(const struct ble_msg_attclient_find_information_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_BY_HANDLE
            void (*ble_rsp_attclient_read_by_handle)(const struct ble_msg_attclient_read_by_handle_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_ATTRIBUTE_WRITE
            void (*ble_rsp_attclient_attribute_write)(const struct ble_msg_attclient_attribute_write_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_WRITE_COMMAND
            void (*ble_rsp_attclient_write_command)(const struct ble_msg_attclient_write_command_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_INDICATE_CONFIRM
            void (*ble_rsp_attclient_indicate_confirm)(const struct ble_msg_attclient_indicate_confirm_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_LONG
            void (*ble_rsp_attclient_read_long)(const struct ble_msg_attclient_read_long_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_PREPARE_WRITE
            void (*ble_rsp_attclient_prepare_write)(const struct ble_msg_attclient_prepare_write_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_EXECUTE_WRITE
            void (*ble_rsp_attclient_execute_write)(const struct ble_msg_attclient_execute_write_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_ATTCLIENT_READ_MULTIPLE
            void (*ble_rsp_attclient_read_multiple)(const struct ble_msg_attclient_read_multiple_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_ENCRYPT_START
            void (*ble_rsp_sm_encrypt_start)(const struct ble_msg_sm_encrypt_start_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_SET_BONDABLE_MODE
            void (*ble_rsp_sm_set_bondable_mode)(const struct ble_msg_sm_set_bondable_mode_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_DELETE_BONDING
            void (*ble_rsp_sm_delete_bonding)(const struct ble_msg_sm_delete_bonding_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_SET_PARAMETERS
            void (*ble_rsp_sm_set_parameters)(const struct ble_msg_sm_set_parameters_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_PASSKEY_ENTRY
            void (*ble_rsp_sm_passkey_entry)(const struct ble_msg_sm_passkey_entry_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_GET_BONDS
            void (*ble_rsp_sm_get_bonds)(const struct ble_msg_sm_get_bonds_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_SM_SET_OOB_DATA
            void (*ble_rsp_sm_set_oob_data)(const struct ble_msg_sm_set_oob_data_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_PRIVACY_FLAGS
            void (*ble_rsp_gap_set_privacy_flags)(const struct ble_msg_gap_set_privacy_flags_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_MODE
            void (*ble_rsp_gap_set_mode)(const struct ble_msg_gap_set_mode_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_DISCOVER
            void (*ble_rsp_gap_discover)(const struct ble_msg_gap_discover_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_CONNECT_DIRECT
            void (*ble_rsp_gap_connect_direct)(const struct ble_msg_gap_connect_direct_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_END_PROCEDURE
            void (*ble_rsp_gap_end_procedure)(const struct ble_msg_gap_end_procedure_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_CONNECT_SELECTIVE
            void (*ble_rsp_gap_connect_selective)(const struct ble_msg_gap_connect_selective_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_FILTERING
            void (*ble_rsp_gap_set_filtering)(const struct ble_msg_gap_set_filtering_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_SCAN_PARAMETERS
            void (*ble_rsp_gap_set_scan_parameters)(const struct ble_msg_gap_set_scan_parameters_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_ADV_PARAMETERS
            void (*ble_rsp_gap_set_adv_parameters)(const struct ble_msg_gap_set_adv_parameters_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_ADV_DATA
            void (*ble_rsp_gap_set_adv_data)(const struct ble_msg_gap_set_adv_data_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_GAP_SET_DIRECTED_CONNECTABLE_MODE
            void (*ble_rsp_gap_set_directed_connectable_mode)(const struct ble_msg_gap_set_directed_connectable_mode_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_IRQ
            void (*ble_rsp_hardware_io_port_config_irq)(const struct ble_msg_hardware_io_port_config_irq_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SET_SOFT_TIMER
            void (*ble_rsp_hardware_set_soft_timer)(const struct ble_msg_hardware_set_soft_timer_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_ADC_READ
            void (*ble_rsp_hardware_adc_read)(const struct ble_msg_hardware_adc_read_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_DIRECTION
            void (*ble_rsp_hardware_io_port_config_direction)(const struct ble_msg_hardware_io_port_config_direction_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_FUNCTION
            void (*ble_rsp_hardware_io_port_config_function)(const struct ble_msg_hardware_io_port_config_function_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_CONFIG_PULL
            void (*ble_rsp_hardware_io_port_config_pull)(const struct ble_msg_hardware_io_port_config_pull_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_WRITE
            void (*ble_rsp_hardware_io_port_write)(const struct ble_msg_hardware_io_port_write_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_READ
            void (*ble_rsp_hardware_io_port_read)(const struct ble_msg_hardware_io_port_read_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SPI_CONFIG
            void (*ble_rsp_hardware_spi_config)(const struct ble_msg_hardware_spi_config_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SPI_TRANSFER
            void (*ble_rsp_hardware_spi_transfer)(const struct ble_msg_hardware_spi_transfer_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_I2C_READ
            void (*ble_rsp_hardware_i2c_read)(const struct ble_msg_hardware_i2c_read_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_I2C_WRITE
            void (*ble_rsp_hardware_i2c_write)(const struct ble_msg_hardware_i2c_write_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_SET_TXPOWER
            void (*ble_rsp_hardware_set_txpower)(const struct ble_msg_hardware_set_txpower_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_TIMER_COMPARATOR
            void (*ble_rsp_hardware_timer_comparator)(const struct ble_msg_hardware_timer_comparator_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_IRQ_ENABLE
            void (*ble_rsp_hardware_io_port_irq_enable)(const struct ble_msg_hardware_io_port_irq_enable_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_HARDWARE_IO_PORT_IRQ_DIRECTION
            void (*ble_rsp_hardware_io_port_irq_direction)(const struct ble_msg_hardware_io_port_irq_direction_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_TX
            void (*ble_rsp_test_phy_tx)(const struct ble_msg_test_phy_tx_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_RX
            void (*ble_rsp_test_phy_rx)(const struct ble_msg_test_phy_rx_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_END
            void (*ble_rsp_test_phy_end)(const struct ble_msg_test_phy_end_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_PHY_RESET
            void (*ble_rsp_test_phy_reset)(const struct ble_msg_test_phy_reset_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_GET_CHANNEL_MAP
            void (*ble_rsp_test_get_channel_map)(const struct ble_msg_test_get_channel_map_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_DEBUG
            void (*ble_rsp_test_debug)(const struct ble_msg_test_debug_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_TEST_CHANNEL_MODE
            void (*ble_rsp_test_channel_mode)(const struct ble_msg_test_channel_mode_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_DFU_RESET
            void (*ble_rsp_dfu_reset)(const struct ble_msg_dfu_reset_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_DFU_FLASH_SET_ADDRESS
            void (*ble_rsp_dfu_flash_set_address)(const struct ble_msg_dfu_flash_set_address_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_DFU_FLASH_UPLOAD
            void (*ble_rsp_dfu_flash_upload)(const struct ble_msg_dfu_flash_upload_rsp_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_COMMAND_DFU_FLASH_UPLOAD_FINISH
            void (*ble_rsp_dfu_flash_upload_finish)(const struct ble_msg_dfu_flash_upload_finish_rsp_t *msg);
        #endif

        #ifdef BGLIB_ENABLE_EVENT_SYSTEM_BOOT
            void (*ble_evt_system_boot)(const struct ble_msg_system_boot_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SYSTEM_DEBUG
            void (*ble_evt_system_debug)(const struct ble_msg_system_debug_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SYSTEM_ENDPOINT_WATERMARK_RX
            void (*ble_evt_system_endpoint_watermark_rx)(const struct ble_msg_system_endpoint_watermark_rx_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SYSTEM_ENDPOINT_WATERMARK_TX
            void (*ble_evt_system_endpoint_watermark_tx)(const struct ble_msg_system_endpoint_watermark_tx_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SYSTEM_SCRIPT_FAILURE
            void (*ble_evt_system_script_failure)(const struct ble_msg_system_script_failure_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SYSTEM_NO_LICENSE_KEY
            void (*ble_evt_system_no_license_key)(const struct ble_msg_system_no_license_key_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SYSTEM_PROTOCOL_ERROR
            void (*ble_evt_system_protocol_error)(const struct ble_msg_system_protocol_error_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_FLASH_PS_KEY
            void (*ble_evt_flash_ps_key)(const struct ble_msg_flash_ps_key_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_ATTRIBUTES_VALUE
            void (*ble_evt_attributes_value)(const struct ble_msg_attributes_value_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_ATTRIBUTES_USER_READ_REQUEST
            void (*ble_evt_attributes_user_read_request)(const struct ble_msg_attributes_user_read_request_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_ATTRIBUTES_STATUS
            void (*ble_evt_attributes_status)(const struct ble_msg_attributes_status_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_CONNECTION_STATUS
            void (*ble_evt_connection_status)(const struct ble_msg_connection_status_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_CONNECTION_VERSION_IND
            void (*ble_evt_connection_version_ind)(const struct ble_msg_connection_version_ind_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_CONNECTION_FEATURE_IND
            void (*ble_evt_connection_feature_ind)(const struct ble_msg_connection_feature_ind_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_CONNECTION_RAW_RX
            void (*ble_evt_connection_raw_rx)(const struct ble_msg_connection_raw_rx_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_CONNECTION_DISCONNECTED
            void (*ble_evt_connection_disconnected)(const struct ble_msg_connection_disconnected_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_INDICATED
            void (*ble_evt_attclient_indicated)(const struct ble_msg_attclient_indicated_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_PROCEDURE_COMPLETED
            void (*ble_evt_attclient_procedure_completed)(const struct ble_msg_attclient_procedure_completed_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_GROUP_FOUND
            void (*ble_evt_attclient_group_found)(const struct ble_msg_attclient_group_found_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_ATTRIBUTE_FOUND
            void (*ble_evt_attclient_attribute_found)(const struct ble_msg_attclient_attribute_found_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_FIND_INFORMATION_FOUND
            void (*ble_evt_attclient_find_information_found)(const struct ble_msg_attclient_find_information_found_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_ATTRIBUTE_VALUE
            void (*ble_evt_attclient_attribute_value)(const struct ble_msg_attclient_attribute_value_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_ATTCLIENT_READ_MULTIPLE_RESPONSE
            void (*ble_evt_attclient_read_multiple_response)(const struct ble_msg_attclient_read_multiple_response_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SM_SMP_DATA
            void (*ble_evt_sm_smp_data)(const struct ble_msg_sm_smp_data_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SM_BONDING_FAIL
            void (*ble_evt_sm_bonding_fail)(const struct ble_msg_sm_bonding_fail_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SM_PASSKEY_DISPLAY
            void (*ble_evt_sm_passkey_display)(const struct ble_msg_sm_passkey_display_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SM_PASSKEY_REQUEST
            void (*ble_evt_sm_passkey_request)(const struct ble_msg_sm_passkey_request_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_SM_BOND_STATUS
            void (*ble_evt_sm_bond_status)(const struct ble_msg_sm_bond_status_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_GAP_SCAN_RESPONSE
            void (*ble_evt_gap_scan_response)(const struct ble_msg_gap_scan_response_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_GAP_MODE_CHANGED
            void (*ble_evt_gap_mode_changed)(const struct ble_msg_gap_mode_changed_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_HARDWARE_IO_PORT_STATUS
            void (*ble_evt_hardware_io_port_status)(const struct ble_msg_hardware_io_port_status_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_HARDWARE_SOFT_TIMER
            void (*ble_evt_hardware_soft_timer)(const struct ble_msg_hardware_soft_timer_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_HARDWARE_ADC_RESULT
            void (*ble_evt_hardware_adc_result)(const struct ble_msg_hardware_adc_result_evt_t *msg);
        #endif
        #ifdef BGLIB_ENABLE_EVENT_DFU_BOOT
            void (*ble_evt_dfu_boot)(const struct ble_msg_dfu_boot_evt_t *msg);
        #endif

    private:
        // incoming packet buffer vars
        uint8_t *bgapiRXBuffer;
        uint8_t bgapiRXBufferSize;
        uint8_t bgapiRXBufferPos;
        uint16_t bgapiRXDataLen;

        // outgoing package buffer vars
        uint8_t *bgapiTXBuffer;
        uint8_t bgapiTXBufferSize;
        uint8_t bgapiTXBufferPos;

        // BGAPI packet structure representation
        const struct ble_msg *packetMessage;
        struct ble_header packetHeader;
        uint8_t *packetData;

	    Usart *uModule;  // required UART object with module connection
        Usart *uOutput;  // optional UART object for host/debug connection

        bool busy;
        uint8_t packetMode;
        uint8_t lastCommand[2];
        uint8_t lastResponse[2];
        uint8_t lastEvent[2];
        uint32_t timeoutStart;
        bool lastError;
        bool lastTimeout;

};
#endif
