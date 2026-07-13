
void __fastcall FUN_00597fb0(int param_1)

{
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_14 = *(undefined4 *)(param_1 + 0xc);
  local_c = *(int *)(param_1 + 8);
  if (*(int *)(param_1 + 0x6c) == 1) {
    local_1c = DAT_0091755c;
  }
  else {
    if (*(int *)(param_1 + 0x6c) == 0) {
      local_18 = DAT_009175b0;
    }
    else {
      local_18 = DAT_00917588;
    }
    local_1c = local_18;
  }
  if (*(int *)(param_1 + 0x6c) == 0) {
    local_20 = *(int *)(param_1 + 0x158) + 1;
  }
  else {
    local_20 = 0;
  }
  local_8 = param_1;
  FUN_00595080(local_14,local_c,local_20,"Control",local_1c,DAT_00917584);
  local_c = local_c + *(int *)(local_8 + 0x24);
  if (*(int *)(local_8 + 0x6c) == 1) {
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      if (local_10 == *(int *)(local_8 + 0x74)) {
        local_24 = DAT_00917560;
      }
      else {
        local_24 = DAT_009175b0;
      }
      FUN_00595080(local_14,local_c,*(int *)(local_8 + 0x158) + 1 + local_10,
                   (&PTR_s_Find_Path_008e8e44)[local_10],local_24,DAT_00917584);
      local_c = local_c + *(int *)(local_8 + 0x28);
      if ((&DAT_00919879)[local_10] != '\0') {
        *(int *)(local_8 + 0x78) = local_10;
        *(undefined4 *)(local_8 + 0x6c) = 0;
      }
    }
    local_c = local_c + *(int *)(local_8 + 0x2c);
    FUN_00595080(local_14,local_c,*(undefined4 *)(local_8 + 0x15c),"Cancel",DAT_0091755c,
                 DAT_00917584);
    if (DAT_0091988b != '\0') {
      *(undefined4 *)(local_8 + 0x6c) = 0;
    }
  }
  else {
    FUN_004c0100(DAT_00917580,local_14,local_c,local_2c,local_28,
                 (&PTR_s_Find_Path_008e8e44)[*(int *)(local_8 + 0x74)],DAT_00917550,DAT_0091755c,
                 DAT_00917584,0,0,0);
  }
  return;
}

