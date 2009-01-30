/*
  Copyright (C) 2003-2009 FreeIPMI Core Team

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.
  
  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA
*/

#if HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#if STDC_HEADERS
#include <string.h>
#endif /* STDC_HEADERS */
#if TIME_WITH_SYS_TIME
#include <sys/time.h>
#include <time.h>
#else /* !TIME_WITH_SYS_TIME */
#if HAVE_SYS_TIME_H
#include <sys/time.h>
#else /* !HAVE_SYS_TIME_H */
#include <time.h>
#endif /* !HAVE_SYS_TIME_H */
#endif /* !TIME_WITH_SYS_TIME */
#include <assert.h>

#include "ipmi-sensors.h"
#include "ipmi-sensors-argp.h"
#include "ipmi-sensors-simple-output.h"
#include "ipmi-sensors-detailed-output.h"
#include "ipmi-sensors-output-common.h"
#include "ipmi-sensors-util.h"

#include "freeipmi-portability.h"
#include "pstdout.h"
#include "tool-common.h"
#include "tool-cmdline-common.h"
#include "tool-fiid-wrappers.h"
#include "tool-hostrange-common.h"
#include "tool-sdr-cache-common.h"

static int 
_sdr_repository_info (ipmi_sensors_state_data_t *state_data)
{
  fiid_obj_t obj_cmd_rs = NULL;
  uint64_t val, val1, val2;
  char str[512];
  time_t t;
  struct tm tmp;
  int rv = -1;

  assert(state_data);
  
  _FIID_OBJ_CREATE(obj_cmd_rs, tmpl_cmd_get_sdr_repository_info_rs);
  
  if (ipmi_cmd_get_sdr_repository_info (state_data->ipmi_ctx, obj_cmd_rs) != 0)
    {
      pstdout_fprintf(state_data->pstate,
                      stderr,
                      "ipmi_cmd_get_sdr_repository_info: %s\n",
                      ipmi_ctx_errormsg(state_data->ipmi_ctx));
      goto cleanup;
    }
 
  _FIID_OBJ_GET (obj_cmd_rs, "sdr_version_major", &val1);
  _FIID_OBJ_GET (obj_cmd_rs, "sdr_version_minor", &val2);
  pstdout_printf (state_data->pstate, 
                  "SDR version:                     %u.%u\n", 
                  val1, 
                  val2);

  _FIID_OBJ_GET (obj_cmd_rs, "record_count", &val);
  pstdout_printf (state_data->pstate, 
                  "SDR record count:                %u\n", 
                  val);

  _FIID_OBJ_GET (obj_cmd_rs, "free_space", &val); 
  pstdout_printf (state_data->pstate, 
                  "Free space remaining:            %u bytes\n", 
                  val);

  _FIID_OBJ_GET (obj_cmd_rs, "most_recent_addition_timestamp", &val);
  t = val;
  localtime_r (&t, &tmp);
  strftime (str, sizeof (str), "%m/%d/%Y - %H:%M:%S", &tmp);
  pstdout_printf (state_data->pstate, 
                  "Most recent addition timestamp:  %s\n", 
                  str);
  
  _FIID_OBJ_GET (obj_cmd_rs, "most_recent_erase_timestamp", &val);
  t = val;
  localtime_r (&t, &tmp);
  strftime (str, sizeof (str), "%m/%d/%Y - %H:%M:%S", &tmp);
  pstdout_printf (state_data->pstate, 
                  "Most recent erase timestamp:     %s\n", 
                  str);
  
  _FIID_OBJ_GET (obj_cmd_rs, "get_sdr_repository_allocation_info_command_supported", &val);
  pstdout_printf (state_data->pstate, 
                  "Get SDR Repository Allocation Information Command supported:         %s\n", 
                  (val ? "Yes" : "No"));

  _FIID_OBJ_GET (obj_cmd_rs, "reserve_sdr_repository_command_supported", &val);
  pstdout_printf (state_data->pstate, 
                  "Reserve SDR Repository Command supported:                            %s\n", 
                  (val ? "Yes" : "No"));

  _FIID_OBJ_GET (obj_cmd_rs, "partial_add_sdr_command_supported", &val);
  pstdout_printf (state_data->pstate, 
                  "Partial Add SDR Command supported:                                   %s\n", 
                  (val ? "Yes" : "No"));

  _FIID_OBJ_GET (obj_cmd_rs, "delete_sdr_command_supported", &val);
  pstdout_printf (state_data->pstate, 
                  "Delete SDR Command supported:                                        %s\n", 
                  (val ? "Yes" : "No"));

  _FIID_OBJ_GET (obj_cmd_rs, "modal_non_modal_sdr_repository_update_operation_supported", &val);
  pstdout_printf (state_data->pstate, 
                  "Modal/non-modal SDR Repository Update operation supported:           ");
  switch (val)
    {
    case IPMI_SDR_MODAL_NON_MODAL_REPOSITORY_UPDATE_OP_UNSPECIFIED:
      pstdout_printf (state_data->pstate, "Unspecified\n");
      break;
    case IPMI_SDR_NON_MODAL_REPOSITORY_UPDATE_OP_SUPPORTED:
      pstdout_printf (state_data->pstate, "Non-Modal\n");
      break;
    case IPMI_SDR_MODAL_REPOSITORY_UPDATE_OP_SUPPORTED:
      pstdout_printf (state_data->pstate, "Modal\n");
      break;
    case IPMI_SDR_MODAL_NON_MODAL_REPOSITORY_UPDATE_OP_SUPPORTED:
      pstdout_printf (state_data->pstate, "Both\n");
      break;
    default:
      pstdout_printf (state_data->pstate, "Unknown\n");
    }

  _FIID_OBJ_GET (obj_cmd_rs, "overflow_flag", &val);
  pstdout_printf (state_data->pstate, 
                  "SDR could not be written due to lack of space in the SDR Repository: %s\n", 
                  (val ? "Yes" : "No"));
  
  rv = 0;
cleanup:
  _FIID_OBJ_DESTROY(obj_cmd_rs);
  return (rv);
}

