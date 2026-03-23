
void FUN_00688370(float *param_1,undefined4 param_2,float param_3,undefined4 param_4,float param_5,
                 undefined4 param_6)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  float *pfVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_24c [16];
  float local_23c;
  float local_238;
  float local_234;
  float local_230 [4];
  float local_220;
  float local_21c;
  float local_218;
  float local_214;
  float local_210;
  float local_20c;
  float local_208;
  undefined4 local_204;
  undefined4 local_1f8;
  undefined4 local_58 [10];
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  memset(local_230,0,0x1d8);
  local_1f8 = param_2;
  if (param_3 < 0.7853982) {
    param_3 = 0.7853982;
  }
  if (2.3561945 < param_3) {
    param_3 = 2.3561945;
  }
  if (param_5 < 100.0) {
    param_5 = 100.0;
  }
  if (1e+09 < param_5) {
    param_5 = 1e+09;
  }
  iVar1 = FUN_00688310(param_2);
  local_234 = (float)iVar1;
  iVar1 = FUN_00688330(param_2);
  local_23c = (float)iVar1;
  local_230[0] = local_234 * 0.5;
  local_230[1] = local_23c * 0.5;
  local_220 = param_5;
  local_20c = param_3;
  fVar6 = (float10)FUN_006882f0(param_3 * 0.5);
  local_238 = (float)fVar6;
  local_208 = local_238 * 0.75;
  local_204 = param_4;
  piVar2 = (int *)FUN_00688340(local_24c,param_2);
  local_18 = *piVar2;
  local_14 = piVar2[1];
  local_10 = piVar2[2];
  local_c = piVar2[3];
  local_21c = (float)local_18;
  local_218 = (float)local_14;
  local_214 = (float)local_10;
  local_210 = (float)local_c;
  FUN_006885c0(local_230,param_6);
  puVar3 = &DAT_008fe1e0;
  puVar5 = local_58;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  local_30 = 0;
  local_28 = 0x3ff0000000000000;
  local_20 = 0;
  FUN_00689090(local_230,local_58);
  pfVar4 = local_230;
  for (iVar1 = 0x76; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

