/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Modifier.hh"
#include "Check.hh"

using namespace Entropy::Hecate;
using namespace std;

const detail::negative_t Entropy::Hecate::negative(-1);
const detail::negative_t Entropy::Hecate::detail::positive;

Modifier::Modifier()
	: _value(), _reason(), _negate(detail::positive)
{}

const string &Modifier::Reason() const
{
	return _reason;
}

PercentType Modifier::Value() const
{
	return _value->Value() * _negate.Multiplier();
}

PercentType &Modifier::Raw()
{
	return _value->Raw();
}

using namespace detail;

negative_t::negative_t()
	: _multiplier(1)
{}

negative_t::negative_t(const char v)
	: _multiplier(v)
{}

char negative_t::Multiplier() const
{
	return _multiplier;
}

ModifierHolder<PercentType>::ModifierHolder(PercentType &t)
	: _value(&t), _clean(false)
{}

ModifierHolder<PercentType>::ModifierHolder(PercentType &&t)
	: _value(new PercentType(t)), _clean(true)
{}

ModifierHolder<PercentType>::~ModifierHolder()
{
	if(_clean)
		delete _value;
}

PercentType ModifierHolder<PercentType>::Value() const
{
	return *_value;
}

PercentType &ModifierHolder<PercentType>::Raw()
{
	return reinterpret_cast<PercentType &>(*_value);
}

ModifierHolder<Check>::ModifierHolder(Check &v)
	: _value(&v), _clean(false)
{}

ModifierHolder<Check>::ModifierHolder(Check &&v)
	: _value(new Check(v)), _clean(true)
{}

ModifierHolder<Check>::~ModifierHolder()
{
	if(_clean)
		delete _value;
}

PercentType ModifierHolder<Check>::Value() const
{
	return (*_value)().Value();
}

PercentType &ModifierHolder<Check>::Raw()
{
	return (*_value->begin())->Raw();
}
