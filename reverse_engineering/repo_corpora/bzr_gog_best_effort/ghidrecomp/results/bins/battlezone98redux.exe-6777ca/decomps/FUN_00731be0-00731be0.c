
void __thiscall FUN_00731be0(undefined4 *param_1,undefined4 param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859e33;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = (undefined8 *)forward<>(8,*param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (puVar1 != (undefined8 *)0x0) {
    puVar2 = (undefined8 *)FUN_00417780(param_2);
    *puVar1 = *puVar2;
  }
  ExceptionList = local_10;
  return;
}

