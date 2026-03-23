
void __thiscall FUN_0047e250(int param_1,int param_2,undefined4 *param_3)

{
  short sVar1;
  short sVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined4 auStack_244 [6];
  undefined4 uStack_22c;
  undefined1 *puStack_228;
  float local_224;
  undefined4 local_220;
  undefined4 local_21c;
  undefined1 *local_218;
  undefined4 *local_214;
  undefined4 local_210;
  undefined1 *local_20c;
  undefined4 *local_208;
  undefined1 local_1fc [64];
  undefined1 local_1bc [64];
  undefined1 local_17c [12];
  undefined1 local_170 [12];
  undefined1 local_164 [12];
  undefined1 local_158 [12];
  undefined1 local_14c [12];
  undefined1 local_140 [12];
  undefined1 local_134 [12];
  undefined1 local_128 [12];
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  int local_104;
  undefined4 local_100;
  int local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  int local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined2 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined2 local_d4;
  undefined4 local_d0 [16];
  undefined4 local_90 [16];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined2 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined2 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_104 = param_1;
  if (param_2 == 0) {
    local_108 = *(float *)(*(int *)(param_1 + 0xc) + 0xd0);
    local_210 = *param_3;
    local_20c = (undefined1 *)param_3[1];
    local_208 = (undefined4 *)param_3[2];
    local_118 = local_108 * -2.0;
    local_214 = param_3;
    local_218 = (undefined1 *)(param_1 + 0x30);
    local_21c = 0x47e2d1;
    fVar6 = (float10)FUN_004428b0();
    local_11c = (float)fVar6;
    local_214 = (undefined4 *)(local_118 * local_11c);
    local_220 = *(undefined4 *)(local_104 + 0x30);
    local_21c = *(undefined4 *)(local_104 + 0x34);
    local_218 = *(undefined1 **)(local_104 + 0x38);
    local_224 = local_108;
    puStack_228 = local_140;
    uStack_22c = 0x47e328;
    puVar3 = (undefined4 *)FUN_00459570();
    local_2c = *puVar3;
    local_28 = puVar3[1];
    local_24 = puVar3[2];
    *(undefined4 *)(local_104 + 0x30) = local_2c;
    *(undefined4 *)(local_104 + 0x34) = local_28;
    *(undefined4 *)(local_104 + 0x38) = local_24;
    local_210 = *(undefined4 *)(local_104 + 0x30);
    local_20c = *(undefined1 **)(local_104 + 0x34);
    local_208 = *(undefined4 **)(local_104 + 0x38);
    local_214 = (undefined4 *)0x47e379;
    fVar6 = (float10)FUN_0045c420();
    *(float *)(local_104 + 0x20) = (float)fVar6;
    if (*(float *)(local_104 + 0x20) <= 0.0) {
      local_110 = 1e+30;
    }
    else {
      local_110 = 1.0 / *(float *)(local_104 + 0x20);
    }
    *(float *)(local_104 + 0x24) = local_110;
    if (5.0 < *(float *)(local_104 + 0x20) || *(float *)(local_104 + 0x20) == 5.0) {
      local_208 = (undefined4 *)0x0;
      local_20c = (undefined1 *)0x0;
      local_210 = *(undefined4 *)(local_104 + 0x14);
      local_214 = (undefined4 *)(*(int *)(local_104 + 0xc) + 0xd4);
      local_218 = (undefined1 *)0x47e42d;
      FUN_0043aa30();
    }
    else {
      *(uint *)(*(int *)(local_104 + 0x14) + 0x14) =
           *(uint *)(*(int *)(local_104 + 0x14) + 0x14) & 0xfffffff7;
    }
    local_208 = (undefined4 *)0x47e435;
    iVar4 = FUN_00572a70();
    if (iVar4 != 0) {
      sVar1 = *(short *)(local_104 + 0x7c);
      local_208 = (undefined4 *)0x47e44c;
      sVar2 = FUN_00572d90();
      if (sVar1 == sVar2) {
        local_208 = (undefined4 *)0x47e462;
        FUN_005856a0();
        puVar3 = (undefined4 *)(*(int *)(local_104 + 0x14) + 0x20);
        puVar5 = auStack_244;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar5 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar3 = (undefined4 *)FUN_00625c50(local_128);
        local_210 = *puVar3;
        local_20c = (undefined1 *)puVar3[1];
        local_e0 = *(undefined2 *)(puVar3 + 2);
        local_208 = (undefined4 *)CONCAT22(local_208._2_2_,local_e0);
        local_214 = (undefined4 *)local_1bc;
        local_218 = (undefined1 *)0x47e4e6;
        local_e8 = local_210;
        local_e4 = local_20c;
        local_20 = local_210;
        local_1c = local_20c;
        local_18 = local_e0;
        puVar3 = (undefined4 *)FUN_00625a30();
        puVar5 = local_d0;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar5 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar3 = local_d0;
        puVar5 = (undefined4 *)(*(int *)(local_104 + 0x14) + 0x20);
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar5 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar5 = puVar5 + 1;
        }
        local_208 = (undefined4 *)(*(int *)(local_104 + 0x14) + 0x20);
        local_20c = local_14c;
        local_210 = 0x47e52a;
        puVar3 = (undefined4 *)FUN_004560b0();
        local_210 = *puVar3;
        local_20c = (undefined1 *)puVar3[1];
        local_208 = (undefined4 *)puVar3[2];
        local_214 = *(undefined4 **)(local_104 + 0x20);
        local_218 = local_164;
        local_21c = 0x47e583;
        local_f4 = local_210;
        local_f0 = (int)local_20c;
        local_ec = local_208;
        puVar3 = (undefined4 *)FUN_004462d0();
        local_38 = *puVar3;
        local_34 = puVar3[1];
        local_30 = puVar3[2];
        *(undefined4 *)(local_104 + 0x30) = local_38;
        *(undefined4 *)(local_104 + 0x34) = local_34;
        *(undefined4 *)(local_104 + 0x38) = local_30;
        puVar3 = (undefined4 *)(*(int *)(local_104 + 0x14) + 0x20);
        puVar5 = (undefined4 *)(local_104 + 0x88);
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar5 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar5 = puVar5 + 1;
        }
        local_208 = (undefined4 *)0x47e5d5;
        fVar6 = (float10)FUN_00822d80();
        *(float *)(local_104 + 200) = (float)fVar6;
        *(undefined4 *)(local_104 + 0x80) = 1;
      }
    }
  }
  else {
    local_208 = (undefined4 *)0x47e607;
    local_208 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0x30))();
    local_20c = (undefined1 *)0x47e60d;
    iVar4 = FUN_00477d70();
    if (iVar4 == 0) {
      local_208 = param_3;
      local_20c = (undefined1 *)param_2;
      local_210 = 0x47e977;
      FUN_004e7e10();
    }
    else {
      local_210 = *param_3;
      local_20c = (undefined1 *)param_3[1];
      local_208 = (undefined4 *)param_3[2];
      local_214 = param_3;
      local_218 = (undefined1 *)(local_104 + 0x30);
      local_21c = 0x47e643;
      fVar6 = (float10)FUN_004428b0();
      local_114 = (float)fVar6;
      local_214 = (undefined4 *)-local_114;
      local_220 = *(undefined4 *)(local_104 + 0x30);
      local_21c = *(undefined4 *)(local_104 + 0x34);
      local_218 = *(undefined1 **)(local_104 + 0x38);
      local_224 = 0.5;
      puStack_228 = local_158;
      uStack_22c = 0x47e699;
      puVar3 = (undefined4 *)FUN_00459570();
      local_50 = *puVar3;
      local_4c = puVar3[1];
      local_48 = puVar3[2];
      *(undefined4 *)(local_104 + 0x30) = local_50;
      *(undefined4 *)(local_104 + 0x34) = local_4c;
      *(undefined4 *)(local_104 + 0x38) = local_48;
      local_210 = *(undefined4 *)(local_104 + 0x30);
      local_20c = *(undefined1 **)(local_104 + 0x34);
      local_208 = *(undefined4 **)(local_104 + 0x38);
      local_214 = (undefined4 *)0x47e6ea;
      fVar6 = (float10)FUN_0045c420();
      *(float *)(local_104 + 0x20) = (float)fVar6;
      if (*(float *)(local_104 + 0x20) <= 0.0) {
        local_10c = 1e+30;
      }
      else {
        local_10c = 1.0 / *(float *)(local_104 + 0x20);
      }
      *(float *)(local_104 + 0x24) = local_10c;
      if (1.0 < *(float *)(local_104 + 0x20) || *(float *)(local_104 + 0x20) == 1.0) {
        local_208 = (undefined4 *)0x0;
        local_20c = (undefined1 *)0x0;
        local_210 = *(undefined4 *)(local_104 + 0x14);
        local_214 = (undefined4 *)(*(int *)(local_104 + 0xc) + 0xd4);
        local_218 = (undefined1 *)0x47e79e;
        FUN_0043aa30();
      }
      else {
        *(uint *)(*(int *)(local_104 + 0x14) + 0x14) =
             *(uint *)(*(int *)(local_104 + 0x14) + 0x14) & 0xfffffff7;
      }
      local_208 = (undefined4 *)0x47e7a6;
      iVar4 = FUN_00572a70();
      if (iVar4 != 0) {
        sVar1 = *(short *)(local_104 + 0x7c);
        local_208 = (undefined4 *)0x47e7bd;
        sVar2 = FUN_00572d90();
        if (sVar1 == sVar2) {
          local_208 = (undefined4 *)0x47e7d3;
          FUN_005856a0();
          puVar3 = (undefined4 *)(*(int *)(local_104 + 0x14) + 0x20);
          puVar5 = auStack_244;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = (undefined4 *)FUN_00625c50(local_134);
          local_210 = *puVar3;
          local_20c = (undefined1 *)puVar3[1];
          local_d4 = *(undefined2 *)(puVar3 + 2);
          local_208 = (undefined4 *)CONCAT22(local_208._2_2_,local_d4);
          local_214 = (undefined4 *)local_1fc;
          local_218 = (undefined1 *)0x47e857;
          local_dc = local_210;
          local_d8 = local_20c;
          local_14 = local_210;
          local_10 = local_20c;
          local_c = local_d4;
          puVar3 = (undefined4 *)FUN_00625a30();
          puVar5 = local_90;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = local_90;
          puVar5 = (undefined4 *)(*(int *)(local_104 + 0x14) + 0x20);
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          local_208 = (undefined4 *)(*(int *)(local_104 + 0x14) + 0x20);
          local_20c = local_17c;
          local_210 = 0x47e89b;
          puVar3 = (undefined4 *)FUN_004560b0();
          local_210 = *puVar3;
          local_20c = (undefined1 *)puVar3[1];
          local_208 = (undefined4 *)puVar3[2];
          local_214 = *(undefined4 **)(local_104 + 0x20);
          local_218 = local_170;
          local_21c = 0x47e8f4;
          local_100 = local_210;
          local_fc = (int)local_20c;
          local_f8 = local_208;
          puVar3 = (undefined4 *)FUN_004462d0();
          local_44 = *puVar3;
          local_40 = puVar3[1];
          local_3c = puVar3[2];
          *(undefined4 *)(local_104 + 0x30) = local_44;
          *(undefined4 *)(local_104 + 0x34) = local_40;
          *(undefined4 *)(local_104 + 0x38) = local_3c;
          puVar3 = (undefined4 *)(*(int *)(local_104 + 0x14) + 0x20);
          puVar5 = (undefined4 *)(local_104 + 0x88);
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          local_208 = (undefined4 *)0x47e946;
          fVar6 = (float10)FUN_00822d80();
          *(float *)(local_104 + 200) = (float)fVar6;
          *(undefined4 *)(local_104 + 0x80) = 1;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

