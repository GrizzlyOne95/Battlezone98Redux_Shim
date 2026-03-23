
void FUN_00437c50(undefined4 param_1)

{
  undefined4 uVar1;
  undefined1 local_34 [16];
  undefined4 local_24;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0043a990(local_34);
  local_24 = 0x14;
  uVar1 = FUN_0043ac70("avconsv9.wav",0);
  FUN_0043aaa0(uVar1);
  FUN_0043a910(0xfffffffe,0xfffffffe,param_1);
  FUN_0043aa30("avconsv9.wav",0,local_34,0);
  FUN_0083e885();
  return;
}

