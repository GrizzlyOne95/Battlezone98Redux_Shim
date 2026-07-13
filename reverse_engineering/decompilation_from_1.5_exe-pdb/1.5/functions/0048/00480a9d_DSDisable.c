/*
 * Entry: 00480a9d
 * Name: DSDisable
 * Namespace: Global
 * Signature: int DSDisable(IDirectSound * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl DSDisable(IDirectSound **param_1)

{
  int *piVar1;
  int *unaff_ESI;
  
  piVar1 = (int *)*unaff_ESI;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *unaff_ESI = 0;
  }
  return 1;
}
