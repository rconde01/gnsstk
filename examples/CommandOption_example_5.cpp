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
#include <iostream>
#include <fstream>
#include <BasicFramework.hpp>
#include <StringUtils.hpp>
#include <CommandOptionWithCommonTimeArg.hpp>
#include <TimeString.hpp>

using namespace std;
using namespace gnsstk;

// Given that Doxygen removes Doxygen comments when rendering
// examples, please do not consider the absence of comments in the
// HTML rendering to be representative.  Refer to the file in the
// depot instead.

// Interesting examples:
// CommandOption5
// CommandOption5 --scream
// CommandOption5 --hush
// CommandOption5 -x
// CommandOption5 -xxxxyyz
// CommandOption5 -xxxxyyz --hush

/// Example of using CommandOptionNOf in an application.
class CommandOption5Example : public BasicFramework
{
public:
      /// Initialize command-line arguments
   CommandOption5Example(const string& applName);
      /// Process command-line arguments
   bool initialize(int argc, char *argv[], bool pretty = true) noexcept override;
      /// Do the processing.
   void process() override;
      /// Clean up.
   void shutDown() override;
      /// generic option x
   CommandOptionNoArg xOpt;
      /// generic option y
   CommandOptionNoArg yOpt;
      /// generic option z
   CommandOptionNoArg zOpt;
      /// Virtual option that is "set" if x y or z are in use
   CommandOptionGroupOr xyzOpts;

      /// Option for demonstrating CommandOptionOneOf
   CommandOptionNoArg screamOpt;
      /// Option for demonstrating CommandOptionOneOf
   CommandOptionNoArg hushOpt;
      /// Make sure only one of hushOpt or screamOpt are used
   CommandOptionMutex hushOrScreamOpt;
      /// Make sure that if xyz options are used, hush is specified
   CommandOptionDependent hushAndXYZOpt;
};


CommandOption5Example ::
CommandOption5Example(const string& applName)
      : BasicFramework(applName, "Example application for CommandOption"),
        xOpt('x', "", "you say you want an x"),
        yOpt('y', "", "you say you want an y"),
        zOpt('z', "", "you say you want an z"),
        screamOpt(0, "scream", "print a message very loudly"),
        hushOpt(0, "hush", "don't print a message very loudly"),
        hushAndXYZOpt(&xyzOpts, &hushOpt)
{
      // One of these options must be used if hush is used
   xyzOpts.addOption(&xOpt);
   xyzOpts.addOption(&yOpt);
   xyzOpts.addOption(&zOpt);
      // Only one of these options may be specified.
   hushOrScreamOpt.addOption(&screamOpt);
   hushOrScreamOpt.addOption(&hushOpt);
}


bool CommandOption5Example ::
initialize(int argc, char *argv[], bool pretty) noexcept
{
   if (!BasicFramework::initialize(argc, argv, pretty))
      return false;
   if (screamOpt)
   {
      cout << "HELLO WORLD x" << screamOpt.getCount() << endl;
   }
   if (hushOpt)
   {
      cout << "ok i'll be quiet x" << hushOpt.getCount() << endl;
   }
      // whichOne returns the option that was used
   CommandOption *which = hushOrScreamOpt.whichOne();
   if (which != nullptr)
   {
      cout << "You used " << which->getFullOptionString() << endl;
   }
   cout << "You specified x,y, and/or z a total of " << xyzOpts.getCount()
        << " times" << endl;
   return true;
}


void CommandOption5Example ::
process()
{
   cout << "Nothing to do" << endl;
}


void CommandOption5Example ::
shutDown()
{
   cout << "Shutting down" << endl;
}


int main(int argc, char *argv[])
{
   try
   {
      CommandOption5Example app(argv[0]);
      if (app.initialize(argc, argv))
      {
         app.run();
      }
      return app.exitCode;
   }
   catch (gnsstk::Exception& e)
   {
      cerr << e << endl;
   }
   catch (std::exception& e)
   {
      cerr << e.what() << endl;
   }
   catch (...)
   {
      cerr << "Caught unknown exception" << endl;
   }
   return gnsstk::BasicFramework::EXCEPTION_ERROR;
}
