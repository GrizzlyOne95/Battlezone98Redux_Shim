
void FUN_004b7bd0(void)

{
  byte bVar1;
  undefined4 uVar2;
  float *pfVar3;
  bool bVar4;
  float10 fVar5;
  undefined1 local_4c [18];
  undefined4 local_3a;
  undefined2 local_36;
  float local_34;
  undefined4 local_30;
  int local_2c;
  int *local_28;
  uint local_24;
  int *local_20;
  int local_1c;
  uint local_18;
  wchar_t *local_14;
  uint local_10;
  int local_c;
  int *local_8;
  
  local_3a = 0;
  local_36 = 0;
  FUN_004bb0b0(&local_3a);
  local_14 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                   *)&DAT_0097a2c4);
  local_c = (**(code **)(*local_8 + 0x30))();
  if ((local_c == 0) || ((*(uint *)(local_c + 0x14) & 0x1000000) == 0)) {
    local_18 = 0;
  }
  else {
    local_18 = 1;
  }
  local_10 = local_18;
  if (local_18 != 0) {
    if ((local_c == 0) || ((*(uint *)(local_c + 0x14) & 0x400000) == 0)) {
      if ((local_c != 0) && ((*(uint *)(local_c + 0x14) & 0x800000) != 0)) {
        local_10 = 3;
      }
    }
    else {
      local_10 = 2;
    }
  }
  *(undefined1 *)local_14 = 6;
  local_1c = FUN_00417c70();
  if (local_1c == 0) {
    local_20 = (int *)0x0;
  }
  else {
    local_20 = (int *)(local_1c + 0x18);
  }
  bVar4 = local_8 == local_20;
  local_24 = (uint)bVar4;
  bVar1 = (**(code **)(*local_8 + 0x20))();
  *(byte *)((int)local_14 + 1) = bVar4 << 7 | (bVar1 & 1) << 6 | (byte)((local_10 & 0xf) << 2) | 1;
  *(int *)(local_14 + 1) = local_8[0x19];
  local_28 = (int *)FUN_00764760();
  uVar2 = (**(code **)(*local_28 + 0x38))(local_4c);
  local_2c = FUN_00577200(uVar2);
  local_30 = FUN_004b75f0(local_8);
  if (local_2c != 0) {
    FUN_00575570(local_30,local_14,6);
  }
  fVar5 = (float10)FUN_00822da0();
  local_8[0x1b] = (int)(float)fVar5;
  fVar5 = (float10)FUN_00822da0();
  local_34 = (float)fVar5;
  pfVar3 = (float *)FUN_004bafe0(local_8 + 0x19);
  *pfVar3 = local_34;
  return;
}