static int
_flush_cache (ipmi_sensors_state_data_t *state_data)
{
  assert(state_data);

  if (sdr_cache_flush_cache(state_data->ipmi_sdr_cache_ctx,
                            state_data->pstate,
                            state_data->prog_data->args->sdr.quiet_cache,
                            state_data->hostname,
                            state_data->prog_data->args->sdr.sdr_cache_directory) < 0)
    return -1;
  
  return 0;
}

static int 
_display_group (ipmi_sensors_state_data_t *state_data)
{
  int i = 0;
  char *group = NULL;
  
  assert(state_data);

  for (i = 0; ipmi_sensor_types[i]; i++)
    {
      if (!(group = strdupa (ipmi_sensor_types[i])))
        {
          pstdout_fprintf (state_data->pstate, 
                           stderr, 
                           "strdupa: %s\n", 
                           strerror(errno));
          return (-1);
        }
      str_replace_char (group, ' ', '_');
      str_replace_char (group, '/', '_');
      pstdout_printf (state_data->pstate, "%s\n", group);
    }
  if (!(group = strdupa (ipmi_oem_sensor_type)))
    {
      pstdout_fprintf (state_data->pstate, 
                       stderr, 
                       "strdupa: %s\n", 
                       strerror(errno));
      return (-1);
    }
  str_replace_char (group, ' ', '_');
  str_replace_char (group, '/', '_');
  pstdout_printf (state_data->pstate, "%s\n", group);
  
  return 0;
}

