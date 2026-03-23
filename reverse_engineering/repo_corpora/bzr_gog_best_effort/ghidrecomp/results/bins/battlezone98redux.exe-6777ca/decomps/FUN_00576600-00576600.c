
undefined4 FUN_00576600(undefined4 param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  void *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b95c;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar3 = FUN_00578c20(local_28,param_1);
  FID_conflict_begin(local_2c);
  cVar1 = FUN_004221b0(uVar3);
  if (cVar1 != '\0') {
    uVar3 = FUN_0041f870(param_2,param_4,uVar2);
    uVar3 = FUN_0081e820("Adding Player %s (ID %lu, Team %d)\n",uVar3);
    FUN_0081e710(uVar3);
    local_18 = operator_new(0x1b8);
    local_8 = 0;
    if (local_18 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00575920(param_1,param_2,param_3,param_4);
    }
    local_20 = local_1c;
    local_8 = 0xffffffff;
    local_24 = local_1c;
    local_14 = (int *)FUN_0045ca50();
    if (local_14 != (int *)0x0) {
      (**(code **)(*local_14 + 0x24))(local_24);
    }
  }
  ExceptionList = local_10;
  return 1;
}

