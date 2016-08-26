/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Modifier.hh"

using namespace Entropy::Hecate;
using namespace std;

const negative_t Entropy::Hecate::negative;

BaseModifier::BaseModifier(const string &r)
	: _reason(r), _negate(false)
{}

BaseModifier::BaseModifier(const string &r, const negative_t &)
	: _reason(r), _negate(true)
{}

BaseModifier::BaseModifier(const BaseModifier &) = default;
BaseModifier::~BaseModifier() = default;

const string &BaseModifier::Reason() const
{
	return _reason;
}

const bool &BaseModifier::Negative() const
{
	return _negate;
}

Modifier<unsigned short> Entropy::Hecate::make_modifier(unsigned short v, const string &r)
{
	Modifier<unsigned short> ret(v, r);
	return ret;
}

Modifier<unsigned short> Entropy::Hecate::make_modifier(unsigned short v, const string &r, const negative_t &n)
{
	Modifier<unsigned short> ret(v, r, n);
	return ret;
}
