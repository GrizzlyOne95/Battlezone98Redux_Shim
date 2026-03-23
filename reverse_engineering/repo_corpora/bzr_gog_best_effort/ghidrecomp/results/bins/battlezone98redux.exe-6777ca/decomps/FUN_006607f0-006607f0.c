
void __fastcall FUN_006607f0(int param_1)

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
  FUN_00589430("portblob.odf");
  local_8 = 0;
  FUN_0047b6c0(0x27a808d4,0x724d9824,local_24,"rpuff.0");
  uVar2 = FUN_0068bed0(local_24,uVar1);
  *(undefined4 *)(param_1 + 0x1ac) = uVar2;
  FUN_0047b6c0(0x27a808d4,0xd0e3bee1,local_24,"bpuff.0");
  uVar2 = FUN_0068bed0(local_24);
  *(undefined4 *)(param_1 + 0x1b0) = uVar2;
  FUN_00589760(0x27a808d4,0xdeb6a738,param_1 + 0x1b8,0xe);
  FUN_00589760(0x27a808d4,0x8df5df5d,param_1 + 0x1bc,3);
  *(undefined4 *)(param_1 + 0x1b4) = 0;
  *(int *)(param_1 + 0x1a8) = param_1 + 0x28;
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

