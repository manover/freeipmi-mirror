/* 
   rmcp.c - remote management control protocol procedures

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

#include "freeipmi.h"

fiid_template_t tmpl_rmcp_hdr =
  {
    {8, "version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {8, "reserved1", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {8, "sequence_number", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {5, "message_class.class", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {2, "message_class.reserved1", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {1, "message_class.ack", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {0, "", 0}
  };

fiid_template_t tmpl_cmd_asf_presence_ping = 
  {
    {32, "iana_enterprise_number", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {8,  "message_type", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {8,  "message_tag", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {8,  "reserved1", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {8,  "data_length", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {0, "", 0}
  };

fiid_template_t tmpl_cmd_asf_presence_pong =
  {
    {32, "iana_enterprise_number", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {8,  "message_type", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {8,  "message_tag", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {8,  "reserved1", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {8,  "data_length", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {32, "oem_iana_enterprise_number", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {32, "oem_defined", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {4,  "supported_entities.version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {3,  "supported_entities.reserved1", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {1,  "supported_entities.ipmi_supported", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {7,  "supported_interactions.reserved1", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {1,  "supported_interactions.security_extensions", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {48, "reserved2", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    {0,  "", 0}
  };

int8_t
fill_rmcp_hdr (uint8_t message_class, fiid_obj_t obj_rmcp_hdr) 
{
  int8_t rv;

  if (!RMCP_HDR_MESSAGE_CLASS_VALID(message_class)
      || !fiid_obj_valid(obj_rmcp_hdr))
    {
      errno = EINVAL;
      return -1;
    }

  if ((rv = fiid_obj_template_compare(obj_rmcp_hdr, tmpl_rmcp_hdr)) < 0)
    return (-1);
  
  if (!rv)
    {
      errno = EINVAL;
      return -1;
    }

  FIID_OBJ_SET (obj_rmcp_hdr, (uint8_t *)"version", RMCP_VER_1_0);
  FIID_OBJ_SET (obj_rmcp_hdr, (uint8_t *)"reserved1", 0);
  FIID_OBJ_SET (obj_rmcp_hdr, (uint8_t *)"sequence_number", RMCP_HDR_SEQ_NUM_NO_RMCP_ACK);
  FIID_OBJ_SET (obj_rmcp_hdr, (uint8_t *)"message_class.class", message_class);
  FIID_OBJ_SET (obj_rmcp_hdr, (uint8_t *)"message_class.reserved1", 0);
  FIID_OBJ_SET (obj_rmcp_hdr, (uint8_t *)"message_class.ack",
                RMCP_HDR_MESSAGE_CLASS_BIT_RMCP_NORMAL);
  return 0;
}

int8_t
fill_rmcp_hdr_ipmi (fiid_obj_t obj_rmcp_hdr) 
{
  return fill_rmcp_hdr(RMCP_HDR_MESSAGE_CLASS_IPMI, obj_rmcp_hdr);
}

int8_t
fill_rmcp_hdr_asf (fiid_obj_t obj_rmcp_hdr)
{
  return fill_rmcp_hdr(RMCP_HDR_MESSAGE_CLASS_ASF, obj_rmcp_hdr);
}

int8_t
fill_cmd_asf_presence_ping(uint8_t message_tag, fiid_obj_t obj_cmd)
{
  int8_t rv;

  if (!fiid_obj_valid(obj_cmd))
    {
      errno = EINVAL;
      return -1;
    }

  if ((rv = fiid_obj_template_compare(obj_cmd, tmpl_cmd_asf_presence_ping)) < 0)
    return (-1);
  
  if (!rv)
    {
      errno = EINVAL;
      return -1;
    }

  FIID_OBJ_SET (obj_cmd, (uint8_t *)"iana_enterprise_number",
                htonl(RMCP_ASF_IANA_ENTERPRISE_NUM));
  FIID_OBJ_SET (obj_cmd, (uint8_t *)"message_type",
                RMCP_ASF_MESSAGE_TYPE_PRESENCE_PING);
  FIID_OBJ_SET (obj_cmd, (uint8_t *)"message_tag", message_tag);
  FIID_OBJ_SET (obj_cmd, (uint8_t *)"reserved1", 0);
  FIID_OBJ_SET (obj_cmd, (uint8_t *)"data_length", 0x00);
  return 0;
}

int32_t
assemble_rmcp_pkt (fiid_obj_t obj_rmcp_hdr, fiid_obj_t obj_cmd, uint8_t *pkt, uint32_t pkt_len)
{
  uint32_t obj_cmd_len, obj_rmcp_hdr_len;
  int8_t rv;

  if (!fiid_obj_valid(obj_rmcp_hdr) 
      || !fiid_obj_valid(obj_cmd)
      || !pkt
      || !pkt_len)
    {
      errno = EINVAL;
      return (-1);
    }

  if ((rv = fiid_obj_template_compare(obj_rmcp_hdr, tmpl_rmcp_hdr)) < 0)
    return (-1);
  
  if (!rv)
    {
      errno = EINVAL;
      return (-1);
    }

  if ((rv = fiid_obj_template_compare(obj_cmd, tmpl_cmd_asf_presence_ping)) < 0)
    return (-1);
  
  if (!rv)
    {
      errno = EINVAL;
      return (-1);
    }

  if ((rv = fiid_obj_packet_valid(obj_rmcp_hdr)) < 0)
    return (-1);

  if (!rv)
    {
      errno = EINVAL;
      return (-1);
    }

  if ((rv = fiid_obj_packet_valid(obj_cmd)) < 0)
    return (-1);

  if (!rv)
    {
      errno = EINVAL;
      return (-1);
    }

  obj_rmcp_hdr_len = fiid_obj_len_bytes (obj_rmcp_hdr);
  ERR(obj_rmcp_hdr_len != -1);
  obj_cmd_len = fiid_obj_len_bytes (obj_cmd);
  ERR(obj_cmd_len != -1);

  if (pkt_len < (obj_rmcp_hdr_len + obj_cmd_len))
    {
      errno = EMSGSIZE;
      return -1;
    }

  memset (pkt, '\0', pkt_len);
  ERR((obj_rmcp_hdr_len = fiid_obj_get_all(obj_rmcp_hdr, pkt, pkt_len)) != -1);
  ERR((obj_cmd_len = fiid_obj_get_all(obj_cmd, pkt + obj_rmcp_hdr_len, pkt_len - obj_rmcp_hdr_len)) != -1);
  return (obj_rmcp_hdr_len + obj_cmd_len);
}  

int32_t
unassemble_rmcp_pkt (void *pkt, uint32_t pkt_len, fiid_obj_t obj_rmcp_hdr, fiid_obj_t obj_cmd)
{
  uint32_t indx = 0;
  int32_t len;
  int8_t rv;

  if (!pkt
      || !fiid_obj_valid(obj_rmcp_hdr)
      || !fiid_obj_valid(obj_cmd))
    {
      errno = EINVAL;
      return -1;
    }

  if ((rv = fiid_obj_template_compare(obj_rmcp_hdr, tmpl_rmcp_hdr)) < 0)
    return (-1);
  
  if (!rv)
    {
      errno = EINVAL;
      return (-1);
    }

  if ((rv = fiid_obj_template_compare(obj_cmd, tmpl_cmd_asf_presence_pong)) < 0)
    return (-1);
  
  if (!rv)
    {
      errno = EINVAL;
      return (-1);
    }

  ERR(!((len = fiid_obj_set_all(obj_rmcp_hdr, pkt + indx, pkt_len - indx)) < 0));
  indx += len;

  if (pkt_len <= indx)
    return 0;

  ERR(!((len = fiid_obj_set_all(obj_cmd, pkt + indx, pkt_len - indx)) < 0));
  indx += len;

  return 0;
}

int8_t
ipmi_rmcp_message_tag_chk (uint8_t message_tag, fiid_obj_t pong)
{
  uint64_t val;
  int8_t rv;

  if (!fiid_obj_valid(pong))
    {
      errno = EINVAL;
      return (-1);
    }

  if ((rv = fiid_obj_template_compare(pong, tmpl_cmd_asf_presence_pong)) < 0)
    return (-1);

  if (!rv)
    {
      errno = EINVAL;
      return -1;
    }

  if (fiid_obj_get (pong, (uint8_t *)"message_tag", &val) < 0)
    return (-1);

  if (message_tag == val)
    return 1;
  else
    return 0;
}

