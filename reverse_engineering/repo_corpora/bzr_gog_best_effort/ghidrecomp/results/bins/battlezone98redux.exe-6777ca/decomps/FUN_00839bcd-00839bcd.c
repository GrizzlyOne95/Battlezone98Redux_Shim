
void FUN_00839bcd(int param_1)

{
  short *psVar1;
  int iVar2;
  
  FUN_0083a034(param_1);
  do {
    iVar2 = FUN_00839963(*(undefined4 *)(param_1 + 0x10));
    if (iVar2 != 0) break;
    iVar2 = FUN_0083b46f(param_1);
    FUN_0083b6c3(param_1,0x3b);
    *(uint *)(*(int *)(param_1 + 0x30) + 0x24) = (uint)*(byte *)(*(int *)(param_1 + 0x30) + 0x32);
  } while (iVar2 == 0);
  psVar1 = (short *)(*(int *)(param_1 + 0x34) + 0x34);
  *psVar1 = *psVar1 + -1;
  return;
}

