/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Check.hh"

using namespace Entropy::Hecate;
using namespace std;

Check::Check(initializer_list<shared_ptr<Modifier>> l)
{
	for(auto &m : l)
	{
		_modifiers.push_back(m);
	}
}

Check::Result::Result(const int v, const list<shared_ptr<Modifier>> &l)
	: _value(v)
{
	for(auto &m : l)
	{
		result_modifier t;

		t.current = m->Value();
		t.modifier = m;

		_modifiers.push_back(t);
	}
}

const int &Check::Result::Value() const
{
	return _value;
}

list<Check::Result::result_modifier>::iterator Check::Result::begin()
{
	return _modifiers.begin();
}

list<Check::Result::result_modifier>::iterator Check::Result::end()
{
	return _modifiers.end();
}
