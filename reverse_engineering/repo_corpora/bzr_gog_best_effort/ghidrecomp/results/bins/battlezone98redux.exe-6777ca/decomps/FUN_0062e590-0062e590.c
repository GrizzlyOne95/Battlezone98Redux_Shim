
void FUN_0062e590(int param_1,float param_2,float param_3,float param_4)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_8c [64];
  float local_4c;
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_008203f0(local_8c,param_1 + 0x20);
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  local_20 = local_20 - (double)param_2;
  local_18 = local_18 - (double)param_3;
  local_10 = local_10 - (double)param_4;
  fVar4 = (float10)FUN_0062e2b0(param_1,local_48,0);
  local_4c = (float)fVar4;
  FUN_00417910(local_4c);
  FUN_0083e885();
  return;
}

