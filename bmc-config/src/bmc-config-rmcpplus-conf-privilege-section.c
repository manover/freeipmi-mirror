#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#if STDC_HEADERS
#include <string.h>
#endif /* STDC_HEADERS */

#include "bmc-config.h"
#include "bmc-config-common.h"
#include "bmc-config-wrapper.h"
#include "bmc-config-diff.h"
#include "bmc-config-map.h"
#include "bmc-config-sections.h"
#include "bmc-config-validate.h"

static config_err_t
id_checkout (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     struct config_keyvalue *kv,
	     int id)
{
  uint8_t priv;
  config_err_t ret;

  if ((ret = get_rmcpplus_cipher_suite_id_privilege (state_data,
                                                     id,
                                                     &priv)) != CONFIG_ERR_SUCCESS)
    return ret;

  if (kv->value)
    free (kv->value);

  if (!(kv->value = strdup (rmcpplus_priv_string (priv))))
    {
      perror("strdup");
      return CONFIG_ERR_FATAL_ERROR;
    }

  return CONFIG_ERR_SUCCESS;
}

static config_err_t
id_commit (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv,
	   int id)
{
  return set_rmcpplus_cipher_suite_id_privilege (state_data,
						 id,
						 rmcpplus_priv_number (kv->value));
}

static config_diff_t
id_diff (bmc_config_state_data_t *state_data,
	 const struct config_section *sect,
	 const struct config_keyvalue *kv,
	 int id)
{
  uint8_t priv;
  config_err_t rc;
  config_diff_t ret;

  if ((rc = get_rmcpplus_cipher_suite_id_privilege (state_data,
                                                    id,
                                                    &priv)) != CONFIG_ERR_SUCCESS)
    {
      if (rc == CONFIG_ERR_NON_FATAL_ERROR)
        return CONFIG_DIFF_NON_FATAL_ERROR;
      return CONFIG_DIFF_FATAL_ERROR;
    }

  if (same (kv->value, rmcpplus_priv_string (priv)))
    ret = CONFIG_DIFF_SAME;
  else 
    {
      ret = CONFIG_DIFF_DIFFERENT;
      report_diff (sect->section_name,
                   kv->key_name,
                   kv->value,
                   rmcpplus_priv_string (priv));
    }
  return ret;
}

static config_err_t
id_0_checkout (bmc_config_state_data_t *state_data,
	       const struct config_section *sect,
	       struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 0);
}

static config_err_t
id_0_commit (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 0);
}

static config_diff_t
id_0_diff (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 0);
}

static config_err_t
id_1_checkout (bmc_config_state_data_t *state_data,
	       const struct config_section *sect,
	       struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 1);
}

static config_err_t
id_1_commit (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 1);
}

static config_diff_t
id_1_diff (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 1);
}


static config_err_t
id_2_checkout (bmc_config_state_data_t *state_data,
	       const struct config_section *sect,
	       struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 2);
}

static config_err_t
id_2_commit (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 2);
}

static config_diff_t
id_2_diff (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 2);
}



static config_err_t
id_3_checkout (bmc_config_state_data_t *state_data,
	       const struct config_section *sect,
	       struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 3);
}

static config_err_t
id_3_commit (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 3);
}

static config_diff_t
id_3_diff (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 3);
}

static config_err_t
id_4_checkout (bmc_config_state_data_t *state_data,
	       const struct config_section *sect,
	       struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 4);
}

static config_err_t
id_4_commit (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 4);
}

static config_diff_t
id_4_diff (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 4);
}



static config_err_t
id_5_checkout (bmc_config_state_data_t *state_data,
	       const struct config_section *sect,
	       struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 5);
}

static config_err_t
id_5_commit (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 5);
}

static config_diff_t
id_5_diff (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 5);
}

static config_err_t
id_6_checkout (bmc_config_state_data_t *state_data,
	       const struct config_section *sect,
	       struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 6);
}

static config_err_t
id_6_commit (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 6);
}

static config_diff_t
id_6_diff (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 6);
}

static config_err_t
id_7_checkout (bmc_config_state_data_t *state_data,
	       const struct config_section *sect,
	       struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 7);
}

static config_err_t
id_7_commit (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 7);
}

static config_diff_t
id_7_diff (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 7);
}


static config_err_t
id_8_checkout (bmc_config_state_data_t *state_data,
	       const struct config_section *sect,
	       struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 8);
}

static config_err_t
id_8_commit (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 8);
}

static config_diff_t
id_8_diff (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 8);
}

static config_err_t
id_9_checkout (bmc_config_state_data_t *state_data,
	       const struct config_section *sect,
	       struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 9);
}

static config_err_t
id_9_commit (bmc_config_state_data_t *state_data,
	     const struct config_section *sect,
	     const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 9);
}

static config_diff_t
id_9_diff (bmc_config_state_data_t *state_data,
	   const struct config_section *sect,
	   const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 9);
}

static config_err_t
id_10_checkout (bmc_config_state_data_t *state_data,
		const struct config_section *sect,
		struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 10);
}

