
void FUN_00834188(int param_1,int param_2)

{
  int iVar1;
  undefined1 local_6c [100];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (((param_1 != param_2) && (iVar1 = FUN_0082d2dc(param_2), iVar1 == 0)) &&
     (iVar1 = FUN_0082e171(param_2,0,local_6c), iVar1 < 1)) {
    FUN_0082c8f6(param_2);
  }
  FUN_0083e885();
  return;
}

