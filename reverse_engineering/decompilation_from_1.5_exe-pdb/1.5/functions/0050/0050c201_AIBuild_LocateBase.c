/*
 * Entry: 0050c201
 * Name: AIBuild_LocateBase
 * Namespace: Global
 * Signature: void AIBuild_LocateBase(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_LocateBase(tag_team *param_1)

{
  tagBUILDING *ptVar1;
  tagUNIT *ptVar2;
  int iVar3;
  int iVar4;
  tagITERATOR local_58;
  int local_8;
  
  iVar3 = 0;
  iVar4 = 0;
  local_8 = 0;
  ITERATE_BUILDINIT_TEAM(&local_58,param_1->team_ID);
  ptVar1 = Iterate_BuildNext(&local_58);
  if (ptVar1 == (tagBUILDING *)0x0) {
LAB_0050c24b:
    ITERATE_UNITINIT_TEAM(&local_58,param_1->team_ID);
    ptVar2 = Iterate_UnitNext(&local_58);
    if (ptVar2 != (tagUNIT *)0x0) {
      do {
        iVar4 = iVar4 + (ptVar2->tilepos).x;
        iVar3 = iVar3 + (ptVar2->tilepos).y;
        local_8 = local_8 + 1;
        ptVar2 = Iterate_UnitNext(&local_58);
      } while (ptVar2 != (tagUNIT *)0x0);
      if (local_8 != 0) goto LAB_0050c292;
    }
    (param_1->aibuild).base_x = 0;
    (param_1->aibuild).base_y = 0;
  }
  else {
    do {
      iVar4 = iVar4 + ptVar1->tilex;
      iVar3 = iVar3 + ptVar1->tiley;
      local_8 = local_8 + 1;
      ptVar1 = Iterate_BuildNext(&local_58);
    } while (ptVar1 != (tagBUILDING *)0x0);
    if (local_8 == 0) goto LAB_0050c24b;
LAB_0050c292:
    (param_1->aibuild).base_x = iVar4 / local_8;
    (param_1->aibuild).base_y = iVar3 / local_8;
    tlog_gdm("AT Team %d Base Located at (%d, %d)\n");
  }
  return;
}
