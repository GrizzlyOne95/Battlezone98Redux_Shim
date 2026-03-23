
void __fastcall FUN_0041d840(int *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  float10 fVar3;
  double local_6c;
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int *local_28;
  int *local_24;
  int *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int *local_8;
  
  local_8 = param_1;
  cVar1 = operator!=<>(param_1 + 0xb,param_1 + 0x17);
  if (((cVar1 != '\0') || (local_8[0x1d] != local_8[0x1e])) || ((char)local_8[2] != '\0')) {
    (**(code **)(*local_8 + 4))();
  }
  if (((DAT_008eaad8 == 0) || (DAT_008eaad8 == 2)) || ((DAT_008eaad8 == 1 || (DAT_008eaad8 == 7))))
  {
    puVar2 = (undefined4 *)FID_conflict_begin(local_48);
    local_10 = *puVar2;
    puVar2 = (undefined4 *)FID_conflict_end(local_4c);
    local_30 = *puVar2;
    while (cVar1 = FID_conflict_operator__(&local_30), cVar1 != '\0') {
      puVar2 = (undefined4 *)get();
      *(undefined4 *)*puVar2 = 0;
      FUN_00421f70();
    }
    puVar2 = (undefined4 *)FID_conflict_begin(local_50);
    local_14 = *puVar2;
    puVar2 = (undefined4 *)FID_conflict_end(local_54);
    local_34 = *puVar2;
    while (cVar1 = FID_conflict_operator__(&local_34), cVar1 != '\0') {
      puVar2 = (undefined4 *)get();
      *(undefined1 *)*puVar2 = 1;
      FUN_00421f70();
    }
    puVar2 = (undefined4 *)FID_conflict_begin(local_58);
    local_18 = *puVar2;
    puVar2 = (undefined4 *)FID_conflict_end(local_5c);
    local_38 = *puVar2;
    while (cVar1 = FID_conflict_operator__(&local_38), cVar1 != '\0') {
      puVar2 = (undefined4 *)get();
      local_24 = (int *)*puVar2;
      (**(code **)(*local_24 + 0x10))();
      FUN_00421f70();
    }
    puVar2 = (undefined4 *)FID_conflict_begin(local_60);
    local_1c = *puVar2;
    puVar2 = (undefined4 *)FID_conflict_end(local_64);
    local_3c = *puVar2;
    while (cVar1 = FID_conflict_operator__(&local_3c), cVar1 != '\0') {
      puVar2 = (undefined4 *)get();
      local_28 = (int *)*puVar2;
      (**(code **)(*local_28 + 0x10))();
      if ((char)local_8[2] != '\0') break;
      FUN_00421f70();
    }
    (**(code **)(*(int *)local_8[0x28] + 0x10))();
    if (local_8[3] != 0) {
      fVar3 = (float10)FUN_004346f0();
      local_6c = (double)fVar3;
      if ((local_6c <= -0.02) || (0.02 <= local_6c)) {
        if (local_6c <= 0.5) {
          if (local_6c < -0.5) {
            local_6c = -0.5;
          }
        }
        else {
          local_6c = 0.5;
        }
      }
      else {
        local_6c = 0.0;
      }
      *(int *)local_8[3] = (int)(local_6c * 2.0 * 65535.0);
      if ((char)local_8[4] != '\0') {
        *(int *)local_8[3] = -*(int *)local_8[3];
      }
    }
    cVar1 = operator!=<>(local_8 + 0xb,local_8 + 0x17);
    if (((cVar1 != '\0') || (local_8[0x1d] != local_8[0x1e])) || ((char)local_8[2] != '\0')) {
      (**(code **)(*local_8 + 4))();
    }
  }
  else {
    FUN_0041e6d0();
    if (DAT_008eaad8 == 3) {
      puVar2 = (undefined4 *)FID_conflict_begin(local_40);
      local_c = *puVar2;
      puVar2 = (undefined4 *)FID_conflict_end(local_44);
      local_2c = *puVar2;
      while (cVar1 = FID_conflict_operator__(&local_2c), cVar1 != '\0') {
        puVar2 = (undefined4 *)get();
        local_20 = (int *)*puVar2;
        (**(code **)(*local_20 + 0x10))();
        if ((char)local_8[2] != '\0') {
          return;
        }
        FUN_00421f70();
      }
    }
  }
  return;
}

