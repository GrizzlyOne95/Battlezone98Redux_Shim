
void __fastcall FUN_0058b500(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849508;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00589430("particle.odf");
  local_8 = 0;
  FUN_0047b6c0(0x92033d5a,0xf50ddfe,local_24,"particle.0");
  uVar2 = FUN_0068bed0(local_24,uVar1);
  *(undefined4 *)(param_1 + 0x3030) = uVar2;
  FUN_00589760(0x92033d5a,0x9ce7acd5,param_1 + 0x3034,0x10);
  FUN_00589800(0x92033d5a,0x531e553d,param_1 + 0x3040,0x3f000000);
  FUN_00589800(0x92033d5a,0xf7e89ce2,param_1 + 0x3038,0x3f000000);
  FUN_00589800(0x92033d5a,0xc7dc5ce9,param_1 + 0x303c,0x3dcccccd);
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

