/*
 * Entry: 005075a4
 * Name: AI_SpentCreditRefund
 * Namespace: Global
 * Signature: void AI_SpentCreditRefund(int param_1, tagBUILDING * param_2, tagUNIT * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SpentCreditRefund(int param_1,tagBUILDING *param_2,tagUNIT *param_3)

{
  tag_team *ptVar1;
  int in_ECX;
  int iVar2;
  int *piVar3;
  int local_8;
  
  ptVar1 = AI_map->team[param_1];
  if (ptVar1 != (tag_team *)0x0) {
    if (param_3 == (tagUNIT *)0x0) {
      if (param_2 == (tagBUILDING *)0x0) {
        Debug_Assert(0,0x3ed,".\\Schedule\\Ai.cpp","1 == 0");
        iVar2 = param_1;
        local_8 = in_ECX;
      }
      else {
        iVar2 = param_2->order;
        if ((iVar2 < 2) || ((3 < iVar2 && (iVar2 != 7)))) {
          local_8 = 0;
          iVar2 = 0;
        }
        else {
          local_8 = (param_2->ai).account;
          iVar2 = (param_2->ai).refundable;
        }
      }
    }
    else {
      Debug_Assert((uint)(param_2 == (tagBUILDING *)0x0),0x3d0,".\\Schedule\\Ai.cpp","!building");
      local_8 = (param_3->ai).cc_account;
      iVar2 = (param_3->ai).cc_construct_cost;
    }
    piVar3 = &(ptVar1->aibuild).prespent_credits;
    Debug_Assert((uint)(iVar2 <= *piVar3),0x3f1,".\\Schedule\\Ai.cpp",
                 "the_team->aibuild.prespent_credits >= credits");
    *piVar3 = *piVar3 - iVar2;
    if (iVar2 != 0) {
      if (local_8 == 0) {
        AIBuild_CreditAdd(param_1,iVar2);
      }
      else {
        piVar3 = (ptVar1->aibuild).credit;
        *piVar3 = *piVar3 + iVar2;
        piVar3 = (ptVar1->aibuild).credit + local_8;
        *piVar3 = *piVar3 + iVar2;
      }
    }
  }
  return;
}
