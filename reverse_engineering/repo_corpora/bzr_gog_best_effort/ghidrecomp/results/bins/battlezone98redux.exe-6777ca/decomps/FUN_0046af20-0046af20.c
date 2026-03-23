
void __fastcall FUN_0046af20(undefined4 param_1)

{
  float *pfVar1;
  int iVar2;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  int local_c;
  
  iVar2 = FUN_00460fc0("edge_path",param_1);
  if (iVar2 == 0) {
    DAT_0091738c = DAT_02cd912c + 30.0;
    DAT_00917394 = DAT_02cd9124 - 30.0;
    DAT_00917390 = DAT_02cd9130 + 30.0;
    DAT_00917388 = DAT_02cd9128 - 30.0;
  }
  else {
    local_14 = 1e+30;
    local_18 = -1e+30;
    local_1c = 1e+30;
    local_20 = -1e+30;
    for (local_c = 0; local_c < *(int *)(iVar2 + 4); local_c = local_c + 1) {
      pfVar1 = (float *)(*(int *)(iVar2 + 8) + local_c * 8);
      if (*pfVar1 <= local_14 && local_14 != *pfVar1) {
        local_14 = *pfVar1;
      }
      if (local_18 < *pfVar1) {
        local_18 = *pfVar1;
      }
      if (pfVar1[1] <= local_1c && local_1c != pfVar1[1]) {
        local_1c = pfVar1[1];
      }
      if (local_20 < pfVar1[1]) {
        local_20 = pfVar1[1];
      }
    }
    DAT_0091738c = local_14 + 0.0;
    DAT_00917394 = local_18 - 0.0;
    DAT_00917390 = local_1c + 0.0;
    DAT_00917388 = local_20 - 0.0;
  }
  FUN_0046a230();
  FUN_00469c70();
  FUN_004645f0();
  FUN_00591fa0();
  return;
}

