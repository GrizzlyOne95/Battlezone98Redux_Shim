
void FUN_0082a820(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845a61;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = (undefined4 *)forward<>(0x20,param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_00417780(param_2);
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar1 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar1 = puVar1 + 1;
    }
  }
  ExceptionList = local_10;
  return;
}

