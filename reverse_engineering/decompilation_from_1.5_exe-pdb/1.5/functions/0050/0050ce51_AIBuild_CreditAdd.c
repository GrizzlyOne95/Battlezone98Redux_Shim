/*
 * Entry: 0050ce51
 * Name: AIBuild_CreditAdd
 * Namespace: Global
 * Signature: void AIBuild_CreditAdd(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_CreditAdd(int param_1,int param_2)

{
  int *piVar1;
  tag_team *ptVar2;
  int iVar3;
  
  ptVar2 = AI_map->team[param_1];
  Debug_Assert((uint)(-1 < param_2),0xbcd,".\\Schedule\\Aibuild.cpp","credits >= 0");
  tlog_gdm("CreditAdd Team %d Credits %d\n");
  if ((param_2 != 0) &&
     (piVar1 = (ptVar2->aibuild).credit, *piVar1 = *piVar1 + param_2,
     (ptVar2->aibuild).budget_valid != 0)) {
    iVar3 = AIBuild_CreditAddProportional(ptVar2,param_2);
    if (iVar3 != 0) {
      AIBuild_CreditAddNonProportional(ptVar2,iVar3);
    }
  }
  return;
}
