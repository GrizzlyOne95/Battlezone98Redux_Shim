
void __thiscall FUN_004c0bb0(int param_1,undefined4 param_2)

{
  undefined1 local_50 [16];
  undefined4 local_40;
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_18;
  int local_14;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(undefined4 *)(param_1 + 0x28) = param_2;
  FUN_0043a990(local_50);
  local_40 = 1;
  FUN_0043a9e0(local_24);
  local_18 = 1;
  local_20 = 0x41;
  local_14 = (int)(*(float *)(param_1 + 0x28) * 10.0);
  FUN_0043aa30("gquak01.wav",0,local_50,local_24);
  FUN_0083e885();
  return;
}

