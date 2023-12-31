/* Return second macro parameter.
   Copyright (C) 2005, 2014 Red Hat, Inc.
   This file is part of elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 2005.

   This file is free software; you can redistribute it and/or modify
   it under the terms of either

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version

   or both in parallel, as here.

   elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "libdwP.h"


int
dwarf_macro_param2 (Dwarf_Macro *macro, Dwarf_Word *paramp, const char **strp)
{
  if (macro == NULL)
    return -1;

  Dwarf_Attribute param;
  if (dwarf_macro_param (macro, 1, &param) != 0)
    return -1;

  switch (param.form)
    {
      /* String forms allowed by libdw_valid_user_form.  */
      case DW_FORM_line_strp:
      case DW_FORM_string:
      case DW_FORM_strp:
      case DW_FORM_strp_sup:
      case DW_FORM_strx:
      case DW_FORM_strx1:
      case DW_FORM_strx2:
      case DW_FORM_strx3:
      case DW_FORM_strx4:
	*strp = dwarf_formstring (&param);
	return 0;
      default:
	return dwarf_formudata (&param, paramp);
    }
}
