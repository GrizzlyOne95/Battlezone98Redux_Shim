
void FUN_004b5690(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008499b1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = (undefined4 *)forward<>(4,param_3,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_00417780(param_4);
    *puVar1 = *puVar2;
  }
  ExceptionList = local_10;
  return;
}

