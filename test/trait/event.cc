/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Event.hh"

using namespace Entropy::Hecate;
using namespace testing;
using namespace std;

namespace {
	class TimeChange :
		public Event
	{
		public:
			enum when_t
			{
				Dawn,
				Day,
				Dusk,
				Night
			};
		public:
			TimeChange(when_t);
			when_t When() const;
		private:
			when_t _when;
	};

	TEST(Event, Create) {
		Event ev(10);
		TimeChange night(TimeChange::Night);
		TimeChange day(TimeChange::Day);

		EXPECT_EQ(night.When(), TimeChange::Night);
		EXPECT_EQ(day.When(), TimeChange::Day);

		EXPECT_EQ(ev.Id(), 10);
		EXPECT_EQ(night.Id(), day.Id());
		EXPECT_NE(ev.Id(), night.Id());
	}

	TimeChange::TimeChange(when_t when)
		: Event(1024), _when(when)
	{}

	TimeChange::when_t TimeChange::When() const
	{
		return _when;
	}
}
