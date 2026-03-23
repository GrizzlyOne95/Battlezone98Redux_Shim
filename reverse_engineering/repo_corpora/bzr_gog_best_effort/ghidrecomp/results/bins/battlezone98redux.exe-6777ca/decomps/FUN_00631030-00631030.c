
undefined4 FUN_00631030(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d378;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00438c70(param_3);
  local_8 = 0;
  puVar2 = (undefined4 *)FUN_0042d8c0(local_1c);
  local_18 = *puVar2;
  uVar3 = FUN_00416410(uVar1);
  uVar4 = get(uVar3);
  FUN_006310c0(local_20,local_18,uVar4,uVar3);
  ExceptionList = local_10;
  return local_14;
}

