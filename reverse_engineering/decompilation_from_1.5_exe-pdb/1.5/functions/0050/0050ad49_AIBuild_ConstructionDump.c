/*
 * Entry: 0050ad49
 * Name: AIBuild_ConstructionDump
 * Namespace: Global
 * Signature: void AIBuild_ConstructionDump(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ConstructionDump(tag_team *param_1)

{
  int iVar1;
  int iVar2;
  
  tlog_gdm("Under Construction List\n");
  iVar2 = 0;
  iVar1 = Units_UnitTypeCount();
  if (0 < iVar1 + 1 + maxbuildingtypes) {
    do {
      tlog_gdm("   Type #%2d, Nr %d\n");
      iVar2 = iVar2 + 1;
      iVar1 = Units_UnitTypeCount();
    } while (iVar2 < iVar1 + 1 + maxbuildingtypes);
  }
  return;
}
