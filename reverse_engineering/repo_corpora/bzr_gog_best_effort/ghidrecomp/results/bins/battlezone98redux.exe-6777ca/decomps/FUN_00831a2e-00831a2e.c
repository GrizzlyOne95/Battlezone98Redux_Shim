
void FUN_00831a2e(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = 0;
  local_20 = param_4;
  local_1c = param_5;
  local_28 = param_1;
  local_24 = param_3;
  FUN_0083bc96(local_14);
  FUN_00831758(local_14,0xc,&local_28);
  FUN_00831931(param_2,0,&local_28);
  FUN_0083e885();
  return;
}

