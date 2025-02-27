//==============================================================================
//
//  This file is part of GNSSTk, the ARL:UT GNSS Toolkit.
//
//  The GNSSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GNSSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GNSSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//
//  This software was developed by Applied Research Laboratories at the
//  University of Texas at Austin.
//  Copyright 2004-2022, The Board of Regents of The University of Texas System
//
//==============================================================================

//==============================================================================
//
//  This software was developed by Applied Research Laboratories at the
//  University of Texas at Austin, under contract to an agency or agencies
//  within the U.S. Department of Defense. The U.S. Government retains all
//  rights to use, duplicate, distribute, disclose, or release this software.
//
//  Pursuant to DoD Directive 523024
//
//  DISTRIBUTION STATEMENT A: This software has been approved for public
//                            release, distribution is unlimited.
//
//==============================================================================

/**
 * @file GNSSconstants.hpp
 * Constants as defined in the GPS-ICD-200D and by all RINEX GNSSs
 */

#ifndef GNSSTK_GPS_URA_HPP
#define GNSSTK_GPS_URA_HPP

#include "Exception.hpp"
#include "RinexSatID.hpp"
#include <cmath>

namespace gnsstk
{
      /// @ingroup GNSSEph
      //@{

      /// constant for the max array index in sv accuracy table
   const int SV_ACCURACY_GPS_MAX_INDEX_VALUE = 15;
      /// map from SV accuracy/URA flag to minimum accuracy values in m
   const double SV_ACCURACY_GPS_MIN_INDEX[] = {0.0, 2.4, 3.4, 4.85, 6.85, 9.65,
                                               13.65, 24.0, 48.0, 96.0, 192.0,
                                               384.0, 768.0, 1536.0, 3072.0,
                                               6144.0};
      /// Map from SV accuracy/URA flag to NOMINAL accuracy values in m
      /// Further details in ICD-GPS-200C, section 20.3.3.3.1.3
   const double SV_ACCURACY_GPS_NOMINAL_INDEX[] = {2.0, 2.8, 4.0, 5.7, 8.0,
                                                   11.3, 16.0, 32.0, 64.0, 128.0,
                                                   256.0, 512.0, 1024.0, 2048.0,
                                                   4096.0, 9.999999999999e99};
      /// map from SV accuracy/URA flag to maximum accuracy values in m
   const double SV_ACCURACY_GPS_MAX_INDEX[] = {2.4, 3.4, 4.85, 6.85, 9.65,
                                               13.65, 24.0, 48.0, 96.0, 192.0,
                                               384.0, 768.0, 1536.0, 3072.0,
                                               6144.0, 9.999999999999e99};
      /// constant for the max array index in sv accuracy table
   const int SV_CNAV_ACCURACY_GPS_MAX_INDEX_VALUE = 15;

      /// map from SV accuracy/URA flag to minimum accuracy values in m
   const double SV_CNAV_ACCURACY_GPS_MIN_INDEX[] = {0.0, 0.01, 0.02, 0.03, 0.04, 0.06,
                                                    0.08, 0.11, 0.15, 0.21, 0.30,
                                                    0.43, 0.60, 0.85, 1.2, 1.7,
                                                    2.4, 3.4, 4.85, 6.85, 9.65,
                                                    13.65, 24.0, 48.0, 96.0, 192.0,
                                                    384.0, 768.0, 1536.0, 3072.0,
                                                    6144.0};
      /// map for SV accuracy/Nominal URA indices
      /// Further details in
      /// IS-GPS-200 30.3.3.1.1.4
      /// IS-GPS-705 20.3.3.1.1.4
      /// IS_GPS-800 3.5.3.5
   const double SV_CNAV_ACCURACY_GPS_NOM_INDEX[] = {0.011049, 0.015625, 0.022097, 0.03125,
                                                    0.044194, 0.0625, 0.088388, 0.125, 0.176777,
                                                    0.25, 0.353553, 0.5, 0.707107, 1, 1.414214, 2,
                                                    2.8, 4, 5.7, 8, 11.3, 16, 32, 64, 128, 256, 512,
                                                    1024, 2048, 4096};
      /// constant for max array index in gps nom index table
   const int SV_CNAV_NOMINAL_MAX_INDEX = 30;

