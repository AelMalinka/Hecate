/*	Michael Thomas (malinka) <AelMalinka@gmail.com>
	2012-12-14
*/

#include "Percentage.hh"

using namespace Entropy::Hecate;

Percentage::Percentage()
	: _val(0)
{}

Percentage::Percentage(const Percentage &) = default;
Percentage::Percentage(Percentage &&) = default;
Percentage::~Percentage() = default;
Percentage &Percentage::operator = (const Percentage &) = default;

Percentage::Percentage(const short &o)
	: _val(o)
{}

bool Percentage::operator < (const Percentage &o) const
{
	return _val < o._val;
}

bool Percentage::operator == (const Percentage &o) const
{
	return _val == o._val;
}

Percentage &Percentage::operator ++()
{
	++_val;
	return *this;
}

Percentage &Percentage::operator --()
{
	--_val;
	return *this;
}

Percentage &Percentage::operator +=(const Percentage &o)
{
	_val += o._val;
	return *this;
}

Percentage &Percentage::operator -=(const Percentage &o)
{
	_val -= o._val;
	return *this;
}

Percentage &Percentage::operator *=(const Percentage &o)
{
	_val *= o._val;
	return *this;
}

Percentage &Percentage::operator /=(const Percentage &o)
{
	_val /= o._val;
	return *this;
}

Percentage &Percentage::operator %=(const Percentage &o)
{
	_val %= o._val;
	return *this;
}

bool Percentage::operator < (const short &o) const
{
	return _val < o;
}

bool Percentage::operator == (const short &o) const
{
	return _val == o;
}

Percentage &Percentage::operator +=(const short &o)
{
	_val += o;
	return *this;
}

Percentage &Percentage::operator -=(const short &o)
{
	_val -= o;
	return *this;
}

Percentage &Percentage::operator *=(const short &o)
{
	_val *= o;
	return *this;
}

Percentage &Percentage::operator /=(const short &o)
{
	_val /= o;
	return *this;
}

Percentage &Percentage::operator %=(const short &o)
{
	_val %= o;
	return *this;
}
