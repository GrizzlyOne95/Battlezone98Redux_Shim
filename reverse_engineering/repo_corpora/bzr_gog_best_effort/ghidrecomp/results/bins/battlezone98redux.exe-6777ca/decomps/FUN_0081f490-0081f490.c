
void FUN_0081f490(undefined4 *param_1,float param_2,float param_3,float param_4,float param_5)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 local_60 [64];
  undefined8 local_20;
  float local_18;
  float local_14;
  float local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_20 = FUN_008205a0(param_2 * 0.5);
  local_c = (undefined4)((ulonglong)local_20 >> 0x20);
  local_10 = (float)local_20;
  local_18 = param_3 * local_10;
  local_14 = param_4 * local_10;
  local_10 = param_5 * local_10;
  puVar1 = (undefined4 *)FUN_0081efe0(local_60,&local_18);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *puVar1;
    puVar1 = puVar1 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

