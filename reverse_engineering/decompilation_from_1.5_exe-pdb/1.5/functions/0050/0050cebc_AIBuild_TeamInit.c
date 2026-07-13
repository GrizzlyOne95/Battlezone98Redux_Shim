/*
 * Entry: 0050cebc
 * Name: AIBuild_TeamInit
 * Namespace: Global
 * Signature: void AIBuild_TeamInit(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_TeamInit(tag_team *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  Debug_Assert((int)param_1,0xcef,".\\Schedule\\Aibuild.cpp","the_team");
  AIBuild_ConstructionNew(param_1->team_ID);
  (param_1->aibuild).construction_program = (tagCONSTRUCTION_PROGRAM *)0x0;
  AIBuild_LocateBase(param_1);
  piVar1 = (param_1->aibuild).credit;
  (param_1->aibuild).prespent_credits = 0;
  iVar3 = 0x20;
  piVar2 = piVar1;
  do {
    piVar2[0x20] = 0;
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *piVar1 = teamdata[param_1->team_ID].credits;
  (param_1->aibuild).budget_valid = 0;
  (param_1->aibuild).wait_crystal_mine = 0;
  (param_1->aibuild).wait_water_mine = 0;
  (param_1->aibuild).wait_standard_facility = 0;
  AIBuild_UnassignedCCInit(param_1);
  AIBuild_BuildListInit(param_1);
  AIBuild_BuildListRebuild(param_1);
  AIBuild_ReservedAreaNew(param_1->team_ID);
  return;
}
