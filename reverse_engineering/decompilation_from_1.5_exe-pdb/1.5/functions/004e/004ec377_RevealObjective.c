/*
 * Entry: 004ec377
 * Name: RevealObjective
 * Namespace: Global
 * Signature: void RevealObjective(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl RevealObjective(long param_1)

{
  char **ppcVar1;
  int iVar2;
  char **unaff_EDI;
  char *unaff_retaddr;
  
  iVar2 = VerifyObjective(od.NumObjs,0x5e6fd4,unaff_EDI,unaff_retaddr);
  if (iVar2 != 0) {
    ppcVar1 = od.FailText + param_1 + 0xf;
    if (((uint)*ppcVar1 & 1) == 0) {
      DEBUG_systemWarning("Objective %d not hidden... cannot reveal");
    }
    *ppcVar1 = (char *)((uint)*ppcVar1 & 0xfffffffe);
    StartGASEvent("cnote.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
  }
  return;
}
