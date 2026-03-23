
void FUN_006a5000(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  float *pfVar4;
  float10 fVar5;
  undefined1 local_350 [12];
  undefined4 local_344;
  int local_340;
  int local_33c;
  int local_338;
  int local_334;
  int local_330;
  int local_32c;
  int local_328;
  void *local_324;
  undefined4 local_320;
  int local_31c;
  int local_318;
  void *local_314;
  float local_310;
  float local_30c;
  int *local_308;
  int *local_304;
  int local_300;
  float local_2fc;
  int local_2f8;
  int local_2f4;
  float local_2f0;
  int *local_2ec;
  int local_2e8;
  int local_2e4;
  float local_2e0;
  int local_2dc;
  int local_2d8;
  uint local_2d4;
  char local_2cd;
  int local_2cc;
  byte local_2c5;
  uint local_2c4;
  float local_2c0;
  undefined4 local_2bc;
  float local_2b8;
  undefined4 local_2b4;
  undefined4 local_2b0;
  undefined4 local_2ac;
  float local_2a8 [3];
  float local_29c [3];
  float local_290 [3];
  float local_284;
  float local_280;
  float local_27c;
  float local_278;
  float local_274;
  float local_270;
  int local_26c;
  char acStack_268 [236];
  char acStack_17c [4];
  float afStack_178 [89];
  char local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(int *)(param_2 + 0x28) != 0) {
    local_2cc = *(int *)(param_2 + 0x28);
    local_2d8 = *(int *)(param_2 + 0x14);
    if (local_2d8 == 0) {
      local_2d8 = 0;
    }
    else {
      local_304 = *(int **)(param_2 + 0x40);
      for (local_2f8 = 0; local_2f8 < *(int *)(param_2 + 0x14); local_2f8 = local_2f8 + 1) {
        local_318 = FUN_0069d590(param_2 + 0xc,local_2f8);
        local_300 = FUN_00462630(*(undefined4 *)(local_318 + 4));
        if (((local_300 == 0) || (iVar2 = FUN_0045bdf0(), iVar2 == 0)) ||
           (iVar2 = (**(code **)(*(int *)(local_300 + 0x18) + 4))(), iVar2 != *local_304)) {
          FUN_006a8b30(param_2,local_318,local_304);
        }
      }
      local_2d8 = *(int *)(param_2 + 0x14);
      if (local_2d8 != 0) {
        if (0x1e < local_2d8) {
          FUN_007d6a70("Squad Send: unitCount(%d)\n",local_2d8);
          local_2d8 = 0x1e;
        }
        for (local_2c4 = 0; (int)local_2c4 < local_2d8; local_2c4 = local_2c4 + 1) {
          local_308 = (int *)FUN_0069d590(param_2 + 0xc,local_2c4);
          local_328 = (int)(local_308[6] + (local_308[6] >> 0x1f & 0xfU)) >> 4;
          local_338 = (int)(local_308[5] + (local_308[5] >> 0x1f & 0xfU)) >> 4;
          local_2ec = (int *)*local_308;
          (&local_26c)[local_2c4 * 2] = (int)local_2ec;
          acStack_268[local_2c4 * 8] = '\x01';
          if ((local_328 == *(int *)(local_2cc + 0x40)) && (local_338 == *(int *)(local_2cc + 0x44))
             ) {
            iVar2 = (**(code **)local_2ec[6])();
            local_32c = *(int *)(iVar2 + 0x14);
            if (local_32c == 0x54544e4b) {
              cVar1 = (**(code **)(*local_2ec + 0x68))();
              if (cVar1 != '\0') {
                acStack_268[local_2c4 * 8] = '\0';
              }
            }
            else {
              acStack_268[local_2c4 * 8] = '\0';
            }
          }
        }
        if ((*(int *)(local_2cc + 4) == 2) || (*(int *)(local_2cc + 4) == 3)) {
          FUN_006a4cf0(local_2cc,&local_26c,local_2d8);
        }
        local_330 = *(int *)(local_2cc + 0x44) << 4;
        local_33c = *(int *)(local_2cc + 0x40) << 4;
        fVar5 = (float10)FUN_006a0980(local_330);
        local_2fc = (float)fVar5;
        fVar5 = (float10)FUN_006a09b0(local_33c);
        local_2f0 = (float)fVar5;
        local_2e0 = 16.0;
        local_2c5 = *(byte *)(DAT_009310a8 +
                             *(int *)(local_2cc + 0x40) * DAT_02c00ed8 + *(int *)(local_2cc + 0x44))
        ;
        if (local_2c5 == 0xff) {
          FUN_007d6a70("Squad_Send_Units: untested gridLayout at (%d, %d)\n",
                       *(undefined4 *)(local_2cc + 0x44),*(undefined4 *)(local_2cc + 0x40));
        }
        if (local_2c5 == 0) {
          sprintf(local_14,"bad_%d_%d",*(undefined4 *)(local_2cc + 0x44),
                  *(undefined4 *)(local_2cc + 0x40));
          local_314 = operator_new(0x18);
          if (local_314 == (void *)0x0) {
            local_31c = 0;
          }
          else {
            local_31c = FUN_00460390(local_14,2);
          }
          local_340 = local_31c;
          local_2e8 = local_31c;
          **(float **)(local_31c + 8) = local_2e0 * 0.25 + local_2fc;
          *(float *)(*(int *)(local_31c + 8) + 4) = local_2e0 * 0.25 + local_2f0;
          *(float *)(*(int *)(local_31c + 8) + 8) = local_2e0 * 0.75 + local_2fc;
          *(float *)(*(int *)(local_31c + 8) + 0xc) = local_2e0 * 0.75 + local_2f0;
          local_324 = operator_new(0x18);
          if (local_324 == (void *)0x0) {
            local_320 = 0;
          }
          else {
            local_320 = FUN_0046f190(local_2e8,*local_304,0,1,0xffffffff,0);
          }
          local_344 = local_320;
        }
        else {
          local_2b4 = DAT_02c00ab0;
          local_2b0 = DAT_02c00ab4;
          local_2ac = DAT_02c00ab8;
          local_2c4 = 0;
          while ((local_2c4 < 5 && ((1 << ((byte)local_2c4 & 0x1f) & (uint)local_2c5) == 0))) {
            local_2c4 = local_2c4 + 1;
          }
          if (local_2c4 != 5) {
            local_310 = *(float *)(&DAT_008ed9f8 + local_2c4 * 8) * local_2e0 + local_2fc;
            local_30c = *(float *)(&DAT_008ed9fc + local_2c4 * 8) * local_2e0 + local_2f0;
            for (local_2c4 = 0; local_2c4 < 5; local_2c4 = local_2c4 + 1) {
              afStack_178[local_2c4 * 3] =
                   *(float *)(&DAT_008ed9f8 + local_2c4 * 8) * local_2e0 + local_2fc;
              afStack_178[local_2c4 * 3 + 1] =
                   *(float *)(&DAT_008ed9fc + local_2c4 * 8) * local_2e0 + local_2f0;
              if ((1 << ((byte)local_2c4 & 0x1f) & (uint)local_2c5) == 0) {
                acStack_17c[local_2c4 * 0xc] = '\x01';
              }
              else {
                acStack_17c[local_2c4 * 0xc] = '\0';
                local_310 = afStack_178[local_2c4 * 3];
                local_2bc = 0;
                local_30c = afStack_178[local_2c4 * 3 + 1];
                acStack_17c[local_2c4 * 0xc + 1] = '\0';
                local_2c0 = local_310;
                local_2b8 = local_30c;
                for (local_2e4 = 0;
                    (acStack_17c[local_2c4 * 0xc + 1] == '\0' && (local_2e4 < local_2d8));
                    local_2e4 = local_2e4 + 1) {
                  local_2f4 = (&local_26c)[local_2e4 * 2];
                  iVar2 = (*(code *)**(undefined4 **)(local_2f4 + 0x18))();
                  if (*(int *)(iVar2 + 0x14) == 0x54544e4b) {
                    puVar3 = (undefined4 *)
                             (**(code **)(*(int *)(local_2f4 + 0x18) + 0xc))
                                       (local_2c0,local_2bc,local_2b8);
                    pfVar4 = (float *)FUN_004401a0(local_350,*puVar3,puVar3[1],puVar3[2]);
                    local_284 = *pfVar4;
                    local_280 = pfVar4[1];
                    local_27c = pfVar4[2];
                    local_278 = local_284;
                    local_274 = local_280;
                    local_270 = local_27c;
                    if (local_284 * local_284 + local_27c * local_27c <= 625.0) {
                      acStack_17c[local_2c4 * 0xc + 1] = '\x01';
                      acStack_268[local_2e4 * 8] = '\0';
                    }
                  }
                }
              }
            }
            local_2d4 = 0;
            for (local_2c4 = 0; local_2c4 < 5; local_2c4 = local_2c4 + 1) {
              if ((acStack_17c[local_2c4 * 0xc] == '\0') &&
                 (acStack_17c[local_2c4 * 0xc + 1] == '\0')) {
                local_2d4 = local_2c4;
                break;
              }
            }
            local_2cd = '\x01';
            for (local_2c4 = 0; (int)local_2c4 < local_2d8; local_2c4 = local_2c4 + 1) {
              if (acStack_268[local_2c4 * 8] != '\0') {
                local_2dc = (&local_26c)[local_2c4 * 2];
                iVar2 = (*(code *)**(undefined4 **)(local_2dc + 0x18))();
                local_334 = *(int *)(iVar2 + 0x14);
                if (local_334 == 0x54544e4b) {
                  while (((acStack_17c[local_2d4 * 0xc] != '\0' ||
                          (acStack_17c[local_2d4 * 0xc + 1] != '\0')) &&
                         ((acStack_17c[local_2d4 * 0xc] != '\0' || (local_2cd != '\0'))))) {
                    local_2d4 = local_2d4 + 1;
                    if (4 < local_2d4) {
                      local_2d4 = 0;
                      local_2cd = '\0';
                    }
                  }
                  acStack_17c[local_2d4 * 0xc + 1] = '\x01';
                  local_2a8[0] = afStack_178[local_2d4 * 3];
                  local_2a8[1] = 0.0;
                  local_2a8[2] = afStack_178[local_2d4 * 3 + 1];
                  local_2d4 = local_2d4 + 1;
                  if (4 < local_2d4) {
                    local_2d4 = 0;
                    local_2cd = '\0';
                  }
                  FUN_004dbe70(3,local_2a8,0,0);
                }
                else if ((*(int *)(local_2cc + 4) == 6) ||
                        ((*(int *)(local_2cc + 4) == 1 &&
                         ((iVar2 = (*(code *)**(undefined4 **)(local_2dc + 0x18))(),
                          *(int *)(iVar2 + 0x14) == 0x57494e47 ||
                          (iVar2 = (*(code *)**(undefined4 **)(local_2dc + 0x18))(),
                          *(int *)(iVar2 + 0x14) == 0x4d4c5952)))))) {
                  local_29c[0] = local_310;
                  local_29c[1] = 0.0;
                  local_29c[2] = local_30c;
                  FUN_004dbe70(0x16,local_29c,0,0);
                }
                else {
                  local_290[0] = local_310;
                  local_290[1] = 0.0;
                  local_290[2] = local_30c;
                  FUN_004dbe70(3,local_290,0,0);
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

