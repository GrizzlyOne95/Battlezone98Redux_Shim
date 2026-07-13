
void FUN_005b5650(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined1 local_84 [12];
  undefined1 local_78 [12];
  undefined1 local_6c [12];
  undefined1 local_60 [12];
  undefined4 local_54;
  undefined4 local_50;
  int local_4c;
  undefined4 *local_48;
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
  puStack_c = &LAB_0084c4b8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00461ba0(local_14);
  local_8 = 0;
  *local_48 = RecycleTask::vftable;
  local_48[0xb] = param_1;
  local_48[0x12] = 0;
  if (param_2 == 0) {
    local_50 = 1;
  }
  else {
    local_50 = 2;
  }
  local_48[0x13] = local_50;
  local_48[0xc] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_60,0,0xbf800000,0);
  local_38 = *puVar1;
  local_34 = puVar1[1];
  local_30 = puVar1[2];
  local_48[0xd] = local_38;
  local_48[0xe] = local_34;
  local_48[0xf] = local_30;
  if (param_2 == 0) {
    local_54 = 0;
  }
  else {
    local_54 = FUN_00462380();
  }
  local_48[0x10] = local_54;
  local_48[0x11] = 0;
  local_48[6] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_78,0,0,0);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  local_48[7] = local_20;
  local_48[8] = local_1c;
  local_48[9] = local_18;
  local_48[10] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_6c,0,0,0);
  local_2c = *puVar1;
  local_28 = puVar1[1];
  local_24 = puVar1[2];
  local_48[0x14] = local_2c;
  local_48[0x15] = local_28;
  local_48[0x16] = local_24;
  local_48[0x17] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_84,0,0,0);
  local_44 = *puVar1;
  local_40 = puVar1[1];
  local_3c = puVar1[2];
  local_48[0x18] = local_44;
  local_48[0x19] = local_40;
  local_48[0x1a] = local_3c;
  local_4c = (*(code *)**(undefined4 **)(param_1 + 0x18))();
  local_48[2] = local_4c + 0x604;
  local_48[3] = local_4c + 0x614;
  local_48[4] = local_4c + 0x624;
  local_48[5] = local_4c + 0x634;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

