
undefined1
FUN_007f42a0(undefined4 param_1,undefined4 param_2,undefined1 *param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_3c [24];
  undefined1 local_24 [19];
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864088;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar2 = FUN_007df2f0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (iVar2 != 0) {
    uVar3 = FUN_00417780(param_4);
    uVar3 = FUN_00423b10(uVar3);
    FUN_007305f0(uVar3);
    local_8 = 0;
    FUN_007f0cc0(local_24,param_5,param_2);
    cVar1 = FUN_007df230(param_1,local_3c,param_3);
    if (cVar1 != '\0') {
      operator==<>(param_1,*param_3);
      local_11 = 1;
      local_8 = 0xffffffff;
      FUN_006cc6b0();
      ExceptionList = local_10;
      return local_11;
    }
    local_8 = 0xffffffff;
    FUN_006cc6b0();
  }
  ExceptionList = local_10;
  return 0;
}

