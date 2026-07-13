
void __fastcall FUN_0059b980(int param_1)

{
  undefined1 local_80 [4];
  undefined1 local_7c [4];
  undefined1 local_78 [4];
  undefined1 local_74 [4];
  char *local_70;
  char *local_6c [2];
  int local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  int local_40;
  int local_3c;
  char local_38 [16];
  char local_28 [16];
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_44 = *(undefined4 *)(param_1 + 0x20);
  local_40 = *(int *)(param_1 + 8);
  if (*(int *)(param_1 + 0x6c) == 1) {
    local_6c[1] = (char *)DAT_0091755c;
  }
  else {
    if (*(int *)(param_1 + 0x6c) == 0) {
      local_54 = DAT_009175b0;
    }
    else {
      local_54 = DAT_00917588;
    }
    local_6c[1] = (char *)local_54;
  }
  if (*(int *)(param_1 + 0x6c) == 0) {
    local_64 = *(int *)(param_1 + 0x158) + 6;
  }
  else {
    local_64 = 0;
  }
  local_3c = param_1;
  FUN_00595080(local_44,local_40,local_64,&DAT_00885478,local_6c[1],DAT_00917584);
  local_40 = local_40 + *(int *)(local_3c + 0x24);
  if (*(int *)(local_3c + 0x6c) == 6) {
    if (*(int *)(local_3c + 0x80) == 0) {
      for (local_48 = 1; local_48 < 8; local_48 = local_48 + 1) {
        sprintf(local_18,"Team %d",local_48);
        if (*(int *)(local_3c + 0x84) == local_48) {
          local_58 = DAT_00917560;
        }
        else {
          local_58 = DAT_009175b0;
        }
        FUN_00595080(local_44,local_40,*(int *)(local_3c + 0x158) + local_48,local_18,local_58,
                     DAT_00917584);
        local_40 = local_40 + *(int *)(local_3c + 0x28);
        if ((&DAT_00919878)[local_48] != '\0') {
          *(int *)(local_3c + 0x84) = local_48;
          *(undefined4 *)(local_3c + 0x6c) = 0;
        }
      }
      FUN_00595080(local_44,local_40,*(int *)(local_3c + 0x158) + 8,"More...",DAT_009175b0,
                   DAT_00917584);
      local_40 = local_40 + *(int *)(local_3c + 0x28);
      if (DAT_00919880 != '\0') {
        *(undefined4 *)(local_3c + 0x80) = 1;
      }
    }
    else {
      for (local_4c = 1; local_4c < 9; local_4c = local_4c + 1) {
        sprintf(local_38,"Team %d",local_4c + 7);
        if (*(int *)(local_3c + 0x84) == local_4c + 7) {
          local_50 = DAT_00917560;
        }
        else {
          local_50 = DAT_009175b0;
        }
        FUN_00595080(local_44,local_40,*(int *)(local_3c + 0x158) + local_4c,local_38,local_50,
                     DAT_00917584);
        local_40 = local_40 + *(int *)(local_3c + 0x28);
        if ((&DAT_00919878)[local_4c] != '\0') {
          *(int *)(local_3c + 0x84) = local_4c + 7;
          *(undefined4 *)(local_3c + 0x80) = 0;
          *(undefined4 *)(local_3c + 0x6c) = 0;
        }
      }
    }
    if (*(int *)(local_3c + 0x84) == -1) {
      local_5c = DAT_00917560;
    }
    else {
      local_5c = DAT_009175b0;
    }
    FUN_00595080(local_44,local_40,*(int *)(local_3c + 0x158) + 9,"Default",local_5c,DAT_00917584);
    local_40 = local_40 + *(int *)(local_3c + 0x28);
    if (DAT_00919881 != '\0') {
      *(undefined4 *)(local_3c + 0x84) = 0xffffffff;
      *(undefined4 *)(local_3c + 0x80) = 0;
      *(undefined4 *)(local_3c + 0x6c) = 0;
    }
    if (*(int *)(local_3c + 0x84) == 0) {
      local_60 = DAT_00917560;
    }
    else {
      local_60 = DAT_009175b0;
    }
    FUN_00595080(local_44,local_40,*(undefined4 *)(local_3c + 0x158),"Neutral",local_60,DAT_00917584
                );
    if (DAT_00919878 != '\0') {
      *(undefined4 *)(local_3c + 0x84) = 0;
      *(undefined4 *)(local_3c + 0x80) = 0;
      *(undefined4 *)(local_3c + 0x6c) = 0;
    }
    local_40 = local_40 + *(int *)(local_3c + 0x28) + *(int *)(local_3c + 0x2c);
    if (*(int *)(local_3c + 0x80) == 0) {
      FUN_00595080(local_44,local_40,*(undefined4 *)(local_3c + 0x15c),"Cancel",DAT_0091755c,
                   DAT_00917584);
      if (DAT_0091988b != '\0') {
        *(undefined4 *)(local_3c + 0x6c) = 0;
      }
    }
    else {
      FUN_00595080(local_44,local_40,*(undefined4 *)(local_3c + 0x15c),&DAT_00877f98,DAT_0091755c,
                   DAT_00917584);
      if (DAT_0091988b != '\0') {
        *(undefined4 *)(local_3c + 0x80) = 0;
      }
    }
  }
  else if (*(int *)(local_3c + 0x84) < 1) {
    local_70 = "Default";
    local_6c[0] = "Neutral";
    FUN_004c0100(DAT_00917580,local_44,local_40,local_78,local_74,
                 local_6c[*(int *)(local_3c + 0x84)],DAT_00917550,DAT_0091755c,DAT_00917584,0,0,0);
  }
  else {
    sprintf(local_28,"Team %d",*(undefined4 *)(local_3c + 0x84));
    FUN_004c0100(DAT_00917580,local_44,local_40,local_80,local_7c,local_28,DAT_00917550,DAT_0091755c
                 ,DAT_00917584,0,0,0);
  }
  FUN_0083e885();
  return;
}

