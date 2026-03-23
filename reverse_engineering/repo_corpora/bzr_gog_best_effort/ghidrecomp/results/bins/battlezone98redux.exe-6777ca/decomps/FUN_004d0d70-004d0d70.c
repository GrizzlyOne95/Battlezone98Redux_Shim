
void __fastcall FUN_004d0d70(int param_1)

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
  FUN_00589430("fireball.odf");
  local_8 = 0;
  FUN_0047b6c0(0x3d017c29,0xbc5e1073,local_24,"particle.0");
  uVar2 = FUN_0068bed0(local_24,uVar1);
  *(undefined4 *)(param_1 + 0x630) = uVar2;
  FUN_00589760(0x3d017c29,0xd045e882,param_1 + 0x634,0x10);
  FUN_00589800(0x3d017c29,0x1ceb4a7a,param_1 + 0x638,0x40a00000);
  FUN_00589800(0x3d017c29,0x91dcfcce,param_1 + 0x63c,0x3f800000);
  FUN_00589800(0x3d017c29,0x83a961da,param_1 + 0x640,0x3f800000);
  *(float *)(param_1 + 0x640) =
       ((*(float *)(param_1 + 0x640) - 1.0) * *(float *)(param_1 + 0x63c) *
       *(float *)(param_1 + 0x638)) / (float)*(int *)(param_1 + 0x634);
  FUN_0047b6c0(0x3d017c29,0x88f1ef89,local_24,"particle.0");
  uVar2 = FUN_0068bed0(local_24);
  *(undefined4 *)(param_1 + 0x648) = uVar2;
  FUN_00589760(0x3d017c29,0xdd33060c,param_1 + 0x64c,0x10);
  FUN_00589800(0x3d017c29,0x567840fc,param_1 + 0x650,0x3f000000);
  FUN_00589800(0x3d017c29,&DAT_01f6a810,param_1 + 0x654,0x3d4ccccd);
  FUN_00589800(0x3d017c29,0x8566cba4,param_1 + 0x658,0x3ecccccd);
  FUN_00589800(0x3d017c29,0x2a532704,param_1 + 0x65c,0x3f800000);
  FUN_00589800(0x3d017c29,0xbb8ad7d1,param_1 + 0x660,0x40400000);
  FUN_00589800(0x3d017c29,0x40a86add,param_1 + 0x664,0x3f4ccccd);
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

