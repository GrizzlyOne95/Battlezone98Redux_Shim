
void __thiscall FUN_005da6e0(int *param_1,float param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_2ac [64];
  undefined1 local_26c [64];
  undefined1 local_22c [64];
  undefined4 local_1ec;
  undefined4 local_1e8;
  float local_1e4;
  float local_1e0;
  int local_1dc;
  int local_1d8;
  int *local_1d4;
  undefined4 local_1d0 [16];
  undefined4 local_190 [16];
  undefined4 local_150 [16];
  undefined4 local_110 [16];
  undefined4 local_d0 [16];
  undefined1 local_90 [16];
  undefined4 local_80;
  undefined1 local_64 [12];
  undefined4 local_58;
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  param_1[0x4f] =
       (int)((*(float *)(param_1[0x3e] + 0x180) - (float)param_1[0x4f]) * param_2 +
            (float)param_1[0x4f]);
  local_1d4 = param_1;
  puVar1 = (undefined4 *)
           FUN_00444d50(local_22c,param_1[0x3d] + 0x20,param_1[0x4e],param_1[0x4f],param_1[0x50],
                        param_2);
  puVar3 = local_d0;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = local_d0;
  puVar3 = (undefined4 *)(local_1d4[0x3d] + 0x20);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  fVar4 = (float10)FUN_007855e0(*(undefined8 *)(local_1d4[0x3d] + 0x48),
                                *(undefined8 *)(local_1d4[0x3d] + 0x58));
  local_1e0 = (float)fVar4;
  *(double *)(local_1d4[0x3d] + 0x50) =
       (double)(param_2 * 2.0) *
       ((double)(local_1e0 + *(float *)(local_1d4[0x3e] + 0x17c)) -
       *(double *)(local_1d4[0x3d] + 0x50)) + *(double *)(local_1d4[0x3d] + 0x50);
  FUN_004db100();
  local_1dc = *(int *)(local_1d4[0x3e] + 0x160);
  local_1d4[0x90] = (int)((float)local_1d4[0x90] + param_2);
  do {
    if ((float)local_1d4[0x90] < 0.0) {
LAB_005dacaa:
      FUN_0083e885();
      return;
    }
    if (local_1dc == 0) {
LAB_005da8da:
      *(uint *)(local_1d4[0x3d] + 0x14) = *(uint *)(local_1d4[0x3d] + 0x14) | 0x200;
      (**(code **)(local_1d4[6] + 0x14))();
      goto LAB_005dacaa;
    }
    iVar2 = FUN_00417c80();
    if (iVar2 < *(int *)(local_1dc + 0x4c)) goto LAB_005da8da;
    if ((*(char *)(local_1d4[0x3e] + 0x164) != '\0') && (local_1d4[0x8e] == 0)) {
      FUN_0043a990();
      local_80 = 0x1001;
      FUN_0043a9e0();
      local_58 = 1;
      iVar2 = FUN_0043aa30(local_1d4[0x3e] + 0x164,local_1d4[0x3d],local_90,local_64);
      local_1d4[0x8e] = iVar2;
    }
    puVar1 = (undefined4 *)
             FUN_00444d50(local_2ac,local_1d4[0x3d] + 0x20,local_1d4[0x4e],local_1d4[0x4f],
                          local_1d4[0x50]);
    puVar3 = local_110;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_110;
    puVar3 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    local_20 = local_20 - (double)((float)local_1d4[0x4b] * (float)local_1d4[0x90]);
    local_18 = local_18 - (double)((float)local_1d4[0x4c] * (float)local_1d4[0x90]);
    local_10 = local_10 - (double)((float)local_1d4[0x4d] * (float)local_1d4[0x90]);
    local_1ec = *(undefined4 *)(local_1d4[0x3e] + 0x184);
    fVar4 = (float10)FUN_004464c0();
    local_1e4 = (float)fVar4;
    puVar1 = (undefined4 *)FUN_0081ec40(local_26c);
    puVar3 = local_150;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_150;
    puVar3 = local_1d0;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = (undefined4 *)FUN_0081fe60();
    puVar3 = local_190;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_190;
    puVar3 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    local_1d8 = FUN_00586ff0(local_48,local_1d4[0x3d]);
    *(undefined4 *)(local_1d8 + 0x80) = 0;
    *(ushort *)(local_1d8 + 0x68) =
         *(ushort *)(local_1d8 + 0x68) & 0xffef | (*(byte *)(local_1d4 + 0x8f) & 1) << 4;
    *(ushort *)(local_1d8 + 0x68) =
         *(ushort *)(local_1d8 + 0x68) & 0xffdf | (*(byte *)((int)local_1d4 + 0x23d) & 1) << 5;
    local_1e8 = FUN_0047e9a0();
    *(ushort *)(local_1d8 + 0x68) =
         *(ushort *)(local_1d8 + 0x68) & 0xfc3f | ((ushort)local_1e8 & 0xf) << 6;
    *(float *)(local_1d8 + 0x10) = (float)local_1d4[0x90] - param_2;
    local_1d4[0x90] = (int)((float)local_1d4[0x90] - *(float *)(local_1d4[0x3e] + 0x178));
    (**(code **)(*local_1d4 + 0x18))();
  } while( true );
}

