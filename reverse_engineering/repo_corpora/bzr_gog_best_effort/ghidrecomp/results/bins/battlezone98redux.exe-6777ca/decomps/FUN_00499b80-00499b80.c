
void __thiscall
FUN_00499b80(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,int param_4,
            undefined4 param_5)

{
  undefined8 uVar1;
  float local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined8 local_b8;
  int local_b0;
  int local_ac;
  undefined4 auStack_a8 [16];
  undefined4 local_68 [4];
  undefined4 local_58;
  undefined4 local_54;
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
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_68[0] = *param_2;
  local_68[1] = param_2[1];
  local_68[2] = param_2[2];
  local_68[3] = *param_2;
  local_58 = param_2[1];
  local_54 = param_3[2];
  local_50 = *param_2;
  local_4c = param_3[1];
  local_48 = param_2[2];
  local_44 = *param_2;
  local_40 = param_3[1];
  local_3c = param_3[2];
  local_38 = *param_3;
  local_34 = param_2[1];
  local_30 = param_2[2];
  local_2c = *param_3;
  local_28 = param_2[1];
  local_24 = param_3[2];
  local_20 = *param_3;
  local_1c = param_3[1];
  local_18 = param_2[2];
  local_14 = *param_3;
  local_10 = param_3[1];
  local_c = param_3[2];
  if (param_4 != 0) {
    FUN_00820180(local_68,local_68,8,param_4,param_1);
  }
  uVar1 = CONCAT44(local_b8._4_4_,(undefined4)local_b8);
  for (local_b0 = 0; local_b8 = uVar1, local_b0 < 8; local_b0 = local_b0 + 1) {
    uVar1 = FUN_00497780(local_68 + local_b0 * 3,DAT_00917594,&local_c4);
    auStack_a8[local_b0 * 2] = (int)uVar1;
    auStack_a8[local_b0 * 2 + 1] = (int)((ulonglong)uVar1 >> 0x20);
    if (local_c4 < 0.0) goto LAB_00499e2b;
  }
  for (local_ac = 0; uVar1 = local_b8, local_ac < 0xc; local_ac = local_ac + 1) {
    local_c0 = auStack_a8[*(int *)(&DAT_00877258 + local_ac * 8) * 2];
    local_bc = auStack_a8[*(int *)(&DAT_00877258 + local_ac * 8) * 2 + 1];
    FUN_0068af40(DAT_00917580,local_c0,local_bc,
                 auStack_a8[*(int *)(&DAT_0087725c + local_ac * 8) * 2],
                 auStack_a8[*(int *)(&DAT_0087725c + local_ac * 8) * 2 + 1],param_5,0);
  }
LAB_00499e2b:
  local_b8 = uVar1;
  FUN_0083e885();
  return;
}

