#pragma once

#include "Features/Characteristics/Health.hpp"
#include "Features/Characteristics/MeleeAttack.hpp"
#include "Features/Characteristics/Mobility.hpp"
#include "Features/Characteristics/RangedAttack.hpp"
#include "Features/Commands/MeleeAttackAction.hpp"
#include "Features/Commands/MoveAction.hpp"
#include "Features/Commands/RangedAttackAction.hpp"

#include <Core/Units/Unit.hpp>
#include <Core/World/Point.hpp>
#include <cstdint>
#include <memory>
#include <string>

namespace sw::features
{
	struct HunterUnitFactory
	{
		static constexpr std::string TypeName = "Hunter";

		static core::IUnitPtr create(core::UnitId id, uint32_t hp, uint32_t agility, uint32_t strength, uint32_t range)
		{
			auto unit = std::make_shared<core::Unit>(id, TypeName);
			unit->addCharacteristic<Mobility>(1);
			unit->addCharacteristic<Health>(hp);
			unit->addCharacteristic<MeleeAttack>(strength);
			unit->addCharacteristic<RangedAttack>(agility, range);

			unit->addAction(std::make_unique<RangedAttackAction>());
			unit->addAction(std::make_unique<MeleeAttackAction>());
			unit->addAction(std::make_unique<MoveAction>());
			return unit;
		}
	};
}