static int
_sensors_group_specified(ipmi_sensors_state_data_t *state_data,
                         uint8_t *sdr_record,
                         unsigned int sdr_record_len)
{
  const char *sdr_group_name = NULL;
  uint8_t record_type;
  uint8_t sensor_type;
  int i;

  assert(state_data);
  assert(sdr_record);
  assert(sdr_record_len);
  assert(state_data->prog_data->args->groups_wanted);

  if (sdr_cache_get_record_id_and_type(state_data->pstate,
                                       sdr_record,
                                       sdr_record_len,
                                       NULL,
                                       &record_type) < 0)
    return -1;
  
  if (record_type == IPMI_SDR_FORMAT_FULL_SENSOR_RECORD
      || record_type == IPMI_SDR_FORMAT_COMPACT_SENSOR_RECORD
      || record_type == IPMI_SDR_FORMAT_EVENT_ONLY_RECORD)
    {
      if (sdr_cache_get_sensor_type (state_data->pstate,
                                     sdr_record,
                                     sdr_record_len,
                                     &sensor_type) < 0)
        return -1;

      sdr_group_name = ipmi_get_sensor_type_string (sensor_type);
    }

  if (sdr_group_name)
    {
      char sdr_group_name_subst[IPMI_SENSORS_MAX_GROUPS_STRING_LENGTH];

      strcpy(sdr_group_name_subst, sdr_group_name);
      str_replace_char (sdr_group_name_subst, ' ', '_');
      str_replace_char (sdr_group_name_subst, '/', '_');
      
      for (i = 0; i < state_data->prog_data->args->groups_length; i++)
        {
          if ((strcasecmp (sdr_group_name, 
                           state_data->prog_data->args->groups[i]) == 0)
              || (strcasecmp (sdr_group_name_subst, 
                              state_data->prog_data->args->groups[i]) == 0))
            return 1;
        }
    }

  return 0;
}

