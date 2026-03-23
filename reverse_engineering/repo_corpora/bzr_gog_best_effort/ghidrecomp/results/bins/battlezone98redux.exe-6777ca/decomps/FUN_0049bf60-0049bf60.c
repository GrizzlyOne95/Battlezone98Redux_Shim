
void __fastcall FUN_0049bf60(int param_1)

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
  FUN_00589430("cnstblob.odf");
  local_8 = 0;
  FUN_0047b6c0(0x8b188e5f,0x5df29add,local_24,"bpuff.0");
  uVar2 = FUN_0068bed0(local_24,uVar1);
  *(undefined4 *)(param_1 + 0x16c) = uVar2;
  FUN_00589760(0x8b188e5f,0xdeb6a738,param_1 + 0x174,0xe);
  FUN_00589760(0x8b188e5f,0x8df5df5d,param_1 + 0x178,3);
  *(undefined4 *)(param_1 + 0x170) = 0;
  *(int *)(param_1 + 0x168) = param_1 + 0x28;
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

