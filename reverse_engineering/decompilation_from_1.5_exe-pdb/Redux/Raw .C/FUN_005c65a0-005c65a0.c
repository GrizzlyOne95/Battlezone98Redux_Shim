
void FUN_005c65a0(float *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float fVar7;
  undefined8 uVar8;
  undefined1 local_130 [64];
  float local_f0;
  float local_ec;
  undefined8 local_e8;
  uint local_e0;
  undefined8 local_dc;
  float local_d4;
  undefined4 local_d0;
  float local_cc;
  undefined4 local_c8;
  float local_c4;
  int local_c0;
  int local_bc;
  undefined4 local_b8 [16];
  undefined4 local_78 [10];
  double local_50;
  double local_48;
  double local_40;
  undefined1 local_38 [12];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = size();
  iVar2 = (0x1000 - iVar2) * 3;
  iVar2 = FUN_0046b550(param_2,(int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2);
  fVar6 = (float10)FUN_00417910((float)iVar2);
  local_ec = (float)fVar6;
  local_c4 = local_ec * 10.0;
  local_c0 = iVar2;
  for (local_bc = 0; local_bc < iVar2; local_bc = local_bc + 1) {
    fVar6 = (float10)FUN_004464c0();
    local_f0 = (float)fVar6;
    local_20 = (double)(local_f0 * local_c4 + *param_1);
    local_18 = (double)param_1[1];
    fVar6 = (float10)FUN_004464c0();
    local_cc = (float)fVar6;
    fVar7 = local_cc * local_c4 + param_1[2];
    local_10 = (double)fVar7;
    cVar1 = FUN_0058fc90((float)local_20,fVar7);
    if (cVar1 == '\0') {
      if (0 < local_c0) {
        local_c0 = local_c0 + -1;
        local_bc = local_bc + -1;
      }
    }
    else {
      FUN_004451d0((undefined4)local_20,local_20._4_4_,(undefined4)local_18,local_18._4_4_,
                   (undefined4)local_10,local_10._4_4_,&local_d4,local_38);
      fVar6 = (float10)FUN_00492cb0(0x40c90fdb);
      uVar8 = FUN_008205a0((float)fVar6);
      local_2c = (undefined4)((ulonglong)uVar8 >> 0x20);
      local_24 = (undefined4)uVar8;
      local_28 = 0;
      local_e8 = uVar8;
      local_dc = uVar8;
      puVar3 = (undefined4 *)FUN_0081f920(local_130,local_38,&local_2c);
      puVar5 = local_b8;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar3 = local_b8;
      puVar5 = local_78;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      local_50 = local_20;
      local_48 = (double)local_d4;
      local_40 = local_10;
      iVar4 = rand();
      local_e0 = (uint)(iVar4 >> 8) % 3;
      local_c8 = *(undefined4 *)(&DAT_025cf890 + local_e0 * 4);
      local_d0 = FUN_004e1190(local_78,0,0,0xffffffff,0);
      iVar4 = FUN_00572a70();
      if (iVar4 != 0) {
        FUN_004b8460();
      }
    }
  }
  FUN_0083e885();
  return;
}

