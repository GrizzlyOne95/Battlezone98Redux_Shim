
void __thiscall FUN_005e5cc0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847900;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_004812d0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = TracerClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_0047b6c0(0x54ae04bc,0xfd5bbc6f,local_24,0);
  if (local_24[0] == '\0') {
    param_1[0x1e] = *(undefined4 *)(param_2 + 0x78);
  }
  else {
    uVar2 = FUN_0068bed0(local_24,uVar1);
    param_1[0x1e] = uVar2;
  }
  FUN_00589760(0x54ae04bc,0xc74275c8,param_1 + 0x1f,DAT_0091755c);
  FUN_00589800(0x54ae04bc,0xbba723cc,param_1 + 0x20,0);
  FUN_00589800(0x54ae04bc,0x67d7c578,param_1 + 0x21,0x41280000);
  FUN_00589800(0x54ae04bc,0x8069b6ca,param_1 + 0x22,0x3d4ccccd);
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

