
void FUN_0083a565(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int local_20 [6];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = *(int *)(param_1 + 4);
  iVar2 = *(int *)(param_1 + 0x30);
  if (*(int *)(param_1 + 0x10) == 0x28) {
    if (iVar1 != *(int *)(param_1 + 8)) {
      FUN_008390b7(param_1,"ambiguous syntax (function call x new statement)");
    }
    FUN_00838ffd(param_1);
    if (*(int *)(param_1 + 0x10) == 0x29) {
      local_20[0] = 0;
    }
    else {
      FUN_0083a118(param_1,local_20);
      FUN_0083ce76(iVar2,local_20,0xffffffff);
    }
    FUN_00839b38(param_1,0x29,0x28,iVar1);
  }
  else if (*(int *)(param_1 + 0x10) == 0x7b) {
    FUN_00839e40(param_1,local_20);
  }
  else {
    if (*(int *)(param_1 + 0x10) != 0x11e) {
      FUN_008390b7(param_1,"function arguments expected");
      goto LAB_0083a67a;
    }
    FUN_00839dc7(param_1,local_20,*(undefined4 *)(param_1 + 0x18));
    FUN_00838ffd(param_1);
  }
  iVar3 = param_2[2];
  if ((local_20[0] == 0xd) || (local_20[0] == 0xe)) {
    iVar4 = -1;
  }
  else {
    if (local_20[0] != 0) {
      FUN_0083c800(iVar2,local_20);
    }
    iVar4 = (*(int *)(iVar2 + 0x24) - iVar3) + -1;
  }
  uVar5 = FUN_0083c5d2(iVar2,0x1c,iVar3,iVar4 + 1,2);
  param_2[4] = 0xffffffff;
  param_2[5] = 0xffffffff;
  *param_2 = 0xd;
  param_2[2] = uVar5;
  FUN_0083c857(iVar2,iVar1);
  *(int *)(iVar2 + 0x24) = iVar3 + 1;
LAB_0083a67a:
  FUN_0083e885();
  return;
}

