
void FUN_005fe690(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_c0 [12];
  undefined1 local_b4 [12];
  undefined1 local_a8 [12];
  undefined1 local_9c [12];
  undefined1 local_90 [12];
  undefined1 local_84 [12];
  undefined1 local_78 [12];
  undefined4 *local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d1d8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00461ba0(local_14);
  local_8 = 0;
  *local_6c = UnitTask::vftable;
  local_6c[4] = 0;
  local_6c[4] = param_1;
  if (param_2 == 0) {
    local_6c[5] = 0;
  }
  else {
    uVar1 = FUN_00477590(param_2);
    local_6c[5] = uVar1;
  }
  local_6c[2] = 0xd;
  local_6c[3] = 0xffffffff;
  *(undefined1 *)(local_6c + 7) = 0;
  local_6c[8] = 0xd;
  local_6c[9] = 0;
  puVar2 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_6c[10] = *puVar2;
  local_6c[0xb] = puVar2[1];
  local_6c[0xc] = puVar2[2];
  puVar2 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_6c[0xd] = *puVar2;
  local_6c[0xe] = puVar2[1];
  local_6c[0xf] = puVar2[2];
  local_6c[0x10] = 0;
  local_6c[0x11] = 0;
  local_6c[0x12] = 0;
  puVar2 = (undefined4 *)FUN_00440000(local_84,0,0,0);
  local_5c = *puVar2;
  local_58 = puVar2[1];
  local_54 = puVar2[2];
  local_6c[0x13] = local_5c;
  local_6c[0x14] = local_58;
  local_6c[0x15] = local_54;
  puVar2 = (undefined4 *)FUN_00440000(local_b4,0,0,0);
  local_44 = *puVar2;
  local_40 = puVar2[1];
  local_3c = puVar2[2];
  local_6c[0x16] = local_44;
  local_6c[0x17] = local_40;
  local_6c[0x18] = local_3c;
  local_6c[0x19] = 0x3d4ccccd;
  local_6c[0x1a] = 0x3d4ccccd;
  local_6c[0x1b] = 0x40400000;
  local_6c[0x1c] = 0x3e4ccccd;
  local_6c[0x1d] = 0x3e99999a;
  local_6c[0x1e] = 0;
  local_6c[0x1f] = 0;
  local_6c[0x20] = 0;
  local_6c[0x21] = 0;
  puVar2 = (undefined4 *)FUN_00440000(local_9c,0,0,0);
  local_2c = *puVar2;
  local_28 = puVar2[1];
  local_24 = puVar2[2];
  local_6c[0x22] = local_2c;
  local_6c[0x23] = local_28;
  local_6c[0x24] = local_24;
  local_6c[0x25] = 0;
  local_6c[0x26] = 0;
  local_6c[0x28] = 0;
  local_6c[0x29] = 0;
  local_6c[0x2a] = 0;
  local_6c[0x2b] = 0;
  local_6c[0x2c] = 0;
  local_6c[0x2d] = 0;
  local_6c[0x2e] = 0;
  local_6c[0x2f] = 0xffffffff;
  local_6c[0x30] = 0;
  *(undefined1 *)(local_6c + 0x31) = 0;
  puVar2 = (undefined4 *)FUN_00440000(local_78,0,0,0);
  local_38 = *puVar2;
  local_34 = puVar2[1];
  local_30 = puVar2[2];
  local_6c[0x32] = local_38;
  local_6c[0x33] = local_34;
  local_6c[0x34] = local_30;
  local_6c[0x35] = 0;
  puVar2 = (undefined4 *)FUN_00440000(local_90,0,0,0);
  local_50 = *puVar2;
  local_4c = puVar2[1];
  local_48 = puVar2[2];
  local_6c[0x36] = local_50;
  local_6c[0x37] = local_4c;
  local_6c[0x38] = local_48;
  puVar2 = (undefined4 *)FUN_00440000(local_a8,0,0,0);
  local_68 = *puVar2;
  local_64 = puVar2[1];
  local_60 = puVar2[2];
  local_6c[0x39] = local_68;
  local_6c[0x3a] = local_64;
  local_6c[0x3b] = local_60;
  local_6c[0x3c] = 0x42960000;
  local_6c[0x3d] = 0;
  local_6c[0x3e] = 0;
  local_6c[0x3f] = DAT_008e7944;
  local_6c[0x40] = 0;
  local_6c[0x41] = 0;
  local_6c[0x42] = 0;
  local_6c[0x44] = 0;
  local_6c[0x45] = 0;
  local_6c[0x46] = 0;
  local_6c[0x47] = 0;
  local_6c[0x48] = 0;
  local_6c[0x49] = 0;
  puVar2 = (undefined4 *)FUN_00440000(local_c0,0,0,0);
  local_20 = *puVar2;
  local_1c = puVar2[1];
  local_18 = puVar2[2];
  local_6c[0x4a] = local_20;
  local_6c[0x4b] = local_1c;
  local_6c[0x4c] = local_18;
  FUN_005fedd0();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

