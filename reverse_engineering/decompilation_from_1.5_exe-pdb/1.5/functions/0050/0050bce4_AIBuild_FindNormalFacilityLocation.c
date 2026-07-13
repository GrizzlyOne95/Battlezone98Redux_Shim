/*
 * Entry: 0050bce4
 * Name: AIBuild_FindNormalFacilityLocation
 * Namespace: Global
 * Signature: int AIBuild_FindNormalFacilityLocation(tag_team * param_1, int param_2, int * param_3, int * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuild_FindNormalFacilityLocation(tag_team *param_1,int param_2,int *param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  tagBUILDINGTYPE *ptVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_14;
  int local_10;
  int local_8;
  
  tlog_gdm("AIBuild_FindNormalFacilityLocation Begins\n");
  ptVar5 = PREREQ_BuildingTypePtr((ushort)param_2);
  bVar4 = false;
  local_14 = 0;
  iVar2 = (param_1->aibuild).base_x;
  iVar3 = (param_1->aibuild).base_y;
  iVar8 = 1;
  local_10 = iVar2;
  do {
    local_10 = local_10 + -1;
    local_8 = 0;
    if (0 < iVar8) {
      do {
        if (bVar4) break;
        iVar1 = (iVar3 - iVar2) + local_10;
        iVar7 = (local_8 - iVar8 / 2) + iVar2;
        iVar6 = AIBuild_CanUnitBuildHere(param_1,(tagUNIT *)0x0,ptVar5,iVar7,iVar1);
        if (iVar6 != 0) {
          bVar4 = true;
          local_14 = 1;
          *param_3 = iVar7;
          *param_4 = iVar1;
        }
        local_8 = local_8 + 1;
      } while (local_8 < iVar8);
    }
    local_8 = 0;
    if (0 < iVar8) {
      do {
        if (bVar4) break;
        iVar1 = (iVar3 - iVar2) + iVar8 + iVar2;
        iVar7 = (local_8 - iVar8 / 2) + iVar2;
        iVar6 = AIBuild_CanUnitBuildHere(param_1,(tagUNIT *)0x0,ptVar5,iVar7,iVar1);
        if (iVar6 != 0) {
          bVar4 = true;
          local_14 = 1;
          *param_3 = iVar7;
          *param_4 = iVar1;
        }
        local_8 = local_8 + 1;
      } while (local_8 < iVar8);
    }
    local_8 = 0;
    if (0 < iVar8) {
      do {
        if (bVar4) break;
        iVar1 = (local_8 - iVar8 / 2) + iVar3;
        iVar7 = AIBuild_CanUnitBuildHere(param_1,(tagUNIT *)0x0,ptVar5,iVar8 + iVar2,iVar1);
        if (iVar7 != 0) {
          bVar4 = true;
          local_14 = 1;
          *param_3 = iVar8 + iVar2;
          *param_4 = iVar1;
        }
        local_8 = local_8 + 1;
      } while (local_8 < iVar8);
    }
    local_8 = 0;
    if (0 < iVar8) {
      do {
        if (bVar4) break;
        iVar1 = (local_8 - iVar8 / 2) + iVar3;
        iVar7 = AIBuild_CanUnitBuildHere(param_1,(tagUNIT *)0x0,ptVar5,local_10,iVar1);
        if (iVar7 != 0) {
          bVar4 = true;
          local_14 = 1;
          *param_3 = local_10;
          *param_4 = iVar1;
        }
        local_8 = local_8 + 1;
      } while (local_8 < iVar8);
    }
    iVar8 = iVar8 + 1;
    if ((mapsizex < iVar8) && (mapsizey < iVar8)) {
      bVar4 = true;
    }
    if (bVar4) {
      tlog_gdm("AIBuild_FindNormalFacilityLocation Ends\n");
      return local_14;
    }
  } while( true );
}
