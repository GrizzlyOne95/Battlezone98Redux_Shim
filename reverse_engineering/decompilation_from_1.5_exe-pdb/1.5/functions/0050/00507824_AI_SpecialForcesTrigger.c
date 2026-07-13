/*
 * Entry: 00507824
 * Name: AI_SpecialForcesTrigger
 * Namespace: Global
 * Signature: void AI_SpecialForcesTrigger(tagSPECIAL_FORCES_BODY * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AI_SpecialForcesTrigger
          (tagSPECIAL_FORCES_BODY *param_1,int param_2,int param_3,int param_4,int param_5)

{
  void *pvVar1;
  tagUNIT *ptVar2;
  ulong uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  Debug_Assert(special_forces_initialised,0x4fa,".\\Schedule\\Ai.cpp","special_forces_initialised");
  Debug_Assert((int)param_1,0x4fb,".\\Schedule\\Ai.cpp","sf");
  iVar6 = param_4 - param_2;
  param_4 = 0;
  if (0 < (param_1->units).count) {
    do {
      pvVar1 = C_Linked_List_Return_Data_By_Number(&param_1->units,param_4);
      ptVar2 = Units_IdToUnitPtr((int)pvVar1,param_1->team);
      if (ptVar2 != (tagUNIT *)0x0) {
        uVar3 = Random_Sync(iVar6 + 1);
        iVar5 = uVar3 + param_2;
        uVar3 = Random_Sync((param_5 - param_3) + 1);
        iVar4 = uVar3 + param_3;
        if (iVar5 < 0) {
          iVar5 = 0;
        }
        if (iVar4 < 0) {
          iVar4 = 0;
        }
        if (mapsizex <= iVar5) {
          iVar5 = mapsizex + -1;
        }
        if (mapsizey <= iVar4) {
          iVar4 = mapsizey + -1;
        }
        Units_SOrderMove(ptVar2,iVar5,iVar4);
      }
      param_4 = param_4 + 1;
    } while (param_4 < (param_1->units).count);
  }
  return;
}
