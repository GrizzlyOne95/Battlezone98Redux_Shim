
void FUN_005010f0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_9c [64];
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float *local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar4 = (float10)FUN_0082c276(param_1,1,0);
  local_5c = (float)fVar4;
  local_4c = (float *)FUN_004ff7a0(param_1,2);
  if (local_4c == (float *)0x0) {
    fVar4 = (float10)FUN_0082c276(param_1,2,0);
    local_50 = (float)fVar4;
    fVar4 = (float10)FUN_0082c276(param_1,3,0);
    local_54 = (float)fVar4;
    fVar4 = (float10)FUN_0082c276(param_1,4,0);
    local_58 = (float)fVar4;
  }
  else {
    local_50 = *local_4c;
    local_54 = local_4c[1];
    local_58 = local_4c[2];
  }
  puVar1 = (undefined4 *)FUN_0081f490(local_9c,local_5c,local_50,local_54,local_58);
  puVar2 = local_48;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)FUN_004ff840();
  puVar1 = local_48;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar2 = puVar2 + 1;
  }
  FUN_0083e885();
  return;
}

