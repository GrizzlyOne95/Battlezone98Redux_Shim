/*
 * Entry: 005088ba
 * Name: AI_Match_Init
 * Namespace: Global
 * Signature: void AI_Match_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Match_Init(void)

{
  int iVar1;
  tagUNITTYPE *ptVar2;
  int iVar3;
  float fVar4;
  
  tlog_gdm("AI_Match_Init");
  iVar3 = 0;
  iVar1 = Units_UnitTypeCount();
  if (0 < iVar1) {
    do {
      ptVar2 = Units_GetTypePtr(iVar3);
      fVar4 = AI_Match_Get_Unit_Type_Strength(ptVar2);
      unit_type_strength[iVar3] = fVar4;
      Units_GetTypePtr(iVar3);
      Units_GetTypePtr(iVar3);
      tlog_gdm("Unit Name \'%s\' Symbol \'%s\' strength %4.4f\n");
      iVar3 = iVar3 + 1;
      iVar1 = Units_UnitTypeCount();
    } while (iVar3 < iVar1);
  }
  return;
}
