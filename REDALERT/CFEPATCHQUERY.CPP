#include "FUNCTION.H"

extern bool DLL_Export_Get_Input_Key_State(KeyNumType key);

/*
//Disable A10s in missions if the player has no buildings
bool CFE_Patch_A10_Override(const ObjectTypeClass& object, const HousesType house)
{
	if (ActiveCFEPatchConfig.DisableCommandoAirstrikes
		&& GameToPlay == GAME_NORMAL
		&& house != PlayerPtr->Class->House
		&& object.What_Am_I() == RTTI_AIRCRAFTTYPE
		&& ((const AircraftTypeClass&)(object)).Type == AIRCRAFT_A10)
	{
		return CFE_Patch_House_Has_Any_Buildings_In_Map(*PlayerPtr);
	}
	return true;
}
*/

bool CFE_Patch_Is_Wall(const ObjectTypeClass& object)
{
	return object.What_Am_I() == RTTI_BUILDINGTYPE && static_cast<const BuildingTypeClass&>(object).IsWall;
}

bool CFE_Patch_Can_Have_Rally_Point(const ObjectClass& object)
{
	return object.What_Am_I() == RTTI_BUILDING && static_cast<const BuildingClass&>(object).Can_Have_Rally_Point();
}

bool CFE_Patch_Should_Extend_Walls()
{
	//#CFE TODO: This isn't multiplayer safe
	return ActiveCFEPatchConfig.WallBuildLength > 1 && !DLL_Export_Get_Input_Key_State(KN_LCTRL);
}

bool CFE_Patch_Should_Attack_Move(const TARGET whom, const TARGET target)
{
	return ActiveCFEPatchConfig.EnableAttackMove && whom == target;
}

bool CFE_Patch_Unit_Should_Rally(const FootClass& object)
{
	switch (object.What_Am_I())
	{
	case RTTI_UNIT:
		return !static_cast<const UnitClass&>(object).Class->IsToHarvest;
	default:
		return true;
	}
}
