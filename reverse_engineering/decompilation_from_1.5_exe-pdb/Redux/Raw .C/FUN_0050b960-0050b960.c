
void __thiscall FUN_0050b960(int *param_1,float param_2)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_370 [64];
  undefined1 local_330 [64];
  undefined1 local_2f0 [64];
  undefined1 local_2b0 [64];
  float local_270;
  int local_26c;
  float local_268;
  int local_264;
  undefined *local_260;
  int local_25c;
  float local_258;
  int *local_254;
  undefined1 local_250 [64];
  undefined4 local_210 [16];
  undefined4 local_1d0 [16];
  undefined4 local_190 [16];
  undefined4 local_150 [16];
  undefined4 local_110 [16];
  undefined4 local_d0 [16];
  undefined1 local_90 [16];
  undefined4 local_80;
  undefined1 local_64 [4];
  undefined4 local_60;
  undefined4 local_58;
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  param_1[0x30] = (int)((float)param_1[0x30] + param_2);
  local_254 = param_1;
  if (((((char)param_1[0x36] == '\0') || (param_1[3] == 0)) ||
      (iVar3 = FUN_00417c80(), iVar3 < *(int *)(local_254[3] + 0x4c))) ||
     (cVar2 = FUN_00611840(), cVar2 == '\0')) {
    if (0.0 < (float)local_254[0x30]) {
      local_254[0x30] = 0;
    }
    if (local_254[0x38] != 0) {
      iVar3 = FUN_0043ac70(0,local_254[4]);
      local_254[0x38] = iVar3;
      if (local_254[0x38] != 0) {
        FUN_0043aaa0(local_254[0x38]);
        local_254[0x38] = 0;
      }
    }
  }
  else {
    if ((*(char *)(local_254[2] + 0x58) != '\0') && (local_254[0x38] == 0)) {
      FUN_0043a990(local_90);
      local_80 = 0x1001;
      FUN_0043a9e0(local_64);
      local_58 = 1;
      if ((*(uint *)(local_254[6] + 0x14) & 0x10) != 0) {
        local_60 = 0x41;
      }
      iVar3 = FUN_0043aa30(local_254[2] + 0x58,local_254[4],local_90,local_64);
      local_254[0x38] = iVar3;
    }
    if (0.0 < (float)local_254[0x30]) {
      puVar4 = (undefined4 *)FUN_00611770(local_250,local_254[6]);
      puVar5 = local_110;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
    }
    while ((0.0 < (float)local_254[0x30] && (cVar2 = (**(code **)(*local_254 + 4))(), cVar2 != '\0')
           )) {
      (**(code **)(*(int *)local_254[0x35] + 0x18))(-*(int *)(local_254[3] + 0x4c));
      if (((*(uint *)(local_254[6] + 0x14) & 0x10) != 0) &&
         ((local_264 = local_254[4], *(int *)(local_264 + 8) == 0x63657467 &&
          (*(undefined1 **)(local_264 + 0xc) == &LAB_006f6e68)))) {
        iVar3 = DAT_00917b24 * 3;
        local_260 = &DAT_00872388 + iVar3;
        FUN_0049b430(0x3f800000,0x40a00000,*local_260,(&DAT_00872389)[iVar3],(&DAT_0087238a)[iVar3])
        ;
        DAT_00917b24 = DAT_00917b24 + 1;
        if (DAT_00917b24 == 0x1e) {
          DAT_00917b24 = 0;
        }
      }
      local_258 = (float)local_254[0x30] - param_2;
      local_25c = FUN_0045c490();
      puVar4 = (undefined4 *)
               FUN_00444d50(local_2b0,local_254[6] + 0x20,*(undefined4 *)(local_25c + 0x24),
                            *(undefined4 *)(local_25c + 0x28),*(undefined4 *)(local_25c + 0x2c),
                            -local_258);
      puVar5 = local_d0;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar4 = local_d0;
      puVar5 = local_48;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      local_20 = local_20 - (double)(*(float *)(local_25c + 0x18) * local_258);
      local_18 = local_18 - (double)(*(float *)(local_25c + 0x1c) * local_258);
      local_10 = local_10 - (double)(*(float *)(local_25c + 0x20) * local_258);
      puVar4 = (undefined4 *)FUN_0081fe60(local_330,local_110,local_48);
      puVar5 = local_150;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar4 = local_150;
      puVar5 = local_48;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      iVar3 = local_254[2];
      fVar6 = (float10)FUN_004464c0();
      local_268 = (float)fVar6;
      iVar1 = local_254[2];
      fVar6 = (float10)FUN_004464c0(local_268 * *(float *)(iVar3 + 0x8c));
      local_270 = (float)fVar6;
      puVar4 = (undefined4 *)
               FUN_0081ed60(local_2f0,
                            local_270 * *(float *)(iVar1 + 0x8c) - *(float *)(local_254[2] + 0x90));
      puVar5 = local_210;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar4 = local_210;
      puVar5 = local_1d0;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar4 = (undefined4 *)FUN_0081fe60(local_370,local_1d0,local_48);
      puVar5 = local_190;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar4 = local_190;
      puVar5 = local_48;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      local_26c = FUN_00586ff0(local_48,local_254[6]);
      *(float *)(local_26c + 0x10) = local_258;
      local_254[0x30] = (int)((float)local_254[0x30] - *(float *)(local_254[2] + 0x80));
    }
  }
  *(undefined1 *)(local_254 + 0x36) = 0;
  FUN_0083e885();
  return;
}

