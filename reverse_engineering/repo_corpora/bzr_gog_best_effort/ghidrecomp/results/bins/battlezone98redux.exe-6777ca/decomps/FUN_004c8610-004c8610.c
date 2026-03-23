
void __fastcall FUN_004c8610(int param_1)

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
  FUN_00589430("engflame.odf");
  local_8 = 0;
  FUN_0047b6c0(0x9e8ab786,0x14e4e216,local_24,"sun.0");
  uVar2 = FUN_0068bed0(local_24,uVar1);
  *(undefined4 *)(param_1 + 0x122c) = uVar2;
  FUN_00589760(0x9e8ab786,0x91cf383d,param_1 + 0x1230,1);
  FUN_00589800(0x9e8ab786,0xbfe61537,param_1 + 0x1234,0x40000000);
  FUN_00589800(0x9e8ab786,0xe8da7038,param_1 + 0x1238,0x3e4ccccd);
  FUN_0047b6c0(0x9e8ab786,0xb051e2db,local_24,"exhaust_b.0");
  uVar2 = FUN_0068bed0(local_24);
  *(undefined4 *)(param_1 + 0x123c) = uVar2;
  FUN_00589760(0x9e8ab786,0x5d27caba,param_1 + 0x1240,4);
  FUN_00589800(0x9e8ab786,0xcf21eb6c,param_1 + 0x1244,0x3f800000);
  FUN_00589800(0x9e8ab786,0xf7c7cb9c,param_1 + 0x1248,0x40400000);
  *(int *)(param_1 + 0x1228) = param_1 + 0x28;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) | 1;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfd;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) | 4;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xf7;
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

