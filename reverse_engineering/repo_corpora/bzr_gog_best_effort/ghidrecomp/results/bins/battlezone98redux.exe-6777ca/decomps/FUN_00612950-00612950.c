
void FUN_00612950(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  float *pfVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined1 local_2bc [64];
  undefined1 local_27c [64];
  undefined1 local_23c [64];
  undefined1 local_1fc [24];
  undefined1 local_1e4 [12];
  undefined1 local_1d8 [12];
  undefined1 local_1cc [4];
  undefined1 local_1c8 [4];
  undefined4 local_1c4;
  undefined1 local_1c0 [4];
  float local_1bc;
  int local_1b8;
  float local_1b4;
  int local_1b0;
  int local_1ac;
  undefined4 local_1a8 [16];
  undefined4 local_168 [16];
  undefined4 local_128 [16];
  undefined4 local_e8 [16];
  undefined4 local_a8 [16];
  undefined1 local_68 [12];
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
  cVar1 = FUN_004b9830();
  if (cVar1 == '\0') {
    cVar1 = (**(code **)(**(int **)(local_1ac + 0x240) + 4))();
    if (cVar1 == '\0') {
      *(undefined4 *)(local_1ac + 0x238) = 0;
    }
    else {
      local_1b8 = 0;
      local_1b4 = *(float *)(*(int *)(local_1ac + 0xf8) + 0x168) *
                  *(float *)(*(int *)(local_1ac + 0xf8) + 0x168);
      FID_conflict_begin(local_1c0);
LAB_006129f9:
      uVar2 = FID_conflict_end(local_1c8);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 != '\0') {
        FUN_0046b260(local_1cc,0);
        piVar3 = (int *)FUN_00421ec0();
        local_1b0 = *piVar3;
        cVar1 = FUN_004db510(local_1b0);
        if (cVar1 == '\0') {
          puVar4 = (undefined4 *)
                   (**(code **)(*(int *)(local_1b0 + 0x18) + 0xc))
                             (*(undefined4 *)(local_1ac + 0x108),*(undefined4 *)(local_1ac + 0x10c),
                              *(undefined4 *)(local_1ac + 0x110));
          pfVar5 = (float *)FUN_004401a0(local_1e4,*puVar4,puVar4[1],puVar4[2]);
          local_44 = *pfVar5;
          local_40 = pfVar5[1];
          local_3c = pfVar5[2];
          local_1bc = local_44 * local_44 + local_40 * local_40 +
                      local_3c * local_3c * *(float *)(*(int *)(local_1ac + 0xf8) + 0x16c);
          local_20 = local_44;
          local_1c = local_40;
          local_18 = local_3c;
          if (local_1bc < local_1b4) {
            puVar4 = (undefined4 *)
                     (**(code **)(**(int **)(local_1ac + 0x240) + 0x2c))
                               (local_68,local_1b0,*(undefined4 *)(local_1ac + 0x108),
                                *(undefined4 *)(local_1ac + 0x10c),
                                *(undefined4 *)(local_1ac + 0x110));
            puVar4 = (undefined4 *)FUN_004401a0(local_1d8,*puVar4,puVar4[1],puVar4[2]);
            local_50 = *puVar4;
            local_4c = puVar4[1];
            local_48 = puVar4[2];
            local_14 = local_50;
            local_10 = local_4c;
            local_c = local_48;
            if (*(char *)(*(int *)(local_1ac + 0xf8) + 0x174) != '\0') {
              local_1c4 = 0x3f800000;
              puVar4 = (undefined4 *)
                       FUN_0049c4f0(local_1fc,*(undefined4 *)(local_1ac + 0x108),
                                    *(undefined4 *)(local_1ac + 0x10c),
                                    *(undefined4 *)(local_1ac + 0x110));
              local_38 = *puVar4;
              local_34 = puVar4[1];
              local_30 = puVar4[2];
              local_2c = puVar4[3];
              local_28 = puVar4[4];
              local_24 = puVar4[5];
              iVar6 = FUN_00784620(local_38,local_34,local_30,local_2c,local_28,local_24,local_14,
                                   local_10,local_c,&local_1c4,0);
              if (iVar6 != 0) goto LAB_006129f9;
            }
            local_1b4 = local_1bc;
            local_5c = local_14;
            local_58 = local_10;
            local_54 = local_c;
            local_1b8 = local_1b0;
          }
        }
        goto LAB_006129f9;
      }
      FUN_0049f450(local_1b8);
      if (local_1b8 != 0) {
        puVar4 = (undefined4 *)FUN_0081fa10(local_23c,local_1ac + 0x108,&local_5c);
        puVar7 = local_a8;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar7 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar7 = puVar7 + 1;
        }
        puVar4 = local_a8;
        puVar7 = local_168;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar7 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar7 = puVar7 + 1;
        }
        puVar4 = (undefined4 *)FUN_008203f0(local_27c,*(int *)(local_1ac + 0xf4) + 0x20);
        puVar7 = local_128;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar7 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar7 = puVar7 + 1;
        }
        puVar4 = local_128;
        puVar7 = local_1a8;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar7 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar7 = puVar7 + 1;
        }
        puVar4 = (undefined4 *)FUN_0081fe60(local_2bc,local_168,local_1a8);
        puVar7 = local_e8;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar7 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar7 = puVar7 + 1;
        }
        puVar4 = local_e8;
        puVar7 = (undefined4 *)(*(int *)(*(int *)(local_1ac + 0x240) + 0x10) + 0x20);
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar7 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar7 = puVar7 + 1;
        }
        if ((*(char *)(*(int *)(local_1ac + 0xf8) + 0x174) == '\0') ||
           (cVar1 = FUN_00462b60(local_1ac,local_1b4,0x3e99999a,0x3f800000), cVar1 == '\0')) {
          (**(code **)(**(int **)(local_1ac + 0x240) + 8))();
        }
      }
    }
  }
  FUN_00511460(param_1);
  FUN_0083e885();
  return;
}

