
void __fastcall FUN_004c9480(int param_1)

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
  FUN_00589430("engsplsh.odf");
  local_8 = 0;
  FUN_0047b6c0(0xb571e03c,0x7caf4e69,local_24,"splash.0");
  uVar2 = FUN_0068bed0(local_24,uVar1);
  *(undefined4 *)(param_1 + 0x122c) = uVar2;
  FUN_00589760(0xb571e03c,0xc4ca506c,param_1 + 0x1234,0xe);
  FUN_00589760(0xb571e03c,0x16194e31,param_1 + 0x1238,3);
  FUN_00589800(0xb571e03c,0xb421904,param_1 + 0x123c,0x3fc00000);
  *(undefined4 *)(param_1 + 0x1230) = 0;
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

