
void FUN_005e4890(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_e0 [12];
  undefined1 local_d4 [12];
  undefined1 local_c8 [12];
  undefined1 local_bc [12];
  undefined1 local_b0 [12];
  undefined1 local_a4 [12];
  float local_98;
  float local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  int local_7c;
  int local_78;
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
  local_7c = FUN_00462610();
  if ((((*(uint *)(*(int *)(local_78 + 0xf4) + 0x14) & 0x200) == 0) && (local_7c != 0)) &&
     (iVar1 = (**(code **)(*(int *)(local_7c + 0x18) + 0x30))(), param_1 == iVar1)) {
    if (*(float *)(*(int *)(local_78 + 0xf8) + 400) != 0.0) {
      local_84 = 0;
      local_80 = 0;
      local_8c = *(undefined4 *)(local_78 + 0xf4);
      local_88 = *(undefined4 *)(local_78 + 0xf4);
      local_90 = (**(code **)(*(int *)(local_78 + 0x18) + 4))();
      local_84 = CONCAT22(local_84._2_2_,
                          (ushort)local_84 & 0xfc30 | ((ushort)local_90 & 0xf) << 6 |
                          *(ushort *)(*(int *)(local_78 + 0xf8) + 0x194) & 0xf);
      local_80 = *(undefined4 *)(*(int *)(local_78 + 0xf8) + 400);
      puVar2 = (undefined4 *)FUN_004560b0(local_e0,*(int *)(local_78 + 0xf4) + 0x20);
      local_68 = *puVar2;
      local_64 = puVar2[1];
      local_60 = puVar2[2];
      local_38 = local_68;
      local_34 = local_64;
      local_30 = local_60;
      (**(code **)(*(int *)(local_7c + 0x18) + 0x38))(&local_8c,&local_68);
    }
    *(uint *)(*(int *)(local_78 + 0xf4) + 0x14) =
         *(uint *)(*(int *)(local_78 + 0xf4) + 0x14) | 0x200;
    *(undefined4 *)(*(int *)(local_78 + 0x228) + 0x110) = 0;
  }
  uVar3 = FUN_00822d90();
  if (uVar3 < *(int *)(local_78 + 0x168) + 1000U) {
    iVar1 = FUN_004b0400();
    iVar4 = FUN_00479f30(param_1);
    if (iVar1 == iVar4) goto LAB_005e4cad;
  }
  fVar5 = (float10)FUN_004428b0(local_78 + 300,param_2 + 0x6c,*(undefined4 *)(param_2 + 0x6c),
                                *(undefined4 *)(param_2 + 0x70),*(undefined4 *)(param_2 + 0x74));
  local_94 = (float)fVar5;
  puVar2 = (undefined4 *)
           FUN_00459570(local_a4,0x3f000000,*(undefined4 *)(local_78 + 300),
                        *(undefined4 *)(local_78 + 0x130),*(undefined4 *)(local_78 + 0x134),
                        -local_94);
  local_44 = *puVar2;
  local_40 = puVar2[1];
  local_3c = puVar2[2];
  *(undefined4 *)(local_78 + 300) = local_44;
  *(undefined4 *)(local_78 + 0x130) = local_40;
  *(undefined4 *)(local_78 + 0x134) = local_3c;
  iVar1 = *(int *)(local_78 + 0xf0);
  puVar2 = (undefined4 *)
           FUN_004401a0(local_bc,*(undefined4 *)(param_2 + 0x54),*(undefined4 *)(param_2 + 0x58),
                        *(undefined4 *)(param_2 + 0x5c),*(undefined4 *)(iVar1 + 8),
                        *(undefined4 *)(iVar1 + 0xc),*(undefined4 *)(iVar1 + 0x10));
  local_20 = *puVar2;
  local_1c = puVar2[1];
  local_18 = puVar2[2];
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  puVar2 = (undefined4 *)FUN_00440300(local_d4,param_2 + 0x60,*(int *)(local_78 + 0xf4) + 0x20);
  local_5c = *puVar2;
  local_58 = puVar2[1];
  local_54 = puVar2[2];
  local_2c = local_5c;
  local_28 = local_58;
  local_24 = local_54;
  puVar2 = (undefined4 *)FUN_004440d0(local_b0,&local_5c,&local_14);
  local_74 = *puVar2;
  local_70 = puVar2[1];
  local_6c = puVar2[2];
  fVar5 = (float10)FUN_004428b0(&local_14,&local_14,local_74,local_70,local_6c);
  local_98 = (float)fVar5;
  puVar2 = (undefined4 *)
           FUN_00439d00(local_c8,*(undefined4 *)(local_78 + 0x138),*(undefined4 *)(local_78 + 0x13c)
                        ,*(undefined4 *)(local_78 + 0x140),0.2 / local_98);
  local_50 = *puVar2;
  local_4c = puVar2[1];
  local_48 = puVar2[2];
  *(undefined4 *)(local_78 + 0x138) = local_50;
  *(undefined4 *)(local_78 + 0x13c) = local_4c;
  *(undefined4 *)(local_78 + 0x140) = local_48;
LAB_005e4cad:
  FUN_0083e885();
  return;
}

