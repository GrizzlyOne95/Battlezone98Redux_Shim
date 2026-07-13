/*
 * Entry: 005c5f7f
 * Name: invertjump
 * Namespace: Global
 * Signature: void invertjump(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl invertjump(FuncState *param_1,expdesc *param_2)

{
  uint uVar1;
  uint *puVar2;
  FuncState *unaff_ESI;
  int unaff_retaddr;
  
  puVar2 = getjumpcontrol(unaff_ESI,unaff_retaddr);
  uVar1 = *puVar2;
  *puVar2 = ((uint)((uVar1 & 0x3fc0) == 0) * 0x40 ^ uVar1) & 0x3fc0 ^ uVar1;
  return;
}
