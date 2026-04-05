#pragma once

#include "Features/Characteristics/Health.hpp"
#include "Features/Characteristics/MeleeAttack.hpp"
#include "Features/Characteristics/Mobility.hpp"
#include "Features/Commands/MeleeAttackAction.hpp"
#include "Features/Commands/MoveAction.hpp"

#include <Core/Units/Unit.hpp>
#include <cstdint>
#include <memory>
#include <string>

namespace sw::features
{
	struct SwordsmanUnitFactory
	{
		static constexpr std::string TypeName = "Swordsman";

		static core::IUnitPtr create(core::UnitId id, uint32_t hp, uint32_t strength)
		{
			auto unit = std::make_shared<core::Unit>(id, TypeName);
			unit->addCharacteristic<Mobility>(1);
			unit->addCharacteristic<Health>(hp);
			unit->addCharacteristic<MeleeAttack>(strength);

			unit->addAction(std::make_unique<MeleeAttackAction>());
			unit->addAction(std::make_unique<MoveAction>());
			return unit;
		}
	};
}
