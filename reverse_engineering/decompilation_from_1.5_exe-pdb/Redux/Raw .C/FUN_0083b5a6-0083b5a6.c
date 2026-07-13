
void FUN_0083b5a6(int param_1,undefined4 param_2,uint param_3)

{
  short *psVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0083a034(param_1);
  if (*(int *)(param_1 + 0x10) == 0x23) {
    uVar4 = 2;
  }
  else if (*(int *)(param_1 + 0x10) == 0x2d) {
    uVar4 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x10) != 0x10e) {
      FUN_0083b250(param_1,param_2);
      goto LAB_0083b60e;
    }
    uVar4 = 1;
  }
  FUN_00838ffd(param_1);
  FUN_0083b5a6(param_1,param_2,8);
  FUN_0083cca2(*(undefined4 *)(param_1 + 0x30),uVar4,param_2);
LAB_0083b60e:
  iVar2 = FUN_0083a71a(*(undefined4 *)(param_1 + 0x10));
  while ((iVar2 != 0xf && (param_3 < (byte)(&DAT_00870750)[iVar2 * 2]))) {
    FUN_00838ffd(param_1);
    FUN_0083c95a(*(undefined4 *)(param_1 + 0x30),iVar2,param_2);
    iVar3 = FUN_0083b5a6(param_1,local_20,(&DAT_00870751)[iVar2 * 2]);
    FUN_0083cafa(*(undefined4 *)(param_1 + 0x30),iVar2,param_2,local_20);
    iVar2 = iVar3;
  }
  psVar1 = (short *)(*(int *)(param_1 + 0x34) + 0x34);
  *psVar1 = *psVar1 + -1;
  FUN_0083e885();
  return;
}

