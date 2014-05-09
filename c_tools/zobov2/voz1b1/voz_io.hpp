/*+
    VIDE -- Void IDentification and Examination -- ./c_tools/zobov2/voz1b1/voz_io.hpp
    Copyright (C) 2010-2014 Guilhem Lavaux
    Copyright (C) 2011-2014 P. M. Sutter

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
+*/
#ifndef __VOZ_IO_HPP
#define __VOZ_IO_HPP

#include <string>

struct PositionData
{
  float *xyz[3];
  pid_t np;
  float xyz_min[3], xyz_max[3];
  float V0;

  void destroy()
  {
    for (int j = 0; j < 3; j++)
      delete[] xyz[j];
  }

  void findExtrema();

  bool readFrom(const std::string& fname);
};

#endif