      /// constant for gps nom index table offset
   const int SV_CNAV_INDEX_OFFSET = 15;

      /// map from SV accuracy/URA flag to maximum accuracy values in m
   const double SV_CNAV_ACCURACY_GPS_MAX_INDEX[] = {0.01, 0.02, 0.03, 0.04, 0.06,
                                                    0.08, 0.11, 0.15, 0.21, 0.30,
                                                    0.43, 0.60, 0.85, 1.20, 1.7,
                                                    2.4, 3.4, 4.85, 6.85, 9.65,
                                                    13.65, 24.0, 48.0, 96.0, 192.0,
                                                    384.0, 768.0, 1536.0, 3072.0,
                                                    6144.0, 9.999999999999e99};


   inline
   short accuracy2ura(double acc) noexcept
   {
      short ura = 0;
      while ( (ura <= SV_ACCURACY_GPS_MAX_INDEX_VALUE) &&
              (acc > SV_ACCURACY_GPS_MAX_INDEX[ura]))
         ura++;
      if (ura > SV_ACCURACY_GPS_MAX_INDEX_VALUE)
         ura = SV_ACCURACY_GPS_MAX_INDEX_VALUE;
      return ura;
   }

   inline
   double ura2accuracy(short ura) noexcept
   {
      if(ura < 0)
         return SV_ACCURACY_GPS_MAX_INDEX[0];
      if(ura > SV_ACCURACY_GPS_MAX_INDEX_VALUE)
         return SV_ACCURACY_GPS_MAX_INDEX[SV_ACCURACY_GPS_MAX_INDEX_VALUE];
      return SV_ACCURACY_GPS_MAX_INDEX[ura];
   }

   inline
   short nominalAccuracy2ura(double acc) noexcept
   {
      short ura = 0;
      while ( (ura <= SV_ACCURACY_GPS_MAX_INDEX_VALUE) &&
              (acc > SV_ACCURACY_GPS_NOMINAL_INDEX[ura]))
         ura++;
      if (ura > SV_ACCURACY_GPS_MAX_INDEX_VALUE)
         ura = SV_ACCURACY_GPS_MAX_INDEX_VALUE;
      return ura;
   }

   inline
   double ura2nominalAccuracy(short ura) noexcept
   {
      if(ura < 0)
         return SV_ACCURACY_GPS_NOMINAL_INDEX[0];
      if(ura > SV_ACCURACY_GPS_MAX_INDEX_VALUE)
         return SV_ACCURACY_GPS_NOMINAL_INDEX[SV_ACCURACY_GPS_MAX_INDEX_VALUE];
      return SV_ACCURACY_GPS_NOMINAL_INDEX[ura];
   }

   inline
   short accuracy2CNAVura(double acc) noexcept
   {
      short ura = -15;
      while ( (ura <= SV_CNAV_ACCURACY_GPS_MAX_INDEX_VALUE) &&
              (acc > SV_CNAV_ACCURACY_GPS_MAX_INDEX[ura+15]))
         ura++;
      if (ura > SV_CNAV_ACCURACY_GPS_MAX_INDEX_VALUE)
         ura = SV_CNAV_ACCURACY_GPS_MAX_INDEX_VALUE;
      return ura;
   }

   inline
   double ura2CNAVaccuracy(short ura)
   {
      short ndx = ura+SV_CNAV_INDEX_OFFSET;
      if(ndx < 0 || ndx > SV_CNAV_NOMINAL_MAX_INDEX)
      {
         InvalidRequest exc("URA index out of range");
         GNSSTK_THROW(exc);
      }
      return SV_CNAV_ACCURACY_GPS_MAX_INDEX[ndx];
   }

   inline
   double ura2CNAVNominalaccuracy(short ura)
   {
      short ndx = ura+SV_CNAV_INDEX_OFFSET;
      if(ndx < 0 || ndx > SV_CNAV_NOMINAL_MAX_INDEX)
      {
         InvalidRequest exc("URA index out of range");
         GNSSTK_THROW(exc);
      }
      return SV_CNAV_ACCURACY_GPS_NOM_INDEX[ndx];
   }

      //@}

} // namespace

#endif //GNSSTK_GPS_URA_HPP
