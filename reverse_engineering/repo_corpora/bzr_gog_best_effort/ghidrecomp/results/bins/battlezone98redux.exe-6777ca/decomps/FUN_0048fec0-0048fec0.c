
void __thiscall FUN_0048fec0(int param_1,float param_2)

{
  int iVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_3bc [64];
  undefined1 local_37c [64];
  undefined1 local_33c [64];
  undefined1 local_2fc [64];
  float local_2bc;
  float local_2b8;
  int local_2b4;
  int local_2b0;
  int local_2ac;
  int local_2a8;
  int local_2a4;
  float local_2a0;
  int local_29c;
  undefined1 local_298 [64];
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
  local_29c = param_1;
  if ((*(int *)(param_1 + 0xf0) < 1) || (cVar2 = FUN_00611840(), cVar2 == '\0')) {
    if (*(char *)(local_29c + 0xd8) == '\0') {
      if (0.0 < *(float *)(local_29c + 0xc0)) {
        if (*(int *)(local_29c + 0xe0) != 0) {
          uVar4 = FUN_0043ac70(*(int *)(local_29c + 8) + 0x58,*(undefined4 *)(local_29c + 0x10));
          *(undefined4 *)(local_29c + 0xe0) = uVar4;
          if (*(int *)(local_29c + 0xe0) != 0) {
            FUN_0043aaa0(*(undefined4 *)(local_29c + 0xe0));
            *(undefined4 *)(local_29c + 0xe0) = 0;
          }
        }
        *(undefined4 *)(local_29c + 0xc0) = 0;
        *(undefined4 *)(local_29c + 0xf0) = *(undefined4 *)(*(int *)(local_29c + 0xe4) + 4);
        if (*(int *)(local_29c + 0xf0) < 1) {
          *(undefined4 *)(local_29c + 0xe4) = *(undefined4 *)(local_29c + 0xe8);
          *(undefined4 *)(local_29c + 0xc) = *(undefined4 *)(*(int *)(local_29c + 0xe4) + 0x20);
          *(undefined4 *)(local_29c + 0xb0) = *(undefined4 *)(*(int *)(local_29c + 0xe4) + 0x28);
          if (*(float *)(*(int *)(local_29c + 0xe4) + 8) == 0.0) {
            *(int *)(local_29c + 0xb0) =
                 *(int *)(local_29c + 0xb0) * *(int *)(*(int *)(local_29c + 0xe4) + 4);
          }
        }
        else {
          *(undefined1 *)(local_29c + 0xd8) = 1;
        }
      }
    }
    else {
      if (*(uint *)(local_29c + 0xe4) < *(uint *)(local_29c + 0xec)) {
        local_2a8 = *(int *)(*(int *)(local_29c + 0xe4) + 0x4c);
        if ((local_2a8 == 0) || (iVar5 = FUN_00417c80(), *(int *)(local_2a8 + 0x4c) <= iVar5)) {
          *(float *)(local_29c + 0xc0) = *(float *)(local_29c + 0xc0) + param_2;
        }
        if (*(float *)(*(int *)(local_29c + 0xe4) + 0x2c) <= *(float *)(local_29c + 0xc0)) {
          *(int *)(local_29c + 0xc) = local_2a8;
          *(undefined4 *)(local_29c + 0xb0) = *(undefined4 *)(*(int *)(local_29c + 0xe4) + 0x54);
          if (*(float *)(*(int *)(local_29c + 0xe4) + 0x34) == 0.0) {
            *(int *)(local_29c + 0xb0) =
                 *(int *)(local_29c + 0xb0) * *(int *)(*(int *)(local_29c + 0xe4) + 0x30);
          }
          *(int *)(local_29c + 0xe4) = *(int *)(local_29c + 0xe4) + 0x2c;
        }
      }
      else if (**(float **)(local_29c + 0xec) <= *(float *)(local_29c + 0xc0) &&
               *(float *)(local_29c + 0xc0) != **(float **)(local_29c + 0xec)) {
        *(undefined4 *)(local_29c + 0xc0) = **(undefined4 **)(local_29c + 0xec);
      }
      if (*(char *)(*(int *)(local_29c + 8) + 0x58) != '\0') {
        if (*(int *)(local_29c + 0xe0) == 0) {
          FUN_0043a990(local_ac);
          local_9c = 0x4001;
          FUN_0043a9e0(local_64);
          local_58 = 1;
          if ((*(uint *)(*(int *)(local_29c + 0x10) + 0x14) & 0x10) != 0) {
            local_60 = 0x41;
          }
          uVar4 = FUN_0043aa30(*(int *)(local_29c + 8) + 0x58,*(undefined4 *)(local_29c + 0x10),
                               local_ac,local_64);
          *(undefined4 *)(local_29c + 0xe0) = uVar4;
        }
        else {
          uVar4 = FUN_0043ac70(*(int *)(local_29c + 8) + 0x58,*(undefined4 *)(local_29c + 0x10));
          *(undefined4 *)(local_29c + 0xe0) = uVar4;
        }
        if (*(int *)(local_29c + 0xe0) != 0) {
          local_2b4 = (int)(*(float *)(local_29c + 0xc0) *
                            *(float *)(*(int *)(local_29c + 8) + 0x9c) +
                           *(float *)(*(int *)(local_29c + 8) + 0x98));
          local_2b0 = (int)(*(float *)(local_29c + 0xc0) *
                            *(float *)(*(int *)(local_29c + 8) + 0xa4) +
                           *(float *)(*(int *)(local_29c + 8) + 0xa0));
          FUN_0043ae50(*(undefined4 *)(local_29c + 0xe0),local_2b0,0xfffffffe,local_2b4);
        }
      }
      *(undefined1 *)(local_29c + 0xd8) = 0;
    }
  }
  else {
    if ((*(char *)(local_29c + 0xd8) != '\0') &&
       (*(undefined1 *)(local_29c + 0xd8) = 0, *(char *)(*(int *)(local_29c + 0xe4) + 0x10) != '\0')
       ) {
      FUN_0043a990(local_d8);
      local_c8 = 0x1000;
      FUN_0043a9e0(local_80);
      if ((*(uint *)(*(int *)(local_29c + 0x18) + 0x14) & 0x10) != 0) {
        local_7c = 0x41;
      }
      FUN_0043aa30(*(int *)(local_29c + 0xe4) + 0x10,*(undefined4 *)(local_29c + 0x10),local_d8,
                   local_80);
    }
    *(float *)(local_29c + 0xc0) = *(float *)(local_29c + 0xc0) + param_2;
    if (0.0 < *(float *)(local_29c + 0xc0)) {
      puVar3 = (undefined4 *)FUN_00611770(local_298,*(undefined4 *)(local_29c + 0x18));
      puVar6 = local_158;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar6 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar6 = puVar6 + 1;
      }
    }
    while( true ) {
      if ((*(int *)(local_29c + 0xf0) < 1) || (*(float *)(local_29c + 0xc0) <= 0.0))
      goto LAB_00490338;
      iVar5 = FUN_00417c80();
      if (iVar5 < *(int *)(*(int *)(local_29c + 0xc) + 0x4c)) break;
      if (*(int *)(local_29c + 0xc) != 0) {
        (**(code **)(**(int **)(local_29c + 0xd4) + 0x18))
                  (-*(int *)(*(int *)(local_29c + 0xc) + 0x4c));
        local_2a0 = *(float *)(local_29c + 0xc0) - param_2;
        local_2a4 = FUN_0045c490();
        puVar3 = (undefined4 *)
                 FUN_00444d50(local_2fc,*(int *)(local_29c + 0x18) + 0x20,
                              *(undefined4 *)(local_2a4 + 0x24),*(undefined4 *)(local_2a4 + 0x28),
                              *(undefined4 *)(local_2a4 + 0x2c),-local_2a0);
        puVar6 = local_118;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar3 = local_118;
        puVar6 = local_48;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        local_20 = local_20 - (double)(*(float *)(local_2a4 + 0x18) * local_2a0);
        local_18 = local_18 - (double)(*(float *)(local_2a4 + 0x1c) * local_2a0);
        local_10 = local_10 - (double)(*(float *)(local_2a4 + 0x20) * local_2a0);
        puVar3 = (undefined4 *)FUN_0081fe60(local_37c,local_158,local_48);
        puVar6 = local_258;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar3 = local_258;
        puVar6 = local_48;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        iVar5 = *(int *)(local_29c + 0xe4);
        fVar7 = (float10)FUN_004464c0();
        local_2b8 = (float)fVar7;
        iVar1 = *(int *)(local_29c + 0xe4);
        fVar7 = (float10)FUN_004464c0(local_2b8 * *(float *)(iVar5 + 0xc));
        local_2bc = (float)fVar7;
        puVar3 = (undefined4 *)FUN_0081ed60(local_33c,local_2bc * *(float *)(iVar1 + 0xc));
        puVar6 = local_218;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar3 = local_218;
        puVar6 = local_1d8;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar3 = (undefined4 *)FUN_0081fe60(local_3bc,local_1d8,local_48);
        puVar6 = local_198;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar3 = local_198;
        puVar6 = local_48;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        local_2ac = FUN_00586ff0(local_48,*(undefined4 *)(local_29c + 0x18));
        *(float *)(local_2ac + 0x10) = local_2a0;
      }
      *(int *)(local_29c + 0xf0) = *(int *)(local_29c + 0xf0) + -1;
      *(float *)(local_29c + 0xc0) =
           *(float *)(local_29c + 0xc0) - *(float *)(*(int *)(local_29c + 0xe4) + 8);
    }
    *(undefined4 *)(local_29c + 0xf0) = 0;
LAB_00490338:
    if (*(int *)(local_29c + 0xf0) == 0) {
      *(undefined4 *)(local_29c + 0xe4) = *(undefined4 *)(local_29c + 0xe8);
      *(undefined4 *)(local_29c + 0xc) = *(undefined4 *)(*(int *)(local_29c + 0xe4) + 0x20);
      *(undefined4 *)(local_29c + 0xb0) = *(undefined4 *)(*(int *)(local_29c + 0xe4) + 0x28);
      if (*(float *)(*(int *)(local_29c + 0xe4) + 8) == 0.0) {
        *(int *)(local_29c + 0xb0) =
             *(int *)(local_29c + 0xb0) * *(int *)(*(int *)(local_29c + 0xe4) + 4);
      }
      *(undefined4 *)(local_29c + 0xc0) = 0;
    }
  }
  *(undefined4 *)(local_29c + 0xa8) = *(undefined4 *)(*(int *)(local_29c + 0xe4) + 0x24);
  FUN_0083e885();
  return;
}

