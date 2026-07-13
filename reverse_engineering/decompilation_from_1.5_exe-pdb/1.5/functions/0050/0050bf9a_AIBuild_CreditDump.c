/*
 * Entry: 0050bf9a
 * Name: AIBuild_CreditDump
 * Namespace: Global
 * Signature: void AIBuild_CreditDump(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_CreditDump(tag_team *param_1)

{
  int iVar1;
  int *piVar2;
  
  tlog_gdm("CreditDump Non Zero Accounts Team %d\n");
  iVar1 = 0;
  piVar2 = (param_1->aibuild).credit;
  do {
    if (*piVar2 != 0) {
      tlog_gdm("   #%d %d\n");
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0x20);
  tlog_gdm("   Prespent Allowance %d\n");
  tlog_gdm("   Actual Cash      %d\n");
  return;
}