static int
_output_sensor (ipmi_sensors_state_data_t *state_data,
                uint8_t *sdr_record,
                unsigned int sdr_record_len)
{
  double *sensor_reading = NULL;
  unsigned int sensor_event_bitmask = 0;
  uint8_t event_reading_type_code;
  int event_reading_type_code_class;
  char **event_message_list = NULL;
  unsigned int event_message_list_len = 0;
  int rv = -1;

  assert(state_data);
  assert(sdr_record);
  assert(sdr_record_len);
  
  if (ipmi_sensor_read (state_data->ipmi_sensor_read_ctx,
                        sdr_record,
                        sdr_record_len,
                        &sensor_reading,
                        &sensor_event_bitmask) < 0)
    {
      int errnum = ipmi_sensor_read_ctx_errnum(state_data->ipmi_sensor_read_ctx);
      
      if (errnum == IPMI_SENSOR_READ_CTX_ERR_SENSOR_NON_ANALOG
          || errnum == IPMI_SENSOR_READ_CTX_ERR_SENSOR_NON_LINEAR)
        {
          if (state_data->prog_data->args->common.debug)
            pstdout_fprintf(state_data->pstate,
                            stderr,
                            "Sensor reading cannot be calculated: %s\n",
                            ipmi_sensor_read_ctx_errormsg(state_data->ipmi_sensor_read_ctx));
          
          goto get_events;
        }

      if (errnum == IPMI_SENSOR_READ_CTX_ERR_SENSOR_READING_UNAVAILABLE
          || errnum == IPMI_SENSOR_READ_CTX_ERR_SENSOR_SCANNING_DISABLED
          || errnum == IPMI_SENSOR_READ_CTX_ERR_SENSOR_NON_ANALOG
          || errnum == IPMI_SENSOR_READ_CTX_ERR_SENSOR_NON_LINEAR
          || errnum == IPMI_SENSOR_READ_CTX_ERR_SENSOR_NOT_OWNED_BY_BMC
          || errnum == IPMI_SENSOR_READ_CTX_ERR_SENSOR_CANNOT_BE_BRIDGED)
        {
          if (state_data->prog_data->args->common.debug)
            pstdout_fprintf(state_data->pstate,
                            stderr,
                            "Sensor reading/event bitmask not available: %s\n",
                            ipmi_sensor_read_ctx_errormsg(state_data->ipmi_sensor_read_ctx));

          if (get_msg_message_list (state_data,
                                    &event_message_list,
                                    &event_message_list_len,
                                    IPMI_SENSORS_NA_STRING_OUTPUT) < 0)
            goto cleanup;

          goto output;
        }
      if (errnum == IPMI_SENSOR_READ_CTX_ERR_SENSOR_IS_SYSTEM_SOFTWARE
          || errnum == IPMI_SENSOR_READ_CTX_ERR_SENSOR_READING_CANNOT_BE_OBTAINED
          || errnum == IPMI_SENSOR_READ_CTX_ERR_NODE_BUSY
          || errnum == IPMI_SENSOR_READ_CTX_ERR_INVALID_SDR_RECORD_TYPE)
        {
          if (state_data->prog_data->args->common.debug)
            pstdout_fprintf(state_data->pstate,
                            stderr,
                            "Sensor reading/event_bitmask retrieval error: %s\n",
                            ipmi_sensor_read_ctx_errormsg(state_data->ipmi_sensor_read_ctx));

          /* output unknown by not setting/creating an
           * event_message_list if sensor can't be read/obtained.  For
           * an invalid SDR type, fall through to output.
           * detailed-output will output SDR information if it
           * pleases, simple-output will ignore this SDR type.
           */
          goto output;
        }

      pstdout_fprintf(state_data->pstate,
                      stderr,
                      "ipmi_sensor_read: %s\n",
                      ipmi_sensor_read_ctx_errormsg(state_data->ipmi_sensor_read_ctx));
      goto cleanup;
    }

 get_events:
  
  if (sdr_cache_get_event_reading_type_code (state_data->pstate,
                                             sdr_record,
                                             sdr_record_len,
                                             &event_reading_type_code) < 0)
    goto cleanup;

  event_reading_type_code_class = ipmi_event_reading_type_code_class (event_reading_type_code);

  if (event_reading_type_code_class == IPMI_EVENT_READING_TYPE_CODE_CLASS_THRESHOLD)
    {
      if (get_threshold_message_list (state_data,
                                      &event_message_list,
                                      &event_message_list_len,
                                      sensor_event_bitmask,
                                      IPMI_SENSORS_NO_EVENT_STRING) < 0)
        goto cleanup;
    }
  else if (event_reading_type_code_class == IPMI_EVENT_READING_TYPE_CODE_CLASS_GENERIC_DISCRETE)
    {
      if (get_generic_event_message_list (state_data,
                                          &event_message_list,
                                          &event_message_list_len,
                                          event_reading_type_code,
                                          sensor_event_bitmask,
                                          IPMI_SENSORS_NO_EVENT_STRING) < 0)
        goto cleanup;
    }
  else if (event_reading_type_code_class ==  IPMI_EVENT_READING_TYPE_CODE_CLASS_SENSOR_SPECIFIC_DISCRETE)
    {
      uint8_t sensor_type;

      if (sdr_cache_get_sensor_type (state_data->pstate,
                                     sdr_record,
                                     sdr_record_len,
                                     &sensor_type) < 0)
        goto cleanup;

      if (get_sensor_specific_event_message_list (state_data,
                                                  &event_message_list,
                                                  &event_message_list_len,
                                                  sensor_type,
                                                  sensor_event_bitmask,
                                                  IPMI_SENSORS_NO_EVENT_STRING) < 0)
        goto cleanup;
    }
  else if (event_reading_type_code_class == IPMI_EVENT_READING_TYPE_CODE_CLASS_OEM)
    {
      char *event_message = NULL;
      char **tmp_event_message_list = NULL;

      if (asprintf (&event_message,
                    "OEM Event = %04Xh",
                    (uint16_t) sensor_event_bitmask) < 0)
        {
          pstdout_perror(state_data->pstate, "asprintf");
          goto cleanup;
        }
      
      if (!(tmp_event_message_list = (char **) malloc (sizeof (char *) * 2)))
        {
          pstdout_perror(state_data->pstate, "malloc");
          goto cleanup;
        }
      
      tmp_event_message_list[0] = event_message;
      tmp_event_message_list[1] = NULL;

      event_message_list = tmp_event_message_list;
      event_message_list_len = 1;
    }
  /* else unknown event_reading_type_code, output "unknown" ultimately */

 output:  
  switch (state_data->prog_data->args->verbose_count)
    {
    case 0:
      rv = ipmi_sensors_simple_output (state_data, 
                                       sdr_record,
                                       sdr_record_len,
                                       sensor_reading,
                                       event_message_list,
                                       event_message_list_len);
      break;
    case 1:
    case 2:
    default:
      rv = ipmi_sensors_detailed_output (state_data, 
                                         sdr_record,
                                         sdr_record_len,
                                         sensor_reading,
                                         event_message_list,
                                         event_message_list_len);
      break;
    }
  
 cleanup:
  if (sensor_reading)
    free(sensor_reading);
  if (event_message_list)
    {
      int j;
      for (j = 0; j < event_message_list_len; j++)
        free(event_message_list[j]);
      free(event_message_list);
    }
  return rv;
}

