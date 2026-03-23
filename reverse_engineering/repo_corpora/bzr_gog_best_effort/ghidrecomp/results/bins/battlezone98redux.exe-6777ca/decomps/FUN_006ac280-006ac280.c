
void __fastcall FUN_006ac280(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int *local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0084fff0;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  for (local_18 = *(int **)(param_1 + 0x1c); local_18 != (int *)0x0; local_18 = (int *)local_18[4])
  {
    (**(code **)(*local_18 + 4))();
  }
  while (*(int *)(param_1 + 0x1c) != 0) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x10);
    _InternalDeleteHelper<>(*(undefined4 *)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = uVar1;
  }
  local_8 = local_8 & 0xffffff00;
  FUN_006ac0b0(uVar2);
  local_8 = 0xffffffff;
  FUN_00417c60();
  ExceptionList = local_10;
  return;
}

