/*
 * Entry: 005078ef
 * Name: AI_SpecialForcesRelease
 * Namespace: Global
 * Signature: void AI_SpecialForcesRelease(tagSPECIAL_FORCES_BODY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SpecialForcesRelease(tagSPECIAL_FORCES_BODY *param_1)

{
  void *pvVar1;
  tagUNIT *ptVar2;
  int iVar3;
  
  Debug_Assert(special_forces_initialised,0x531,".\\Schedule\\Ai.cpp","special_forces_initialised");
  Debug_Assert((int)param_1,0x532,".\\Schedule\\Ai.cpp","sf");
  iVar3 = 0;
  if (0 < (param_1->units).count) {
    do {
      pvVar1 = C_Linked_List_Return_Data_By_Number(&param_1->units,iVar3);
      ptVar2 = Units_IdToUnitPtr((int)pvVar1,param_1->team);
      if (ptVar2 != (tagUNIT *)0x0) {
        AI_UnitAppeared(ptVar2);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (param_1->units).count);
  }
  return;
}
