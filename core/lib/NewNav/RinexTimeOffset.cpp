//==============================================================================
//
//  This file is part of GNSSTk, the GNSS Toolkit.
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
//  Copyright 2004-2021, The Board of Regents of The University of Texas System
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

#include "RinexTimeOffset.hpp"
#include "TimeString.hpp"

using namespace std;

namespace gnsstk
{
   RinexTimeOffset ::
   RinexTimeOffset()
         : deltatLS(0)
   {
   }


   RinexTimeOffset ::
   RinexTimeOffset(const TimeSystemCorrection& right, double leapSec)
         : TimeSystemCorrection(right), deltatLS(leapSec)
   {
   }


   bool RinexTimeOffset ::
   validate() const
   {
         /// @todo implement some validation
      return true;
   }


   CommonTime RinexTimeOffset ::
   getUserTime() const
   {
         /// @todo figure out a sensible value, if there is one.
      return TimeOffsetData::getUserTime();
   }


   void RinexTimeOffset ::
   dump(ostream& s, DumpDetail dl) const
   {
      const ios::fmtflags oldFlags = s.flags();
      NavData::dump(s,dl);
      double offset;
      switch (dl)
      {
         case DumpDetail::OneLine:
            break;
         case DumpDetail::Brief:
               // brief just shows the offset as of the reference time.
            s << StringUtils::asString(frTS) << "-"
              << StringUtils::asString(toTS) << " offset = " << (deltatLS+A0)
              << endl;
            break;
         case DumpDetail::Full:
            s << setprecision(16)
              << "  src system = " << StringUtils::asString(frTS) << endl
              << "  tgt system = " << StringUtils::asString(toTS) << endl
              << "  A0         = " << A0 << endl
              << "  A1         = " << A1 << endl
              << "  delta tLS  = " << deltatLS << endl
              << "  ref time   = "
              << printTime(refTime, "%Y/%02m/%02d %02H:%02M:%02S") << endl
              << "  provider   = " << geoProvider << endl
              << "  UTC        = ";
            switch (geoUTCid)
            {
               case 0: s << "Unknown" << endl; break;
               case 1: s << "NIST" << endl; break;
               case 2: s << "USNO" << endl; break;
               case 3: s << "SU" << endl; break;
               case 4: s << "BIPM" << endl; break;
               case 5: s << "Europe" << endl; break;
               case 6: s << "CRL" << endl; break;
               default: s << geoUTCid << "=???" << endl; break;
            }
            break;
      }
      s.flags(oldFlags);
   }


   bool RinexTimeOffset ::
   getOffset(TimeSystem fromSys, TimeSystem toSys,
             const CommonTime& when, double& offset)
      const
   {
      try
      {
            // TimeSystemCorrection::Correction assumes the source
            // time system is defined in the refTime value and the
            // target is defined in "when".
         offset = deltatLS + Correction(when);
         return true;
      }
      catch (gnsstk::Exception& exc)
      {
         cerr << exc << endl;
         return false;
      }
   }


   TimeCvtSet RinexTimeOffset ::
   getConversions() const
   {
      TimeCvtKey keyF(frTS,toTS);
      TimeCvtKey keyR(toTS,frTS);
      return TimeCvtSet({ keyF, keyR });
   }

} // namespace gnsstk