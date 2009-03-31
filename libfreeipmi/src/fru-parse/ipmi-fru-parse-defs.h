/*
  Copyright (C) 2003-2009 FreeIPMI Core Team

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
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

*/

#ifndef _IPMI_FRU_PARSE_DEFS_H
#define _IPMI_FRU_PARSE_DEFS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdint.h>

#include "freeipmi/fru-parse/ipmi-fru-parse.h"

#define IPMI_FRU_PARSE_CTX_MAGIC 0x12CD1DBF

#define IPMI_FRU_PARSE_FLAGS_MASK \
  (IPMI_FRU_PARSE_FLAGS_DEBUG_DUMP \
   | IPMI_FRU_PARSE_FLAGS_SKIP_CHECKSUM_CHECKS)

#define IPMI_FRU_PARSE_BUF_LEN 2048

struct ipmi_fru_parse_ctx {
  uint32_t magic;
  int errnum;
  unsigned int flags;
  char *debug_prefix;

  ipmi_ctx_t ipmi_ctx;
  uint8_t fru_device_id;
  uint64_t fru_inventory_area_size;
  uint64_t chassis_info_area_starting_offset;
  uint64_t board_info_area_starting_offset;
  uint64_t product_info_area_starting_offset;
  uint64_t multirecord_area_starting_offset;
  unsigned int device_opened;

  int chassis_info_area_parsed;
  int board_info_area_parsed;
  int product_info_area_parsed;
  int multirecord_area_parsed;
};

#endif /* _IPMI_FRU_PARSE_DEFS_H */
