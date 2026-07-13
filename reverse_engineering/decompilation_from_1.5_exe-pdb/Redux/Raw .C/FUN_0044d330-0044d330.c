
undefined4 * __thiscall
FUN_0044d330(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *local_24;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084673a;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0044dcd0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = MultiRender::vftable;
  FUN_0083ead2(param_1 + 0x1e,4,0x40,FUN_00423890,FUN_0044dc30);
  local_8._0_1_ = 1;
  param_1[0x1c] = *(undefined4 *)(param_2 + 0x108);
  if ((uint)param_1[0x1c] < 0x40) {
    param_1[0x5e] = 0;
    param_1[0x1d] = param_1 + 0x1e;
  }
  else {
    uVar1 = param_1[0x1c];
    uVar3 = -(uint)((int)((ulonglong)uVar1 * 4 >> 0x20) != 0) | (uint)((ulonglong)uVar1 * 4);
    local_24 = (uint *)FUN_0083d92c(-(uint)(0xfffffffb < uVar3) | uVar3 + 4,uVar2);
    local_8._0_1_ = 2;
    if (local_24 == (uint *)0x0) {
      local_24 = (uint *)0x0;
    }
    else {
      *local_24 = uVar1;
      FUN_0083ead2(local_24 + 1,4,uVar1,FUN_00423890,FUN_0044dc30);
      local_24 = local_24 + 1;
    }
    param_1[0x5e] = local_24;
    param_1[0x1d] = param_1[0x5e];
  }
  local_8._0_1_ = 1;
  for (local_18 = 0; local_18 < (int)param_1[0x1c]; local_18 = local_18 + 1) {
    if (*(int *)(*(int *)(param_2 + 0x104) + local_18 * 4) == 0) {
      FUN_0044dc60(0,0);
    }
    else {
      (**(code **)(**(int **)(*(int *)(param_2 + 0x104) + local_18 * 4) + 8))
                (param_1[0x1d] + local_18 * 4,param_4);
    }
  }
  ExceptionList = local_10;
  return param_1;
}