static int 
_display_sensors (ipmi_sensors_state_data_t *state_data)
{
  struct ipmi_sensors_arguments *args = NULL;
  int i;
  
  assert(state_data);

  args = state_data->prog_data->args;

  if (args->sensors_wanted)
    {
      for (i = 0; i < state_data->prog_data->args->sensors_length; i++)
        {
          uint8_t sdr_record[IPMI_SDR_CACHE_MAX_SDR_RECORD_LENGTH];
          int sdr_record_len = 0;

          if (ipmi_sdr_cache_search_record_id(state_data->ipmi_sdr_cache_ctx,
                                              state_data->prog_data->args->sensors[i]) < 0)
            {
              if (ipmi_sdr_cache_ctx_errnum(state_data->ipmi_sdr_cache_ctx) == IPMI_SDR_CACHE_CTX_ERR_NOT_FOUND)
                {
                  pstdout_printf(state_data->pstate,
                                 "Sensor Record ID '%d' not found\n",
                                 state_data->prog_data->args->sensors[i]);
                  continue;
                }
              else
                {
                  pstdout_fprintf(state_data->pstate,
                                  stderr,
                                  "ipmi_sdr_cache_search_record_id: %s\n",
                                  ipmi_sdr_cache_ctx_errormsg(state_data->ipmi_sdr_cache_ctx));
                  return -1;
                }
            }
          
          if ((sdr_record_len = ipmi_sdr_cache_record_read(state_data->ipmi_sdr_cache_ctx,
                                                           sdr_record,
                                                           IPMI_SDR_CACHE_MAX_SDR_RECORD_LENGTH)) < 0)
            {
              pstdout_fprintf(state_data->pstate,
                              stderr,
                              "ipmi_sdr_cache_record_read: %s\n",
                              ipmi_sdr_cache_ctx_errormsg(state_data->ipmi_sdr_cache_ctx));
              return -1;
            }
          
          /* Shouldn't be possible */
          if (!sdr_record_len)
            continue;

          if (_output_sensor (state_data,
                              sdr_record,
                              sdr_record_len) < 0)
            return -1;
        }
    }
  else
    {
      uint16_t record_count;

      if (ipmi_sdr_cache_record_count(state_data->ipmi_sdr_cache_ctx, &record_count) < 0)
        {
          pstdout_fprintf(state_data->pstate,
                          stderr,
                          "ipmi_sdr_cache_record_count: %s\n",
                          ipmi_sdr_cache_ctx_errormsg(state_data->ipmi_sdr_cache_ctx));
          return -1;
        }
      
      for (i = 0; i < record_count; i++, ipmi_sdr_cache_next(state_data->ipmi_sdr_cache_ctx))
        {
          uint8_t sdr_record[IPMI_SDR_CACHE_MAX_SDR_RECORD_LENGTH];
          int sdr_record_len = 0;
          int ret;
          
          if ((sdr_record_len = ipmi_sdr_cache_record_read(state_data->ipmi_sdr_cache_ctx,
                                                           sdr_record,
                                                           IPMI_SDR_CACHE_MAX_SDR_RECORD_LENGTH)) < 0)
            {
              pstdout_fprintf(state_data->pstate,
                              stderr,
                              "ipmi_sdr_cache_record_read: %s\n",
                              ipmi_sdr_cache_ctx_errormsg(state_data->ipmi_sdr_cache_ctx));
              return -1;
            }
          
          /* Shouldn't be possible */
          if (!sdr_record_len)
            continue;
          
          if (args->groups_wanted)
            {
              if ((ret = _sensors_group_specified (state_data,
                                                   sdr_record,
                                                   sdr_record_len)) < 0)
                return -1;
            }
          else
            ret = 1;            /* display everything */
          
          if (ret)
            {
              if (_output_sensor (state_data,
                                  sdr_record,
                                  sdr_record_len) < 0)
                return -1;
            }
        }
    }
  
  return 0;
}

