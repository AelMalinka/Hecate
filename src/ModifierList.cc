/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "ModifierList.hh"

using namespace Entropy::Hecate;
using namespace std;

ModifierList::ModifierList()
	: _modifiers()
{}

ModifierList::ModifierList(initializer_list<Modifier> il)
	: _modifiers()
{
	for(auto &&i : il) {
		Add(i);
	}
}

ModifierList::ModifierList(const vector<Modifier> &v)
	: _modifiers()
{
	// 2017-01-04 AMR TODO: decide if we should store all modifiers and do the right thing on calculation or just store calculated result
	for(auto &&i : v) {
		Add(i);
	}
}

PercentType ModifierList::Value() const
{
	PercentType ret = 0;
	for(auto &&t : _modifiers) {
		PercentType temp = 0;

		if(t.first.Stacking()) {
			for(auto &&v : t.second) {
				temp += v.Value();
			}
		} else {
			for(auto &&v : t.second) {
				if(v.Value() > temp) {
					temp = v.Value();
				}
			}
		}

		ret += temp;
	}

	return ret;
}

void ModifierList::Add(const Modifier &v)
{
	_modifiers[v.Type()].push_back(v);
}

vector<Modifier> &ModifierList::operator [] (const ModifierType &k)
{
	return _modifiers[k];
}

std::map<ModifierType, std::vector<Modifier>>::iterator ModifierList::begin()
{
	return _modifiers.begin();
}

std::map<ModifierType, std::vector<Modifier>>::iterator ModifierList::end()
{
	return _modifiers.end();
}

size_t ModifierList::size() const
{
	return _modifiers.size();
}

const vector<Modifier> &ModifierList::operator [] (const ModifierType &k) const
{
	if(_modifiers.find(k) != _modifiers.end())
		return _modifiers.find(k)->second;
	else
		ENTROPY_THROW(Exception("Out of bounds"));
}

map<ModifierType, vector<Modifier>>::const_iterator ModifierList::begin() const
{
	return _modifiers.begin();
}

map<ModifierType, vector<Modifier>>::const_iterator ModifierList::end() const
{
	return _modifiers.end();
}
