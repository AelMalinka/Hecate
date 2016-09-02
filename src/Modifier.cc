/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Modifier.hh"

using namespace Entropy::Hecate;
using namespace std;

const negative_t Entropy::Hecate::negative;

Modifier::Modifier(const string &r)
	: _reason(r), _negate(false)
{}

Modifier::Modifier(const string &r, const negative_t &)
	: _reason(r), _negate(true)
{}

Modifier::Modifier(const Modifier &) = default;
Modifier::~Modifier() = default;

const string &Modifier::Reason() const
{
	return _reason;
}

const bool &Modifier::Negative() const
{
	return _negate;
}

shared_ptr<Modifier> Entropy::Hecate::make_modifier(Percent v, const string &r)
{
	return make_shared<ModifierImpl<Percent>>(v, r);
}

shared_ptr<Modifier> Entropy::Hecate::make_modifier(Percent v, const string &r, const negative_t &n)
{
	return make_shared<ModifierImpl<Percent>>(v, r, n);
}
