
void __thiscall FUN_005a18a0(int param_1,byte *param_2,int *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_60 [12];
  undefined1 local_54 [12];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 *local_40;
  float local_3c;
  int local_38;
  undefined4 *local_34;
  int local_30;
  undefined1 local_29;
  byte *local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = param_2;
  *(float *)(param_1 + 500) = (float)param_2[1] / 255.0;
  local_24 = param_1;
  iVar1 = FUN_0046d060();
  FUN_004a7700((int)((float)iVar1 * *(float *)(local_24 + 500)));
  *(float *)(local_24 + 0x1e8) = (float)*local_28 / 255.0;
  FUN_004a76a0(*(float *)(local_24 + 0x1f0) * *(float *)(local_24 + 0x1e8));
  puVar2 = (undefined4 *)
           FUN_00625950(local_54,*(undefined4 *)(local_28 + 2),*(undefined2 *)(local_28 + 6));
  local_14 = *puVar2;
  local_10 = puVar2[1];
  local_c = puVar2[2];
  *(undefined4 *)(local_24 + 0x114) = local_14;
  *(undefined4 *)(local_24 + 0x118) = local_10;
  *(undefined4 *)(local_24 + 0x11c) = local_c;
  iVar1 = *(int *)(local_24 + 0x218);
  *(undefined4 *)(iVar1 + 0x1c) = *(undefined4 *)(local_24 + 0x114);
  *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(local_24 + 0x118);
  *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(local_24 + 0x11c);
  puVar2 = (undefined4 *)
           FUN_00625950(local_60,*(undefined4 *)(local_28 + 8),*(undefined2 *)(local_28 + 0xc));
  local_20 = *puVar2;
  local_1c = puVar2[1];
  local_18 = puVar2[2];
  iVar1 = *(int *)(local_24 + 0x218);
  *(undefined4 *)(iVar1 + 0x28) = local_20;
  *(undefined4 *)(iVar1 + 0x2c) = local_1c;
  *(undefined4 *)(iVar1 + 0x30) = local_18;
  iVar1 = *(int *)(local_24 + 0x218);
  *(undefined4 *)(local_24 + 0x120) = *(undefined4 *)(iVar1 + 0x28);
  *(undefined4 *)(local_24 + 0x124) = *(undefined4 *)(iVar1 + 0x2c);
  *(undefined4 *)(local_24 + 0x128) = *(undefined4 *)(iVar1 + 0x30);
  fVar3 = (float10)FUN_0045c420(*(undefined4 *)(local_24 + 0x114),*(undefined4 *)(local_24 + 0x118),
                                *(undefined4 *)(local_24 + 0x11c));
  *(float *)(*(int *)(local_24 + 0x218) + 0xc) = (float)fVar3;
  if (*(float *)(*(int *)(local_24 + 0x218) + 0xc) <= 0.0) {
    local_3c = 1e+30;
  }
  else {
    local_3c = 1.0 / *(float *)(*(int *)(local_24 + 0x218) + 0xc);
  }
  *(float *)(*(int *)(local_24 + 0x218) + 0x10) = local_3c;
  *(undefined4 *)(local_24 + 0x104) = *(undefined4 *)(*(int *)(local_24 + 0x218) + 0xc);
  *(undefined4 *)(local_24 + 0x108) = *(undefined4 *)(*(int *)(local_24 + 0x218) + 0x10);
  *(uint *)(*(int *)(local_24 + 0x218) + 0xd8) = local_28[0x12] & 1;
  *(uint *)(*(int *)(local_24 + 0x218) + 0xd4) = local_28[0x12] & 2;
  *(uint *)(*(int *)(local_24 + 0x218) + 0xdc) = local_28[0x12] & 4;
  fVar3 = (float10)FUN_006258b0(local_28[0xe]);
  *(float *)(*(int *)(local_24 + 0x218) + 0xc4) = (float)fVar3;
  fVar3 = (float10)FUN_006258b0(local_28[0xf]);
  *(float *)(*(int *)(local_24 + 0x218) + 200) = (float)fVar3;
  fVar3 = (float10)FUN_006258b0(local_28[0x10]);
  *(float *)(*(int *)(local_24 + 0x218) + 0xcc) = (float)fVar3;
  fVar3 = (float10)FUN_006258b0(local_28[0x11]);
  *(float *)(*(int *)(local_24 + 0x218) + 0xd0) = (float)fVar3;
  if ((local_28[0x12] & 8) == 0) {
    *(uint *)(*(int *)(local_24 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_24 + 0x218) + 0x114) & 0xffffff7f;
  }
  else {
    *(uint *)(*(int *)(local_24 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_24 + 0x218) + 0x114) | 0x80;
  }
  if ((local_28[0x12] & 0x10) == 0) {
    *(uint *)(*(int *)(local_24 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_24 + 0x218) + 0x114) & 0xfffffffb;
  }
  else {
    *(uint *)(*(int *)(local_24 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_24 + 0x218) + 0x114) | 4;
  }
  if ((local_28[0x12] & 0x40) == 0) {
    *(uint *)(*(int *)(local_24 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_24 + 0x218) + 0x114) & 0xffffefff;
  }
  else {
    *(uint *)(*(int *)(local_24 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_24 + 0x218) + 0x114) | 0x1000;
  }
  if ((local_28[0x13] & 3) == 0) {
    *(undefined4 *)(local_24 + 0x210) = 2;
  }
  else if ((local_28[0x13] & 3) == 1) {
    *(undefined4 *)(local_24 + 0x210) = 0;
  }
  else if ((local_28[0x13] & 3) == 2) {
    *(undefined4 *)(local_24 + 0x210) = 1;
  }
  else if ((local_28[0x13] & 3) == 3) {
    *(undefined4 *)(local_24 + 0x210) = 3;
  }
  if ((local_28[0x13] & 4) != 0) {
    local_40 = *(undefined4 **)(local_24 + 0xe4);
    local_34 = local_40;
    if (local_40 == (undefined4 *)0x0) {
      local_44 = 0;
    }
    else {
      local_44 = (**(code **)*local_40)(1);
    }
    *(undefined4 *)(local_24 + 0xe4) = 0;
  }
  if (*(int *)(local_24 + 0x188) != 0) {
    for (local_30 = 0; local_30 < 5; local_30 = local_30 + 1) {
      local_38 = FUN_00417f60(local_30);
      if ((local_38 != 0) && (*(int *)(*(int *)(local_38 + 8) + 0xc) == 0x534e4950)) {
        if ((local_28[0x13] & 8) == 0) {
          FUN_004d9880(0);
        }
        else {
          FUN_004d9880(1 << ((byte)local_30 & 0x1f));
        }
      }
    }
  }
  local_29 = (local_28[0x12] & 0x20) != 0;
  FUN_0049f300(local_29);
  if ((local_28[0x12] & 0x80) != 0) {
    FUN_004a76a0(0xbf800000);
    local_48 = FUN_0045ca50();
    FUN_0062de40(*(undefined4 *)(local_24 + 0xdc),&DAT_01000080);
    FUN_004b8460();
  }
  *param_3 = *param_3 + -0x14;
  FUN_0083e885();
  return;
}

