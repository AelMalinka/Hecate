/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Event.hh"

using namespace std;
using namespace Entropy::Hecate;

Event::Event(const size_t &id)
	: Entropy::Event(id)
{}

Event::~Event() = default;
