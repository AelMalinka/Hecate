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

			class onSuccess
			{
				public:
					onSuccess(const std::function<void(const Check::Result &)> &);
					onSuccess(const onSuccess &);
					onSuccess(onSuccess &&);
					~onSuccess();
					void operator () (const Check::Result &) const;
				private:
					std::function<void(const Check::Result &)> _cb;
			};

			class onFailure
			{
				public:
					onFailure(const std::function<void(const Check::Result &)> &);
					onFailure(const onFailure &);
					onFailure(onFailure &&);
					~onFailure();
					void operator () (const Check::Result &) const;
				private:
					std::function<void(const Check::Result &)> _cb;
			};

			class onCritical
			{
				public:
					onCritical(const std::function<void(const Check::Result &)> &);
					onCritical(const onCritical &);
					onCritical(onCritical &&);
					~onCritical();
					void operator () (const Check::Result &) const;
				private:
					std::function<void(const Check::Result &)> _cb;
			};
		}
	}

#	include "Check.impl.hh"

#endif
