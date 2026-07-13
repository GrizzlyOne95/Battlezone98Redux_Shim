/*
 * Entry: 005c5b3e
 * Name: getjump
 * Namespace: Global
 * Signature: int getjump(FuncState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl getjump(FuncState *param_1,int param_2)

{
  int *in_EAX;
  uint uVar1;
  int in_ECX;
  
  uVar1 = *(uint *)(*(int *)(*in_EAX + 0xc) + in_ECX * 4) >> 0xe;
  if (uVar1 == 0x1fffe) {
    return -1;
  }
  return (uVar1 - 0x1fffe) + in_ECX;
}
