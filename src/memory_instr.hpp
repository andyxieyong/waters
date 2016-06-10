/***************************************************************************
    begin                : Thu Apr 24 15:54:58 CEST 2003
    copyright            : (C) 2003 by Giuseppe Lipari
    email                : lipari@sssup.it
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/*
 * $Id: exeinstr.hpp,v 1.7 2005/10/05 16:46:22 cesare Exp $
 *
 * $Log: exeinstr.hpp,v $
 * Revision 1.7  2005/10/05 16:46:22  cesare
 * Added DLL support.
 *
 * Revision 1.6  2005/04/28 01:34:47  cesare
 * Moved to sstream. Headers install. Code cleaning.
 *
 * Revision 1.5  2004/11/26 03:47:10  cesare
 * Finished merging the main trunk with Lipari's branch.
 *
 */
#ifndef __MEMORYINSTR_HPP__
#define __MEMORYINSTR_HPP__

#include <memory>

//From metasim
#include <debugstream.hpp>
#include <event.hpp>
#include <randomvar.hpp>
#include <simul.hpp>

//From RTLIB
#include <instr.hpp>
#include <exeinstr.hpp>

namespace RTSim {

  using namespace std;
  using namespace MetaSim;

  /**
      \ingroup instr

      These instructions (ExecInstr & FixedInstr) are used to model a
      basic block of time-consuming computation, and are the basic
      building block of a real task

      @author Luigi Palopoli, Giuseppe Lipari, Gerardo Lamastra, Antonio Casile
      @version 2.0
      @see Instr */

class ReadInstr : public FixedInstr {
public:
    ReadInstr(Task *t, Tick duration, char *n = "");
    static Instr *createInstance(vector<string> &par);
};
class WriteInstr : public FixedInstr {
public:
    WriteInstr(Task *t, Tick duration, char *n = "") ;
    static Instr *createInstance(vector<string> &par);
};
} // namespace RTSim

#endif
