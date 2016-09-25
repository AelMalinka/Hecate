/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Check.hh"

using namespace Entropy::Hecate;
using namespace std;

PercentType Check::default_luck(ENTROPY_HECATE_DEFAULT_LUCK);

Check::Check()
	: _modifiers(), _luck(default_luck)
{}

Check::Check(PercentType &luck)
	: _modifiers(), _luck(luck)
{}

Check::Check(const vector<Modifier> &modifiers)
	: Check()
{
	for(auto &mod : modifiers) {
		Add(mod);
	}
}

Check::Check(PercentType &luck, const vector<Modifier> &modifiers)
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

size_t Check::size() const
{
	return _modifiers.size();
}

vector<shared_ptr<Modifier>>::iterator Check::begin()
{
	return _modifiers.begin();
}

vector<shared_ptr<Modifier>>::iterator Check::end()
{
	return _modifiers.end();
}

Check::Result::Result(const PercentType value, const PercentType luck, const vector<shared_ptr<Modifier>> &vector)
	: _value(value), _luck(luck)
{
	for(auto &m : vector) {
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

PercentType Check::Result::Luck() const
{
	return _luck;
}

size_t Check::Result::size() const
{
	return _modifiers.size();
}

vector<Check::Result::result_modifier>::iterator Check::Result::begin()
{
	return _modifiers.begin();
}

vector<Check::Result::result_modifier>::iterator Check::Result::end()
{
	return _modifiers.end();
}
