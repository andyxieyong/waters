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
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

#include <factory.hpp>
#include <simul.hpp>
#include <strtoken.hpp>

#include <cpu.hpp>
#include <memory_instr.hpp>
#include <task.hpp>

namespace RTSim {

    using namespace MetaSim;
    using namespace std;
    using namespace parse_util;


WriteInstr::WriteInstr(Task *t, Tick duration, char *n)  : FixedInstr(t, 9*5, n)
{}

Instr *WriteInstr::createInstance(vector<string> &par)
{
    Task *task = dynamic_cast<Task *>(Entity::_find(par[1]));
    return new WriteInstr(task, atoi(par[0].c_str()));
}

ReadInstr::ReadInstr(Task *t, Tick duration, char *n)  : FixedInstr(t, 9*5, n)
{}

Instr *ReadInstr::createInstance(vector<string> &par)
{
    Task *task = dynamic_cast<Task *>(Entity::_find(par[1]));
    return new ReadInstr(task, atoi(par[0].c_str()));
}

}
