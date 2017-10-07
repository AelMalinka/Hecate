// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Headers for CppUnitTest
#include "CppUnitTest.h"

#ifndef HAVE___ATTRIBUTE__
#	define __attribute__(x)
#endif

#include <random>
#include "pcg_random.hpp"

#include <Entropy/Hecate/Stat.hh>
#include <Entropy/Hecate/Skill.hh>
#include <Entropy/Hecate/Template.hh>
#include <Entropy/Hecate/Trait.hh>
#include <Entropy/Hecate/Resource.hh>
#include <Entropy/Hecate/Character.hh>
#include <Entropy/Hecate/Check.hh>
#include <Entropy/Hecate/Event.hh>