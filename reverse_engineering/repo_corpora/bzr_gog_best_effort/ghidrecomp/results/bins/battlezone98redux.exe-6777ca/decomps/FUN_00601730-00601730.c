
void __fastcall FUN_00601730(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  float *pfVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_118 [24];
  undefined1 local_100 [12];
  undefined1 local_f4 [12];
  undefined1 local_e8 [12];
  undefined1 local_dc [4];
  undefined8 local_d8;
  float local_d0;
  float local_cc;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  undefined8 local_a8;
  float local_a0;
  float local_9c;
  float local_98;
  undefined8 local_94;
  float local_8c;
  undefined4 *local_88;
  undefined8 local_84;
  undefined4 local_7c;
  uint local_78;
  float *local_74;
  undefined1 local_6d;
  int local_6c;
  undefined1 local_68 [12];
  undefined1 local_5c [4];
  float local_58;
  float local_50;
  float local_4c;
  float local_48;
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
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_74 = (float *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0xc4);
  local_6c = param_1;
  local_7c = FUN_0045c4d0();
  puVar1 = (undefined4 *)FUN_00447f60(local_118,local_7c);
  local_2c = *puVar1;
  local_28 = puVar1[1];
  local_24 = puVar1[2];
  local_20 = puVar1[3];
  local_1c = puVar1[4];
  local_18 = puVar1[5];
  uVar2 = (**(code **)(*(int *)(*(int *)(local_6c + 0x10) + 0x18) + 0x2c))
                    (local_2c,local_28,local_24,local_20,local_1c,local_18,local_dc,local_5c,0);
  FUN_00444f70(uVar2);
  uVar2 = FUN_00462490(local_5c);
  fVar5 = (float10)FUN_004428b0(uVar2);
  local_cc = (float)fVar5;
  fVar5 = (float10)FUN_00447ed0(local_cc * -1.0,0xbf800000,0x3f800000);
  local_74[1] = (float)fVar5;
  if (((*(uint *)(*(int *)(*(int *)(local_6c + 0x10) + 0x230) + 0x114) & 4) == 0) &&
     (*(int *)(*(int *)(local_6c + 0x40) + 0x10) != 3)) {
    local_6d = 0;
  }
  else {
    local_6d = 1;
  }
  puVar1 = (undefined4 *)FUN_00601cf0(local_68,local_6d);
  *(undefined4 *)(local_6c + 0x4c) = *puVar1;
  *(undefined4 *)(local_6c + 0x50) = puVar1[1];
  *(undefined4 *)(local_6c + 0x54) = puVar1[2];
  pfVar3 = (float *)FUN_00440300(local_f4,local_6c + 0x4c,local_7c);
  local_50 = *pfVar3;
  local_4c = pfVar3[1];
  local_48 = pfVar3[2];
  local_14 = local_50;
  local_10 = local_4c;
  local_c = local_48;
  fVar5 = (float10)FUN_004428b0(&local_14,&local_14);
  local_d0 = (float)fVar5;
  if (0.0001 < local_d0) {
    if (*(int *)(local_6c + 0x44) == 0) {
      puVar1 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_6c + 0x10) + 0x18) + 0xc))();
      local_d8 = FUN_0045c460(*puVar1,puVar1[1],puVar1[2]);
      iVar4 = *(int *)(*(int *)(local_6c + 0x40) + 8);
      local_94 = FUN_00444e40(*(undefined4 *)(iVar4 + *(int *)(local_6c + 0x44) * 8),
                              *(undefined4 *)(iVar4 + 4 + *(int *)(local_6c + 0x44) * 8),local_d8);
      local_84 = local_94;
    }
    else {
      local_88 = (undefined4 *)
                 (*(int *)(*(int *)(local_6c + 0x40) + 8) + *(int *)(local_6c + 0x44) * 8);
      local_b0 = FUN_00444e40(*local_88,local_88[1],local_88[-2],local_88[-1]);
      local_84 = local_b0;
    }
    puVar1 = (undefined4 *)FUN_00439d80(local_100,local_7c);
    local_44 = *puVar1;
    local_40 = puVar1[1];
    local_3c = puVar1[2];
    local_c0 = FUN_0045c460(local_44,local_40,local_3c);
    local_b8 = local_c0;
    puVar1 = (undefined4 *)FUN_004560b0(local_e8,local_7c);
    local_38 = *puVar1;
    local_34 = puVar1[1];
    local_30 = puVar1[2];
    local_c8 = FUN_0045c460(local_38,local_34,local_30);
    local_a8 = local_c8;
    fVar5 = (float10)FUN_0046e0a0((float)local_84 * (float)local_b8 +
                                  local_84._4_4_ * local_b8._4_4_,
                                  (float)local_84 * (float)local_c8 +
                                  local_84._4_4_ * (float)((ulonglong)local_c8 >> 0x20));
    local_9c = (float)fVar5;
    iVar4 = FUN_0045c490(0xbf800000,0x3f800000);
    fVar5 = (float10)FUN_00447ed0(-(*(float *)(iVar4 + 0x28) * *(float *)(local_6c + 0x70) +
                                   local_9c) * *(float *)(local_6c + 0x6c));
    *local_74 = (float)fVar5;
  }
  fVar5 = (float10)FUN_00453f80(*local_74);
  local_a0 = (float)fVar5;
  if (local_a0 == 1.0) {
    local_78 = 0x3e800000;
  }
  else {
    fVar5 = (float10)FUN_00453f80(*local_74);
    local_98 = (float)fVar5;
    if (local_98 <= 0.7) {
      local_78 = 0x3f800000;
    }
    else {
      local_78 = 0x3f000000;
    }
  }
  fVar5 = (float10)FUN_00447ed0(local_c * *(float *)(local_6c + 100),local_78 ^ 0x80000000,local_78)
  ;
  local_74[3] = (float)fVar5;
  fVar5 = (float10)FUN_00447ed0(local_14 * *(float *)(local_6c + 0x68),local_78 ^ 0x80000000,
                                local_78);
  local_74[2] = (float)fVar5;
  if ((local_74[3] < 1.0) || (0.8 <= local_58)) {
    local_8c = 0.0;
  }
  else {
    local_8c = 1.4013e-45;
  }
  local_74[4] = local_8c;
  FUN_0083e885();
  return;
}

