/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_EVENT_INC
#	define ENTROPY_HECATE_EVENT_INC

#	include "Exception.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			class Event
			{
				public:
					Event(const std::size_t &);
					Event(const Event &);
					Event(Event &&);
					virtual ~Event();
					const std::size_t &Id() const;
				private:
					const std::size_t _id;
			};
		}
	}

#endif
