/*	Michael Thomas (malinka) <AelMalinka@gmail.com>
	2012-12-15
*/

#include "Stat.hh"

using namespace Entropy::Hecate;

StatPrototype::StatPrototype()
	: _name()
{}

StatPrototype::StatPrototype(const std::string &name)
	: _name(name)
{}

StatPrototype::~StatPrototype() = default;

bool StatPrototype::operator==(const std::string &r) const
{
	return _name == r;
}

const std::string& StatPrototype::extractor::operator()(const StatPrototype &o) const
{
	return o._name;
}