static int 
run_cmd_args (ipmi_sensors_state_data_t *state_data)
{
  struct ipmi_sensors_arguments *args;

  assert(state_data);

  args = state_data->prog_data->args;
  
  if (args->sdr_info)
    return _sdr_repository_info (state_data);
  
  if (args->sdr.flush_cache)
    return _flush_cache (state_data);
  
  if (args->list_groups)
    return _display_group (state_data);
  
  if (sdr_cache_create_and_load (state_data->ipmi_sdr_cache_ctx,
                                 state_data->pstate,
                                 state_data->ipmi_ctx,
                                 args->sdr.quiet_cache,
                                 args->sdr.sdr_cache_recreate,
                                 state_data->hostname,
                                 args->sdr.sdr_cache_directory) < 0)
    return -1;
  
  if (_display_sensors (state_data) < 0)
    return -1;

  return 0;
}

static int
_ipmi_sensors (pstdout_state_t pstate,
               const char *hostname,
               void *arg)
{
  ipmi_sensors_state_data_t state_data;
  ipmi_sensors_prog_data_t *prog_data;
  char errmsg[IPMI_OPEN_ERRMSGLEN];
  int exit_code = -1;

  prog_data = (ipmi_sensors_prog_data_t *)arg;
  memset(&state_data, '\0', sizeof(ipmi_sensors_state_data_t));
  
  state_data.prog_data = prog_data;
  state_data.pstate = pstate;
  state_data.hostname = (char *)hostname;

  /* Special case, just flush, don't do an IPMI connection */
  /* Special case, just list groups, don't do an IPMI connection */
  if (!prog_data->args->sdr.flush_cache
      && !prog_data->args->list_groups)
    {
      if (!(state_data.ipmi_ctx = ipmi_open(prog_data->progname,
                                            hostname,
                                            &(prog_data->args->common),
                                            errmsg,
                                            IPMI_OPEN_ERRMSGLEN)))
        {
          pstdout_fprintf(pstate,
                          stderr,
                          "%s\n",
                          errmsg);
          exit_code = EXIT_FAILURE;
          goto cleanup;
        }
    }      
 
  if (!(state_data.ipmi_sdr_cache_ctx = ipmi_sdr_cache_ctx_create()))
    {
      pstdout_perror (pstate, "ipmi_sdr_cache_ctx_create()");
      exit_code = EXIT_FAILURE;
      goto cleanup;
    }

  if (state_data.prog_data->args->common.debug)
    {
      /* Don't error out, if this fails we can still continue */
      if (ipmi_sdr_cache_ctx_set_flags(state_data.ipmi_sdr_cache_ctx,
                                       IPMI_SDR_CACHE_FLAGS_DEBUG_DUMP) < 0)
        pstdout_fprintf (pstate,
                         stderr,
                         "ipmi_sdr_cache_ctx_set_flags: %s\n",
                         ipmi_sdr_cache_ctx_strerror(ipmi_sdr_cache_ctx_errnum(state_data.ipmi_sdr_cache_ctx)));

      if (hostname)
        {
          if (ipmi_sdr_cache_ctx_set_debug_prefix(state_data.ipmi_sdr_cache_ctx,
                                                  hostname) < 0)
            pstdout_fprintf (pstate,
                             stderr,
                             "ipmi_sdr_cache_ctx_set_debug_prefix: %s\n",
                             ipmi_sdr_cache_ctx_strerror(ipmi_sdr_cache_ctx_errnum(state_data.ipmi_sdr_cache_ctx)));
        }
    }

  if (!(state_data.ipmi_sensor_read_ctx = ipmi_sensor_read_ctx_create(state_data.ipmi_ctx)))
    {
      pstdout_perror (pstate, "ipmi_sensor_read_ctx_create()");
      exit_code = EXIT_FAILURE;
      goto cleanup;
    }
  
  if (state_data.prog_data->args->common.debug
      || state_data.prog_data->args->bridge_sensors)
    {
      unsigned int flags = 0;

      if (state_data.prog_data->args->common.debug)
        flags |= IPMI_SENSOR_READ_FLAGS_DEBUG_DUMP;
      if (state_data.prog_data->args->bridge_sensors)
        flags |= IPMI_SENSOR_READ_FLAGS_BRIDGE_SENSORS;

      if (ipmi_sensor_read_ctx_set_flags(state_data.ipmi_sensor_read_ctx, flags) < 0)
        pstdout_fprintf (pstate,
                         stderr,
                         "ipmi_sensor_read_ctx_set_flags: %s\n",
                         ipmi_sensor_read_ctx_strerror(ipmi_sensor_read_ctx_errnum(state_data.ipmi_sensor_read_ctx)));
    }

  if (run_cmd_args (&state_data) < 0)
    {
      exit_code = EXIT_FAILURE;
      goto cleanup;
    }
  
  exit_code = 0;
 cleanup:
  if (state_data.ipmi_sdr_cache_ctx)
    ipmi_sdr_cache_ctx_destroy(state_data.ipmi_sdr_cache_ctx);
  if (state_data.ipmi_sensor_read_ctx)
    ipmi_sensor_read_ctx_destroy(state_data.ipmi_sensor_read_ctx);
  if (state_data.ipmi_ctx)
    {
      ipmi_ctx_close (state_data.ipmi_ctx);
      ipmi_ctx_destroy (state_data.ipmi_ctx);
    }
  return exit_code;
}

