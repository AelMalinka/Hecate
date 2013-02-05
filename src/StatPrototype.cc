/*	Copyright 2012 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "StatPrototype.hh"

#include <utility>

using namespace std;
using namespace Entropy::Hecate;

set<string> StatPrototype::_protos;

StatPrototype::StatPrototype(const string &name)
	: _name(nullptr)
{
	for(auto i = _protos.cbegin(); i != _protos.cend(); i++)
	{
		if(*i == name)
		{
			_name = &*i;
			break;
		}
	}

	if(_name == nullptr)
		ENTROPY_THROW(InvalidStatPrototype() << StatName(name));
}

StatPrototype::~StatPrototype() = default;

bool StatPrototype::operator == (const StatPrototype &o) const
{
	return _name == o._name;
}

bool StatPrototype::operator == (const string &o) const
{
	if(_name == nullptr) return false;
	return *_name == o;
}

StatPrototype::operator string() const
{
	return Value();
}

const string &StatPrototype::Value() const
{
	if(_name == nullptr) ENTROPY_THROW(InvalidStatPrototype() << StatName("(nullptr)"));;
	return *_name;
}

StatPrototype &&StatPrototype::create(const string &name)
{
	_protos.insert(name);
	StatPrototype t(name);
	return move(t);
}

void StatPrototype::clear()
{
	_protos.clear();
}
