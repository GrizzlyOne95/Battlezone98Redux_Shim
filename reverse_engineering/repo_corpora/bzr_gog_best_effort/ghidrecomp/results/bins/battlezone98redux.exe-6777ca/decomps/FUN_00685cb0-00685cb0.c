
void FUN_00685cb0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  int *piVar2;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>(param_1);
  local_8 = 0;
  piVar2 = (int *)(**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x164))(uVar1);
  piVar2 = (int *)(**(code **)(*piVar2 + 0x17c))(local_2c,ZERO_exref,IDENTITY_exref);
  local_8 = 0xffffffff;
  ~basic_string<>();
  (**(code **)(*piVar2 + 0x124))(param_2);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

