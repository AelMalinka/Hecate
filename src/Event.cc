/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Event.hh"

using namespace std;
using namespace Entropy::Hecate;

Event::Event(const size_t &id)
	: _id(id)
{}

Event::Event(const Event &) = default;
Event::Event(Event &&) = default;
Event::~Event() = default;

const size_t &Event::Id() const
{
	return _id;
}
