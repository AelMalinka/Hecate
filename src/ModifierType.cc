/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "ModifierType.hh"

using namespace std;
using namespace Entropy::Hecate;

size_t ModifierType::_next(1);

ModifierType::ModifierType(const bool stacking, const size_t type)
	: _type((type != 0) ? type : _next++), _stacking(stacking)
{}

bool ModifierType::Stacking() const
{
	return _stacking;
}

bool ModifierType::operator == (const ModifierType &o) const
{
	return _type == o._type;
}

bool ModifierType::operator != (const ModifierType &o) const
{
	return _type != o._type;
}

bool ModifierType::operator < (const ModifierType &o) const
{
	return _type < o._type;
}

namespace Entropy { namespace Hecate {
	const ModifierType Untyped(true);
}}
