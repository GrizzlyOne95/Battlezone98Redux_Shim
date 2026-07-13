/*
 * Entry: 0050ccfc
 * Name: AIBuild_TeamProcess
 * Namespace: Global
 * Signature: void AIBuild_TeamProcess(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_TeamProcess(tag_team *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  Debug_Assert((int)param_1,0xac9,".\\Schedule\\Aibuild.cpp","the_team");
  AIBuild_CreditDump(param_1);
  Debug_Assert((uint)((param_1->aibuild).prespent_credits + (param_1->aibuild).credit[0] ==
                     teamdata[param_1->team_ID].credits),0xad1,".\\Schedule\\Aibuild.cpp",
               "the_team->aibuild.credit[0] + the_team->aibuild.prespent_credits == teamdata[the_team->team_ID].credits"
              );
  if ((param_1->aibuild).budget_valid != 0) {
    iVar1 = 0;
    piVar2 = (param_1->aibuild).credit;
    iVar3 = 0x1f;
    do {
      piVar2 = piVar2 + 1;
      iVar1 = iVar1 + *piVar2;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    Debug_Assert((uint)((param_1->aibuild).credit[0] == iVar1),0xad8,".\\Schedule\\Aibuild.cpp",
                 "the_team->aibuild.credit[0] == total");
  }
  piVar2 = &(param_1->aibuild).wait_crystal_mine;
  iVar3 = *piVar2;
  if (iVar3 != 0) {
    *piVar2 = iVar3 + -1;
  }
  piVar2 = &(param_1->aibuild).wait_water_mine;
  iVar3 = *piVar2;
  if (iVar3 != 0) {
    *piVar2 = iVar3 + -1;
  }
  piVar2 = &(param_1->aibuild).wait_standard_facility;
  iVar3 = *piVar2;
  if (iVar3 != 0) {
    *piVar2 = iVar3 + -1;
  }
  if ((param_1->aibuild).construction_program != (tagCONSTRUCTION_PROGRAM *)0x0) {
    AIBuild_BuildListRebuild(param_1);
    AIBuild_ProcessFacilityUpgrade(param_1);
    AIBuild_ProcessFacilityConstruction(param_1);
    AIBuild_ProcessUnitConstruction(param_1);
    if ((param_1->aibuild).budget_valid != 0) {
      iVar1 = 0;
      piVar2 = (param_1->aibuild).credit;
      iVar3 = 0x1f;
      do {
        piVar2 = piVar2 + 1;
        iVar1 = iVar1 + *piVar2;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      Debug_Assert((uint)((param_1->aibuild).credit[0] == iVar1),0xb01,".\\Schedule\\Aibuild.cpp",
                   "the_team->aibuild.credit[0] == total");
    }
    Debug_Assert((uint)((param_1->aibuild).prespent_credits + (param_1->aibuild).credit[0] ==
                       teamdata[param_1->team_ID].credits),0xb05,".\\Schedule\\Aibuild.cpp",
                 "the_team->aibuild.credit[0] + the_team->aibuild.prespent_credits == teamdata[the_team->team_ID].credits"
                );
  }
  return;
}
