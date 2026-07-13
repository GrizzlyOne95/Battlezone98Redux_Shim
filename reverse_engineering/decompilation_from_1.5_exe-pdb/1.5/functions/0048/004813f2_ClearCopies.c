/*
 * Entry: 004813f2
 * Name: ClearCopies
 * Namespace: Global
 * Signature: void ClearCopies(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClearCopies(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = &copies[0].count;
  iVar2 = 0x1e;
  do {
    if ((_gas_object *)piVar1[1] != (_gas_object *)0x0) {
      *piVar1 = 0;
    }
    piVar1 = piVar1 + 4;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}
