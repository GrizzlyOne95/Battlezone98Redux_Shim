
undefined4 __fastcall FUN_005f6ff0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  uint local_30;
  int local_2c;
  undefined4 local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  char local_5;
  
  local_14 = 0;
  local_c = param_1;
  if ((*(int *)(*(int *)(param_1 + 0x34) + 0x98) != 0) &&
     (*(int *)(*(int *)(*(int *)(param_1 + 0x34) + 0x98) + 0xc) == 0x534e4950)) {
    fVar4 = (float10)FUN_00822d80();
    local_38 = (float)fVar4;
    local_34 = local_38;
    fVar4 = (float10)FUN_0046d040();
    local_3c = (float)fVar4;
    if (local_38 - local_3c < 3.0) {
      uVar2 = FUN_00462530();
      local_14 = FUN_00462630(uVar2);
    }
  }
  if (*(int *)(local_c + 0x24) != 0) {
    local_1c = *(int *)(local_c + 0x24);
    local_28 = *(undefined4 *)(local_c + 0x28);
    uVar2 = FUN_00462630(*(undefined4 *)(local_c + 0x3c),*(undefined4 *)(local_c + 0x2c));
    *(undefined4 *)(local_c + 0x60) = uVar2;
    local_10 = FUN_00417c70();
    if ((*(char *)(local_c + 100) != '\0') && (*(int *)(local_c + 0x60) != local_10)) {
      if (*(int *)(local_c + 0x60) == 0) {
        if (((local_10 == 0) ||
            (local_18 = (**(code **)(*(int *)(local_10 + 0x18) + 0x30))(), local_18 == 0)) ||
           ((*(int *)(local_18 + 0x84) != 4 && ((*(uint *)(local_18 + 0x14) & 0x200) == 0)))) {
          *(undefined1 *)(local_c + 100) = 1;
          if (local_10 != 0) {
            uVar2 = (**(code **)(*(int *)(local_10 + 0x18) + 4))();
            FUN_004db4f0(uVar2);
          }
        }
        else {
          *(undefined1 *)(local_c + 100) = 0;
        }
      }
      else {
        *(undefined4 *)(local_c + 0x60) = 0;
        *(undefined1 *)(local_c + 100) = 1;
      }
    }
    if (*(int *)(local_c + 0x60) != 0) {
      uVar2 = (**(code **)(*(int *)(*(int *)(local_c + 0x60) + 0x18) + 4))();
      cVar1 = FUN_004db560(uVar2);
      if (cVar1 != '\0') {
        *(undefined4 *)(local_c + 0x60) = 0;
      }
    }
    goto LAB_005f72eb;
  }
  local_1c = *(int *)(local_c + 0x1c);
  local_28 = *(undefined4 *)(local_c + 0x3c);
  if (local_14 != 0) {
    *(int *)(local_c + 0x60) = local_14;
    goto LAB_005f72eb;
  }
  if (*(char *)(local_c + 100) != '\0') {
    uVar2 = FUN_00417c70();
    *(undefined4 *)(local_c + 0x60) = uVar2;
    if (*(int *)(local_c + 0x60) == 0) {
LAB_005f722e:
      local_20 = 0;
    }
    else {
      uVar2 = (**(code **)(*(int *)(*(int *)(local_c + 0x60) + 0x18) + 0xc))();
      uVar2 = (**(code **)(*(int *)(*(int *)(local_c + 0x34) + 0x18) + 0xc))(uVar2);
      fVar4 = (float10)FUN_00462010(uVar2);
      local_40 = (float)fVar4;
      if (*(float *)(local_c + 0x6c) <= local_40) goto LAB_005f722e;
      local_20 = 1;
    }
    *(undefined1 *)(local_c + 100) = (undefined1)local_20;
  }
  if (*(char *)(local_c + 100) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    local_44 = (float)fVar4;
    if (local_44 < *(float *)(local_c + 0x30)) {
      return 0;
    }
    local_48 = *(undefined4 *)(local_c + 0x6c);
    uVar2 = FUN_00463240(*(undefined4 *)(local_c + 0x34),&local_48);
    *(undefined4 *)(local_c + 0x60) = uVar2;
    if (*(int *)(local_c + 0x60) == 0) {
      fVar4 = (float10)FUN_00822d80();
      fVar5 = (float10)FUN_004464c0();
      *(float *)(local_c + 0x30) = (float)fVar4 + 7.0 + (float)fVar5 * 3.0;
      return 0;
    }
  }
LAB_005f72eb:
  local_24 = local_1c;
  if ((local_1c < 7) || (8 < local_1c)) {
    *(undefined4 *)(local_c + 0x5c) = 0;
  }
  else {
    uVar2 = FUN_00462630(local_28);
    *(undefined4 *)(local_c + 0x5c) = uVar2;
  }
  if ((*(int *)(local_c + 0x60) == 0) || (iVar3 = FUN_00417ca0(), iVar3 == 0)) {
    local_2c = 0;
  }
  else {
    local_2c = 1;
  }
  local_5 = (char)local_2c;
  if (local_2c != 0) {
    if (local_14 == 0) {
      local_5 = FUN_005f75c0(local_1c);
    }
    else {
      local_5 = *(int *)(local_c + 0x60) == local_14;
      local_30 = (uint)(byte)local_5;
    }
  }
  if (*(int *)(local_c + 0x24) == 0) {
    if (local_5 == '\0') {
      return 0;
    }
    *(undefined4 *)(local_c + 0x24) = *(undefined4 *)(local_c + 0x1c);
    *(undefined4 *)(local_c + 0x20) = 0xf;
    *(undefined4 *)(local_c + 0x28) = *(undefined4 *)(local_c + 0x3c);
    uVar2 = FUN_00477590(*(undefined4 *)(local_c + 0x60));
    *(undefined4 *)(local_c + 0x3c) = uVar2;
    iVar3 = FUN_00417c70();
    if (*(int *)(local_c + 0x60) == iVar3) {
      *(undefined1 *)(local_c + 100) = 1;
    }
    else {
      *(undefined1 *)(local_c + 100) = 0;
    }
    *(undefined4 *)(local_c + 0x2c) = *(undefined4 *)(local_c + 0x10);
    *(undefined4 *)(local_c + 0x10) = 0;
  }
  else {
    if (local_5 != '\0') {
      return 0;
    }
    *(undefined4 *)(local_c + 0x20) = *(undefined4 *)(local_c + 0x24);
    *(undefined4 *)(local_c + 0x3c) = *(undefined4 *)(local_c + 0x28);
    *(undefined4 *)(local_c + 0x10) = *(undefined4 *)(local_c + 0x2c);
    *(undefined4 *)(local_c + 0x24) = 0;
    *(undefined4 *)(local_c + 0x28) = 0;
    *(undefined4 *)(local_c + 0x2c) = 0;
  }
  return 1;
}

