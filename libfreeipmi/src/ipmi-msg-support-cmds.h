/*
   ipmi-msg-support-cmds.h - IPMI Message Support Commands

   Copyright (C) 2003, 2004, 2005 FreeIPMI Core Team

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef _IPMI_MSG_SUPPORT_CMDS_H
#define	_IPMI_MSG_SUPPORT_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_USER_NAME_MAX_LENGTH        16
#define IPMI_USER_PASSWORD_MAX_LENGTH    16
#define IPMI_SESSION_MAX_USERNAME_LEN     16
#define IPMI_SESSION_CHALLENGE_STR_LEN    16
#define IPMI_SESSION_MAX_AUTH_CODE_LEN    16

#define IPMI_SESSION_AUTH_TYPE_NONE                0x00
#define IPMI_SESSION_AUTH_TYPE_MD2                 0x01
#define IPMI_SESSION_AUTH_TYPE_MD5                 0x02
#define IPMI_SESSION_AUTH_TYPE_STRAIGHT_PASSWD_KEY 0x04
#define IPMI_SESSION_AUTH_TYPE_OEM_PROP            0x05

#define IPMI_SESSION_AUTH_TYPE_VALID(__auth_type) \
        (((__auth_type) == IPMI_SESSION_AUTH_TYPE_NONE \
          || (__auth_type) == IPMI_SESSION_AUTH_TYPE_MD2 \
          || (__auth_type) == IPMI_SESSION_AUTH_TYPE_MD5 \
          || (__auth_type) == IPMI_SESSION_AUTH_TYPE_STRAIGHT_PASSWD_KEY \
          || (__auth_type) == IPMI_SESSION_AUTH_TYPE_OEM_PROP) ? 1 : 0) 

#define IPMI_PRIV_LEVEL_RESERVED     0x00
#define IPMI_PRIV_LEVEL_CALLBACK     0x01
#define IPMI_PRIV_LEVEL_USER         0x02
#define IPMI_PRIV_LEVEL_OPERATOR     0x03
#define IPMI_PRIV_LEVEL_ADMIN        0x04
#define IPMI_PRIV_LEVEL_OEM          0x05
#define IPMI_PRIV_LEVEL_NO_ACCESS    0x0F

#define IPMI_PRIV_LEVEL_VALID(__priv_level) \
        (((__priv_level) == IPMI_PRIV_LEVEL_RESERVED \
          || (__priv_level) == IPMI_PRIV_LEVEL_CALLBACK \
          || (__priv_level) == IPMI_PRIV_LEVEL_USER \
          || (__priv_level) == IPMI_PRIV_LEVEL_OPERATOR \
          || (__priv_level) == IPMI_PRIV_LEVEL_ADMIN \
          || (__priv_level) == IPMI_PRIV_LEVEL_OEM) ? 1 : 0)

#define IPMI_OEM_ID_LEN                0x03

#define IPMI_SLAVE_ADDR_BMC            0x20 /* 12.4 */
#define IPMI_SLAVE_ADDR_SWID           0x81 /* 5.5 */

#define IPMI_MESSAGING_ACCESS_MODE_DISABLED            0x0
#define IPMI_MESSAGING_ACCESS_MODE_PRE_BOOT_ONLY       0x1
#define IPMI_MESSAGING_ACCESS_MODE_ALWAYS_AVAILABLE    0x2
#define IPMI_MESSAGING_ACCESS_MODE_SHARED              0x3

#define IPMI_AUTH_STATUS_ANONYMOUS_LOGIN_ENABLED       1
#define IPMI_AUTH_STATUS_ANONYMOUS_LOGIN_DISABLED      0

#define IPMI_AUTH_STATUS_NULL_USERNAMES_ENABLED        1
#define IPMI_AUTH_STATUS_NULL_USERNAMES_DISABLED       0

#define IPMI_AUTH_STATUS_NON_NULL_USERNAMES_ENABLED    1
#define IPMI_AUTH_STATUS_NON_NULL_USERNAMES_DISABLED   0

#define IPMI_USER_LEVEL_AUTHENTICATION_ENABLE     0x0
#define IPMI_USER_LEVEL_AUTHENTICATION_DISABLE    0x1

#define IPMI_PER_MESSAGE_AUTHENTICATION_ENABLE     0x0
#define IPMI_PER_MESSAGE_AUTHENTICATION_DISABLE    0x1

#define IPMI_PEF_ALERTING_ENABLE     0x0
#define IPMI_PEF_ALERTING_DISABLE    0x1

