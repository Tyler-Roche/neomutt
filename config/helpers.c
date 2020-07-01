/**
 * @file
 * Helper functions to get config values
 *
 * @authors
 * Copyright (C) 2020 Richard Russon <rich@flatcap.org>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @page config_helpers Helper functions to get config values
 *
 * Helper functions to get config values
 */

#include "config.h"
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "mutt/lib.h"
#include "quad.h"
#include "subset.h"
#include "types.h"

/**
 * cs_subset_address - Get an Address config item by name
 * @param sub   Config Subset
 * @param name  Name of config item
 * @retval ptr  Address
 * @retval NULL Empty address, or error
 */
const struct Address *cs_subset_address(const struct ConfigSubset *sub, const char *name)
{
  if (!sub || !name)
    return NULL;

  struct HashElem *he = cs_subset_create_inheritance(sub, name);
  if (!he)
    return NULL;

  if (DTYPE(he->type) != DT_ADDRESS)
    return NULL;

  intptr_t value = cs_subset_he_native_get(sub, he, NULL);
  if (value == INT_MIN)
    return NULL;

  return (const struct Address *) value;
}

/**
 * cs_subset_bool - Get a boolean config item by name
 * @param sub   Config Subset
 * @param name  Name of config item
 * @retval bool  Boolean
 * @retval false Error
 */
bool cs_subset_bool(const struct ConfigSubset *sub, const char *name)
{
  if (!sub || !name)
    return false;

  struct HashElem *he = cs_subset_create_inheritance(sub, name);
  if (!he)
    return false;

  if (DTYPE(he->type) != DT_BOOL)
    return false;

  intptr_t value = cs_subset_he_native_get(sub, he, false);
  if (value == INT_MIN)
    return false;

  return (bool) value;
}

/**
 * cs_subset_long - Get a long config item by name
 * @param sub   Config Subset
 * @param name  Name of config item
 * @retval num Long value
 * @retval 0   Error
 */
long cs_subset_long(const struct ConfigSubset *sub, const char *name)
{
  if (!sub || !name)
    return 0;

  struct HashElem *he = cs_subset_create_inheritance(sub, name);
  if (!he)
    return 0;

  if (DTYPE(he->type) != DT_LONG)
    return 0;

  intptr_t value = cs_subset_he_native_get(sub, he, 0);
  if (value == INT_MIN)
    return 0;

  return (long) value;
}

/**
 * cs_subset_number - Get a number config item by name
 * @param sub   Config Subset
 * @param name  Name of config item
 * @retval num Number
 * @retval 0   Error
 */
short cs_subset_number(const struct ConfigSubset *sub, const char *name)
{
  if (!sub || !name)
    return 0;

  struct HashElem *he = cs_subset_create_inheritance(sub, name);
  if (!he)
    return 0;

  if (DTYPE(he->type) != DT_NUMBER)
    return 0;

  intptr_t value = cs_subset_he_native_get(sub, he, 0);
  if (value == INT_MIN)
    return 0;

  return (short) value;
}

/**
 * cs_subset_quad - Get a quad-value config item by name
 * @param sub   Config Subset
 * @param name  Name of config item
 * @retval num Quad-value
 * @retval 0   Error
 */
enum QuadOption cs_subset_quad(const struct ConfigSubset *sub, const char *name)
{
  if (!sub || !name)
    return MUTT_ABORT;

  struct HashElem *he = cs_subset_create_inheritance(sub, name);
  if (!he)
    return MUTT_ABORT;

  if (DTYPE(he->type) != DT_QUAD)
    return MUTT_ABORT;

  intptr_t value = cs_subset_he_native_get(sub, he, NULL);
  if (value == INT_MIN)
    return MUTT_ABORT;

  return (enum QuadOption) value;
}

/**
 * cs_subset_regex - Get a regex config item by name
 * @param sub   Config Subset
 * @param name  Name of config item
 * @retval ptr  Regex
 * @retval NULL Empty regex, or error
 */
const struct Regex *cs_subset_regex(const struct ConfigSubset *sub, const char *name)
{
  if (!sub || !name)
    return NULL;

  struct HashElem *he = cs_subset_create_inheritance(sub, name);
  if (!he)
    return NULL;

  if (DTYPE(he->type) != DT_REGEX)
    return NULL;

  intptr_t value = cs_subset_he_native_get(sub, he, NULL);
  if (value == INT_MIN)
    return NULL;

  return (const struct Regex *) value;
}

/**
 * cs_subset_slist - Get a string-list config item by name
 * @param sub   Config Subset
 * @param name  Name of config item
 * @retval ptr  String list
 * @retval NULL Empty string list, or error
 */
const struct Slist *cs_subset_slist(const struct ConfigSubset *sub, const char *name)
{
  if (!sub || !name)
    return NULL;

  struct HashElem *he = cs_subset_create_inheritance(sub, name);
  if (!he)
    return NULL;

  if (DTYPE(he->type) != DT_SLIST)
    return NULL;

  intptr_t value = cs_subset_he_native_get(sub, he, NULL);
  if (value == INT_MIN)
    return NULL;

  return (const struct Slist *) value;
}

/**
 * cs_subset_string - Get a string config item by name
 * @param sub   Config Subset
 * @param name  Name of config item
 * @retval ptr  String
 * @retval NULL Empty string, or error
 */
const char *cs_subset_string(const struct ConfigSubset *sub, const char *name)
{
  if (!sub || !name)
    return NULL;

  struct HashElem *he = cs_subset_create_inheritance(sub, name);
  if (!he)
    return NULL;

  if (DTYPE(he->type) != DT_STRING)
    return NULL;

  intptr_t value = cs_subset_he_native_get(sub, he, NULL);
  if (value == INT_MIN)
    return NULL;

  return (const char *) value;
}
