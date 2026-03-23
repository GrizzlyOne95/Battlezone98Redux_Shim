
void __thiscall FUN_005b8b10(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c5e0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_0056b3c0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = RemoteDetonatorClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_0047b6c0(0xb7b58a5f,0x5b8f7784,local_24,0);
  if (local_24[0] == '\0') {
    param_1[0x26] = *(undefined4 *)(param_2 + 0x98);
  }
  else {
    uVar2 = FUN_0068bed0(local_24,uVar1);
    param_1[0x26] = uVar2;
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

