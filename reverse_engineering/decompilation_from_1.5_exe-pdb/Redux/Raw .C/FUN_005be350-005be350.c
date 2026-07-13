
void __thiscall FUN_005be350(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847900;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004812d0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = RocketClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0xbfed7b6f,0x278d7166,param_1 + 0x1e,*(undefined4 *)(param_2 + 0x78));
  FUN_00589800(0xbfed7b6f,0xf7c7cb9c,param_1 + 0x1f,*(undefined4 *)(param_2 + 0x7c));
  FUN_0047b6c0(0xbfed7b6f,0xb051e2db,local_24,0);
  if (local_24[0] == '\0') {
    param_1[0x20] = *(undefined4 *)(param_2 + 0x80);
  }
  else {
    uVar1 = FUN_0068bed0(local_24);
    param_1[0x20] = uVar1;
  }
  FUN_00589760(0xbfed7b6f,0x5d27caba,param_1 + 0x21,*(undefined4 *)(param_2 + 0x84));
  FUN_00589800(0xbfed7b6f,0x1ceb10c5,param_1 + 0x22,*(undefined4 *)(param_2 + 0x88));
  FUN_0047b6c0(0xbfed7b6f,0x14e4e216,local_24,0);
  if (local_24[0] == '\0') {
    param_1[0x23] = *(undefined4 *)(param_2 + 0x8c);
  }
  else {
    uVar1 = FUN_0068bed0(local_24);
    param_1[0x23] = uVar1;
  }
  FUN_00589760(0xbfed7b6f,0x91cf383d,param_1 + 0x24,*(undefined4 *)(param_2 + 0x90));
  FUN_00589800(0xbfed7b6f,0xf3e8cfc6,param_1 + 0x25,*(undefined4 *)(param_2 + 0x94));
  FUN_00589800(0xbfed7b6f,0x80c3efaa,param_1 + 0x26,*(undefined4 *)(param_2 + 0x98));
  FUN_00589800(0xbfed7b6f,0x40a86add,param_1 + 0x27,*(undefined4 *)(param_2 + 0x9c));
  FUN_00589800(0xbfed7b6f,0x8566cba4,param_1 + 0x28,*(undefined4 *)(param_2 + 0xa0));
  FUN_00589800(0xbfed7b6f,&DAT_01f6a810,param_1 + 0x29,
               (float)param_1[0x28] / *(float *)(param_2 + 0x54));
  FUN_00589800(0xbfed7b6f,0x78049c9,param_1 + 0x2c,1.0 / *(float *)(param_2 + 0xb0));
  param_1[0x2c] = 1.0 / (float)param_1[0x2c];
  FUN_0047b6c0(0xbfed7b6f,0x88f1ef89,local_24,0);
  if (local_24[0] == '\0') {
    param_1[0x2a] = *(undefined4 *)(param_2 + 0xa8);
  }
  else {
    uVar1 = FUN_0068bed0(local_24);
    param_1[0x2a] = uVar1;
  }
  FUN_00589760(0xbfed7b6f,0xdd33060c,param_1 + 0x2b,*(undefined4 *)(param_2 + 0xac));
  FUN_00589800(0xbfed7b6f,0x2776564d,param_1 + 0x2d,*(undefined4 *)(param_2 + 0xb4));
  FUN_0047b6c0(0xbfed7b6f,0x8b69afae,local_24,0);
  if (local_24[0] == '\0') {
    param_1[0x2e] = *(undefined4 *)(param_2 + 0xb8);
  }
  else {
    uVar1 = FUN_0068bed0(local_24);
    param_1[0x2e] = uVar1;
  }
  FUN_00589c20(0xbfed7b6f,0x2b341d45,param_1 + 0x30,*(undefined4 *)(param_2 + 0xc0),
               *(undefined4 *)(param_2 + 0xc4));
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

