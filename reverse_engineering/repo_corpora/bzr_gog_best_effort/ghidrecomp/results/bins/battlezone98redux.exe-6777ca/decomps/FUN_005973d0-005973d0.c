
void __fastcall FUN_005973d0(int param_1)

{
  undefined1 local_b4 [4];
  float local_b0;
  int local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  char local_88 [128];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_9c = *(undefined4 *)(param_1 + 0x10);
  local_90 = *(int *)(param_1 + 8);
  if (*(int *)(param_1 + 0x6c) == 2) {
    local_a8 = DAT_0091755c;
  }
  else {
    if (*(int *)(param_1 + 0x6c) == 0) {
      local_a0 = DAT_009175b0;
    }
    else {
      local_a0 = DAT_00917588;
    }
    local_a8 = local_a0;
  }
  if (*(int *)(param_1 + 0x6c) == 0) {
    local_ac = *(int *)(param_1 + 0x158) + 2;
  }
  else {
    local_ac = 0;
  }
  local_8c = param_1;
  FUN_00595080(local_9c,local_90,local_ac,&DAT_008852ac,local_a8,DAT_00917584);
  local_90 = local_90 + *(int *)(local_8c + 0x24);
  if (*(int *)(local_8c + 0x6c) == 2) {
    for (local_94 = 0; local_94 < 9; local_94 = local_94 + 1) {
      if ((1 << ((byte)local_94 & 0x1f) & *(uint *)(local_8c + 0x70)) == 0) {
        local_a4 = DAT_009175b0;
      }
      else {
        local_a4 = DAT_00917560;
      }
      FUN_00595080(local_9c,local_90,*(int *)(local_8c + 0x158) + 1 + local_94,
                   (&PTR_s_Slabs_008e8e18)[local_94],local_a4,DAT_00917584);
      local_90 = local_90 + *(int *)(local_8c + 0x28);
      if ((&DAT_00919879)[local_94] != '\0') {
        *(uint *)(local_8c + 0x70) = 1 << ((byte)local_94 & 0x1f) ^ *(uint *)(local_8c + 0x70);
        *(undefined4 *)(local_8c + 0x6c) = 0;
      }
    }
    local_90 = local_90 + *(int *)(local_8c + 0x2c);
    FUN_00595080(local_9c,local_90,*(undefined4 *)(local_8c + 0x15c),"Cancel",DAT_0091755c,
                 DAT_00917584);
    if (DAT_0091988b != '\0') {
      *(undefined4 *)(local_8c + 0x6c) = 0;
    }
  }
  else {
    for (local_98 = 0; local_98 < 9; local_98 = local_98 + 1) {
      if ((1 << ((byte)local_98 & 0x1f) & *(uint *)(local_8c + 0x70)) != 0) {
        sprintf(local_88,"%s",(&PTR_s_Slabs_008e8e18)[local_98]);
        FUN_004c0100(DAT_00917580,local_9c,local_90,local_b4,&local_b0,local_88,DAT_00917550,
                     DAT_0091755c,DAT_00917584,0,0,0);
        local_90 = (int)local_b0 + 2;
      }
    }
  }
  FUN_0083e885();
  return;
}

