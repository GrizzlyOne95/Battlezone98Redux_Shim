
void FUN_007a47b0(undefined4 param_1,int param_2)

{
  uint uVar1;
  undefined1 local_24 [28];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_2 == 0) {
    FUN_007a7bb0();
  }
  else {
    FUN_007d6a70("Chat Message: %s\n",param_2);
    FUN_007a8030(&param_1,&param_2);
    FUN_007a7ab0(local_24);
    uVar1 = FUN_004170c0();
    if (0x14 < uVar1) {
      FUN_007a7a20();
    }
    FUN_00430250();
  }
  DAT_00945549 = 1;
  FUN_0083e885();
  return;
}

