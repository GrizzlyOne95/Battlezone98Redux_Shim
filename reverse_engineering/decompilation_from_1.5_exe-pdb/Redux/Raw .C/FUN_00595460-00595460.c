
void FUN_00595460(int param_1,char param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  float10 fVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  undefined1 *puVar7;
  undefined1 local_100 [4];
  undefined1 local_fc [4];
  undefined1 local_f8 [4];
  float local_f4;
  float local_f0;
  int local_ec;
  int local_e8;
  undefined4 local_e4;
  int local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  float local_d4;
  float local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  float local_ac;
  float local_a8;
  int local_a4;
  int local_a0;
  undefined4 *local_9c;
  int local_98;
  int *local_94;
  float *local_90;
  char local_89;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  float local_68 [7];
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_dc = DAT_00920ef4;
  if (param_2 == '\0') {
    local_d0 = 0.6;
  }
  else {
    local_d0 = 0.4;
  }
  DAT_00920ef4 = local_d0;
  local_9c = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  fVar3 = (float10)FUN_00462470();
  local_a8 = (float)fVar3;
  iVar1 = FUN_00462400();
  local_ac = *(float *)(iVar1 + 0xc);
  local_89 = param_2;
  fVar3 = (float10)FUN_00456080(local_a8,local_ac);
  local_f0 = (float)fVar3;
  if (local_f0 * (float)local_94[0x10] <= 4.0) {
    FUN_005946f0(*local_9c,local_9c[2],local_a8,&local_b4,&local_b0,&local_c0,&local_c8);
    uVar2 = FUN_00492ce0(0);
    FUN_0068afb0(DAT_00917580,local_b4,local_b0,local_c0,local_c8,uVar2);
    if (param_2 == '\0') {
      local_cc = 0x3f0ccccd;
    }
    else {
      local_cc = 0x3eb33333;
    }
    DAT_00920ef4 = (float)local_cc;
    FUN_0068b020(DAT_00917580,local_b4,local_b0,local_c0,local_c8,param_3,0);
  }
  else {
    iVar1 = (*(code *)**(undefined4 **)(param_1 + 0x18))();
    local_90 = (float *)(iVar1 + 0x10c);
    local_68[0] = *local_90;
    local_68[1] = *(float *)(iVar1 + 0x110);
    local_68[2] = *(float *)(iVar1 + 0x120);
    local_68[3] = 0.0;
    local_68[4] = 0.0;
    local_68[5] = 0.0;
    local_68[6] = *(float *)(iVar1 + 0x118);
    local_4c = *(float *)(iVar1 + 0x110);
    local_48 = *(undefined4 *)(iVar1 + 0x120);
    local_44 = 0;
    local_40 = 0;
    local_3c = 0;
    local_38 = *(float *)(iVar1 + 0x118);
    local_34 = *(float *)(iVar1 + 0x110);
    local_30 = *(undefined4 *)(iVar1 + 0x114);
    local_2c = 0;
    local_28 = 0;
    local_24 = 0;
    local_20 = *local_90;
    local_1c = *(float *)(iVar1 + 0x110);
    local_18 = *(undefined4 *)(iVar1 + 0x114);
    local_14 = 0;
    local_10 = 0;
    local_c = 0;
    local_f4 = 1.0 / DAT_00920ef4;
    for (local_98 = 0; local_98 < 4; local_98 = local_98 + 1) {
      uVar2 = FUN_0045c4d0();
      FUN_00820180(local_68 + local_98 * 6,local_68 + local_98 * 6,1,uVar2);
      (**(code **)(*local_94 + 0x24))
                (local_68[local_98 * 6],local_68[local_98 * 6 + 2],&local_a4,&local_a0);
      local_68[local_98 * 6] = (float)local_a4;
      local_68[local_98 * 6 + 1] = (float)local_a0;
      local_68[local_98 * 6 + 2] = local_f4;
      local_68[local_98 * 6 + 5] = 1.0;
    }
    local_d8 = FUN_00439e60();
    iVar1 = FUN_00684ce0(0);
    if (iVar1 != 0) {
      FUN_006856f0(DAT_00920ef4);
      uVar2 = FUN_00492ce0();
      FUN_00686600(local_d8,local_68,4,uVar2);
      FUN_006856e0();
      local_88 = (int)local_68[0];
      local_84 = (int)local_68[1];
      local_80 = (int)local_68[6];
      local_7c = (int)local_4c;
      local_78 = (int)local_38;
      local_74 = (int)local_34;
      local_70 = (int)local_20;
      local_6c = (int)local_1c;
      if (param_2 == '\0') {
        local_d4 = 0.55;
      }
      else {
        local_d4 = 0.35;
      }
      DAT_00920ef4 = local_d4;
      FUN_00687550(&local_88,4,param_3);
    }
    (**(code **)(*local_94 + 0x24))(*local_9c,local_9c[2],&local_a4,&local_a0);
    if (param_2 == '\0') {
      local_b8 = 0x3f0ccccd;
    }
    else {
      local_b8 = 0x3eb33333;
    }
    DAT_00920ef4 = (float)local_b8;
    uVar2 = FUN_00492ce0(0);
    FUN_00461fd0(local_ac * (float)local_94[0x10] + 0.5,0x10,uVar2);
    uVar2 = FUN_0083f040();
    FUN_0068ad00(DAT_00917580,local_a4,local_a0,uVar2);
    FUN_00461fd0(local_a8 * (float)local_94[0x10] + 0.5,0x10,param_3,0);
    uVar2 = FUN_0083f040();
    FUN_0068ad00(DAT_00917580,local_a4,local_a0,uVar2);
    if ((local_94[0x1d] == 3) || ((local_94[0x1d] == 2 && (iVar1 = FUN_0045bdf0(), iVar1 != 0)))) {
      local_89 = '\x01';
    }
  }
  iVar1 = FUN_00417c70();
  if (param_1 == iVar1) {
    local_89 = '\x01';
  }
  if (local_89 != '\0') {
    puVar7 = local_f8;
    piVar6 = &local_e0;
    piVar5 = &local_ec;
    piVar4 = &local_e8;
    fVar3 = (float10)FUN_0044fb20(local_a8,local_ac,piVar4,piVar5,piVar6,puVar7);
    FUN_005946f0(*local_9c,local_9c[2],(float)fVar3,piVar4,piVar5,piVar6,puVar7);
    if (param_2 == '\0') {
      local_bc = 0x3e4ccccd;
    }
    else {
      local_bc = 0x3e19999a;
    }
    DAT_00920ef4 = (float)local_bc;
    local_e4 = FUN_00595400(param_1);
    if (param_2 == '\0') {
      local_c4 = 2;
    }
    else {
      local_c4 = 0;
    }
    FUN_004c0100(DAT_00917580,(local_e8 + local_e0) / 2,local_ec + -2,local_100,local_fc,local_e4,
                 DAT_00917550,DAT_0091755c,DAT_00917584,local_c4,1,2);
  }
  DAT_00920ef4 = (float)local_dc;
  FUN_0083e885();
  return;
}

