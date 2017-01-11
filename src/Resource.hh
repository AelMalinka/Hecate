/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_RESOURCE_INC
#	define ENTROPY_HECATE_RESOURCE_INC

#	include "Skill.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<
				typename tag,
				typename ModF,
				typename CostF,
				typename ...skills
			>
			class Resource :
				public Skill<Resource<tag, ModF, CostF, skills...>, CostF, skills...>
			{
				public:
					template<typename ...Skills>
					explicit Resource(const PercentType &, Skills &...);
					template<typename sl, typename = typename std::enable_if<detail::is_specialization_of<sl, tuple>::value>::type>
					Resource(sl  &);
					virtual ~Resource();
					virtual PercentType Value() const;
					virtual PercentType &Current();
					virtual const PercentType &Current() const;
					virtual PercentType Max() const;
				private:
					typedef Skill<Resource<tag, ModF, CostF, skills...>, CostF, skills...> Base;
					PercentType _current;
			};
		}
 }

#	include "Resource.impl.hh"

#endif
