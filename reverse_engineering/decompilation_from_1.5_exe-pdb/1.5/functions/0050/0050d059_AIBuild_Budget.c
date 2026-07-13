/*
 * Entry: 0050d059
 * Name: AIBuild_Budget
 * Namespace: Global
 * Signature: void AIBuild_Budget(tag_team * param_1, int * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_Budget(tag_team *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  Debug_Assert((int)param_1,0xc66,".\\Schedule\\Aibuild.cpp","the_team");
  iVar2 = (int)param_2 - (int)param_3;
  iVar3 = 0x1f;
  piVar1 = (param_1->aibuild).max_reserve;
  do {
    piVar1 = piVar1 + 1;
    param_3 = param_3 + 1;
    piVar1[-0x21] = *(int *)(iVar2 + (int)param_3);
    *piVar1 = *param_3;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 0x1f;
  iVar2 = 0;
  piVar1 = (param_1->aibuild).budget;
  do {
    piVar1 = piVar1 + 1;
    iVar2 = iVar2 + *piVar1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  (param_1->aibuild).budget_denominator = (float)iVar2;
  if (iVar2 == 0) {
    (param_1->aibuild).budget_valid = 0;
    piVar1 = (param_1->aibuild).credit;
    for (iVar3 = 0x1f; piVar1 = piVar1 + 1, iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar1 = 0;
    }
  }
  else {
    (param_1->aibuild).budget_valid = 1;
  }
  AIBuild_CreditDistribute(param_1->team_ID);
  return;
}
