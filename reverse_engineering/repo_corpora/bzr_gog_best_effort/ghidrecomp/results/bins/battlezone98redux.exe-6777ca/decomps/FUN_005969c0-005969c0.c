
void __fastcall FUN_005969c0(int *param_1)

{
  undefined2 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  uint local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  float local_24;
  float local_20;
  uint local_1c;
  uint local_18;
  int *local_14;
  undefined1 local_10 [5];
  undefined2 local_b;
  byte local_9;
  undefined2 local_8;
  byte local_6;
  
  uVar3 = 4;
  uVar2 = 0xfffffffc;
  local_30 = param_1[0x17] & 0xfffffffc;
  local_34 = param_1[0x19] + 3U & 0xfffffffc;
  local_2c = param_1[0x1a] + 3U & 0xfffffffc;
  local_28 = param_1[0x18] & 0xfffffffc;
  local_14 = param_1;
  for (local_18 = local_28; (int)local_18 < (int)local_2c; local_18 = local_18 + 4) {
    for (local_1c = local_30; (int)local_1c < (int)local_34; local_1c = local_1c + 4) {
      local_24 = (float)(int)local_1c * DAT_02cc50e0;
      local_40 = DAT_02cc50e0 * 4.0 + local_24;
      local_20 = (float)(int)local_18 * DAT_02cc50e0;
      local_3c = DAT_02cc50e0 * 4.0 + local_20;
      local_38 = FUN_00780dc0(local_1c,local_18,uVar2,uVar3);
      puVar1 = (undefined2 *)FUN_00780fd0(local_10,local_38);
      local_b = *puVar1;
      local_9 = *(byte *)(puVar1 + 1);
      local_8._0_1_ = (byte)local_b;
      local_8._1_1_ = (byte)((ushort)local_b >> 8);
      local_44 = (uint)(byte)local_8 << 0x10 | 0xff000000 | (uint)local_8._1_1_ << 8 | (uint)local_9
      ;
      local_8 = local_b;
      local_6 = local_9;
      (**(code **)(*local_14 + 0x24))(local_24,local_20,&local_54,&local_48);
      (**(code **)(*local_14 + 0x24))(local_40,local_3c,&local_4c,&local_50);
      FUN_0068afb0(DAT_00917580,local_54,local_50,local_4c,local_48,local_44,0);
    }
  }
  return;
}