#define IPMI_CHANNEL_ACCESS_NO_CHANGE           0x0
#define IPMI_CHANNEL_ACCESS_SET_NON_VOLATILE    0x1
#define IPMI_CHANNEL_ACCESS_SET_VOLATILE        0x2
#define IPMI_CHANNEL_ACCESS_RESERVED            0x3

#define IPMI_CHANNEL_ACCESS_GET_NON_VOLATILE    0x1
#define IPMI_CHANNEL_ACCESS_GET_VOLATILE        0x2

#define IPMI_PRIV_LEVEL_LIMIT_NO_CHANGE           0x0
#define IPMI_PRIV_LEVEL_LIMIT_SET_NON_VOLATILE    0x1
#define IPMI_PRIV_LEVEL_LIMIT_SET_VOLATILE        0x2
#define IPMI_PRIV_LEVEL_LIMIT_RESERVED            0x3

/* channel medium type */
#define IPMI_CHANNEL_MEDIUM_TYPE_RESERVED       0x0 /* 0x0D to 0x5F */
#define IPMI_CHANNEL_MEDIUM_TYPE_IPMB           0x1
#define IPMI_CHANNEL_MEDIUM_TYPE_ICMB_10        0x2
#define IPMI_CHANNEL_MEDIUM_TYPE_ICMB_09        0x3
#define IPMI_CHANNEL_MEDIUM_TYPE_LAN_802_3      0x4
#define IPMI_CHANNEL_MEDIUM_TYPE_RS232          0x5
#define IPMI_CHANNEL_MEDIUM_TYPE_OTHER_LAN      0x6
#define IPMI_CHANNEL_MEDIUM_TYPE_PCI_SMBUS      0x7
#define IPMI_CHANNEL_MEDIUM_TYPE_SMBUS_10_11    0x8
#define IPMI_CHANNEL_MEDIUM_TYPE_SMBUS_20       0x9
#define IPMI_CHANNEL_MEDIUM_TYPE_USB_1X         0xA
#define IPMI_CHANNEL_MEDIUM_TYPE_USB_2X         0xB
#define IPMI_CHANNEL_MEDIUM_TYPE_SYS_IFACE      0xC
#define IPMI_CHANNEL_MEDIUM_TYPE_OEM            0x7F /* 0x60 to 0x7F */

/* channel protocol type */
#define IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED       0x0 /* 0x03, 0x0A to 0x1B */
#define IPMI_CHANNEL_PROTOCOL_TYPE_IPMB           0x1
#define IPMI_CHANNEL_PROTOCOL_TYPE_ICMB_10        0x2
#define IPMI_CHANNEL_PROTOCOL_TYPE_SMBUS_1X_2X    0x4
#define IPMI_CHANNEL_PROTOCOL_TYPE_KCS            0x5
#define IPMI_CHANNEL_PROTOCOL_TYPE_SMIC           0x6
#define IPMI_CHANNEL_PROTOCOL_TYPE_BT_10          0x7
#define IPMI_CHANNEL_PROTOCOL_TYPE_BT_15          0x8
#define IPMI_CHANNEL_PROTOCOL_TYPE_TMODE          0x9
#define IPMI_CHANNEL_PROTOCOL_TYPE_OEM            0x1F /* 0x1C to 0x1F */

/* channel session support */
#define IPMI_CHANNEL_SESSION_LESS      0x0
#define IPMI_CHANNEL_SINGLE_SESSION    0x1
#define IPMI_CHANNEL_MULTI_SESSION     0x2
#define IPMI_CHANNEL_SESSION_BASED     0x3
#define IPMI_CHANNEL_CURRENT_CHANNEL   0xE

/* To avoid gcc warnings, added +1 and -1 in comparison */
#define IPMI_CHANNEL_NUMBER_VALID(__channel_number) \
        (((__channel_number+1) >= 0x1 \
          && (__channel_number-1) <= 0xE) ? 1 : 0)

#define IPMI_PASSWORD_OPERATION_DISABLE_USER     0x0
#define IPMI_PASSWORD_OPERATION_ENABLE_USER      0x1
#define IPMI_PASSWORD_OPERATION_SET_PASSWORD     0x2
#define IPMI_PASSWORD_OPERATION_TEST_PASSWORD    0x3

#define IPMI_PASSWORD_OPERATION_TEST_FAILED    0x80

