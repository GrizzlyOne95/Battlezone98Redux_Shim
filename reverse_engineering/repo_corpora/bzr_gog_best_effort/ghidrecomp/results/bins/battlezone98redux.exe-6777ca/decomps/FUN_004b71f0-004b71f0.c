
void FUN_004b71f0(float *param_1,float param_2,undefined4 param_3)

{
  undefined1 local_28 [4];
  undefined4 local_24;
  int local_20;
  int local_1c;
  int *local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = DAT_00917554;
  (**(code **)(*DAT_00917554 + 0x24))(*param_1,param_1[2],&local_1c,&local_24);
  local_14 = *param_1 + param_2;
  local_10 = param_1[1];
  local_c = param_1[2];
  (**(code **)(*local_18 + 0x24))(local_14,local_c,&local_20,local_28);
  FUN_0068ad00(DAT_00917580,local_1c,local_24,local_20 - local_1c,0x18,param_3,0);
  FUN_0083e885();
  return;
}

