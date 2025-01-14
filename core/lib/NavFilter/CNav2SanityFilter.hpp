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

#ifndef CNAV2SANITYFILTER_HPP
#define CNAV2SANITYFILTER_HPP

#include "NavFilter.hpp"

namespace gnsstk
{
      /// @ingroup NavFilter
      //@{

      /** Filter GPS CNAV messages with
       * 1. a bad preamble
       * 2. an invalid TOW count, or
       * 3. an invalid message ID.
       * Input data is assumed to be upright.
       *
       * @attention Processing depth = 1 epoch. */
   class CNav2SanityFilter : public NavFilter
   {
   public:
      CNav2SanityFilter();

         /** Check the TLM and HOW of GPS legacy nav messages
          * (i.e. data fields common to all subframes).
          * @pre CNavFilterData::sf is set
          * @param[in,out] msgBitsIn A list of CNavFilterData* objects
          *   containing GPS legacy navigation messages (id 2).
          * @param[out] msgBitsOut The messages successfully passing
          *   the filter. */
      virtual void validate(NavMsgList& msgBitsIn, NavMsgList& msgBitsOut);

         /// Filter stores no data, therefore this does nothing.
      virtual void finalize(NavMsgList& msgBitsOut)
      {}

         /// No internal storage of subframe data so return 0.
      virtual unsigned processingDepth() const noexcept
      { return 0; }

         /// Return the filter name.
      virtual std::string filterName() const noexcept
      { return "CNav2Sanity"; }
   };

      //@}

}

#endif // CNAV2SANITYFILTER_HPP
