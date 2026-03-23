
undefined4 __fastcall FUN_00583520(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  int local_4c;
  float local_48;
  float local_44;
  int local_40;
  float local_3c;
  float local_38;
  float local_34;
  uint local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int *local_c;
  char local_5;
  
  if (param_1[6] == 0) {
    return 0;
  }
  local_14 = 0;
  local_c = param_1;
  if ((*(int *)(param_1[0xd] + 0x98) != 0) &&
     (*(int *)(*(int *)(param_1[0xd] + 0x98) + 0xc) == 0x534e4950)) {
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
  if (local_c[9] != 0) {
    local_1c = local_c[9];
    local_28 = local_c[10];
    local_40 = local_c[0xb];
    if (local_c[7] == 0xf) {
      iVar3 = FUN_00462630(local_c[0xf]);
      local_c[0x19] = iVar3;
      local_10 = FUN_00417c70();
      if (((char)local_c[0x1e] != '\0') && (local_c[0x19] != local_10)) {
        if (local_c[0x19] == 0) {
          if (((local_10 == 0) ||
              (local_18 = (**(code **)(*(int *)(local_10 + 0x18) + 0x30))(), local_18 == 0)) ||
             ((*(int *)(local_18 + 0x84) != 4 && ((*(uint *)(local_18 + 0x14) & 0x200) == 0)))) {
            *(undefined1 *)(local_c + 0x1e) = 1;
            if (local_10 != 0) {
              uVar2 = (**(code **)(*(int *)(local_10 + 0x18) + 4))();
              FUN_004db4f0(uVar2);
            }
          }
          else {
            *(undefined1 *)(local_c + 0x1e) = 0;
          }
        }
        else {
          local_c[0x19] = 0;
          *(undefined1 *)(local_c + 0x1e) = 1;
        }
      }
      if (local_c[0x19] != 0) {
        uVar2 = (**(code **)(*(int *)(local_c[0x19] + 0x18) + 4))();
        cVar1 = FUN_004db560(uVar2);
        if (cVar1 != '\0') {
          local_c[0x19] = 0;
        }
      }
    }
    else {
      local_c[0x19] = 0;
    }
    goto LAB_0058388c;
  }
  local_1c = local_c[7];
  local_28 = local_c[0xf];
  local_40 = local_c[4];
  if (local_14 != 0) {
    local_c[0x19] = local_14;
    goto LAB_0058388c;
  }
  if ((char)local_c[0x1e] != '\0') {
    iVar3 = FUN_00417c70();
    local_c[0x19] = iVar3;
    if (local_c[0x19] == 0) {
LAB_005837ce:
      local_20 = 0;
    }
    else {
      uVar2 = (**(code **)(*(int *)(local_c[0x19] + 0x18) + 0xc))();
      uVar2 = (**(code **)(*(int *)(local_c[0xd] + 0x18) + 0xc))(uVar2);
      fVar4 = (float10)FUN_00462010(uVar2);
      local_44 = (float)fVar4;
      if ((float)local_c[0x1a] <= local_44) goto LAB_005837ce;
      uVar2 = (**(code **)(*(int *)(local_c[0x19] + 0x18) + 0x30))();
      iVar3 = FUN_00417e20(uVar2);
      if ((iVar3 != 0) && (cVar1 = FUN_00462670(), cVar1 != '\0')) goto LAB_005837ce;
      local_20 = 1;
    }
    *(undefined1 *)(local_c + 0x1e) = (undefined1)local_20;
  }
  if ((char)local_c[0x1e] == '\0') {
    fVar4 = (float10)FUN_00822d80();
    local_48 = (float)fVar4;
    if (local_48 < (float)local_c[0xc]) {
      return 0;
    }
    local_4c = local_c[0x1a];
    iVar3 = (**(code **)(*local_c + 0xe4))(&local_4c);
    local_c[0x19] = iVar3;
    if (local_c[0x19] == 0) {
      fVar4 = (float10)FUN_00822d80();
      fVar5 = (float10)FUN_004464c0();
      local_c[0xc] = (int)((float)fVar4 + 7.0 + (float)fVar5 * 3.0);
      return 0;
    }
  }
LAB_0058388c:
  local_24 = local_1c;
  if ((local_1c < 7) || (8 < local_1c)) {
    local_c[0x18] = 0;
  }
  else {
    iVar3 = FUN_00462630(local_28);
    local_c[0x18] = iVar3;
  }
  if ((local_c[0x19] == 0) || (iVar3 = FUN_00417ca0(), iVar3 == 0)) {
    local_2c = 0;
  }
  else {
    local_2c = 1;
  }
  local_5 = (char)local_2c;
  if ((char)local_2c != '\0') {
    if (local_14 == 0) {
      local_5 = (**(code **)(*local_c + 0xe8))(local_1c);
    }
    else {
      local_5 = local_c[0x19] == local_14;
      local_30 = (uint)(byte)local_5;
    }
    uVar2 = (**(code **)(*(int *)(local_c[0x19] + 0x18) + 0x30))();
    iVar3 = FUN_00417e20(uVar2);
    if ((iVar3 != 0) && (cVar1 = FUN_00462670(local_c[0x19]), cVar1 != '\0')) {
      local_5 = '\0';
    }
  }
  if (local_c[9] == 0) {
    if (local_5 == '\0') {
      return 0;
    }
    local_c[9] = local_c[7];
    local_c[8] = 0xf;
    local_c[10] = local_c[0xf];
    iVar3 = FUN_00477590(local_c[0x19]);
    local_c[0xf] = iVar3;
    iVar3 = FUN_00417c70();
    if (local_c[0x19] == iVar3) {
      *(undefined1 *)(local_c + 0x1e) = 1;
    }
    else {
      *(undefined1 *)(local_c + 0x1e) = 0;
    }
    local_c[0xb] = local_c[4];
    local_c[4] = 0;
  }
  else {
    if (local_5 != '\0') {
      return 0;
    }
    local_c[8] = local_c[9];
    local_c[0xf] = local_c[10];
    local_c[4] = local_c[0xb];
    local_c[9] = 0;
    local_c[10] = 0;
    local_c[0xb] = 0;
  }
  return 1;
}

