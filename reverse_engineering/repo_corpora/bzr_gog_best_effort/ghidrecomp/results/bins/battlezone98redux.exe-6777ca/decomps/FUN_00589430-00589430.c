
undefined4 * FUN_00589430(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_2c [4];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  void *local_1c;
  undefined1 local_18 [4];
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084641c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_24 = FUN_00446460(param_1,0x811c9dc5,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FUN_0044eb20(local_18,&local_24);
  uVar2 = FUN_0044eaa0(local_2c);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 == '\0') {
    local_1c = operator_new(0x38);
    local_8 = 0;
    if (local_1c == (void *)0x0) {
      local_20 = 0;
    }
    else {
      local_20 = FUN_00588e00(param_1);
    }
    local_28 = local_20;
    local_8 = 0xffffffff;
    puVar4 = (undefined4 *)FUN_0058a0c0(&local_24);
    *puVar4 = local_28;
    *local_14 = local_28;
  }
  else {
    iVar3 = FUN_0042da60();
    *local_14 = *(undefined4 *)(iVar3 + 4);
    *(int *)*local_14 = *(int *)*local_14 + 1;
  }
  ExceptionList = local_10;
  return local_14;
}

