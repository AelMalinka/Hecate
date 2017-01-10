/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Percent.hh"

using namespace Entropy::Hecate;
using namespace std;

Percent::Percent()
	: _value(0), _modifiers()
{}

Percent::Percent(const PercentType v)
	: _value(v)
{}

Percent::~Percent() = default;

void Percent::Add(const Modifier &mod)
{
	_modifiers.Add(mod);
}

ModifierList &Percent::Modifiers()
{
	return _modifiers;
}

const ModifierList &Percent::Modifiers() const
{
	return _modifiers;
}

PercentType Percent::Value() const
{
	return _value + _modifiers.Value();
}

PercentType &Percent::Raw()
{
	return _value;
}

const PercentType &Percent::Raw() const
{
	return _value;
}
