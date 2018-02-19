#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <cstdint>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <fstream>
#include <functional>
#include <stdlib.h>
#include <shlobj.h>

#include "options.hpp"

#include "../utils/singleton.hpp"
#include "../utils/input.hpp"
#include "../utils/utilities.hpp"
#include "../utils/netvars.hpp"
#include "../utils/vector.hpp"

#include "interfaces/ibaseclientdll.hpp"
#include "interfaces/iclientmode.hpp"
#include "interfaces/icliententitylist.hpp"
#include "interfaces/ipanel.hpp"
#include "interfaces/isurface.hpp"
#include "interfaces/ienginetrace.hpp"
#include "interfaces/ivengineclient.hpp"
#include "interfaces/iconsole.hpp"
#include "interfaces/ivdebugoverlay.hpp"
#include "interfaces/cglobalvarsbase.hpp"
#include "interfaces/ivmodelinfo.hpp"
#include "interfaces/ivrenderview.hpp"
#include "interfaces/imaterialsystem.hpp"
#include "interfaces/ivmodelrender.hpp"

#include "classes/cusercmd.hpp"
#include "classes/studio.hpp"
#include "classes/trace.hpp"
#include "classes/convar.hpp"
#include "classes/material.hpp"
#include "classes/entities.hpp"

#include "../utils/vmt.hpp"
#include "../utils/interfaces.hpp"