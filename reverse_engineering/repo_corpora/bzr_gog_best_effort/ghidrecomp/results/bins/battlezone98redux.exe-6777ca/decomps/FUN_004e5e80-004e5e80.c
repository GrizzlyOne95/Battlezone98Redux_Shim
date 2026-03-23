
void __fastcall FUN_004e5e80(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_dc [12];
  undefined1 local_d0 [12];
  undefined1 local_c4 [12];
  undefined1 local_b8 [12];
  undefined1 local_ac [12];
  undefined4 local_a0;
  float local_9c;
  undefined4 local_98;
  void *local_94;
  float local_90;
  float local_8c;
  int local_88;
  int local_84;
  undefined4 local_80;
  undefined4 local_7c;
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
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a42f;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_90 = 1e+30;
  local_88 = -1;
  local_84 = param_1;
  local_14 = uVar1;
  if (*(int *)(param_1 + 0x134) == 0) {
    local_94 = operator_new(0x18);
    local_8 = 0;
    if (local_94 == (void *)0x0) {
      local_98 = 0;
    }
    else {
      iVar4 = local_84 + 0x140;
      uVar2 = (**(code **)(*(int *)(*(int *)(local_84 + 0x10) + 0x18) + 0xc))(iVar4);
      local_98 = FUN_00460490(uVar2,iVar4);
    }
    local_a0 = local_98;
    local_8 = 0xffffffff;
    *(undefined4 *)(local_84 + 0x134) = local_98;
    *(undefined1 *)(local_84 + 0x13c) = 1;
    *(undefined4 *)(local_84 + 0x138) = 0;
  }
  while (*(int *)(local_84 + 0x138) < *(int *)(*(int *)(local_84 + 0x134) + 4)) {
    iVar4 = *(int *)(*(int *)(local_84 + 0x134) + 8);
    puVar3 = (undefined4 *)
             FUN_004e5270(local_d0,*(undefined4 *)(iVar4 + *(int *)(local_84 + 0x138) * 8),
                          *(undefined4 *)(iVar4 + 4 + *(int *)(local_84 + 0x138) * 8),uVar1);
    local_5c = *puVar3;
    local_58 = puVar3[1];
    local_54 = puVar3[2];
    fVar5 = (float10)FUN_00462010(local_84 + 0x88,&local_5c);
    local_8c = (float)fVar5;
    if (local_8c < local_90) {
      local_88 = *(int *)(local_84 + 0x138);
      local_90 = local_8c;
    }
    *(int *)(local_84 + 0x138) = *(int *)(local_84 + 0x138) + 1;
  }
  if (local_88 == *(int *)(*(int *)(local_84 + 0x134) + 4) + -1) {
    *(int *)(local_84 + 0x138) = local_88;
  }
  else {
    iVar4 = *(int *)(*(int *)(local_84 + 0x134) + 8);
    puVar3 = (undefined4 *)
             FUN_004e5270(local_ac,*(undefined4 *)(iVar4 + 8 + local_88 * 8),
                          *(undefined4 *)(iVar4 + 0xc + local_88 * 8),uVar1);
    local_80 = *puVar3;
    local_7c = puVar3[1];
    local_78 = puVar3[2];
    iVar4 = *(int *)(*(int *)(local_84 + 0x134) + 8);
    local_44 = local_80;
    local_40 = local_7c;
    local_3c = local_78;
    puVar3 = (undefined4 *)
             FUN_004e5270(local_b8,*(undefined4 *)(iVar4 + local_88 * 8),
                          *(undefined4 *)(iVar4 + 4 + local_88 * 8));
    local_74 = *puVar3;
    local_70 = puVar3[1];
    local_6c = puVar3[2];
    local_20 = local_74;
    local_1c = local_70;
    local_18 = local_6c;
    puVar3 = (undefined4 *)
             FUN_004401a0(local_c4,local_80,local_7c,local_78,local_74,local_70,local_6c);
    local_50 = *puVar3;
    local_4c = puVar3[1];
    local_48 = puVar3[2];
    local_2c = local_50;
    local_28 = local_4c;
    local_24 = local_48;
    puVar3 = (undefined4 *)
             FUN_004401a0(local_dc,*(undefined4 *)(local_84 + 0x88),*(undefined4 *)(local_84 + 0x8c)
                          ,*(undefined4 *)(local_84 + 0x90),local_74,local_70,local_6c);
    local_68 = *puVar3;
    local_64 = puVar3[1];
    local_60 = puVar3[2];
    local_38 = local_68;
    local_34 = local_64;
    local_30 = local_60;
    fVar5 = (float10)FUN_004428b0(&local_50,&local_68);
    local_9c = (float)fVar5;
    if (0.0 <= local_9c) {
      *(int *)(local_84 + 0x138) = local_88 + 1;
    }
    else {
      *(int *)(local_84 + 0x138) = local_88;
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

