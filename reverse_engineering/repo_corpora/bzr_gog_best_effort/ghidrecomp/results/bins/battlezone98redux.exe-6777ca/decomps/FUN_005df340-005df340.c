
void FUN_005df340(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 *local_28;
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084cb40;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00611aa0(param_1,param_2,param_3);
  local_8 = 0;
  *local_28 = TargetingGunClass::vftable;
  FUN_00589430(local_28 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589c20(0xce3a7e4a,0x760b0e1f,&local_34,param_2,param_3);
  uVar2 = FUN_00586c60(local_34,local_30,uVar1);
  local_28[0x24] = uVar2;
  FUN_0047b6c0(0xce3a7e4a,0xe4cf54db,local_28 + 0x20,param_1 + 0x80);
  FUN_00589800(0xce3a7e4a,0xd9356908,local_28 + 0x25,*(undefined4 *)(param_1 + 0x94));
  FUN_00589800(0xce3a7e4a,0x16c2de34,local_28 + 0x26,*(undefined4 *)(param_1 + 0x98));
  FUN_00589800(0xce3a7e4a,0xd76f37db,local_28 + 0x27,*(undefined4 *)(param_1 + 0x9c));
  FUN_00589760(0xce3a7e4a,0x9260ea63,local_28 + 0x28,*(undefined4 *)(param_1 + 0xa0));
  FUN_00589800(0xce3a7e4a,0x22c3372e,local_28 + 0x29,*(undefined4 *)(param_1 + 0xa4));
  FUN_0047b6c0(0xce3a7e4a,0x4e2778a,local_24,0);
  if (local_24[0] == '\0') {
    local_28[0x2a] = *(undefined4 *)(param_1 + 0xa8);
  }
  else {
    uVar2 = FUN_0068bed0(local_24);
    local_28[0x2a] = uVar2;
  }
  FUN_0047b6c0(0xce3a7e4a,0x748a8151,local_24,0);
  if (local_24[0] == '\0') {
    local_28[0x2b] = *(undefined4 *)(param_1 + 0xac);
  }
  else {
    uVar2 = FUN_0068bed0(local_24);
    local_28[0x2b] = uVar2;
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

