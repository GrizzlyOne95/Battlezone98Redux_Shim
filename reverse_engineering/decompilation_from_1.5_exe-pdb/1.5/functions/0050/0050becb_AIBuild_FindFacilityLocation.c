/*
 * Entry: 0050becb
 * Name: AIBuild_FindFacilityLocation
 * Namespace: Global
 * Signature: int AIBuild_FindFacilityLocation(tag_team * param_1, int param_2, int * param_3, int * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_FindFacilityLocation(tag_team *param_1,int param_2,int *param_3,int *param_4)

{
  tagBUILDINGTYPE *ptVar1;
  int iVar2;
  
  tlog_gdm("AIBuild_FindFacilityLocation Begins\n");
  iVar2 = 0;
  ptVar1 = PREREQ_BuildingTypePtr((ushort)param_2);
  if (ptVar1->resource[0].maxrate == 0) {
    if (ptVar1->resource[1].maxrate == 0) {
      if ((param_1->aibuild).wait_standard_facility == 0) {
        iVar2 = AIBuild_FindNormalFacilityLocation(param_1,param_2,param_3,param_4);
        if (iVar2 == 0) {
          (param_1->aibuild).wait_standard_facility = 300;
        }
      }
    }
    else if ((param_1->aibuild).wait_crystal_mine == 0) {
      iVar2 = AIBuild_ResourceClosestBuildable
                        (param_1,1,ptVar1,(param_1->aibuild).base_x,(param_1->aibuild).base_y,
                         param_3,param_4);
      if (iVar2 == 0) {
        (param_1->aibuild).wait_crystal_mine = 300;
      }
    }
  }
  else if ((param_1->aibuild).wait_water_mine == 0) {
    iVar2 = AIBuild_ResourceClosestBuildable
                      (param_1,0,ptVar1,(param_1->aibuild).base_x,(param_1->aibuild).base_y,param_3,
                       param_4);
    if (iVar2 == 0) {
      (param_1->aibuild).wait_water_mine = 300;
    }
  }
  return iVar2;
}
