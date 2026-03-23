
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0059add0(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_134 [64];
  int local_f4;
  float local_f0;
  int local_ec;
  undefined4 local_e8;
  float local_e4;
  undefined1 local_e0 [4];
  undefined1 local_dc [4];
  int local_d8;
  int local_d4;
  float local_d0;
  int local_cc;
  int *local_c8;
  undefined4 local_c4 [16];
  undefined4 local_84 [10];
  undefined8 local_5c;
  undefined8 local_54;
  undefined8 local_4c;
  float local_44 [2];
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c [3];
  float local_20 [3];
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_c8 = param_1;
  local_cc = FUN_00462630(param_1[0x31]);
  if (DAT_00919870 == '\0') {
    if ((DAT_00919872 == '\0') || (local_cc == 0)) {
      if (((DAT_00919873 != '\0') && (local_cc != 0)) &&
         ((local_c8[0x39] != DAT_009175a0 || (local_c8[0x3a] != DAT_009175a4)))) {
        local_c8[0x39] = DAT_009175a0;
        local_c8[0x3a] = DAT_009175a4;
        (**(code **)(*local_c8 + 0x28))(DAT_009175a0,DAT_009175a4,local_20,local_20 + 2);
        local_20[1] = 0.0;
        local_d4 = FUN_0045c4d0();
        local_38 = 0;
        local_34 = 0x3f800000;
        local_30 = 0;
        local_2c[0] = local_20[0] - (float)*(double *)(local_d4 + 0x28);
        local_2c[1] = 0.0;
        local_2c[2] = local_20[2] - (float)*(double *)(local_d4 + 0x38);
        puVar2 = (undefined4 *)FUN_0081f920(local_134,&local_38,local_2c);
        puVar3 = local_c4;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = local_c4;
        puVar3 = local_84;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        local_5c = *(undefined8 *)(local_d4 + 0x28);
        local_54 = *(undefined8 *)(local_d4 + 0x30);
        local_4c = *(undefined8 *)(local_d4 + 0x38);
        FUN_0056d6a0(local_84);
      }
    }
    else if ((local_c8[0x39] != DAT_009175a0) || (local_c8[0x3a] != DAT_009175a4)) {
      local_c8[0x39] = DAT_009175a0;
      local_c8[0x3a] = DAT_009175a4;
      (**(code **)(*local_c8 + 0x28))(DAT_009175a0,DAT_009175a4,&local_14,&local_c);
      local_14 = local_14 - (float)local_c8[0x3b];
      local_c = local_c - (float)local_c8[0x3c];
      fVar4 = (float10)FUN_007855e0((double)local_14,(double)local_c);
      local_10 = (float)fVar4;
      (**(code **)(*(int *)(local_cc + 0x18) + 0x30))();
      iVar1 = FUN_00417e20();
      if ((iVar1 != 0) && (local_f4 = local_cc, *(int *)(local_cc + 0x228) == 0)) {
        fVar4 = (float10)FUN_007855e0((double)(local_14 - 5.0),(double)(local_c - 5.0));
        local_d0 = (float)fVar4;
        if (local_10 < local_d0) {
          local_10 = local_d0;
        }
        fVar4 = (float10)FUN_007855e0((double)(local_14 - 5.0),(double)(local_c + 5.0));
        local_d0 = (float)fVar4;
        if (local_10 < local_d0) {
          local_10 = local_d0;
        }
        fVar4 = (float10)FUN_007855e0((double)(local_14 + 5.0),(double)(local_c + 5.0));
        local_d0 = (float)fVar4;
        if (local_10 < local_d0) {
          local_10 = local_d0;
        }
        fVar4 = (float10)FUN_007855e0((double)(local_14 + 5.0),(double)(local_c - 5.0));
        local_d0 = (float)fVar4;
        if (local_10 < local_d0) {
          local_10 = local_d0;
        }
        local_10 = local_10 + 10.0;
      }
      FUN_005873a0();
      iVar1 = (**(code **)(*(int *)(local_cc + 0x18) + 0x30))();
      if (*(int *)(iVar1 + 0x84) == 2) {
        _DAT_009454c0 = 1;
      }
    }
  }
  else {
    local_ec = local_cc;
    FUN_00599800(&local_cc);
    iVar1 = FUN_00477590(local_cc);
    local_c8[0x31] = iVar1;
    if (local_cc != 0) {
      FUN_004c0af0(local_44);
      local_c8[0x39] = DAT_009175a0;
      local_c8[0x3a] = DAT_009175a4;
      (**(code **)(*local_c8 + 0x28))(DAT_009175a0,DAT_009175a4,local_c8 + 0x3b,local_c8 + 0x3c);
      local_c8[0x3b] = (int)((float)local_c8[0x3b] - local_44[0]);
      local_c8[0x3c] = (int)((float)local_c8[0x3c] - local_3c);
    }
    if ((local_cc != 0) && (local_cc == local_ec)) {
      fVar4 = (float10)FUN_00822da0();
      local_f0 = (float)fVar4;
      if (local_f0 < (float)local_c8[0x38]) {
        FUN_0059ad10();
      }
    }
    fVar4 = (float10)FUN_00822da0();
    local_e4 = (float)fVar4;
    local_c8[0x38] = (int)(local_e4 + 0.5);
  }
  if ((DAT_00919874 != '\0') && (local_cc != 0)) {
    (**(code **)(*(int *)(local_cc + 0x18) + 0x10))();
    local_cc = 0;
    local_c8[0x31] = 0;
  }
  if ((local_cc != 0) && (FUN_00595460(local_cc,1,DAT_0091755c), DAT_00919873 != '\0')) {
    local_e8 = DAT_00920ef4;
    DAT_00920ef4 = 0x3e99999a;
    local_d8 = FUN_0045c4d0();
    (**(code **)(*local_c8 + 0x24))
              ((float)*(double *)(local_d8 + 0x28),(float)*(double *)(local_d8 + 0x38),local_e0,
               local_dc);
    FUN_0068af40();
    DAT_00920ef4 = local_e8;
  }
  FUN_0083e885();
  return;
}

