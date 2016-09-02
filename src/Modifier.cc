/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Modifier.hh"

using namespace Entropy::Hecate;
using namespace std;

const detail::negative_t Entropy::Hecate::negative(-1);
const detail::negative_t Entropy::Hecate::detail::positive(1);

const string &Modifier::Reason() const
{
	return _reason;
}

ModifierType Modifier::Value() const
{
	return _value->Value() * _negate.multiplier;
}

ModifierType &Modifier::Raw()
{
	return _value->Raw();
}

using namespace detail;

negative_t::negative_t(const char v)
	: multiplier(v)
{}

ModifierHolder<ModifierType>::ModifierHolder(ModifierType &t)
	: _value(&t), _clean(false)
{}

ModifierHolder<ModifierType>::ModifierHolder(ModifierType &&t)
	: _value(new ModifierType(t)), _clean(true)
{}

ModifierHolder<ModifierType>::~ModifierHolder()
{
	if(_clean)
		delete _value;
}

ModifierType ModifierHolder<ModifierType>::Value() const
{
	return *_value;
}

ModifierType &ModifierHolder<ModifierType>::Raw()
{
	return *_value;
}

ModifierHolder<Percent>::ModifierHolder(Percent &t)
	: _value(&t), _clean(false)
{}

ModifierHolder<Percent>::ModifierHolder(Percent &&t)
	: _value(new Percent(t)), _clean(true)
{}

ModifierHolder<Percent>::~ModifierHolder()
{
	if(_clean)
		delete _value;
}

ModifierType ModifierHolder<Percent>::Value() const
{
	return *_value;
}

ModifierType &ModifierHolder<Percent>::Raw()
{
	return reinterpret_cast<ModifierType &>(*_value);
}
