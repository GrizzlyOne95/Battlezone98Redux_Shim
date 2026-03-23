
void FUN_007f1a90(undefined4 param_1,undefined4 param_2,undefined1 *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864018;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  uVar2 = FUN_007f2560(local_2c,param_2,uVar1);
  local_8 = 0;
  local_2d = FUN_007edae0(param_1,&local_2e,&DAT_0260c032,*param_3);
  local_8 = 0xffffffff;
  FUN_00430320(uVar1,uVar2);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

