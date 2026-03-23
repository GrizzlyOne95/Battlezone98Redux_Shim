
void __fastcall FUN_004acbc0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  float *pfVar3;
  undefined4 *puVar4;
  undefined1 local_168 [64];
  undefined1 local_128 [24];
  undefined1 local_110 [12];
  undefined1 local_104 [12];
  undefined4 local_f8;
  float *local_f4;
  int local_f0;
  int local_ec;
  undefined4 local_e8 [16];
  undefined4 local_a8 [10];
  double local_80;
  double local_78;
  double local_70;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_ec = param_1;
  for (local_f0 = 0; local_f0 < *(int *)(local_ec + 0x27c); local_f0 = local_f0 + 1) {
    if ((*(int *)(local_ec + 0x23c + local_f0 * 4) != 0) &&
       (*(int *)(*(int *)(local_ec + 0x23c + local_f0 * 4) + 0x18) != *(int *)(local_ec + 0x238))) {
      FUN_0044dc60(0,0);
    }
    if (((*(int *)(local_ec + 0x238) == 0) ||
        ((*(uint *)(*(int *)(local_ec + 0xf4) + 0x14) & 0x600) != 0)) ||
       (iVar1 = FUN_00451de0(), iVar1 != 0)) {
      if (*(int *)(local_ec + 0x23c + local_f0 * 4) != 0) {
        FUN_0044dc60(0,0);
      }
    }
    else {
      puVar2 = (undefined4 *)
               FUN_0062e070(local_168,*(undefined4 *)(local_ec + 0x25c + local_f0 * 4),0);
      puVar4 = local_e8;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_e8;
      puVar4 = local_a8;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      if (*(int *)(*(int *)(local_ec + 0xf0) + 0xb0) == 0) {
        iVar1 = *(int *)(local_ec + 0x25c + local_f0 * 4);
        local_f4 = (float *)(iVar1 + 0xb0);
        puVar2 = (undefined4 *)
                 FUN_00440000(local_110,(*(float *)(iVar1 + 0xbc) + *local_f4) * 0.5,
                              (*(float *)(iVar1 + 0xc0) + *(float *)(iVar1 + 0xb4)) * 0.5,
                              *(undefined4 *)(iVar1 + 0xb8));
        local_50 = *puVar2;
        local_4c = puVar2[1];
        local_48 = puVar2[2];
        local_14 = local_50;
        local_10 = local_4c;
        local_c = local_48;
        pfVar3 = (float *)FUN_00440210(local_104,&local_50,local_a8);
        local_44 = *pfVar3;
        local_40 = pfVar3[1];
        local_3c = pfVar3[2];
        local_80 = (double)local_44 + local_80;
        local_78 = (double)local_40 + local_78;
        local_70 = (double)local_3c + local_70;
        local_20 = local_44;
        local_1c = local_40;
        local_18 = local_3c;
      }
      else {
        local_f8 = *(undefined4 *)(*(int *)(local_ec + 0xf0) + 0xb0);
        puVar2 = (undefined4 *)FUN_0067d8f0(local_128,*(undefined4 *)(local_ec + 0xf0),local_f8);
        local_68 = *puVar2;
        local_64 = puVar2[1];
        local_60 = puVar2[2];
        local_5c = puVar2[3];
        local_58 = puVar2[4];
        local_54 = puVar2[5];
        local_38 = local_68;
        local_34 = local_64;
        local_30 = local_60;
        local_2c = local_5c;
        local_28 = local_58;
        local_24 = local_54;
        FUN_0044b7d0(local_a8,&local_68);
      }
      if (*(int *)(local_ec + 0x23c + local_f0 * 4) == 0) {
        (**(code **)(**(int **)(local_ec + 0x238) + 8))(local_ec + 0x23c + local_f0 * 4,local_a8);
      }
      else {
        FUN_0044dca0(local_a8);
      }
    }
  }
  FUN_0083e885();
  return;
}