extern fiid_template_t tmpl_cmd_get_channel_auth_caps_rq;
extern fiid_template_t tmpl_cmd_get_channel_auth_caps_rs;
extern fiid_template_t tmpl_cmd_get_session_challenge_rq;
extern fiid_template_t tmpl_cmd_get_session_challenge_rs;
extern fiid_template_t tmpl_cmd_activate_session_rq;
extern fiid_template_t tmpl_cmd_activate_session_rs;
extern fiid_template_t tmpl_cmd_set_session_priv_level_rq;
extern fiid_template_t tmpl_cmd_set_session_priv_level_rs;
extern fiid_template_t tmpl_cmd_close_session_rq;
extern fiid_template_t tmpl_cmd_close_session_rs;
extern fiid_template_t tmpl_get_channel_access_rq;
extern fiid_template_t tmpl_get_channel_access_rs;

int8_t fill_cmd_get_channel_auth_caps (uint8_t channel_num,
                                       uint8_t max_priv_level, 
                                       fiid_obj_t obj_cmd);

int8_t fill_cmd_get_session_challenge (uint8_t auth_type, 
				       char *username, 
				       uint32_t username_len, 
				       fiid_obj_t obj_cmd);

int8_t fill_cmd_activate_session (uint8_t auth_type, 
				  uint8_t max_priv_level, 
				  uint8_t *challenge_str, 
				  uint32_t challenge_str_len, 
				  uint32_t initial_outbound_seq_num, 
				  fiid_obj_t obj_cmd);

int8_t fill_cmd_set_session_priv_level (uint8_t priv_level, 
					fiid_obj_t obj_cmd);

int8_t fill_cmd_close_session (uint32_t close_session_id, 
			       fiid_obj_t obj_cmd);

int8_t fill_kcs_set_channel_access (uint8_t channel_number, 
                                    uint8_t ipmi_messaging_access_mode, 
                                    uint8_t user_level_authentication, 
                                    uint8_t per_message_authentication, 
                                    uint8_t pef_alerting, 
                                    uint8_t channel_access_set_flag, 
                                    uint8_t channel_privilege_level_limit, 
                                    uint8_t channel_privilege_level_limit_set_flag,
                                    fiid_obj_t obj_data_rq);

int8_t fill_kcs_set_user_name (uint8_t user_id, 
                               char *user_name,
                               unsigned int user_name_len,
                               fiid_obj_t obj_data_rq);

int8_t fill_kcs_get_user_name (uint8_t user_id, fiid_obj_t obj_data_rq);
       
int8_t fill_kcs_set_user_password (uint8_t user_id, 
                                   uint8_t operation, 
                                   char *user_password,
                                   unsigned int user_password_len,
                                   fiid_obj_t obj_data_rq);

int8_t fill_kcs_set_user_access (uint8_t channel_number,
                                 uint8_t user_id,
                                 uint8_t restrict_to_callback,
                                 uint8_t enable_link_auth,
                                 uint8_t enable_ipmi_msgs,
                                 uint8_t user_privilege_level_limit,
                                 uint8_t user_session_number_limit,
                                 fiid_obj_t obj_data_rq);

int8_t fill_kcs_get_user_access (uint8_t channel_number,
                                 uint8_t user_id,
                                 fiid_obj_t obj_data_rq);
       
int8_t fill_kcs_get_channel_access (uint8_t channel_number,
                                    uint8_t channel_access_set_flag,
                                    fiid_obj_t obj_data_rq);

int8_t fill_kcs_get_channel_info (uint8_t channel_number, fiid_obj_t obj_data_rq);

extern fiid_template_t tmpl_set_channel_access_rq;
extern fiid_template_t tmpl_set_channel_access_rs;

extern fiid_template_t tmpl_set_user_access_rq;
extern fiid_template_t tmpl_set_user_access_rs;

extern fiid_template_t tmpl_set_user_name_rq;
extern fiid_template_t tmpl_set_user_name_rs;

extern fiid_template_t tmpl_get_user_name_rq;
extern fiid_template_t tmpl_get_user_name_rs;

extern fiid_template_t tmpl_set_user_password_rq;
extern fiid_template_t tmpl_set_user_password_rs;

extern fiid_template_t tmpl_get_user_access_rq;
extern fiid_template_t tmpl_get_user_access_rs;

extern fiid_template_t tmpl_get_channel_info_rq;
extern fiid_template_t tmpl_get_channel_info_rs;

int8_t ipmi_check_cmd(fiid_template_t tmpl_cmd, fiid_obj_t obj_cmd, uint8_t cmd);

int8_t ipmi_check_comp_code(fiid_template_t tmpl_cmd, fiid_obj_t obj_cmd, uint8_t comp_code);

#ifdef __cplusplus
}
#endif

#endif /* ipmi-msg-support-cmds.h */


