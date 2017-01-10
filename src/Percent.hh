/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_PERCENT_INC
#	define ENTROPY_HECATE_PERCENT_INC

#	include "Exception.hh"
#	include "ModifierList.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			class Percent
			{
				public:
					Percent();
					Percent(const PercentType);
					virtual ~Percent();
					virtual void Add(const Modifier &);
					virtual ModifierList &Modifiers();
					virtual const ModifierList &Modifiers() const;
					virtual PercentType Value() const;
					virtual PercentType &Raw();
					virtual const PercentType &Raw() const;
					virtual CostType Cost() const = 0;
				private:
					PercentType _value;
					ModifierList _modifiers;
			};
		}
	}

#endif
