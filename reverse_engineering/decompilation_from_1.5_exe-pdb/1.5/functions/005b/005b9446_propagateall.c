/*
 * Entry: 005b9446
 * Name: propagateall
 * Namespace: Global
 * Signature: uint propagateall(global_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl propagateall(global_State *param_1)

{
  int iVar1;
  int unaff_ESI;
  global_State *unaff_EDI;
  uint uVar2;
  
  uVar2 = 0;
  iVar1 = *(int *)(unaff_ESI + 0x24);
  while (iVar1 != 0) {
    iVar1 = propagatemark(unaff_EDI);
    uVar2 = uVar2 + iVar1;
    iVar1 = *(int *)(unaff_ESI + 0x24);
  }
  return uVar2;
}
