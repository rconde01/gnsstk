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
#include "BDSD2NavData.hpp"
#include "TestUtil.hpp"

/// Make a non-abstract child class of BDSD2NavData for testing
class TestClass : public gnsstk::BDSD2NavData
{
public:
   gnsstk::CommonTime getUserTime() const override
   { return gnsstk::CommonTime::BEGINNING_OF_TIME; }
   gnsstk::NavDataPtr clone() const override
   { return std::make_shared<TestClass>(*this); }
};


class BDSD2NavData_T
{
public:
      /// Make sure constructor behavior remains unchanged.
   unsigned constructorTest();
   unsigned validateTest();
};


unsigned BDSD2NavData_T ::
constructorTest()
{
   TUDEF("BDSD2NavData", "BDSD2NavData");
   TestClass obj;
   TUASSERTE(uint32_t, 0, obj.pre);
   TUASSERTE(uint32_t, 0, obj.rev);
   TUASSERTE(uint8_t, 0, obj.fraID);
   TUASSERTE(uint32_t, 0, obj.sow);
   TURETURN();
}


unsigned BDSD2NavData_T ::
validateTest()
{
   TUDEF("BDSD2NavData", "validate");
   TestClass obj;
   obj.fraID = 1;
   TUASSERTE(bool, true, obj.validate());
   obj.pre = 0x22c; // no this is not valid
   TUASSERTE(bool, false, obj.validate());
   obj.pre = 0x712; // this is
   TUASSERTE(bool, true, obj.validate());
   obj.fraID = 0;
   TUASSERTE(bool, false, obj.validate());
   obj.fraID = 6;
   TUASSERTE(bool, false, obj.validate());
   TURETURN();
}


int main()
{
   BDSD2NavData_T testClass;
   unsigned errorTotal = 0;

   errorTotal += testClass.constructorTest();
   errorTotal += testClass.validateTest();

   std::cout << "Total Failures for " << __FILE__ << ": " << errorTotal
             << std::endl;

   return errorTotal;
}
