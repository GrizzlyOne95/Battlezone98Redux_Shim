
void FUN_0083b18d(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int local_20 [2];
  int local_18;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  piVar1 = *(int **)(param_1 + 0x30);
  FUN_00838ffd(param_1);
  iVar2 = FUN_00839963(*(undefined4 *)(param_1 + 0x10));
  if ((iVar2 == 0) && (*(int *)(param_1 + 0x10) != 0x3b)) {
    iVar2 = FUN_0083a118(param_1,local_20);
    if ((local_20[0] == 0xd) || (local_20[0] == 0xe)) {
      FUN_0083ce76(piVar1,local_20,0xffffffff);
      if ((local_20[0] == 0xd) && (iVar2 == 1)) {
        *(uint *)(*(int *)(*piVar1 + 0xc) + local_18 * 4) =
             *(uint *)(*(int *)(*piVar1 + 0xc) + local_18 * 4) & 0xffffffdd | 0x1d;
      }
      uVar3 = (uint)*(byte *)((int)piVar1 + 0x32);
      iVar2 = -1;
    }
    else if (iVar2 == 1) {
      uVar3 = FUN_0083c7b7();
    }
    else {
      FUN_0083c800(piVar1,local_20);
      uVar3 = (uint)*(byte *)((int)piVar1 + 0x32);
    }
  }
  else {
    iVar2 = 0;
    uVar3 = 0;
  }
  FUN_0083cd4c(piVar1,uVar3,iVar2);
  FUN_0083e885();
  return;
}

