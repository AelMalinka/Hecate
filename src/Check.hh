/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHECK_INC
#	define ENTROPY_HECATE_CHECK_INC

#	include <memory>
#	include <vector>
#	include <functional>

#	include "Modifier.hh"

#	ifndef ENTROPY_HECATE_DEFAULT_LUCK
#		define ENTROPY_HECATE_DEFAULT_LUCK 5
#	endif

	namespace Entropy
	{
		namespace Hecate
		{
			class Check
			{
				public:
					class Result
					{
						private:
							struct result_modifier
							{
								PercentType current;
								std::shared_ptr<Modifier> modifier;
							};
						public:
							Result(const PercentType, const PercentType, const PercentType, const std::vector<std::shared_ptr<Modifier>> &);
							operator bool () const;
							bool isSuccess() const;
							bool isCritical() const;
							PercentType Value() const;
							PercentType Luck() const;
							std::size_t size() const;
							std::vector<result_modifier>::iterator begin();
							std::vector<result_modifier>::iterator end();
						private:
							PercentType _value;
							PercentType _roll;
							PercentType _luck;
							std::vector<result_modifier> _modifiers;
					};
				public:
					Check();
					Check(PercentType &);
					Check(const std::vector<Modifier> &);
					Check(PercentType &, const std::vector<Modifier> &);
					Check(const Check &) = default;
					Check(Check &&) = default;
					template<typename T>
					Check &Add(T &, const std::string &, const detail::negative_t & = detail::positive);
					template<typename T>
					Check &Add(T &&, const std::string &, const detail::negative_t & = detail::positive);
					Check &Add(const std::shared_ptr<Modifier> &);
					Check &Add(const Modifier &);
					Check &Add(const std::function<void(const Result &)> &);
					template<typename ...mods>
					Result operator () (const mods &...) const;
					std::size_t size() const;
					std::vector<std::shared_ptr<Modifier>>::iterator begin();
					std::vector<std::shared_ptr<Modifier>>::iterator end();
				private:
					static PercentType default_luck;
					std::vector<std::shared_ptr<Modifier>> _modifiers;
					std::vector<std::function<void(Result &)>> _callbacks;
					PercentType &_luck;
			};
		}
	}

#	include "Check.impl.hh"

#endif
