/*
 * Entry: 0050c004
 * Name: AIBuild_CreditSubtract
 * Namespace: Global
 * Signature: void AIBuild_CreditSubtract(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Type propagation algorithm not settling */

void __cdecl AIBuild_CreditSubtract(int param_1,int param_2)

{
  tag_team *ptVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int local_8;
  
  ptVar1 = AI_map->team[param_1];
  tlog_gdm("CreditSubtract Team %d Credits %d\n");
  tlog_gdm("  BudgetValid  %d\n");
  if (param_2 != 0) {
    Debug_Assert((uint)(0 < param_2),0xb77,".\\Schedule\\Aibuild.cpp","credits > 0");
    piVar3 = (ptVar1->aibuild).credit;
    Debug_Assert((uint)(param_2 <= *piVar3),0xb78,".\\Schedule\\Aibuild.cpp",
                 "credits <= the_team->aibuild.credit[0]");
    *piVar3 = *piVar3 - param_2;
    iVar5 = param_1;
    iVar4 = param_2;
    iVar2 = (ptVar1->aibuild).budget_valid;
    while (iVar2 != 0) {
      tlog_gdm("     Removing credits %d\n");
      local_8 = 0;
      param_2 = 1;
      piVar3 = (ptVar1->aibuild).credit;
      do {
        piVar3 = piVar3 + 1;
        iVar2 = *piVar3;
        if ((iVar2 != 0) && ((local_8 == 0 || (iVar5 < iVar2)))) {
          param_1 = param_2;
          local_8 = 1;
          iVar5 = iVar2;
        }
        param_2 = param_2 + 1;
      } while (param_2 < 0x20);
      if (local_8 == 0) {
        tlog_gdm("    No account found with cash in it\n");
      }
      else {
        tlog_gdm("    Found Account %d with %d credits\n");
      }
      Debug_Assert(local_8,0xb9f,".\\Schedule\\Aibuild.cpp","found");
      if (iVar4 <= iVar5) {
        tlog_gdm("   Taking only from account %d\n");
        (ptVar1->aibuild).credit[param_1] = iVar5 - iVar4;
        return;
      }
      tlog_gdm("    Emptying account %d\n");
      (ptVar1->aibuild).credit[param_1] = 0;
      iVar4 = iVar4 - iVar5;
      iVar2 = iVar4;
    }
  }
  return;
}