int 
main (int argc, char **argv)
{
  ipmi_sensors_prog_data_t prog_data;
  struct ipmi_sensors_arguments cmd_args;
  int exit_code;
  int hosts_count;
  int rv;
  
  ipmi_disable_coredump();
  
  memset(&prog_data, '\0', sizeof(ipmi_sensors_prog_data_t));
  prog_data.progname = argv[0];
  ipmi_sensors_argp_parse (argc, argv, &cmd_args);
  prog_data.args = &cmd_args;

  if ((hosts_count = pstdout_setup(&(prog_data.args->common.hostname),
                                   prog_data.args->hostrange.buffer_output,
                                   prog_data.args->hostrange.consolidate_output,
                                   prog_data.args->hostrange.fanout,
                                   prog_data.args->hostrange.eliminate,
                                   prog_data.args->hostrange.always_prefix)) < 0)
    {
      exit_code = EXIT_FAILURE;
      goto cleanup;
    }

  /* We don't want caching info to output when are doing ranged output */
  if (hosts_count > 1)
    prog_data.args->sdr.quiet_cache = 1;

  if ((rv = pstdout_launch(prog_data.args->common.hostname,
                           _ipmi_sensors,
                           &prog_data)) < 0)
    {
      fprintf(stderr,
              "pstdout_launch: %s\n",
              pstdout_strerror(pstdout_errnum));
      exit_code = EXIT_FAILURE;
      goto cleanup;
    }

  exit_code = rv;
 cleanup:
  return (exit_code);
}
