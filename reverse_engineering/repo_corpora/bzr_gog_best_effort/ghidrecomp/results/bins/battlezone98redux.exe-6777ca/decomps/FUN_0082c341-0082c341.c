
void FUN_0082c341(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_6c [20];
  int local_58;
  undefined1 local_48 [64];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0082e171(param_1,param_2,local_6c);
  if (iVar1 != 0) {
    FUN_0082e08b(param_1,&DAT_0086ea0c,local_6c);
    if (0 < local_58) {
      FUN_0082cc9e(param_1,"%s:%d: ",local_48,local_58);
      goto LAB_0082c3a8;
    }
  }
  FUN_0082cd08(param_1,&DAT_008a1ad8,0);
LAB_0082c3a8:
  FUN_0083e885();
  return;
}

