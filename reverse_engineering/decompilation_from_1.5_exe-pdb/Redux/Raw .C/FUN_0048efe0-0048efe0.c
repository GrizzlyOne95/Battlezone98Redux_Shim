
void __thiscall FUN_0048efe0(int param_1,float param_2)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_36c [64];
  undefined1 local_32c [64];
  undefined1 local_2ec [64];
  undefined1 local_2ac [64];
  float local_26c;
  int local_268;
  float local_264;
  int local_260;
  int local_25c;
  float local_258;
  int local_254;
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
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xc0) + param_2;
  local_254 = param_1;
  if ((*(char *)(param_1 + 0xd8) == '\0') || (*(float *)(param_1 + 0xc0) <= 0.0)) {
    if (0.0 < *(float *)(param_1 + 0xc0)) {
      *(undefined4 *)(param_1 + 0xc0) = 0;
    }
  }
  else {
    if ((((*(int *)(param_1 + 0xd0) == *(int *)(param_1 + 0xb4)) && (*(int *)(param_1 + 0xc) != 0))
        && (iVar3 = FUN_00417c80(), *(int *)(*(int *)(local_254 + 0xc) + 0x4c) <= iVar3)) &&
       (cVar2 = FUN_00611840(), cVar2 != '\0')) {
      *(undefined4 *)(local_254 + 0xc4) = *(undefined4 *)(*(int *)(local_254 + 8) + 0x84);
      *(float *)(local_254 + 200) = *(float *)(local_254 + 0xc0) - param_2;
    }
    *(float *)(local_254 + 0xc0) =
         *(float *)(local_254 + 0xc0) -
         *(float *)(local_254 + 0xcc) / (float)*(int *)(local_254 + 0xb8);
    local_260 = *(int *)(local_254 + 0xd0) + 1;
    *(int *)(local_254 + 0xd0) = local_260;
    if (local_260 == *(int *)(local_254 + 0xb8)) {
      *(undefined4 *)(local_254 + 0xd0) = 0;
    }
  }
  if (0 < *(int *)(local_254 + 0xc4)) {
    *(float *)(local_254 + 200) = *(float *)(local_254 + 200) + param_2;
    if (0.0 <= *(float *)(local_254 + 200)) {
      if (*(char *)(*(int *)(local_254 + 8) + 0x58) != '\0') {
        FUN_0043a990(local_90);
        local_80 = 0x1000;
        FUN_0043a9e0(local_64);
        if ((*(uint *)(*(int *)(local_254 + 0x18) + 0x14) & 0x10) != 0) {
          local_60 = 0x41;
        }
        FUN_0043aa30(*(int *)(local_254 + 8) + 0x58,*(undefined4 *)(local_254 + 0x10),local_90,
                     local_64);
      }
      puVar4 = (undefined4 *)FUN_00611770(local_250,*(undefined4 *)(local_254 + 0x18));
      puVar5 = local_150;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
    }
    while( true ) {
      if ((*(int *)(local_254 + 0xc4) < 1) || (*(float *)(local_254 + 200) < 0.0))
      goto LAB_0048f5ba;
      iVar3 = FUN_00417c80();
      if (iVar3 < *(int *)(*(int *)(local_254 + 0xc) + 0x4c)) break;
      (**(code **)(**(int **)(local_254 + 0xd4) + 0x18))
                (-*(int *)(*(int *)(local_254 + 0xc) + 0x4c));
      local_258 = *(float *)(local_254 + 200) - param_2;
      local_25c = FUN_0045c490();
      puVar4 = (undefined4 *)
               FUN_00444d50(local_2ac,*(int *)(local_254 + 0x18) + 0x20,
                            *(undefined4 *)(local_25c + 0x24),*(undefined4 *)(local_25c + 0x28),
                            *(undefined4 *)(local_25c + 0x2c),-local_258);
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
      puVar4 = (undefined4 *)FUN_0081fe60(local_32c,local_150,local_48);
      puVar5 = local_110;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar4 = local_110;
      puVar5 = local_48;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      iVar3 = *(int *)(local_254 + 8);
      fVar6 = (float10)FUN_004464c0();
      local_264 = (float)fVar6;
      iVar1 = *(int *)(local_254 + 8);
      fVar6 = (float10)FUN_004464c0(local_264 * *(float *)(iVar3 + 0x8c));
      local_26c = (float)fVar6;
      puVar4 = (undefined4 *)
               FUN_0081ed60(local_2ec,
                            local_26c * *(float *)(iVar1 + 0x8c) -
                            *(float *)(*(int *)(local_254 + 8) + 0x90));
      puVar5 = local_1d0;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar4 = local_1d0;
      puVar5 = local_210;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar4 = (undefined4 *)FUN_0081fe60(local_36c,local_210,local_48);
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
      local_268 = FUN_00586ff0(local_48,*(undefined4 *)(local_254 + 0x18));
      *(float *)(local_268 + 0x10) = local_258;
      *(float *)(local_254 + 200) =
           *(float *)(local_254 + 200) - *(float *)(*(int *)(local_254 + 8) + 0x88);
      *(int *)(local_254 + 0xc4) = *(int *)(local_254 + 0xc4) + -1;
    }
    *(undefined4 *)(local_254 + 0xc4) = 0;
  }
LAB_0048f5ba:
  *(undefined1 *)(local_254 + 0xd8) = 0;
  FUN_0083e885();
  return;
}

