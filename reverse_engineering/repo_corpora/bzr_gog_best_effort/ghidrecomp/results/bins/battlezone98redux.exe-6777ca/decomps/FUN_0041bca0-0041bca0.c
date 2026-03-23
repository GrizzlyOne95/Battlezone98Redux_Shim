
undefined4 * FUN_0041bca0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844d28;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0041b7b0(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = TouchInputToggleActionButton::vftable;
  *(undefined1 *)(local_14 + 0x2a) = 1;
  FUN_00421e00(local_18,local_14 + 0x1f);
  uVar3 = FID_conflict_begin(local_1c);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 != '\0') {
    iVar4 = FUN_00421ea0(uVar2);
    if (*(int *)(iVar4 + 0x18) == 0) {
      local_14[2] = 0;
    }
    else {
      local_14[2] = 1;
    }
  }
  ExceptionList = local_10;
  return local_14;
}

