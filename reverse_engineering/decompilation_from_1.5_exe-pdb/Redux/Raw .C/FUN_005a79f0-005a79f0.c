
undefined4 * __thiscall FUN_005a79f0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  uint uVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847998;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004da0b0(param_2,param_3);
  local_8 = 0;
  *param_1 = PowerUp::vftable;
  param_1[6] = PowerUp::vftable;
  uVar3 = FUN_0045c4f0(param_2,uVar2);
  param_1[0x8a] = uVar3;
  *(undefined4 *)param_1[0x8a] = param_1[0x3c];
  FUN_004dbce0(0);
  if (((param_1[0x3c] == 0) || (*(int *)(param_1[0x3c] + 0x24) != 1)) ||
     (*(int *)(param_1[0x3c] + 0x28) == 0)) {
    FUN_0062e650(param_1[0x3d],param_1[0x3d] + 0xb0,param_1[0x3d] + 0xbc);
  }
  else {
    piVar1 = *(int **)(param_1[0x3c] + 0x28);
    *(int *)(param_1[0x3d] + 0xb0) = piVar1[3];
    *(int *)(param_1[0x3d] + 0xb4) = piVar1[7];
    *(int *)(param_1[0x3d] + 0xb8) = piVar1[0xb];
    *(int *)(param_1[0x3d] + 0xbc) = piVar1[*piVar1 + 2];
    *(int *)(param_1[0x3d] + 0xc0) = piVar1[piVar1[1] + 6];
    *(int *)(param_1[0x3d] + 0xc4) = piVar1[piVar1[2] + 10];
  }
  ExceptionList = local_10;
  return param_1;
}

