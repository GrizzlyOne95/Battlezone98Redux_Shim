
void __thiscall FUN_004d1170(int param_1,float param_2)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  float10 fVar4;
  float fVar5;
  uint local_6c;
  float local_68;
  int local_64;
  double *local_60;
  double local_5c;
  double local_54;
  double local_4c;
  float local_44;
  float local_40;
  float local_3c;
  double local_38;
  double local_30;
  double local_28;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_6c = *(uint *)(param_1 + 0x28);
  local_64 = param_1;
  while (local_6c != *(uint *)(local_64 + 0x2c)) {
    local_60 = (double *)(local_64 + 0x30 + local_6c * 0x30);
    local_6c = local_6c + 1;
    if (0x1f < local_6c) {
      local_6c = 0;
    }
    *(float *)((int)local_60 + 0x2c) =
         *(float *)(local_64 + 0x640) * param_2 + *(float *)((int)local_60 + 0x2c);
    *(float *)((int)local_60 + 0x24) =
         *(float *)(local_64 + 0x638) * param_2 + *(float *)((int)local_60 + 0x24);
    if (*(float *)((int)local_60 + 0x24) <
        (float)(*(int *)(local_64 + 0x630) + *(int *)(local_64 + 0x634))) {
      *(float *)((int)local_60 + 0x1c) = *(float *)((int)local_60 + 0x1c) - param_2 * 9.8;
      local_68 = param_2;
      iVar2 = FUN_00784620(*(undefined4 *)local_60,*(undefined4 *)((int)local_60 + 4),
                           *(undefined4 *)(local_60 + 1),*(undefined4 *)((int)local_60 + 0xc),
                           *(undefined4 *)(local_60 + 2),*(undefined4 *)((int)local_60 + 0x14),
                           *(undefined4 *)(local_60 + 3),*(undefined4 *)((int)local_60 + 0x1c),
                           *(undefined4 *)(local_60 + 4),&local_68,&local_20);
      if (iVar2 == 0) {
        *local_60 = (double)(*(float *)(local_60 + 3) * param_2) + *local_60;
        local_60[1] = (double)(*(float *)((int)local_60 + 0x1c) * param_2) + local_60[1];
        local_60[2] = (double)(*(float *)(local_60 + 4) * param_2) + local_60[2];
        *(float *)(local_60 + 5) = *(float *)(local_60 + 5) + local_68;
        while (0.0 < *(float *)(local_60 + 5)) {
          local_5c = *local_60 - (double)(*(float *)(local_60 + 3) * *(float *)(local_60 + 5));
          local_54 = local_60[1] -
                     (double)(*(float *)((int)local_60 + 0x1c) * *(float *)(local_60 + 5));
          local_4c = local_60[2] - (double)(*(float *)(local_60 + 4) * *(float *)(local_60 + 5));
          fVar5 = *(float *)(local_64 + 0x664);
          fVar1 = *(float *)(local_60 + 3);
          fVar4 = (float10)FUN_004464c0();
          local_44 = fVar5 * fVar1 + (float)fVar4 * *(float *)(local_64 + 0x660);
          fVar5 = *(float *)(local_64 + 0x664);
          fVar1 = *(float *)((int)local_60 + 0x1c);
          fVar4 = (float10)FUN_004464c0();
          local_40 = fVar5 * fVar1 + (float)fVar4 * *(float *)(local_64 + 0x660);
          fVar5 = *(float *)(local_64 + 0x664);
          fVar1 = *(float *)(local_60 + 4);
          fVar4 = (float10)FUN_004464c0();
          local_3c = fVar5 * fVar1 + (float)fVar4 * *(float *)(local_64 + 0x660);
          FUN_004910c0(*(undefined4 *)(local_64 + 0x644),&local_5c,&local_44,
                       *(undefined4 *)(local_60 + 5));
          *(float *)(local_60 + 5) = *(float *)(local_60 + 5) - *(float *)(local_64 + 0x654);
        }
      }
      else {
        *local_60 = (double)(*(float *)(local_60 + 3) * local_68) + *local_60;
        local_60[1] = (double)(*(float *)((int)local_60 + 0x1c) * local_68) + local_60[1];
        local_60[2] = (double)(*(float *)(local_60 + 4) * local_68) + local_60[2];
        *(float *)(local_60 + 5) = *(float *)(local_60 + 5) + local_68;
        while (0.0 < *(float *)(local_60 + 5)) {
          local_38 = *local_60 - (double)(*(float *)(local_60 + 3) * *(float *)(local_60 + 5));
          local_30 = local_60[1] -
                     (double)(*(float *)((int)local_60 + 0x1c) * *(float *)(local_60 + 5));
          local_28 = local_60[2] - (double)(*(float *)(local_60 + 4) * *(float *)(local_60 + 5));
          fVar5 = *(float *)(local_64 + 0x664);
          fVar1 = *(float *)(local_60 + 3);
          fVar4 = (float10)FUN_004464c0();
          local_14 = fVar5 * fVar1 + (float)fVar4 * *(float *)(local_64 + 0x660);
          fVar5 = *(float *)(local_64 + 0x664);
          fVar1 = *(float *)((int)local_60 + 0x1c);
          fVar4 = (float10)FUN_004464c0();
          local_10 = fVar5 * fVar1 + (float)fVar4 * *(float *)(local_64 + 0x660);
          fVar5 = *(float *)(local_64 + 0x664) * *(float *)(local_60 + 4);
          fVar4 = (float10)FUN_004464c0(fVar5);
          local_c = fVar5 + (float)fVar4 * *(float *)(local_64 + 0x660);
          FUN_004910c0(*(undefined4 *)(local_64 + 0x644),&local_38,&local_14,
                       *(undefined4 *)(local_60 + 5));
          *(float *)(local_60 + 5) = *(float *)(local_60 + 5) - *(float *)(local_64 + 0x654);
        }
        fVar5 = *(float *)(local_60 + 3) * local_20 + *(float *)((int)local_60 + 0x1c) * local_1c +
                *(float *)(local_60 + 4) * local_18;
        *(float *)(local_60 + 3) = *(float *)(local_60 + 3) * 0.5 - fVar5 * local_20;
        *(float *)((int)local_60 + 0x1c) = *(float *)((int)local_60 + 0x1c) * 0.5 - fVar5 * local_1c
        ;
        *(float *)(local_60 + 4) = *(float *)(local_60 + 4) * 0.5 - fVar5 * local_18;
        local_68 = param_2 - local_68;
        *local_60 = (double)(*(float *)(local_60 + 3) * local_68) + *local_60;
        local_60[1] = (double)(*(float *)((int)local_60 + 0x1c) * local_68) + local_60[1];
        local_60[2] = (double)(*(float *)(local_60 + 4) * local_68) + local_60[2];
        *(float *)(local_60 + 5) = *(float *)(local_60 + 5) + local_68;
        while (0.0 < *(float *)(local_60 + 5)) {
          local_38 = *local_60 - (double)(*(float *)(local_60 + 3) * *(float *)(local_60 + 5));
          local_30 = local_60[1] -
                     (double)(*(float *)((int)local_60 + 0x1c) * *(float *)(local_60 + 5));
          local_28 = local_60[2] - (double)(*(float *)(local_60 + 4) * *(float *)(local_60 + 5));
          fVar5 = *(float *)(local_64 + 0x664);
          fVar1 = *(float *)(local_60 + 3);
          fVar4 = (float10)FUN_004464c0();
          local_14 = fVar5 * fVar1 + (float)fVar4 * *(float *)(local_64 + 0x660);
          fVar5 = *(float *)(local_64 + 0x664);
          fVar1 = *(float *)((int)local_60 + 0x1c);
          fVar4 = (float10)FUN_004464c0();
          local_10 = fVar5 * fVar1 + (float)fVar4 * *(float *)(local_64 + 0x660);
          fVar5 = *(float *)(local_64 + 0x664);
          fVar1 = *(float *)(local_60 + 4);
          fVar4 = (float10)FUN_004464c0();
          local_c = fVar5 * fVar1 + (float)fVar4 * *(float *)(local_64 + 0x660);
          FUN_004910c0(*(undefined4 *)(local_64 + 0x644),&local_38,&local_14,
                       *(undefined4 *)(local_60 + 5));
          *(float *)(local_60 + 5) = *(float *)(local_60 + 5) - *(float *)(local_64 + 0x654);
        }
      }
    }
    else {
      uVar3 = *(int *)(local_64 + 0x28) + 1;
      *(uint *)(local_64 + 0x28) = uVar3;
      if (0x1f < uVar3) {
        *(undefined4 *)(local_64 + 0x28) = 0;
      }
    }
  }
  FUN_0083e885();
  return;
}

