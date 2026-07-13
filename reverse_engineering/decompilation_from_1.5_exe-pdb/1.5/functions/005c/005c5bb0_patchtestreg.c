/*
 * Entry: 005c5bb0
 * Name: patchtestreg
 * Namespace: Global
 * Signature: int patchtestreg(FuncState * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl patchtestreg(FuncState *param_1,int param_2,int param_3)

{
  uint uVar1;
  uint *puVar2;
  uint in_EDX;
  FuncState *unaff_ESI;
  int unaff_retaddr;
  
  puVar2 = getjumpcontrol(unaff_ESI,unaff_retaddr);
  uVar1 = *puVar2;
  if (((byte)uVar1 & 0x3f) != 0x1b) {
    return 0;
  }
  if ((in_EDX == 0xff) || (in_EDX == uVar1 >> 0x17)) {
    *puVar2 = (uVar1 & 0xffb5ffff | 0x340000) >> 0x11 | uVar1 & 0x7fc000;
  }
  else {
    *puVar2 = (in_EDX << 6 ^ uVar1) & 0x3fc0 ^ uVar1;
  }
  return 1;
}
