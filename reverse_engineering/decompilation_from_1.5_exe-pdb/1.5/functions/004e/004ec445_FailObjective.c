/*
 * Entry: 004ec445
 * Name: FailObjective
 * Namespace: Global
 * Signature: void FailObjective(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FailObjective(long param_1)

{
  char **ppcVar1;
  int iVar2;
  char **unaff_EDI;
  char *unaff_retaddr;
  char *pcVar3;
  
  iVar2 = VerifyObjective(od.NumObjs,0x5e70e0,unaff_EDI,unaff_retaddr);
  if (iVar2 != 0) {
    ppcVar1 = od.FailText + param_1 + 0xf;
    pcVar3 = *ppcVar1;
    if (((uint)pcVar3 & 4) == 0) {
      if (((uint)pcVar3 & 2) == 0) {
        if (((uint)pcVar3 & 1) != 0) {
          DEBUG_systemWarning("Objective %d is hidden... failing anyway");
        }
        *ppcVar1 = (char *)((uint)*ppcVar1 | 4);
        return;
      }
      pcVar3 = "Objective %d already succeeded... cannot fail";
    }
    else {
      pcVar3 = "Objective %d already failed...";
    }
    DEBUG_systemWarning(pcVar3);
  }
  return;
}
