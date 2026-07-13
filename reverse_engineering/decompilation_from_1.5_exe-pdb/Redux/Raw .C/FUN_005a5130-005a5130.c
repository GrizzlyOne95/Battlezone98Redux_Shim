
void __fastcall FUN_005a5130(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  float *pfVar3;
  float10 fVar4;
  undefined1 local_5c [12];
  float local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  float local_40;
  int local_3c;
  float *local_38;
  uint local_34;
  int local_30;
  undefined1 local_2c [12];
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_30 = param_1;
  if (*(int *)(param_1 + 8) == 0xd) goto LAB_005a541e;
  if (*(int *)(param_1 + 0x14) != 0) {
    local_3c = FUN_00462630();
    if (local_3c == 0) {
      FUN_00601200();
      *(undefined4 *)(local_30 + 8) = 0xd;
      goto LAB_005a541e;
    }
    puVar1 = (undefined4 *)(**(code **)(*(int *)(local_3c + 0x18) + 0xc))();
    *(undefined4 *)(local_30 + 0x28) = *puVar1;
    *(undefined4 *)(local_30 + 0x2c) = puVar1[1];
    *(undefined4 *)(local_30 + 0x30) = puVar1[2];
    *(undefined4 *)
     (*(int *)(*(int *)(local_30 + 0x40) + 8) + -8 + *(int *)(*(int *)(local_30 + 0x40) + 4) * 8) =
         *(undefined4 *)(local_30 + 0x28);
    *(undefined4 *)
     (*(int *)(*(int *)(local_30 + 0x40) + 8) + -4 + *(int *)(*(int *)(local_30 + 0x40) + 4) * 8) =
         *(undefined4 *)(local_30 + 0x30);
    iVar2 = FUN_0045bdf0();
    if (iVar2 != 0) {
      FUN_00601200();
      *(undefined4 *)(local_30 + 8) = 0xd;
      goto LAB_005a541e;
    }
  }
  puVar1 = (undefined4 *)FUN_00601cf0(local_2c,1);
  *(undefined4 *)(local_30 + 0x4c) = *puVar1;
  *(undefined4 *)(local_30 + 0x50) = puVar1[1];
  *(undefined4 *)(local_30 + 0x54) = puVar1[2];
  local_38 = (float *)(*(int *)(*(int *)(local_30 + 0x10) + 0x230) + 0xc4);
  local_44 = FUN_0045c4d0();
  pfVar3 = (float *)FUN_00440300(local_5c,local_30 + 0x4c,local_44);
  local_20 = *pfVar3;
  local_1c = pfVar3[1];
  local_18 = pfVar3[2];
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  fVar4 = (float10)FUN_00820570((double)(local_20 * local_20 + local_18 * local_18 + 0.0001));
  local_50 = (float)fVar4;
  local_40 = local_14 * local_50 * -5.0;
  iVar2 = FUN_0045c490(0xbf800000,0x3f800000);
  fVar4 = (float10)FUN_00447ed0(local_40 - *(float *)(iVar2 + 0x28));
  *local_38 = (float)fVar4;
  fVar4 = (float10)FUN_00453f80();
  local_4c = (float)fVar4;
  if (local_4c == 1.0) {
    local_34 = 0x3e800000;
  }
  else {
    fVar4 = (float10)FUN_00453f80();
    local_48 = (float)fVar4;
    if (local_48 <= 0.7) {
      local_34 = 0x3f800000;
    }
    else {
      local_34 = 0x3f000000;
    }
  }
  fVar4 = (float10)FUN_00447ed0(local_c * *(float *)(local_30 + 100),local_34 ^ 0x80000000,local_34)
  ;
  local_38[3] = (float)fVar4;
  fVar4 = (float10)FUN_00447ed0(local_14 * *(float *)(local_30 + 0x68),local_34 ^ 0x80000000,
                                local_34);
  local_38[2] = (float)fVar4;
LAB_005a541e:
  FUN_0083e885();
  return;
}

