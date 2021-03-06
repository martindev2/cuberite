
#include "Globals.h"  // NOTE: MSVC stupidness requires this to be the same across all modules

#include "Rabbit.h"
#include "../Entities/Player.h"
#include "../World.h"





cRabbit::cRabbit(void) :
	super("Rabbit", mtRabbit, "mob.rabbit.idle", "mob.rabbit.death", 0.82, 0.68)
{
}





void cRabbit::GetDrops(cItems & a_Drops, cEntity * a_Killer)
{
	unsigned int LootingLevel = 0;
	if (a_Killer != nullptr)
	{
		LootingLevel = a_Killer->GetEquippedWeapon().m_Enchantments.GetLevel(cEnchantments::enchLooting);
	}
	AddRandomDropItem(a_Drops, 0, 1 + LootingLevel, IsOnFire() ? E_ITEM_COOKED_RABBIT : E_ITEM_RAW_RABBIT);
	AddRandomDropItem(a_Drops, 0, 1 + LootingLevel, E_ITEM_RABBIT_HIDE);
	cItems RareDrops;
	RareDrops.Add(cItem(E_ITEM_RABBITS_FOOT));
	AddRandomRareDropItem(a_Drops, RareDrops, LootingLevel);
}

