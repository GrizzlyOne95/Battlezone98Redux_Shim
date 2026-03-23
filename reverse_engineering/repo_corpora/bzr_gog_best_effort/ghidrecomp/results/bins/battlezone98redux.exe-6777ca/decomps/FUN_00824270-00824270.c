
void FUN_00824270(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_b0 [64];
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar4 = (float10)FUN_00822d60();
  local_64 = (float)fVar4;
  if (DAT_009467ac == 0) {
    DAT_009467a8 = 8.0;
  }
  else {
    if (DAT_009467a4 - 1.0 <= DAT_009467a8) {
      DAT_009467a4 = 0.0;
    }
    fVar4 = (float10)FUN_004c1050();
    DAT_009467a8 = (float)fVar4;
    if ((DAT_009467a8 < 1.0) && (DAT_009467a4 == 0.0)) {
      DAT_009467ac = 0;
      DAT_009467b0 = 0;
    }
  }
  iVar1 = ___scrt_is_user_matherr_present();
  if (iVar1 == 0) {
    fVar4 = (float10)FUN_00822da0();
    local_4c = (float)fVar4;
    local_50 = (DAT_009467a8 * *(float *)(param_1 + 0x24)) / 320.0;
    fVar4 = (float10)FUN_00822970();
    local_68 = (float)fVar4;
    local_60 = local_68 * local_50;
    fVar4 = (float10)FUN_00822970();
    local_5c = (float)fVar4;
    local_58 = local_5c * local_50;
    local_6c = local_50 * 0.1;
    fVar4 = (float10)FUN_00822970();
    local_54 = (float)fVar4;
    local_70 = local_6c * local_54;
    puVar2 = (undefined4 *)FUN_0081ee70(local_b0,local_60,local_58,local_70,0,0,0);
    puVar3 = local_48;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar2 = (undefined4 *)FUN_0081fe60();
    puVar3 = (undefined4 *)(param_1 + 0x40);
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  FUN_0083e885();
  return;
}

