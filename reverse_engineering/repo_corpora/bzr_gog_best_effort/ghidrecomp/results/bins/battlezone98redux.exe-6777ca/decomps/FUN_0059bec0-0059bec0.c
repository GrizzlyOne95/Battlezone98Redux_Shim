
void __fastcall FUN_0059bec0(int param_1)

{
  int iVar1;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined4 local_28;
  undefined4 local_24;
  undefined *local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_10 = *(undefined4 *)(param_1 + 0x14);
  local_c = *(int *)(param_1 + 8);
  if (*(int *)(param_1 + 0x6c) == 4) {
    local_18 = DAT_0091755c;
  }
  else {
    if (*(int *)(param_1 + 0x6c) == 0) {
      local_14 = DAT_009175b0;
    }
    else {
      local_14 = DAT_00917588;
    }
    local_18 = local_14;
  }
  if (*(int *)(param_1 + 0x6c) == 0) {
    local_1c = *(int *)(param_1 + 0x158) + 3;
  }
  else {
    local_1c = 0;
  }
  local_8 = param_1;
  FUN_00595080(local_10,local_c,local_1c,&DAT_00885534,local_18,DAT_00917584);
  local_c = local_c + *(int *)(local_8 + 0x24);
  if (*(int *)(local_8 + 0x6c) == 4) {
    if ((*(uint *)(DAT_0094672c + 0x30) & 1) == 0) {
      local_24 = DAT_009175b0;
    }
    else {
      local_24 = DAT_00917560;
    }
    FUN_00595080(local_10,local_c,*(int *)(local_8 + 0x158) + 1,&DAT_00884428,local_24,DAT_00917584)
    ;
    local_c = local_c + *(int *)(local_8 + 0x28);
    if (DAT_00919879 != '\0') {
      *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) | 1;
      *(undefined4 *)(local_8 + 0x6c) = 0;
    }
    if ((*(uint *)(DAT_0094672c + 0x30) & 1) == 0) {
      local_28 = DAT_00917560;
    }
    else {
      local_28 = DAT_009175b0;
    }
    FUN_00595080(local_10,local_c,*(int *)(local_8 + 0x158) + 2,&DAT_00884424,local_28,DAT_00917584)
    ;
    iVar1 = *(int *)(local_8 + 0x28);
    if (DAT_0091987a != '\0') {
      *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffffe;
      *(undefined4 *)(local_8 + 0x6c) = 0;
    }
    local_c = local_c + iVar1 + *(int *)(local_8 + 0x2c);
    FUN_00595080(local_10,local_c,*(undefined4 *)(local_8 + 0x15c),"Cancel",DAT_0091755c,
                 DAT_00917584);
    if (DAT_0091988b != '\0') {
      *(undefined4 *)(local_8 + 0x6c) = 0;
    }
  }
  else {
    if ((*(uint *)(DAT_0094672c + 0x30) & 1) == 0) {
      local_20 = &DAT_00884424;
    }
    else {
      local_20 = &DAT_00884428;
    }
    FUN_004c0100(DAT_00917580,local_10,local_c,local_30,local_2c,local_20,DAT_00917550,DAT_0091755c,
                 DAT_00917584,0,0,0);
  }
  return;
}

