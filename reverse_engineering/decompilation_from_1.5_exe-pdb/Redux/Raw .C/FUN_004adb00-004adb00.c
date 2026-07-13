
void __thiscall FUN_004adb00(int param_1,undefined4 param_2,undefined4 param_3)

{
  float *pfVar1;
  undefined4 uVar2;
  int iVar3;
  float *pfVar4;
  undefined1 local_d0 [64];
  int *local_90;
  int local_8c;
  float local_88 [16];
  float local_48 [4];
  float local_38;
  float local_34;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_8c = param_1;
  pfVar1 = (float *)FUN_0062e070(local_d0,*(undefined4 *)(*(int *)(param_1 + 0x230) + 0xfc),0);
  pfVar4 = local_88;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar4 = pfVar4 + 1;
  }
  pfVar1 = local_88;
  pfVar4 = local_48;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar4 = pfVar4 + 1;
  }
  local_20 = (double)(*(float *)(*(int *)(local_8c + 0xf0) + 0x14) * local_48[3]) + local_20;
  local_18 = (double)(*(float *)(*(int *)(local_8c + 0xf0) + 0x14) * local_38) + local_18;
  local_10 = (double)(*(float *)(*(int *)(local_8c + 0xf0) + 0x14) * local_34) + local_10;
  local_90 = (int *)FUN_004e1190(local_48,*(undefined4 *)(local_8c + 0x174),0,0xffffffff,0);
  *(uint *)(local_90[0x8c] + 0x114) = *(uint *)(local_90[0x8c] + 0x114) | 8;
  FUN_0046fb20(param_3);
  iVar3 = FUN_00572a70();
  if (iVar3 != 0) {
    FUN_004b8460();
  }
  if ((*(uint *)(*(int *)(local_8c + 0xf4) + 0x14) & 0x10) == 0) {
    uVar2 = FUN_0045ca50(local_90);
    FUN_00461440(uVar2);
  }
  else {
    (**(code **)(*local_90 + 0xc))();
  }
  (**(code **)(*(int *)(local_8c + 0x18) + 8))(*(undefined4 *)(local_8c + 0x174));
  FUN_0083e885();
  return;
}

