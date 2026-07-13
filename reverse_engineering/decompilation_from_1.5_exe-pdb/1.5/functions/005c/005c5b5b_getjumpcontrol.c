/*
 * Entry: 005c5b5b
 * Name: getjumpcontrol
 * Namespace: Global
 * Signature: uint * getjumpcontrol(FuncState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint * __cdecl getjumpcontrol(FuncState *param_1,int param_2)

{
  int *in_EAX;
  uint *puVar1;
  int in_ECX;
  
  puVar1 = (uint *)(*(int *)(*in_EAX + 0xc) + in_ECX * 4);
  if ((0 < in_ECX) && ((luaP_opmodes[puVar1[-1] & 0x3f] & 0x80) != 0)) {
    puVar1 = puVar1 + -1;
  }
  return puVar1;
}
