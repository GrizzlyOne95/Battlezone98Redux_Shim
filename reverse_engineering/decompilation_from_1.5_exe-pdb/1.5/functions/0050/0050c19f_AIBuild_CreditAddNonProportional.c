/*
 * Entry: 0050c19f
 * Name: AIBuild_CreditAddNonProportional
 * Namespace: Global
 * Signature: void AIBuild_CreditAddNonProportional(tag_team * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_CreditAddNonProportional(tag_team *param_1,int param_2)

{
  bool bVar1;
  tag_team *ptVar2;
  int *piVar3;
  tag_team *ptVar4;
  tag_team *ptVar5;
  
  ptVar2 = param_1;
  ptVar4 = (tag_team *)0x1;
  bVar1 = false;
  piVar3 = (param_1->aibuild).budget;
  ptVar5 = param_1;
  do {
    piVar3 = piVar3 + 1;
    if ((*piVar3 != 0) && ((!bVar1 || (piVar3[-0x20] < (int)param_1)))) {
      bVar1 = true;
      ptVar5 = ptVar4;
      param_1 = (tag_team *)piVar3[-0x20];
    }
    ptVar4 = (tag_team *)((int)&ptVar4->team_ID + 1);
  } while ((int)ptVar4 < 0x20);
  Debug_Assert((int)ptVar5,0xc1d,".\\Schedule\\Aibuild.cpp","min_node");
  piVar3 = (ptVar2->aibuild).credit + (int)ptVar5;
  *piVar3 = *piVar3 + param_2;
  return;
}
