/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_RESOURCE_IMPL
#	define ENTROPY_HECATE_RESOURCE_IMPL

#	include "Resource.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename tag, typename ModF, typename CostF, typename ...skills>
			template<typename ...Skills>
			Resource<tag, ModF, CostF, skills...>::Resource(const PercentType &v, Skills &...s)
				: Base(v, s...), _current(0)
			{
				_current = this->Value();
			}

			template<typename tag, typename ModF, typename CostF, typename ...skills>
			template<typename sl, typename>
			Resource<tag, ModF, CostF, skills...>::Resource(sl  &s)
				: Base(s), _current(0)
			{
				_current = this->Value();
			}

			template<typename tag, typename ModF, typename CostF, typename ...skills> Resource<tag, ModF, CostF, skills...>::~Resource() = default;

			template<typename tag, typename ModF, typename CostF, typename ...skills>
			PercentType Resource<tag, ModF, CostF, skills...>::Value() const
			{
				return ModF()(Base::Value());
			}


			template<typename tag, typename ModF, typename CostF, typename ...skills>
			PercentType &Resource<tag, ModF, CostF, skills...>::Current()
			{
				return _current;
			}

			template<typename tag, typename ModF, typename CostF, typename ...skills>
			const PercentType &Resource<tag, ModF, CostF, skills...>::Current() const
			{
				return _current;
			}

			template<typename tag, typename ModF, typename CostF, typename ...skills>
			PercentType Resource<tag, ModF, CostF, skills...>::Max() const
			{
				return this->Value();
			}
		}
	}

#endif
