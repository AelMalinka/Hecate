/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Check.hh"

using namespace Entropy::Hecate;
using namespace std;

unsigned short Check::default_luck(ENTROPY_HECATE_DEFAULT_LUCK);

Check::Check(initializer_list<shared_ptr<Modifier>> l)
	: Check(default_luck, l)
{}

Check::Check(unsigned short &luck, initializer_list<shared_ptr<Modifier>> list)
	: _luck(luck)
{
	for(auto &m : list)
	{
		_modifiers.push_back(m);
	}
}

Check::Result::Result(const int value, const unsigned short luck, const list<shared_ptr<Modifier>> &list)
	: _value(value), _luck(luck)
{
	for(auto &m : list)
	{
		result_modifier t;

		t.current = m->Value();
		t.modifier = m;

		_modifiers.push_back(t);
	}
}

int Check::Result::Value() const
{
	return _value;
}

unsigned short Check::Result::Luck() const
{
	return _luck;
}

list<Check::Result::result_modifier>::iterator Check::Result::begin()
{
	return _modifiers.begin();
}

list<Check::Result::result_modifier>::iterator Check::Result::end()
{
	return _modifiers.end();
}
