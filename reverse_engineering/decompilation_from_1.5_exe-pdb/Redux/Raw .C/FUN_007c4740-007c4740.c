
void __thiscall FUN_007c4740(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b778;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(int *)(param_1 + 0x150) = *(int *)(param_1 + 0x150) + param_2;
  local_14 = uVar1;
  uVar2 = FUN_00482630(local_2c,*(undefined4 *)(param_1 + 0x150),uVar1);
  local_8 = 0;
  uVar2 = FUN_0041f870(uVar1,uVar2);
  (**(code **)(**(int **)(param_1 + 0x144) + 0x3c))(uVar2);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

