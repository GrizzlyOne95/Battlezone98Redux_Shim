
void FUN_007f3b70(undefined1 *param_1,undefined4 param_2,undefined1 *param_3,undefined1 *param_4)

{
  char cVar1;
  undefined1 auStack_ac [4];
  undefined4 uStack_a8;
  undefined1 *puStack_a4;
  undefined1 *puStack_a0;
  undefined1 *puStack_9c;
  undefined1 *puStack_98;
  undefined1 *puStack_94;
  uint uStack_90;
  undefined1 local_80 [20];
  undefined1 *local_6c;
  undefined1 *local_58;
  undefined1 *local_54;
  undefined1 *local_50;
  undefined1 local_4c [4];
  undefined1 local_48 [9];
  undefined1 local_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864050;
  local_10 = ExceptionList;
  uStack_90 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_94 = param_4;
  puStack_98 = local_48;
  puStack_9c = (undefined1 *)0x7f3ba8;
  local_14 = uStack_90;
  FUN_007f4b30();
  puStack_94 = param_4;
  puStack_98 = local_4c;
  puStack_9c = (undefined1 *)0x7f3bb8;
  FUN_007f4b50();
  local_50 = (undefined1 *)&puStack_94;
  puStack_98 = local_4c;
  puStack_9c = (undefined1 *)0x7f3bca;
  FUN_00447eb0();
  local_58 = (undefined1 *)&puStack_98;
  puStack_9c = local_48;
  puStack_a0 = (undefined1 *)0x7f3bd9;
  FUN_00447eb0();
  puStack_9c = param_3;
  puStack_a0 = (undefined1 *)param_2;
  puStack_a4 = param_1;
  uStack_a8 = 0x7f3bf0;
  puStack_9c = (undefined1 *)FUN_004324a0();
  puStack_a0 = (undefined1 *)0x7f3bf9;
  FUN_007eb400();
  local_3f = 0;
  puStack_94 = (undefined1 *)0x0;
  puStack_98 = param_4;
  local_54 = auStack_ac;
  FUN_007eaec0(local_80);
  cVar1 = FUN_007f4b70();
  if (cVar1 != '\0') {
    while( true ) {
      puStack_94 = (undefined1 *)0x7f3c33;
      cVar1 = FUN_007f4a70();
      if (cVar1 != '\0') break;
      puStack_94 = (undefined1 *)0xffffffff;
      puStack_98 = param_1;
      puStack_9c = (undefined1 *)0x7f3c4c;
      FUN_007ed7e0();
      local_8 = 0;
      puStack_94 = param_1;
      puStack_98 = (undefined1 *)0x7f3c5f;
      FUN_007ed940();
      local_8._0_1_ = 1;
      puStack_94 = &DAT_0260c032;
      puStack_98 = param_3;
      puStack_9c = (undefined1 *)param_2;
      puStack_a0 = param_1;
      puStack_a4 = (undefined1 *)0x7f3c7f;
      cVar1 = FUN_007f4be0();
      if (cVar1 == '\0') {
        local_3d = 0;
        local_8 = (uint)local_8._1_3_ << 8;
        puStack_94 = (undefined1 *)0x7f3c96;
        FUN_007ed6c0();
        local_8 = 0xffffffff;
        puStack_94 = (undefined1 *)0x7f3ca5;
        FUN_007ed880();
        goto LAB_007f3d34;
      }
      local_3e = 0;
      puStack_94 = (undefined1 *)0x0;
      puStack_98 = param_4;
      local_6c = auStack_ac;
      FUN_007eaec0(local_80);
      cVar1 = FUN_007f4b70();
      if (cVar1 == '\0') {
        local_8 = (uint)local_8._1_3_ << 8;
        puStack_94 = (undefined1 *)0x7f3ce7;
        FUN_007ed6c0();
        local_8 = 0xffffffff;
        puStack_94 = (undefined1 *)0x7f3cf6;
        FUN_007ed880();
        break;
      }
      local_8 = (uint)local_8._1_3_ << 8;
      puStack_94 = (undefined1 *)0x7f3d04;
      FUN_007ed6c0();
      puStack_94 = (undefined1 *)0x1;
      puStack_98 = (undefined1 *)0xffffffff;
      puStack_9c = (undefined1 *)0x7f3d10;
      FUN_007ed8e0();
      local_8 = 0xffffffff;
      puStack_94 = (undefined1 *)0x7f3d1f;
      FUN_007ed880();
    }
    puStack_94 = param_1;
    puStack_98 = (undefined1 *)0x7f3d2d;
    FUN_007eba50();
  }
LAB_007f3d34:
  ExceptionList = local_10;
  uStack_90 = 0x7f3d49;
  FUN_0083e885();
  return;
}

