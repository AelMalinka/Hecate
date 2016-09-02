/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Check.hh"

using namespace Entropy::Hecate;
using namespace std;

Percent Check::default_luck(ENTROPY_HECATE_DEFAULT_LUCK);

Check::Check()
	: _modifiers(), _luck(default_luck)
{}

Check::Check(Percent &luck)
	: _modifiers(), _luck(luck)
{}

Check::Check(const vector<Modifier> &modifiers)
	: Check()
{
	for(auto &mod : modifiers) {
		Add(mod);
	}
}

Check::Check(Percent &luck, const vector<Modifier> &modifiers)
	: Check(luck)
{
	for(auto &mod : modifiers) {
		Add(mod);
	}
}

Check &Check::Add(const shared_ptr<Modifier> &mod)
{
	_modifiers.push_back(mod);

	return *this;
}

Check &Check::Add(const Modifier &mod)
{
	_modifiers.push_back(make_shared<Modifier>(mod));

	return *this;
}

Check::Result::Result(const ModifierType value, const Percent luck, const list<shared_ptr<Modifier>> &list)
	: _value(value), _luck(luck)
{
	for(auto &m : list) {
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

Percent Check::Result::Luck() const
{
	return _luck;
}

size_t Check::Result::size() const
{
	return _modifiers.size();
}

list<Check::Result::result_modifier>::iterator Check::Result::begin()
{
	return _modifiers.begin();
}

list<Check::Result::result_modifier>::iterator Check::Result::end()
{
	return _modifiers.end();
}
