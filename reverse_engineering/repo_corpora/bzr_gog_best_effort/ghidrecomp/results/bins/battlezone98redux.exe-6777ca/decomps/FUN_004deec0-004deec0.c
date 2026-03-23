
void FUN_004deec0(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  int *piVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_1ac [64];
  undefined1 local_16c [16];
  undefined1 local_15c [16];
  undefined1 local_14c [16];
  double local_13c;
  undefined8 local_134;
  undefined8 local_12c;
  double local_124;
  undefined8 local_11c;
  double local_114;
  float local_10c;
  float local_108;
  float local_104;
  int local_100;
  int *local_fc;
  undefined4 local_f8 [16];
  undefined4 local_b8 [10];
  double local_90;
  double local_88;
  double local_80;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_fc = (int *)FUN_00479f30(param_1);
  if (local_fc != (int *)0x0) {
    iVar2 = FUN_00572a70();
    if (iVar2 == 0) {
      fVar7 = (float10)FUN_00822d60();
      local_10c = (float)fVar7;
      local_fc[0x1d] = (int)(local_10c + (float)local_fc[0x1d]);
      if (0.0 < (float)local_fc[0x1d]) {
        (**(code **)(*local_fc + 0x3c))(local_fc[0x1d]);
        local_fc[0x1d] = 0;
      }
    }
    else {
      cVar1 = FUN_004b9830();
      if (cVar1 != '\0') {
        puVar3 = (undefined4 *)(param_1 + 0x20);
        puVar6 = local_b8;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        if (*(double *)(local_fc + 0x16) != -1.0) {
          piVar4 = local_fc + 10;
          piVar5 = (int *)(param_1 + 0x20);
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *piVar5 = *piVar4;
            piVar4 = piVar4 + 1;
            piVar5 = piVar5 + 1;
          }
        }
      }
      fVar7 = (float10)FUN_00822d60();
      local_108 = (float)fVar7;
      local_fc[0x1d] = (int)(local_108 + (float)local_fc[0x1d]);
      local_100 = 0;
      do {
        fVar7 = (float10)FUN_00447ed0(local_fc[0x1d],0x3a83126f,0x3dcccccd);
        local_104 = (float)fVar7;
        local_fc[0x1d] = (int)((float)local_fc[0x1d] - local_104);
        (**(code **)(*local_fc + 0x3c))(local_104);
        if ((*(uint *)(param_1 + 0x14) & 0x200) != 0) goto LAB_004df35d;
        local_100 = local_100 + 1;
      } while ((0.0 < (float)local_fc[0x1d]) && (local_100 < 5));
      if (((*(uint *)(param_1 + 0x14) & 0x200) == 0) && (cVar1 = FUN_004b9830(), cVar1 != '\0')) {
        puVar3 = (undefined4 *)FUN_0081f1e0(local_16c,local_b8);
        local_68 = *puVar3;
        local_64 = puVar3[1];
        local_60 = puVar3[2];
        local_5c = puVar3[3];
        local_28 = local_68;
        local_24 = local_64;
        local_20 = local_60;
        local_1c = local_5c;
        FUN_004dead0(&local_68);
        puVar3 = (undefined4 *)FUN_0081f1e0(local_14c,param_1 + 0x20);
        local_58 = *puVar3;
        local_54 = puVar3[1];
        local_50 = puVar3[2];
        local_4c = puVar3[3];
        local_48 = local_58;
        local_44 = local_54;
        local_40 = local_50;
        local_3c = local_4c;
        FUN_004dead0(&local_58);
        puVar3 = (undefined4 *)FUN_004debe0(local_15c,&local_68,&local_58,0x3f000000);
        local_38 = *puVar3;
        local_34 = puVar3[1];
        local_30 = puVar3[2];
        local_2c = puVar3[3];
        local_18 = local_38;
        local_14 = local_34;
        local_10 = local_30;
        local_c = local_2c;
        FUN_004dead0(&local_18);
        local_78 = local_18;
        local_74 = local_14;
        local_70 = local_10;
        local_6c = local_c;
        piVar4 = (int *)(param_1 + 0x20);
        piVar5 = local_fc + 10;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar5 = *piVar4;
          piVar4 = piVar4 + 1;
          piVar5 = piVar5 + 1;
        }
        local_11c = *(undefined8 *)(param_1 + 0x48);
        local_12c = *(undefined8 *)(param_1 + 0x50);
        local_134 = *(undefined8 *)(param_1 + 0x58);
        puVar3 = (undefined4 *)FUN_0081efe0(local_1ac,&local_78);
        puVar6 = local_f8;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar3 = local_f8;
        puVar6 = (undefined4 *)(param_1 + 0x20);
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        *(undefined8 *)(param_1 + 0x48) = local_11c;
        *(undefined8 *)(param_1 + 0x50) = local_12c;
        *(undefined8 *)(param_1 + 0x58) = local_134;
        local_114 = *(double *)(param_1 + 0x48) - local_90;
        local_13c = *(double *)(param_1 + 0x50) - local_88;
        local_124 = *(double *)(param_1 + 0x58) - local_80;
        *(double *)(param_1 + 0x48) = local_114 * 0.30000001192092896 + local_90;
        *(double *)(param_1 + 0x50) = local_13c * 0.30000001192092896 + local_88;
        *(double *)(param_1 + 0x58) = local_124 * 0.30000001192092896 + local_80;
        FUN_004db100();
      }
    }
  }
LAB_004df35d:
  FUN_0083e885();
  return;
}