static config_err_t
id_10_commit (bmc_config_state_data_t *state_data,
	      const struct config_section *sect,
	      const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 10);
}

static config_diff_t
id_10_diff (bmc_config_state_data_t *state_data,
	    const struct config_section *sect,
	    const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 10);
}

static config_err_t
id_11_checkout (bmc_config_state_data_t *state_data,
		const struct config_section *sect,
		struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 11);
}

static config_err_t
id_11_commit (bmc_config_state_data_t *state_data,
	      const struct config_section *sect,
	      const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 11);
}

static config_diff_t
id_11_diff (bmc_config_state_data_t *state_data,
	    const struct config_section *sect,
	    const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 11);
}

static config_err_t
id_12_checkout (bmc_config_state_data_t *state_data,
		const struct config_section *sect,
		struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 12);
}

static config_err_t
id_12_commit (bmc_config_state_data_t *state_data,
	      const struct config_section *sect,
	      const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 12);
}

static config_diff_t
id_12_diff (bmc_config_state_data_t *state_data,
	    const struct config_section *sect,
	    const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 12);
}

static config_err_t
id_13_checkout (bmc_config_state_data_t *state_data,
		const struct config_section *sect,
		struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 13);
}

static config_err_t
id_13_commit (bmc_config_state_data_t *state_data,
	      const struct config_section *sect,
	      const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 13);
}

static config_diff_t
id_13_diff (bmc_config_state_data_t *state_data,
	    const struct config_section *sect,
	    const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 13);
}

static config_err_t
id_14_checkout (bmc_config_state_data_t *state_data,
		const struct config_section *sect,
		struct config_keyvalue *kv)
{
  return id_checkout (state_data, sect, kv, 14);
}

static config_err_t
id_14_commit (bmc_config_state_data_t *state_data,
	      const struct config_section *sect,
	      const struct config_keyvalue *kv)
{
  return id_commit (state_data, sect, kv, 14);
}

static config_diff_t
id_14_diff (bmc_config_state_data_t *state_data,
	    const struct config_section *sect,
	    const struct config_keyvalue *kv)
{
  return id_diff (state_data, sect, kv, 14);
}

struct config_section *
bmc_config_rmcpplus_conf_privilege_section_get (bmc_config_state_data_t *state_data)
{
  struct config_section *rmcpplus_conf_privilege_section = NULL;
  char *section_comment = 
    "If your system supports IPMI 2.0 and Serial-over-LAN (SOL),"
    "cipher suite IDs may be configurable below.  In the "
    "Rmcpplus_Conf_Privilege section, maximum user privilege levels "
    "allowed for authentication under IPMI 2.0 (including Serial-over-LAN) "
    "are set for each supported cipher suite ID.  Each cipher suite ID "
    "supports different sets of authentication, integrity, and encryption "
    "algorithms for IPMI 2.0.  Typically, the highest privilege level any "
    "username configured should set for support under a cipher suite ID. "
    "This is typically \"Administrator\".";

  if (!(rmcpplus_conf_privilege_section = bmc_config_section_create (state_data, 
                                                                     "Rmcpplus_Conf_Privilege",
                                                                     "Rmcpplus_Conf_Privilege",
                                                                     section_comment,
                                                                     0)))
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_0",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_0_checkout,
                                       id_0_commit,
                                       id_0_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_1",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_1_checkout,
                                       id_1_commit,
                                       id_1_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_2",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_2_checkout,
                                       id_2_commit,
                                       id_2_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_3",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_3_checkout,
                                       id_3_commit,
                                       id_3_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_4",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_4_checkout,
                                       id_4_commit,
                                       id_4_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_5",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_5_checkout,
                                       id_5_commit,
                                       id_5_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_6",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_6_checkout,
                                       id_6_commit,
                                       id_6_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_7",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_7_checkout,
                                       id_7_commit,
                                       id_7_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_8",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_8_checkout,
                                       id_8_commit,
                                       id_8_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_9",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_9_checkout,
                                       id_9_commit,
                                       id_9_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_10",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_10_checkout,
                                       id_10_commit,
                                       id_10_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_11",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_11_checkout,
                                       id_11_commit,
                                       id_11_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_12",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_12_checkout,
                                       id_12_commit,
                                       id_12_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_13",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_13_checkout,
                                       id_13_commit,
                                       id_13_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  if (bmc_config_section_add_keyvalue (state_data,
                                       rmcpplus_conf_privilege_section,
                                       "Maximum_Privilege_Cipher_Suite_Id_14",
                                       "Possible values: Unused/User/Operator/Administrator/OEM_Proprietary",
                                       0,
                                       id_14_checkout,
                                       id_14_commit,
                                       id_14_diff,
                                       rmcpplus_priv_number_validate) < 0)
    goto cleanup;

  return rmcpplus_conf_privilege_section;

 cleanup:
  if (rmcpplus_conf_privilege_section)
    bmc_config_section_destroy (state_data, rmcpplus_conf_privilege_section);
  return NULL;
}

