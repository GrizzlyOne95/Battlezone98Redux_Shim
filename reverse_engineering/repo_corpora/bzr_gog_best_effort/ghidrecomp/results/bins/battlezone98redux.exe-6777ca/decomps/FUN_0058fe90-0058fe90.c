
void FUN_0058fe90(float *param_1,float *param_2)

{
  float fVar1;
  float *pfVar2;
  float10 fVar3;
  undefined1 local_74 [16];
  float local_64;
  float local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  float *local_3c;
  char local_36;
  char local_35;
  float *local_34;
  int local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084be93;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_20 = *param_1;
  local_1c = param_1[1];
  local_18 = param_1[2];
  local_2c = *param_2;
  local_28 = param_2[1];
  local_24 = param_2[2];
  DAT_00918154 = FUN_0058d650(&local_20,local_14);
  DAT_00918164 = FUN_0058d650(&local_2c);
  local_48 = FUN_0058bca0(0x34);
  local_8 = 0;
  if (local_48 == 0) {
    local_44 = 0;
  }
  else {
    local_44 = FUN_00592010();
  }
  local_4c = local_44;
  local_8 = 0xffffffff;
  local_30 = local_44;
  *(undefined4 *)(local_44 + 0x10) = 4;
  *(undefined4 *)(local_44 + 0x14) = 0;
  FUN_00591fc0();
  local_8 = 1;
  FUN_00592230(local_74);
  FUN_00592230(local_74);
  local_34 = (float *)FUN_005111d0(0);
  local_3c = (float *)FUN_005111d0(1);
  *local_34 = local_20;
  local_34[1] = local_18;
  *local_3c = local_2c;
  local_3c[1] = local_24;
  local_36 = FUN_0048fca0(local_20,local_18);
  local_35 = FUN_0048fca0(local_2c,local_24);
  if ((((DAT_00918154 == 0) || (DAT_00918164 == 0)) || (local_36 == '\0')) ||
     ((local_35 == '\0' || (local_36 != local_35)))) {
    *(undefined4 *)(local_30 + 0x10) = 1;
    fVar1 = local_3c[1];
    *(float *)(local_30 + 0x18) = *local_3c;
    *(float *)(local_30 + 0x1c) = fVar1;
    local_58 = local_30;
    local_8 = 0xffffffff;
    FUN_00417c60();
  }
  else if (DAT_00918154 == DAT_00918164) {
    fVar3 = (float10)FUN_0058bec0(*(undefined4 *)(DAT_00918154 + 0x10));
    local_60 = (float)fVar3;
    if (local_60 == 99999.0) {
      *(undefined4 *)(local_30 + 0x10) = 1;
      *(undefined4 *)(local_30 + 0x14) = 0;
      fVar1 = local_3c[1];
      *(float *)(local_30 + 0x18) = *local_3c;
      *(float *)(local_30 + 0x1c) = fVar1;
    }
    else {
      *(undefined4 *)(local_30 + 0x10) = 0;
      *(undefined4 *)(local_30 + 0x14) = 0;
      fVar1 = local_3c[1];
      *(float *)(local_30 + 0x18) = *local_3c;
      *(float *)(local_30 + 0x1c) = fVar1;
    }
    local_54 = local_30;
    local_8 = 0xffffffff;
    FUN_00417c60();
  }
  else {
    DAT_00918150 = local_30;
    local_40 = 0;
    fVar3 = (float10)FUN_0058bec0(*(undefined4 *)(DAT_00918154 + 0x10));
    local_64 = (float)fVar3;
    if (local_64 == 99999.0) {
      local_40 = FUN_0058f750(local_34,local_3c);
      if (*(int *)(local_40 + 0x10) == 0) {
        pfVar2 = (float *)std::
                          basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                          ::back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                                  *)(local_40 + 4));
        fVar1 = pfVar2[1];
        *local_34 = *pfVar2;
        local_34[1] = fVar1;
      }
      else {
        *local_34 = local_20;
        local_34[1] = local_18;
      }
      *local_34 = *local_34 + 0.1;
      local_34[1] = local_34[1] + 0.1;
    }
    *(undefined4 *)(local_30 + 0x10) = 4;
    *local_34 = *local_34 * DAT_02cc50e4;
    local_34[1] = local_34[1] * DAT_02cc50e4;
    *local_3c = *local_3c * DAT_02cc50e4;
    local_3c[1] = local_3c[1] * DAT_02cc50e4;
    FUN_0058f470(local_30);
    FUN_0058eec0();
    FUN_0058f490();
    if (local_40 != 0) {
      local_5c = FUN_0058fa10(local_40,local_30);
      FUN_00590b90(local_40);
      FUN_00590b90(local_30);
      local_30 = local_5c;
    }
    DAT_00918150 = 0;
    local_50 = local_30;
    local_8 = 0xffffffff;
    FUN_00417c60();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

