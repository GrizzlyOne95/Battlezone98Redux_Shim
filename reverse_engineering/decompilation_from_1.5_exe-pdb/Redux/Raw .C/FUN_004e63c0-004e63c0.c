
void __fastcall FUN_004e63c0(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_b8 [12];
  undefined1 local_ac [12];
  undefined1 local_a0 [12];
  float local_94;
  int local_90;
  float local_8c;
  int local_88;
  float local_84;
  float local_80;
  undefined4 local_7c;
  void *local_78;
  int local_74;
  int local_70;
  float local_6c;
  int local_68;
  int *local_64;
  float local_60;
  undefined4 *local_5c;
  undefined4 *local_58;
  int local_54;
  float local_50;
  float local_4c;
  float local_48;
  int local_44;
  char local_3d;
  int *local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a46c;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_3c = param_1;
  cVar1 = (**(code **)(*param_1 + 0x38))(local_14);
  if (cVar1 == '\0') goto switchD_004e67e5_caseD_3;
  if (local_3c[5] != 0) {
    local_44 = FUN_00462630(local_3c[5]);
    if (local_44 == 0) {
      local_3c[3] = 0xd;
      local_3c[5] = 0;
      goto switchD_004e67e5_caseD_3;
    }
    local_3d = '\0';
    local_5c = (undefined4 *)(**(code **)(*(int *)(local_3c[4] + 0x18) + 0xc))();
    local_58 = (undefined4 *)(**(code **)(*(int *)(local_44 + 0x18) + 0xc))();
    fVar6 = (float10)FUN_004624d0();
    local_84 = (float)fVar6;
    if (0.1 < local_84) {
      fVar6 = (float10)FUN_00462010(local_58,local_3c + 0x50);
      local_50 = (float)fVar6;
      if (1600.0 < local_50) {
        local_3d = '\x01';
      }
    }
    if ((((local_3d == '\0') && (local_3c[0x10] != 0)) &&
        (local_3c[0x11] == *(int *)(local_3c[0x10] + 4) + -1)) &&
       ((cVar1 = FUN_00466d40(local_58), cVar1 == '\0' &&
        (cVar1 = FUN_004682f0(*local_5c,local_5c[2],*local_58,local_58[2]), cVar1 != '\0')))) {
      fVar6 = (float10)FUN_00462010(local_5c,local_3c + 0xd);
      local_50 = (float)fVar6;
      if (local_50 < 25.0) {
        uVar2 = (**(code **)(*(int *)(local_44 + 0x18) + 0xc))();
        uVar2 = (**(code **)(*(int *)(local_3c[4] + 0x18) + 0xc))(uVar2);
        fVar6 = (float10)FUN_00462010(uVar2);
        local_50 = (float)fVar6;
        iVar3 = FUN_00462400();
        fVar6 = (float10)FUN_00462470(*(undefined4 *)(iVar3 + 0xc));
        fVar6 = (float10)FUN_0044fb20((float)fVar6);
        local_80 = (float)fVar6;
        fVar6 = (float10)FUN_00462470();
        local_94 = (float)fVar6;
        local_6c = local_94 + local_80 + 5.0;
        if (local_6c * local_6c <= local_50) {
          local_3d = '\x01';
        }
      }
    }
    if (local_3d != '\0') {
      if (local_3c[0x10] != 0) {
        local_88 = local_3c[0x10];
        local_70 = local_88;
        if (local_88 == 0) {
          local_7c = 0;
        }
        else {
          local_7c = FUN_00460640(1);
        }
        local_3c[0x10] = 0;
      }
      if (((char)local_3c[0x4f] != '\0') && (local_3c[0x4d] != 0)) {
        FUN_00460600(local_3c[0x4d]);
        local_3c[0x4d] = 0;
      }
      local_3c[3] = 2;
      piVar4 = (int *)(**(code **)(*(int *)(local_44 + 0x18) + 0xc))();
      local_3c[0x50] = *piVar4;
      local_3c[0x51] = piVar4[1];
      local_3c[0x52] = piVar4[2];
      local_78 = operator_new(0x18);
      local_8 = 0;
      if (local_78 == (void *)0x0) {
        local_74 = 0;
      }
      else {
        piVar4 = local_3c + 0x50;
        uVar2 = (**(code **)(*(int *)(local_3c[4] + 0x18) + 0xc))(piVar4);
        local_74 = FUN_00460490(uVar2,piVar4);
      }
      local_90 = local_74;
      local_8 = 0xffffffff;
      local_3c[0x4d] = local_74;
      *(undefined1 *)(local_3c + 0x4f) = 1;
      local_3c[0x4e] = 0;
      FUN_00602920();
      FUN_004e5e80();
      piVar4 = (int *)FUN_004e5270(local_a0,*(undefined4 *)
                                             (*(int *)(local_3c[0x4d] + 8) + local_3c[0x4e] * 8),
                                   *(undefined4 *)
                                    (*(int *)(local_3c[0x4d] + 8) + 4 + local_3c[0x4e] * 8));
      local_20 = *piVar4;
      local_1c = piVar4[1];
      local_18 = piVar4[2];
      local_3c[10] = local_20;
      local_3c[0xb] = local_1c;
      local_3c[0xc] = local_18;
      goto switchD_004e67e5_caseD_3;
    }
  }
  local_54 = local_3c[2] + -1;
  switch(local_54) {
  case 0:
  case 5:
    FUN_00602420();
    break;
  case 1:
    if (*(int *)(local_3c[0x10] + 4) + -1 <= local_3c[0x11]) {
      uVar2 = (**(code **)(*(int *)(local_3c[4] + 0x18) + 0xc))(local_3c + 0xd);
      fVar6 = (float10)FUN_00462010(uVar2);
      local_60 = (float)fVar6;
      local_48 = 5.0;
      if (local_3c[0x20] != 0) {
        fVar6 = (float10)FUN_00462470();
        local_8c = (float)fVar6;
        if (local_48 < local_8c) {
          iVar3 = (*(code *)**(undefined4 **)(local_3c[0x20] + 0x18))();
          local_68 = *(int *)(iVar3 + 0x1c);
          if ((local_68 != 3) && (local_68 != 7)) {
            fVar6 = (float10)FUN_00462470();
            local_48 = (float)fVar6;
          }
        }
      }
      local_4c = (local_48 + 5.0) * (local_48 + 5.0);
      local_48 = local_48 * local_48;
      if (*(char *)((int)local_3c + 0x13d) == '\0') {
        local_4c = local_4c * 2.0;
        local_48 = local_48 * 6.0;
      }
      if (local_60 < local_4c) {
        uVar2 = (**(code **)(*(int *)(local_3c[4] + 0x18) + 0xc))();
        cVar1 = FUN_00466d40(uVar2);
        if (cVar1 == '\0') {
          FUN_00602920();
        }
      }
      if (local_60 < local_48) {
LAB_004e69c9:
        if (local_3c[0x4e] < *(int *)(local_3c[0x4d] + 4) + -1) {
          local_3c[0x4e] = local_3c[0x4e] + 1;
          local_3c[3] = 2;
          piVar4 = (int *)FUN_004e5270(local_b8,*(undefined4 *)
                                                 (*(int *)(local_3c[0x4d] + 8) + local_3c[0x4e] * 8)
                                       ,*(undefined4 *)
                                         (*(int *)(local_3c[0x4d] + 8) + 4 + local_3c[0x4e] * 8));
          local_38 = *piVar4;
          local_34 = piVar4[1];
          local_30 = piVar4[2];
          local_3c[10] = local_38;
          local_3c[0xb] = local_34;
          local_3c[0xc] = local_30;
        }
        else if (*(int *)(local_3c[0x4d] + 0x10) == 2) {
          local_3c[0x4e] = 0;
          local_3c[3] = 2;
          piVar4 = (int *)FUN_004e5270(local_ac,*(undefined4 *)
                                                 (*(int *)(local_3c[0x4d] + 8) + local_3c[0x4e] * 8)
                                       ,*(undefined4 *)
                                         (*(int *)(local_3c[0x4d] + 8) + 4 + local_3c[0x4e] * 8));
          local_2c = *piVar4;
          local_28 = piVar4[1];
          local_24 = piVar4[2];
          local_3c[10] = local_2c;
          local_3c[0xb] = local_28;
          local_3c[0xc] = local_24;
        }
        else if (*(char *)((int)local_3c + 0x13e) == '\0') {
          local_3c[3] = 0xd;
        }
        break;
      }
      if ((*(int *)(*(int *)(local_3c[4] + 0x230) + 0x4c) != 0) &&
         (iVar3 = FUN_00462630(local_3c[5]), iVar3 != 0)) {
        iVar3 = FUN_00462630(local_3c[5]);
        local_64 = (int *)(iVar3 + 0x18);
        iVar3 = (**(code **)(*local_64 + 0x30))();
        iVar5 = FUN_0062e050(*(undefined4 *)(*(int *)(local_3c[4] + 0x230) + 0x50));
        if (iVar5 == iVar3) goto LAB_004e69c9;
      }
    }
    cVar1 = FUN_006027f0();
    if (cVar1 == '\0') {
      FUN_00601250();
    }
    else {
      local_3c[3] = 3;
    }
    break;
  case 2:
    FUN_006029b0();
  }
switchD_004e67e5_caseD_3:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

