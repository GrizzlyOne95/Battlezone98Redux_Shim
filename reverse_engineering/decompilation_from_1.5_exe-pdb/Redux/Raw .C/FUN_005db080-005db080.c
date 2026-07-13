
void __thiscall FUN_005db080(int *param_1,uint param_2,undefined4 *param_3)

{
  short sVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  float10 fVar7;
  undefined4 auStack_354 [6];
  undefined4 uStack_33c;
  undefined1 *puStack_338;
  float local_334;
  int local_330;
  int local_32c;
  int *local_328;
  undefined4 *local_324;
  undefined1 *local_320;
  undefined4 *local_31c;
  undefined4 *local_318;
  undefined1 local_30c [64];
  undefined1 local_2cc [64];
  undefined1 local_28c [64];
  undefined1 local_24c [12];
  undefined4 local_240 [3];
  undefined1 local_234 [12];
  undefined4 local_228 [3];
  undefined1 local_21c [12];
  undefined1 local_210 [12];
  undefined1 local_204 [12];
  undefined1 local_1f8 [12];
  undefined1 local_1ec [12];
  undefined1 local_1e0 [12];
  undefined4 local_1d4;
  float local_1d0;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  int local_1b8;
  int *local_1b4;
  int local_1b0;
  uint local_1ac;
  int local_1a8;
  int local_1a4;
  uint local_1a0;
  int local_19c;
  undefined4 local_198;
  undefined4 local_194;
  undefined2 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined2 local_184;
  undefined4 local_180 [16];
  undefined4 local_140 [16];
  undefined4 local_100 [16];
  undefined4 local_c0 [10];
  undefined8 local_98;
  undefined8 local_90;
  undefined8 local_88;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined2 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined2 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1b4 = param_1;
  if (param_2 == 0) {
    local_1c4 = *(float *)(param_1[3] + 0xd4);
    local_320 = (undefined1 *)*param_3;
    local_31c = (undefined4 *)param_3[1];
    local_318 = (undefined4 *)param_3[2];
    local_1c8 = local_1c4 * -2.0;
    local_324 = param_3;
    local_328 = param_1 + 0xc;
    local_32c = 0x5db101;
    fVar7 = (float10)FUN_004428b0();
    local_1d0 = (float)fVar7;
    local_324 = (undefined4 *)(local_1c8 * local_1d0);
    local_330 = local_1b4[0xc];
    local_32c = local_1b4[0xd];
    local_328 = (int *)local_1b4[0xe];
    local_334 = local_1c4;
    puStack_338 = local_210;
    uStack_33c = 0x5db158;
    piVar2 = (int *)FUN_00459570();
    local_50 = *piVar2;
    local_4c = piVar2[1];
    local_48 = piVar2[2];
    local_1b4[0xc] = local_50;
    local_1b4[0xd] = local_4c;
    local_1b4[0xe] = local_48;
    local_320 = (undefined1 *)local_1b4[0xc];
    local_31c = (undefined4 *)local_1b4[0xd];
    local_318 = (undefined4 *)local_1b4[0xe];
    local_324 = (undefined4 *)0x5db1a9;
    fVar7 = (float10)FUN_0045c420();
    local_1b4[8] = (int)(float)fVar7;
    if ((float)local_1b4[8] <= 0.0) {
      local_1c0 = 1e+30;
    }
    else {
      local_1c0 = 1.0 / (float)local_1b4[8];
    }
    local_1b4[9] = (int)local_1c0;
    if (5.0 < (float)local_1b4[8] || (float)local_1b4[8] == 5.0) {
      local_318 = (undefined4 *)0x0;
      local_31c = (undefined4 *)0x0;
      local_320 = (undefined1 *)local_1b4[5];
      local_324 = (undefined4 *)(local_1b4[3] + 0xd8);
      local_328 = (undefined4 *)0x5db42a;
      FUN_0043aa30();
      local_318 = (undefined4 *)0x5db432;
      iVar4 = FUN_00572a70();
      if (iVar4 != 0) {
        iVar4 = local_1b4[0x1f];
        local_318 = (undefined4 *)0x5db449;
        sVar1 = FUN_00572d90();
        if ((short)iVar4 == sVar1) {
          local_318 = (undefined4 *)0x0;
          local_31c = (undefined4 *)0x5db475;
          (**(code **)(*local_1b4 + 0x10))();
          puVar3 = (undefined4 *)(local_1b4[5] + 0x20);
          puVar5 = auStack_354;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = (undefined4 *)FUN_00625c50(local_1e0);
          local_320 = (undefined1 *)*puVar3;
          local_31c = (undefined4 *)puVar3[1];
          local_184 = *(undefined2 *)(puVar3 + 2);
          local_318 = (undefined4 *)CONCAT22(local_318._2_2_,local_184);
          local_324 = (undefined4 *)local_2cc;
          local_328 = (int *)0x5db4f9;
          local_18c = local_320;
          local_188 = local_31c;
          local_20 = local_320;
          local_1c = local_31c;
          local_18 = local_184;
          puVar3 = (undefined4 *)FUN_00625a30();
          puVar5 = local_140;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = local_140;
          puVar5 = (undefined4 *)(local_1b4[5] + 0x20);
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          local_318 = (undefined4 *)(local_1b4[5] + 0x20);
          local_31c = (undefined4 *)local_1f8;
          local_320 = (undefined1 *)0x5db53d;
          piVar2 = (int *)FUN_004560b0();
          local_320 = (undefined1 *)*piVar2;
          local_31c = (undefined4 *)piVar2[1];
          local_318 = (undefined4 *)piVar2[2];
          local_324 = (undefined4 *)local_1b4[8];
          local_328 = local_228;
          local_32c = 0x5db596;
          local_1b0 = (int)local_320;
          local_1ac = (uint)local_31c;
          local_1a8 = (int)local_318;
          piVar2 = (int *)FUN_004462d0();
          local_2c = *piVar2;
          local_28 = piVar2[1];
          local_24 = piVar2[2];
          local_1b4[0xc] = local_2c;
          local_1b4[0xd] = local_28;
          local_1b4[0xe] = local_24;
          piVar2 = (int *)(local_1b4[5] + 0x20);
          piVar6 = local_1b4 + 0x22;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *piVar6 = *piVar2;
            piVar2 = piVar2 + 1;
            piVar6 = piVar6 + 1;
          }
          local_318 = (undefined4 *)0x5db5e8;
          fVar7 = (float10)FUN_00822d80();
          local_1b4[0x32] = (int)(float)fVar7;
          local_1b4[0x20] = 1;
        }
      }
    }
    else {
      local_1b8 = *(int *)(local_1b4[3] + 0xd0);
      if (local_1b8 == 0) {
        local_318 = param_3;
        local_31c = (undefined4 *)param_2;
        local_320 = (undefined1 *)0x5db402;
        FUN_004e7e10();
      }
      else {
        local_318 = (undefined4 *)(local_1b4[5] + 0x20);
        local_31c = (undefined4 *)local_234;
        local_320 = (undefined1 *)0x5db25c;
        puVar3 = (undefined4 *)FUN_004560b0();
        local_80 = *puVar3;
        local_7c = puVar3[1];
        local_78 = puVar3[2];
        local_318 = (undefined4 *)0x0;
        local_31c = (undefined4 *)0x3f800000;
        local_320 = (undefined1 *)0x0;
        local_324 = (undefined4 *)local_204;
        local_328 = (int *)0x5db2b8;
        local_68 = local_80;
        local_64 = local_7c;
        local_60 = local_78;
        puVar3 = (undefined4 *)FUN_00440000();
        local_74 = *puVar3;
        local_70 = puVar3[1];
        local_6c = puVar3[2];
        local_318 = &local_80;
        local_31c = &local_74;
        local_320 = local_28c;
        local_324 = (undefined4 *)0x5db2f2;
        local_44 = local_74;
        local_40 = local_70;
        local_3c = local_6c;
        puVar3 = (undefined4 *)FUN_0081f920();
        puVar5 = local_180;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar5 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar3 = local_180;
        puVar5 = local_c0;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar5 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar5 = puVar5 + 1;
        }
        local_98 = *(undefined8 *)(local_1b4[5] + 0x48);
        local_90 = *(undefined8 *)(local_1b4[5] + 0x50);
        local_88 = *(undefined8 *)(local_1b4[5] + 0x58);
        local_318 = (undefined4 *)0x0;
        local_31c = (undefined4 *)0xffffffff;
        local_320 = (undefined1 *)0x0;
        local_324 = (undefined4 *)local_1b4[5];
        local_328 = (int *)0x5db36e;
        local_324 = (undefined4 *)FUN_0047e9a0();
        local_328 = local_c0;
        local_32c = 0x5db384;
        local_1d4 = FUN_004e1190();
        if (*(int *)(local_1b8 + 0x14) == 0x53424d42) {
          local_318 = (undefined4 *)(uint)((byte)(*(ushort *)(local_1b4 + 0x1a) >> 5) & 1);
          local_31c = (undefined4 *)(uint)((byte)(*(ushort *)(local_1b4 + 0x1a) >> 4) & 1);
          local_320 = (undefined1 *)0x5db3d0;
          FUN_005dacc0();
        }
        *(uint *)(local_1b4[5] + 0x14) = *(uint *)(local_1b4[5] + 0x14) | 0x200;
      }
    }
  }
  else {
    local_318 = (undefined4 *)0x5db61a;
    local_318 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0x30))();
    local_31c = (undefined4 *)0x5db620;
    iVar4 = FUN_00477d70();
    if (iVar4 == 0) {
      local_318 = param_3;
      local_31c = (undefined4 *)param_2;
      local_320 = (undefined1 *)0x5db99b;
      FUN_004e7e10();
    }
    else {
      local_320 = (undefined1 *)*param_3;
      local_31c = (undefined4 *)param_3[1];
      local_318 = (undefined4 *)param_3[2];
      local_324 = param_3;
      local_328 = local_1b4 + 0xc;
      local_32c = 0x5db656;
      fVar7 = (float10)FUN_004428b0();
      local_1cc = (float)fVar7;
      local_324 = (undefined4 *)-local_1cc;
      local_330 = local_1b4[0xc];
      local_32c = local_1b4[0xd];
      local_328 = (int *)local_1b4[0xe];
      local_334 = 0.5;
      puStack_338 = local_24c;
      uStack_33c = 0x5db6ac;
      piVar2 = (int *)FUN_00459570();
      local_38 = *piVar2;
      local_34 = piVar2[1];
      local_30 = piVar2[2];
      local_1b4[0xc] = local_38;
      local_1b4[0xd] = local_34;
      local_1b4[0xe] = local_30;
      local_320 = (undefined1 *)local_1b4[0xc];
      local_31c = (undefined4 *)local_1b4[0xd];
      local_318 = (undefined4 *)local_1b4[0xe];
      local_324 = (undefined4 *)0x5db6fd;
      fVar7 = (float10)FUN_0045c420();
      local_1b4[8] = (int)(float)fVar7;
      if ((float)local_1b4[8] <= 0.0) {
        local_1bc = 1e+30;
      }
      else {
        local_1bc = 1.0 / (float)local_1b4[8];
      }
      local_1b4[9] = (int)local_1bc;
      if (1.0 < (float)local_1b4[8] || (float)local_1b4[8] == 1.0) {
        local_318 = (undefined4 *)0x0;
        local_31c = (undefined4 *)0x0;
        local_320 = (undefined1 *)local_1b4[5];
        local_324 = (undefined4 *)(local_1b4[3] + 0xd8);
        local_328 = (undefined4 *)0x5db7ac;
        FUN_0043aa30();
        local_318 = (undefined4 *)0x5db7b4;
        iVar4 = FUN_00572a70();
        if (iVar4 != 0) {
          iVar4 = local_1b4[0x1f];
          local_318 = (undefined4 *)0x5db7cb;
          sVar1 = FUN_00572d90();
          if ((short)iVar4 == sVar1) {
            local_318 = (undefined4 *)0x0;
            local_31c = (undefined4 *)0x5db7f7;
            (**(code **)(*local_1b4 + 0x10))();
            puVar3 = (undefined4 *)(local_1b4[5] + 0x20);
            puVar5 = auStack_354;
            for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar5 = *puVar3;
              puVar3 = puVar3 + 1;
              puVar5 = puVar5 + 1;
            }
            puVar3 = (undefined4 *)FUN_00625c50(local_1ec);
            local_320 = (undefined1 *)*puVar3;
            local_31c = (undefined4 *)puVar3[1];
            local_190 = *(undefined2 *)(puVar3 + 2);
            local_318 = (undefined4 *)CONCAT22(local_318._2_2_,local_190);
            local_324 = (undefined4 *)local_30c;
            local_328 = (int *)0x5db87b;
            local_198 = local_320;
            local_194 = local_31c;
            local_14 = local_320;
            local_10 = local_31c;
            local_c = local_190;
            puVar3 = (undefined4 *)FUN_00625a30();
            puVar5 = local_100;
            for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar5 = *puVar3;
              puVar3 = puVar3 + 1;
              puVar5 = puVar5 + 1;
            }
            puVar3 = local_100;
            puVar5 = (undefined4 *)(local_1b4[5] + 0x20);
            for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar5 = *puVar3;
              puVar3 = puVar3 + 1;
              puVar5 = puVar5 + 1;
            }
            local_318 = (undefined4 *)(local_1b4[5] + 0x20);
            local_31c = (undefined4 *)local_21c;
            local_320 = (undefined1 *)0x5db8bf;
            piVar2 = (int *)FUN_004560b0();
            local_320 = (undefined1 *)*piVar2;
            local_31c = (undefined4 *)piVar2[1];
            local_318 = (undefined4 *)piVar2[2];
            local_324 = (undefined4 *)local_1b4[8];
            local_328 = local_240;
            local_32c = 0x5db918;
            local_1a4 = (int)local_320;
            local_1a0 = (uint)local_31c;
            local_19c = (int)local_318;
            piVar2 = (int *)FUN_004462d0();
            local_5c = *piVar2;
            local_58 = piVar2[1];
            local_54 = piVar2[2];
            local_1b4[0xc] = local_5c;
            local_1b4[0xd] = local_58;
            local_1b4[0xe] = local_54;
            piVar2 = (int *)(local_1b4[5] + 0x20);
            piVar6 = local_1b4 + 0x22;
            for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
              *piVar6 = *piVar2;
              piVar2 = piVar2 + 1;
              piVar6 = piVar6 + 1;
            }
            local_318 = (undefined4 *)0x5db96a;
            fVar7 = (float10)FUN_00822d80();
            local_1b4[0x32] = (int)(float)fVar7;
            local_1b4[0x20] = 1;
          }
        }
      }
      else {
        local_318 = param_3;
        local_31c = (undefined4 *)param_2;
        local_320 = (undefined1 *)0x5db784;
        FUN_004e7e10();
      }
    }
  }
  FUN_0083e885();
  return;
}

