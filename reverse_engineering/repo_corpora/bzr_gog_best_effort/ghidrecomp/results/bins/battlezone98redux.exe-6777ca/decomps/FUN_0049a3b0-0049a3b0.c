
void __fastcall FUN_0049a3b0(int param_1)

{
  int iVar1;
  int iVar2;
  float local_88;
  undefined8 local_84;
  float local_7c;
  int local_78;
  int local_74;
  undefined4 local_70;
  undefined8 local_6c;
  float local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  undefined8 local_38;
  float local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = *(int *)(param_1 + 0x1c);
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  if (0 < local_24) {
    local_c = local_24 % 10;
    local_24 = local_24 / 10;
  }
  if (0 < local_24) {
    local_10 = local_24 % 6;
    local_24 = local_24 / 6;
  }
  if (0 < local_24) {
    local_14 = local_24 % 10;
    local_24 = local_24 / 10;
  }
  if (*(char *)(param_1 + 0x2b) == '\0') {
    if (0 < local_24) {
      local_18 = local_24;
    }
  }
  else {
    if (0 < local_24) {
      local_18 = local_24 % 6;
      local_24 = local_24 / 6;
    }
    if (0 < local_24) {
      local_1c = local_24;
    }
  }
  if (*(char *)(param_1 + 0x28) == '\0') {
    if (*(int *)(param_1 + 0x1c) < *(int *)(param_1 + 0x20)) {
      local_2c = *(int *)(param_1 + 0xc);
    }
    else if (*(int *)(param_1 + 0x1c) < *(int *)(param_1 + 0x24)) {
      local_2c = *(int *)(param_1 + 0x10);
    }
    else {
      local_2c = *(int *)(param_1 + 0x14);
    }
  }
  else if (*(int *)(param_1 + 0x20) < *(int *)(param_1 + 0x1c)) {
    local_2c = *(int *)(param_1 + 0xc);
  }
  else if (*(int *)(param_1 + 0x24) < *(int *)(param_1 + 0x1c)) {
    local_2c = *(int *)(param_1 + 0x10);
  }
  else {
    local_2c = *(int *)(param_1 + 0x14);
  }
  local_28 = param_1;
  local_6c = FUN_00689eb0();
  local_84 = FUN_00689eb0();
  local_30 = 1.0;
  local_38 = local_84;
  iVar1 = FUN_004344a0();
  if (iVar1 == 2) {
    local_30 = 0.75;
    local_38._0_4_ = (float)local_38 * 0.8;
    local_38._4_4_ = local_38._4_4_ * 0.8;
    FUN_00689ec0((float)local_38,local_38._4_4_);
  }
  local_70 = FUN_0081cb40("names","Mission Time");
  FUN_00689ab0(DAT_00917550,local_70,&local_7c,&local_88);
  iVar2 = (int)local_7c;
  iVar1 = FUN_0068f090(local_2c,(int)local_88,iVar2);
  local_44 = (int)((float)iVar1 * (float)local_38 * local_30);
  iVar1 = FUN_0068f0c0(local_2c);
  local_48 = (int)((float)iVar1 * local_38._4_4_ * local_30);
  iVar1 = FUN_0068f090(local_2c + 10);
  local_4c = (int)((float)iVar1 * (float)local_38 * local_30);
  if (*(char *)(local_28 + 0x2b) == '\0') {
    local_5c = local_4c + 9 + local_44 * 4;
  }
  else {
    local_5c = (local_44 + 2) * 5 + 2 + local_4c * 2;
  }
  local_50 = local_5c;
  local_60 = local_48;
  iVar1 = FUN_004344a0();
  if (iVar1 == 2) {
    local_58 = (int)((float)(DAT_02cecee0 - local_50 / 2) - (float)local_6c * 80.0);
    local_54 = (int)((float)local_6c * 2.0);
  }
  else {
    local_58 = DAT_02cecee0 / 2;
    local_54 = ((DAT_02cecee4 - (int)(local_38._4_4_ * 20.0)) - local_60) -
               (int)(local_38._4_4_ * 10.0);
  }
  local_78 = local_58 - iVar2 / 2;
  local_74 = (int)(local_38._4_4_ * 10.0) + local_54;
  local_40 = local_58 - local_50 / 2;
  local_3c = (int)(local_38._4_4_ * 20.0) + local_54;
  if (400 < DAT_02cecee0) {
    local_64 = DAT_00920ef4;
    DAT_00920ef4 = DAT_00920ef4 + 0.001;
    FUN_0068af70(DAT_00917580,local_40 + -2,local_74 + -2,local_40 + 2 + local_50,
                 local_3c + 2 + local_60,DAT_00917584,0);
    DAT_00920ef4 = local_64;
  }
  std::_Init_atomic_counter(DAT_00917550,DAT_0091755c);
  FUN_00689d10(DAT_00917550,DAT_00917580,local_78,local_74,local_70);
  local_20 = local_40;
  if (*(char *)(local_28 + 0x2b) != '\0') {
    FUN_0068c560(DAT_00917580,local_2c + local_1c,local_40,local_3c,4,local_30);
    local_20 = local_20 + 2 + local_44;
    FUN_0068c560(DAT_00917580,local_2c + 10,local_20,
                 ((int)(local_48 + (local_48 >> 0x1f & 3U)) >> 2) + local_3c,0x40004,local_30);
    FUN_0068c560(DAT_00917580,local_2c + 10,local_20,
                 ((int)(local_48 * 3 + (local_48 * 3 >> 0x1f & 3U)) >> 2) + local_3c,0x40004,
                 local_30);
    local_20 = local_20 + 3 + local_4c;
  }
  FUN_0068c560(DAT_00917580,local_2c + local_18,local_20,local_3c,4,local_30);
  local_20 = local_20 + 2 + local_44;
  FUN_0068c560(DAT_00917580,local_2c + local_14,local_20,local_3c,4,local_30);
  local_20 = local_20 + 2 + local_44;
  FUN_0068c560(DAT_00917580,local_2c + 10,local_20,
               ((int)(local_48 + (local_48 >> 0x1f & 3U)) >> 2) + local_3c,0x40004,local_30);
  FUN_0068c560(DAT_00917580,local_2c + 10,local_20,
               ((int)(local_48 * 3 + (local_48 * 3 >> 0x1f & 3U)) >> 2) + local_3c,0x40004,local_30)
  ;
  local_20 = local_20 + 3 + local_4c;
  FUN_0068c560(DAT_00917580,local_2c + local_10,local_20,local_3c,4,local_30);
  local_20 = local_20 + 2 + local_44;
  FUN_0068c560(DAT_00917580,local_2c + local_c,local_20,local_3c,4,local_30);
  FUN_00689ec0(local_6c);
  FUN_0083e885();
  return;
}

