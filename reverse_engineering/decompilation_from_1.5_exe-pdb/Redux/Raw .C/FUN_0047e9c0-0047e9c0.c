
undefined4 * __thiscall FUN_0047e9c0(undefined4 *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847998;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004da0b0(param_2,param_3);
  local_8 = 0;
  *param_1 = Building::vftable;
  param_1[6] = Building::vftable;
  if ((*(int *)(param_3 + 0x30) == 0x74736261) && (*(int *)(param_3 + 0x34) == 0x726f)) {
    uVar2 = FUN_0046cfe0(uVar1);
    param_1[0x88] = uVar2;
  }
  param_1[0x8c] = 0;
  *(undefined1 *)(param_1 + 0x8d) = 1;
  ExceptionList = local_10;
  return param_1;
}

