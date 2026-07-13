
void __fastcall FUN_00814fa0(int *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_48 [52];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864b78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  uVar2 = FUN_00815240(local_48,param_1[1]);
  local_8 = 0;
  FUN_0080f7d0(*param_1 + 0x18,uVar2,uVar1);
  FUN_0080f1c0(uVar2);
  local_8 = 0xffffffff;
  FUN_00800170();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

