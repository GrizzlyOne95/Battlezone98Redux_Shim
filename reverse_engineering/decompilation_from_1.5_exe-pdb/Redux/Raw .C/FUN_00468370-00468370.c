
void FUN_00468370(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = param_1;
  local_10 = 0x447a0000;
  local_c = param_2;
  local_20 = param_3;
  local_1c = 0x447a0000;
  local_18 = param_4;
  FUN_0058fb40(0,0);
  puVar1 = (undefined4 *)FUN_0058fe90(&local_14,&local_20);
  if ((puVar1 != (undefined4 *)0x0) && (puVar1 != (undefined4 *)0x0)) {
    (**(code **)*puVar1)(1);
  }
  FUN_0083e885();
  return;
}

