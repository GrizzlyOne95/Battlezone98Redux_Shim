
void __fastcall FUN_006a29f0(int param_1)

{
  bool bVar1;
  char cVar2;
  wchar_t *pwVar3;
  undefined4 *puVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_50 [12];
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  int local_28;
  int *local_24;
  float local_20;
  byte *local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = param_1;
  if (*(int *)(param_1 + 0x18) == -1) {
    while (cVar2 = FUN_0041fc90(), cVar2 == '\0') {
      pwVar3 = std::
               basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
               ::back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                       *)&DAT_0260af80);
      local_38 = *(int *)pwVar3;
      local_34 = *(undefined4 *)(pwVar3 + 2);
      if (local_38 != -1) {
        *(undefined4 *)(local_18 + 0x18) = local_34;
        *(int *)(local_18 + 0x1c) = local_38;
        *(undefined4 *)(local_18 + 0x20) = 0;
        goto LAB_006a2a72;
      }
      FUN_006a6400();
    }
  }
  else {
LAB_006a2a72:
    local_40 = *(int *)(local_18 + 0x1c) << 4;
    local_3c = *(int *)(local_18 + 0x18) << 4;
    fVar6 = (float10)FUN_006a0980(local_40);
    local_20 = (float)fVar6;
    fVar6 = (float10)FUN_006a09b0(local_3c);
    local_30 = 0x42a00000;
    local_20 = *(float *)(&DAT_008ed9f8 + *(int *)(local_18 + 0x20) * 8) * 80.0 + local_20;
    local_2c = *(float *)(&DAT_008ed9fc + *(int *)(local_18 + 0x20) * 8) * 80.0 + (float)fVar6;
    local_1c = (byte *)(*(int *)(local_18 + 0x18) * DAT_02c00ed8 + *(int *)(local_18 + 0x1c) +
                       DAT_009310a8);
    if (*(int *)(local_18 + 0x20) == 0) {
      *local_1c = *local_1c & 0x1f;
    }
    cVar2 = FUN_00466d40(&DAT_02c00ab0);
    if (cVar2 != '\0') {
      FUN_006a2060();
    }
    puVar4 = (undefined4 *)FUN_00440000(local_50,local_20,0,local_2c);
    local_14 = *puVar4;
    local_10 = puVar4[1];
    local_c = puVar4[2];
    cVar2 = FUN_00466d40(&local_14);
    if ((cVar2 == '\0') &&
       (cVar2 = FUN_00468370(DAT_02c00ab0,DAT_02c00ab8,local_20,local_2c), cVar2 != '\0')) {
      *local_1c = *local_1c | (byte)(1 << ((byte)*(undefined4 *)(local_18 + 0x20) & 0x1f));
    }
    else {
      *local_1c = *local_1c &
                  ~(byte)(*(int *)(local_18 + 0x20) <<
                         ((byte)*(undefined4 *)(local_18 + 0x20) & 0x1f));
    }
    *(int *)(local_18 + 0x20) = *(int *)(local_18 + 0x20) + 1;
    if (*(int *)(local_18 + 0x20) == 5) {
      local_28 = FUN_0067ac40();
      do {
        local_44 = local_28;
        iVar5 = local_28 + -1;
        bVar1 = local_28 < 1;
        local_28 = iVar5;
        if (bVar1) goto LAB_006a2c8c;
        local_24 = (int *)FUN_0067ac60(iVar5);
      } while ((*local_24 != *(int *)(local_18 + 0x1c)) ||
              (local_24[1] != *(int *)(local_18 + 0x18)));
      *local_24 = -1;
      local_24[1] = -1;
LAB_006a2c8c:
      *(undefined4 *)(local_18 + 0x18) = 0xffffffff;
      *(undefined4 *)(local_18 + 0x1c) = 0xffffffff;
      *(undefined4 *)(local_18 + 0x20) = 0;
    }
  }
  FUN_0083e885();
  return;
}

