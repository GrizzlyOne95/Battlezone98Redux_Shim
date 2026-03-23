
undefined4 __fastcall FUN_004e8780(int param_1)

{
  undefined4 uVar1;
  float10 fVar2;
  float10 fVar3;
  undefined4 local_24;
  float local_20;
  float local_1c;
  int local_14;
  int local_10;
  int local_c;
  char local_6;
  char local_5;
  
  if ((*(int *)(param_1 + 0x1c) == 3) && (*(int *)(param_1 + 0x24) != 0)) {
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x28);
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 0x28) = 0;
    *(undefined4 *)(param_1 + 0x2c) = 0;
    uVar1 = 1;
  }
  else {
    local_c = param_1;
    local_6 = FUN_004e8b90();
    if (*(int *)(local_c + 0x1c) == 0x10) {
      if (local_6 != '\0') {
        *(undefined4 *)(local_c + 0x20) = *(undefined4 *)(local_c + 0x24);
        *(undefined4 *)(local_c + 0x3c) = *(undefined4 *)(local_c + 0x28);
        *(undefined4 *)(local_c + 0x10) = *(undefined4 *)(local_c + 0x2c);
        *(undefined4 *)(local_c + 0x24) = 0;
        *(undefined4 *)(local_c + 0x28) = 0;
        *(undefined4 *)(local_c + 0x2c) = 0;
        return 1;
      }
    }
    else if (local_6 == '\0') {
      if (*(int *)(local_c + 0x24) == 0) {
        *(undefined4 *)(local_c + 0x24) = *(undefined4 *)(local_c + 0x1c);
        *(undefined4 *)(local_c + 0x28) = *(undefined4 *)(local_c + 0x3c);
        *(undefined4 *)(local_c + 0x2c) = *(undefined4 *)(local_c + 0x10);
        *(undefined4 *)(local_c + 0x20) = 0x10;
        return 1;
      }
      *(undefined4 *)(local_c + 0x20) = *(undefined4 *)(local_c + 0x24);
      *(undefined4 *)(local_c + 0x3c) = *(undefined4 *)(local_c + 0x28);
      *(undefined4 *)(local_c + 0x10) = *(undefined4 *)(local_c + 0x2c);
      *(undefined4 *)(local_c + 0x24) = 0;
      *(undefined4 *)(local_c + 0x28) = 0;
      *(undefined4 *)(local_c + 0x2c) = 0;
      return 1;
    }
    if (*(int *)(local_c + 0x1c) == 7) {
      if (*(int *)(local_c + 0x24) == 0) {
        *(undefined4 *)(local_c + 0x24) = 3;
      }
      local_5 = '\x01';
      local_10 = FUN_00462630(*(undefined4 *)(local_c + 0x3c));
      if (local_10 == 0) {
        local_5 = '\0';
      }
      else {
        local_1c = 40000.0;
        uVar1 = (**(code **)(*(int *)(local_10 + 0x18) + 0xc))();
        uVar1 = (**(code **)(*(int *)(*(int *)(local_c + 0x34) + 0x18) + 0xc))(uVar1);
        fVar2 = (float10)FUN_00462010(uVar1);
        if (local_1c < (float)fVar2) {
          local_5 = '\0';
        }
      }
      if (local_5 == '\0') {
        *(undefined4 *)(local_c + 0x20) = *(undefined4 *)(local_c + 0x24);
        *(undefined4 *)(local_c + 0x3c) = *(undefined4 *)(local_c + 0x28);
        *(undefined4 *)(local_c + 0x10) = *(undefined4 *)(local_c + 0x2c);
        *(undefined4 *)(local_c + 0x24) = 0;
        *(undefined4 *)(local_c + 0x28) = 0;
        *(undefined4 *)(local_c + 0x2c) = 0;
        return 1;
      }
    }
    else if (*(int *)(local_c + 0x1c) != 0x10) {
      fVar2 = (float10)FUN_00822d80();
      local_20 = (float)fVar2;
      if (local_20 < *(float *)(local_c + 0x30)) {
        return 0;
      }
      local_24 = 0x471c4000;
      local_14 = FUN_00463240(*(undefined4 *)(local_c + 0x34),&local_24);
      if (local_14 != 0) {
        *(undefined4 *)(local_c + 0x24) = *(undefined4 *)(local_c + 0x1c);
        *(undefined4 *)(local_c + 0x28) = *(undefined4 *)(local_c + 0x3c);
        *(undefined4 *)(local_c + 0x2c) = *(undefined4 *)(local_c + 0x10);
        *(undefined4 *)(local_c + 0x20) = 7;
        uVar1 = FUN_00477590(local_14);
        *(undefined4 *)(local_c + 0x3c) = uVar1;
        return 1;
      }
      fVar2 = (float10)FUN_00822d80();
      fVar3 = (float10)FUN_004464c0();
      *(float *)(local_c + 0x30) = (float)fVar2 + 7.0 + (float)fVar3 * 3.0;
      return 0;
    }
    uVar1 = 0;
  }
  return uVar1;
}

