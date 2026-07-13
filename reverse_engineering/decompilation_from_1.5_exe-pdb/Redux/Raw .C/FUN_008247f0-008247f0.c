
void FUN_008247f0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 *puVar1;
  int iVar2;
  float *pfVar3;
  float10 fVar4;
  undefined1 local_bc [72];
  undefined1 local_74 [72];
  undefined1 local_2c [12];
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_00440060(local_2c,*param_4,param_4[1],param_4[2]);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  if (param_2 != 0) {
    iVar2 = FUN_0062e000(param_2);
    if (iVar2 != 0) {
      pfVar3 = (float *)FUN_0062bf70(local_bc,param_2);
      local_1c = *pfVar3;
      fVar4 = (float10)FUN_004428b0(param_3,&local_14);
      local_18 = (float)fVar4;
      fVar4 = (float10)FUN_00461fd0(local_1c * 0.5 * local_18 * local_18 * 0.5 * 0.0001);
      goto LAB_0082491b;
    }
  }
  pfVar3 = (float *)FUN_0062bf70(local_74,param_1);
  local_1c = *pfVar3;
  fVar4 = (float10)FUN_004428b0(param_3,&local_14);
  local_18 = (float)fVar4;
  fVar4 = (float10)FUN_00461fd0(local_1c * 0.5 * local_18 * local_18 * 0.75 * 0.0001);
LAB_0082491b:
  local_20 = (float)fVar4;
  FUN_0083e885();
  return;
}

