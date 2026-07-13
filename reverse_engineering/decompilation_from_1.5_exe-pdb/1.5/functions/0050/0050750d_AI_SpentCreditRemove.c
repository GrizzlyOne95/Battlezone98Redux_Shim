/*
 * Entry: 0050750d
 * Name: AI_SpentCreditRemove
 * Namespace: Global
 * Signature: void AI_SpentCreditRemove(int param_1, tagBUILDING * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SpentCreditRemove(int param_1,tagBUILDING *param_2,int param_3)

{
  int *piVar1;
  tag_team *ptVar2;
  int iVar3;
  
  ptVar2 = AI_map->team[param_2->team];
  if (ptVar2 != (tag_team *)0x0) {
    Debug_Assert((uint)(param_3 <= (ptVar2->aibuild).prespent_credits),0x3a3,".\\Schedule\\Ai.cpp",
                 "the_team->aibuild.prespent_credits >= credits");
    piVar1 = &(ptVar2->aibuild).prespent_credits;
    *piVar1 = *piVar1 - param_3;
    iVar3 = param_2->order;
    if ((iVar3 < 2) || ((3 < iVar3 && (iVar3 != 7)))) {
      Debug_Assert(0,0x3b1,".\\Schedule\\Ai.cpp","1 == 0");
    }
    else {
      Debug_Assert((uint)(param_3 <= (param_2->ai).refundable),0x3ab,".\\Schedule\\Ai.cpp",
                   "building->ai.refundable >= credits");
      piVar1 = &(param_2->ai).refundable;
      *piVar1 = *piVar1 - param_3;
    }
  }
  return;
}
