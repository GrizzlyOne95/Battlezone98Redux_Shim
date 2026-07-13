/*
 * Entry: 0050c15b
 * Name: AIBuild_CreditAddProportional
 * Namespace: Global
 * Signature: int AIBuild_CreditAddProportional(tag_team * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_CreditAddProportional(tag_team *param_1,int param_2)

{
  int extraout_EAX;
  int iVar1;
  int *piVar2;
  
  iVar1 = param_2;
  piVar2 = (param_1->aibuild).credit;
  param_2 = 0x1f;
  do {
    piVar2 = piVar2 + 1;
    _ftol2_sse();
    *piVar2 = *piVar2 + extraout_EAX;
    iVar1 = iVar1 - extraout_EAX;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return iVar1;
}
