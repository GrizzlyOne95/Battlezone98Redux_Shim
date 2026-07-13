
void FUN_0083515d(undefined4 param_1)

{
  int iVar1;
  undefined1 local_214 [524];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0082bbb2(param_1,1,6);
  FUN_0082d226(param_1,1);
  FUN_0082b98a(param_1,local_214);
  iVar1 = FUN_0082c6c8(param_1,FUN_00836400,local_214);
  if (iVar1 != 0) {
    FUN_0082bc39(param_1,"unable to dump given function");
  }
  FUN_0082c2cb(local_214);
  FUN_0083e885();
  return;
}

