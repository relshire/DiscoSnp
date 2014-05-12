/*****************************************************************************
 *   GATB : Genome Assembly Tool Box
 *   Copyright (C) 2014  INRIA
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef _TOOL_KISSNP2_HPP_
#define _TOOL_KISSNP2_HPP_

/********************************************************************************/
#include <gatb/gatb_core.hpp>
/********************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
class Kissnp2 : public Tool
{
public:

    // Constructor
    Kissnp2 ();

    // Actual job done by the tool is here
    void execute ();
};

/********************************************************************************/

#endif /* _TOOL_KISSNP2_HPP_ */
