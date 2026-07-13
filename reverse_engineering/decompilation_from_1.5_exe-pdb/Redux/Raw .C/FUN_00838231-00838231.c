
void FUN_00838231(undefined4 param_1)

{
  int iVar1;
  undefined1 local_6c [100];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0082e171(param_1,1,local_6c);
  if (iVar1 != 0) {
    iVar1 = FUN_0082e08b(param_1,&DAT_0087d188,local_6c);
    if (iVar1 != 0) {
      iVar1 = FUN_0082c99e(param_1,0xffffffff);
      if (iVar1 == 0) goto LAB_00838289;
    }
  }
  FUN_0082bc39(param_1,"\'module\' not called from a Lua function");
LAB_00838289:
  FUN_0082cdd2(param_1,0xfffffffe);
  FUN_0082d08e(param_1,0xfffffffe);
  FUN_0082d226(param_1,0xfffffffe);
  FUN_0083e885();
  return;
}

