/*
 * Entry: 005c3a00
 * Name: enterblock
 * Namespace: Global
 * Signature: void enterblock(FuncState * param_1, BlockCnt * param_2, uchar param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl enterblock(FuncState *param_1,BlockCnt *param_2,uchar param_3)

{
  undefined4 *in_EAX;
  int in_ECX;
  undefined1 in_DL;
  
  in_EAX[1] = 0xffffffff;
  *(undefined1 *)((int)in_EAX + 10) = in_DL;
  *(undefined1 *)(in_EAX + 2) = *(undefined1 *)(in_ECX + 0x32);
  *(undefined1 *)((int)in_EAX + 9) = 0;
  *in_EAX = *(undefined4 *)(in_ECX + 0x14);
  *(undefined4 **)(in_ECX + 0x14) = in_EAX;
  return;
}
