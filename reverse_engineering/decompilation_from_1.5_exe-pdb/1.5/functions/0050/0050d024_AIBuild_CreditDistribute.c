/*
 * Entry: 0050d024
 * Name: AIBuild_CreditDistribute
 * Namespace: Global
 * Signature: void AIBuild_CreditDistribute(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_CreditDistribute(int param_1)

{
  tag_team *ptVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  ptVar1 = AI_map->team[param_1];
  tlog_gdm("AIBuild_CreditDistribute team %d");
  piVar4 = (ptVar1->aibuild).credit;
  iVar2 = *piVar4;
  for (iVar3 = 0x20; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar4 = 0;
    piVar4 = piVar4 + 1;
  }
  AIBuild_CreditAdd(param_1,iVar2);
  return;
}
