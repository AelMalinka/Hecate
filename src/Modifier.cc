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

ModifierType ModifierHolder<PercentType>::Value() const
{
	return *_value;
}

ModifierType &ModifierHolder<PercentType>::Raw()
{
	return reinterpret_cast<ModifierType &>(*_value);
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

ModifierType ModifierHolder<Check>::Value() const
{
	return (*_value)().Value();
}

ModifierType &ModifierHolder<Check>::Raw()
{
	return (*_value->begin())->Raw();
}
