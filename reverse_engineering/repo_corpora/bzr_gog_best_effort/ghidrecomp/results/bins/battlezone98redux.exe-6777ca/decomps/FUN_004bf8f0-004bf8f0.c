
void FUN_004bf8f0(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a01;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = (undefined4 *)forward<>(6,param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_00417780(param_2);
    *puVar1 = *puVar2;
    *(undefined2 *)(puVar1 + 1) = *(undefined2 *)(puVar2 + 1);
  }
  ExceptionList = local_10;
  return;
}

