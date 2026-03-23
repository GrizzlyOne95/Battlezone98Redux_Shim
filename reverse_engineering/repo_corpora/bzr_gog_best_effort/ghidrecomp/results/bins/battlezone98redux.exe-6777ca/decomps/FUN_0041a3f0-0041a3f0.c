
void __thiscall FUN_0041a3f0(int *param_1,undefined4 *param_2,int param_3,int param_4)

{
  longlong lVar1;
  undefined1 local_20;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = *param_2;
  local_14 = param_2[1];
  local_10 = 0;
  local_c = 0;
  (**(code **)(*param_1 + 4))(&local_18,0);
  lVar1 = FUN_00822ea0();
  *(longlong *)(param_1 + 0x20) = lVar1 + CONCAT44(param_4,param_3);
  if ((param_4 < 1) && ((param_4 < 0 || (param_3 == 0)))) {
    local_20 = 1;
  }
  else {
    local_20 = 0;
  }
  *(undefined1 *)(param_1 + 0x1f) = local_20;
  FUN_00418f30(1);
  FUN_0083e885();
  return;
}

