/*
 * Entry: 004ec3cd
 * Name: SucceedObjective
 * Namespace: Global
 * Signature: void SucceedObjective(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SucceedObjective(long param_1)

{
  char **ppcVar1;
  int iVar2;
  char **unaff_EDI;
  char *unaff_retaddr;
  char *pcVar3;
  
  iVar2 = VerifyObjective(od.NumObjs,0x5e705c,unaff_EDI,unaff_retaddr);
  if (iVar2 != 0) {
    ppcVar1 = od.FailText + param_1 + 0xf;
    pcVar3 = *ppcVar1;
    if (((uint)pcVar3 & 2) == 0) {
      if (((uint)pcVar3 & 4) == 0) {
        if (((uint)pcVar3 & 1) != 0) {
          DEBUG_systemWarning("Objective %d is hidden... succeeding anyway");
        }
        *ppcVar1 = (char *)((uint)*ppcVar1 | 2);
        StartGASEvent("cnote.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
        return;
      }
      pcVar3 = "Objective %d already failed... cannot succeed";
    }
    else {
      pcVar3 = "Objective %d already succeeded...";
    }
    DEBUG_systemWarning(pcVar3);
  }
  return;
}
