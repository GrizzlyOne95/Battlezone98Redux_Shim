
void __thiscall FUN_005dfcb0(int param_1,float param_2)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_430 [64];
  undefined1 local_3f0 [64];
  undefined1 local_3b0 [64];
  undefined1 local_370 [64];
  undefined1 local_330 [64];
  float local_2f0;
  float local_2ec;
  int local_2e8;
  int local_2e4;
  float local_2e0;
  int local_2dc;
  undefined1 local_2d8 [64];
  undefined4 local_298 [16];
  undefined4 local_258 [16];
  undefined4 local_218 [16];
  undefined4 local_1d8 [16];
  undefined4 local_198 [16];
  undefined4 local_158 [16];
  undefined4 local_118 [16];
  undefined1 local_d8 [16];
  undefined4 local_c8;
  undefined1 local_ac [16];
  undefined4 local_9c;
  undefined1 local_80 [4];
  undefined4 local_7c;
  undefined1 local_64 [4];
  undefined4 local_60;
  undefined4 local_58;
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(float *)(param_1 + 200) = *(float *)(param_1 + 200) + param_2;
  local_2dc = param_1;
  if ((*(int *)(param_1 + 0xcc) < 1) || (cVar2 = FUN_00611840(), cVar2 == '\0')) {
    if ((*(char *)(local_2dc + 0xd4) == '\0') || (cVar2 = FUN_00611840(), cVar2 == '\0')) {
      if (*(int *)(local_2dc + 0xc0) != 0) {
        FUN_0043aaa0(*(undefined4 *)(local_2dc + 0xc0));
        *(undefined4 *)(local_2dc + 0xc0) = 0;
      }
      *(undefined1 *)(local_2dc + 0xd4) = 0;
    }
    else {
      if (*(int *)(local_2dc + 0xc0) != 0) {
        FUN_0043aaa0(*(undefined4 *)(local_2dc + 0xc0));
        *(undefined4 *)(local_2dc + 0xc0) = 0;
      }
      if (((*(int *)(local_2dc + 0xd8) == 0) && (0.0 < *(float *)(local_2dc + 200))) &&
         (iVar3 = FUN_00417c80(), *(int *)(*(int *)(local_2dc + 0xc4) + 0x4c) <= iVar3)) {
        if (*(char *)(*(int *)(local_2dc + 8) + 0x80) != '\0') {
          FUN_0043a990(local_d8);
          local_c8 = 0x1000;
          FUN_0043a9e0(local_80);
          if ((*(uint *)(*(int *)(local_2dc + 0x18) + 0x14) & 0x10) != 0) {
            local_7c = 0x41;
          }
          FUN_0043aa30(*(int *)(local_2dc + 8) + 0x80,*(undefined4 *)(local_2dc + 0x10),local_d8,
                       local_80);
        }
        (**(code **)(**(int **)(local_2dc + 0xd0) + 0x18))
                  (-*(int *)(*(int *)(local_2dc + 0xc4) + 0x4c));
        puVar5 = (undefined4 *)
                 FUN_0081fe60(local_430,*(int *)(local_2dc + 0x10) + 0x20,local_2dc + 0x28);
        puVar6 = local_258;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar5 = local_258;
        puVar6 = local_218;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        uVar4 = FUN_00586ff0(local_218,*(undefined4 *)(local_2dc + 0x18));
        *(undefined4 *)(local_2dc + 0xd8) = uVar4;
        FUN_005df1f0(local_2dc);
        *(float *)(*(int *)(local_2dc + 0xd8) + 0x10) = *(float *)(local_2dc + 200) - param_2;
        *(float *)(local_2dc + 200) =
             *(float *)(local_2dc + 200) - *(float *)(*(int *)(local_2dc + 8) + 0x94);
      }
      *(undefined1 *)(local_2dc + 0xd4) = 0;
    }
  }
  else {
    FUN_00611770(local_2d8,*(undefined4 *)(local_2dc + 0x18));
    while( true ) {
      if ((*(int *)(local_2dc + 0xcc) < 1) || (*(float *)(local_2dc + 200) <= 0.0))
      goto LAB_005e0108;
      iVar3 = FUN_00417c80();
      if (iVar3 < *(int *)(*(int *)(local_2dc + 0xc) + 0x4c)) break;
      if ((*(char *)(*(int *)(local_2dc + 8) + 0x58) != '\0') && (*(int *)(local_2dc + 0xc0) == 0))
      {
        FUN_0043a990(local_ac);
        local_9c = 0x1001;
        FUN_0043a9e0(local_64);
        local_58 = 1;
        if ((*(uint *)(*(int *)(local_2dc + 0x18) + 0x14) & 0x10) != 0) {
          local_60 = 0x41;
        }
        uVar4 = FUN_0043aa30(*(int *)(local_2dc + 8) + 0x58,*(undefined4 *)(local_2dc + 0x10),
                             local_ac,local_64);
        *(undefined4 *)(local_2dc + 0xc0) = uVar4;
      }
      (**(code **)(**(int **)(local_2dc + 0xd0) + 0x18))
                (-*(int *)(*(int *)(local_2dc + 0xc) + 0x4c));
      local_2e0 = *(float *)(local_2dc + 200) - param_2;
      local_2e4 = FUN_0045c490();
      puVar5 = (undefined4 *)
               FUN_00444d50(local_330,*(int *)(local_2dc + 0x18) + 0x20,
                            *(undefined4 *)(local_2e4 + 0x24),*(undefined4 *)(local_2e4 + 0x28),
                            *(undefined4 *)(local_2e4 + 0x2c),-local_2e0);
      puVar6 = local_118;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar5 = local_118;
      puVar6 = local_48;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      local_20 = local_20 - (double)(*(float *)(local_2e4 + 0x18) * local_2e0);
      local_18 = local_18 - (double)(*(float *)(local_2e4 + 0x1c) * local_2e0);
      local_10 = local_10 - (double)(*(float *)(local_2e4 + 0x20) * local_2e0);
      puVar5 = (undefined4 *)FUN_0081fe60(local_3f0,local_2d8,local_48);
      puVar6 = local_1d8;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar5 = local_1d8;
      puVar6 = local_48;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      iVar3 = *(int *)(local_2dc + 8);
      fVar7 = (float10)FUN_004464c0();
      local_2f0 = (float)fVar7;
      iVar1 = *(int *)(local_2dc + 8);
      fVar7 = (float10)FUN_004464c0(local_2f0 * *(float *)(iVar3 + 0xa4));
      local_2ec = (float)fVar7;
      puVar5 = (undefined4 *)FUN_0081ed60(local_370,local_2ec * *(float *)(iVar1 + 0xa4));
      puVar6 = local_158;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar5 = local_158;
      puVar6 = local_198;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar5 = (undefined4 *)FUN_0081fe60(local_3b0,local_198,local_48);
      puVar6 = local_298;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar5 = local_298;
      puVar6 = local_48;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      local_2e8 = FUN_00586ff0(local_48,*(undefined4 *)(local_2dc + 0x18));
      FUN_0056a490(*(undefined4 *)(local_2dc + 0xdc));
      *(float *)(local_2e8 + 0x10) = local_2e0;
      *(float *)(local_2dc + 200) =
           *(float *)(local_2dc + 200) - *(float *)(*(int *)(local_2dc + 8) + 0x9c);
      *(int *)(local_2dc + 0xcc) = *(int *)(local_2dc + 0xcc) + -1;
    }
    *(undefined4 *)(local_2dc + 0xcc) = 0;
LAB_005e0108:
    if (*(int *)(local_2dc + 0xcc) == 0) {
      *(float *)(local_2dc + 200) =
           *(float *)(local_2dc + 200) - *(float *)(*(int *)(local_2dc + 8) + 0x94);
    }
  }
  if (0.0 < *(float *)(local_2dc + 200)) {
    *(undefined4 *)(local_2dc + 200) = 0;
  }
  FUN_0083e885();
  return;
}

