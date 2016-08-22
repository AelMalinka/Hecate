/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_SKILL_INC
#	define ENTROPY_HECATE_SKILL_INC

#	include <tuple>

#	include "Stat.hh"

#	ifndef ENTROPY_HECATE_DEFINE_SKILL
#		define ENTROPY_HECATE_DEFINE_SKILL(name, ...) struct name ## _tag {}; typedef ::Entropy::Hecate::Skill<name ## _tag,  __VA_ARGS__> name
#	endif

	namespace Entropy
	{
		namespace Hecate
		{
			using std::tuple;

			namespace detail
			{
				// 2016-04-25 AMR NOTE: ganked shamelessly from https://bitbucket.org/martinhofernandes/wheels/src/default/include/wheels/meta/type_traits.h%2B%2B?fileviewer=file-view-default#type_traits.h%2B%2B-161 which is CC0
				template <typename T, template <typename...> class Template>
				struct is_specialization_of :
					std::false_type
				{};

				template <template <typename...> class Template, typename... Args>
				struct is_specialization_of<Template<Args...>, Template> :
					std::true_type
				{};
			}

			template<
				typename tag,
				typename ...skills
			>
			class Skill
			{
				public:
					template<typename ...Skills>
					Skill(const unsigned short, Skills &...);
					template<typename sl, typename = typename std::enable_if<detail::is_specialization_of<sl, tuple>::value>::type>
					Skill(sl &);
					~Skill();
					unsigned short Value() const;
					void setValue(const unsigned short);
				private:
					unsigned short _value;
					tuple<skills &...> _base_skills;
			};
		}
	}

#	include "Skill.impl.hh"

#endif
