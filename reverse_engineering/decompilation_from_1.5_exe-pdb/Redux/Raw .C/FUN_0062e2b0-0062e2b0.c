
void FUN_0062e2b0(int param_1,undefined4 param_2,float param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_a0 [64];
  int local_60;
  float local_5c;
  uint local_58;
  undefined4 local_54 [16];
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  do {
    puVar1 = (undefined4 *)FUN_0081fe60(local_a0,param_1 + 0x20,param_2);
    puVar3 = local_54;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    if ((*(uint *)(param_1 + 0x14) & 1) == 0) {
      iVar2 = FUN_004e3620(param_1,0);
      if (iVar2 == 1) {
        local_60 = *(int *)(param_1 + 100);
        for (local_58 = 0; local_58 < *(uint *)(local_60 + 4); local_58 = local_58 + 1) {
          FUN_00820180(&local_14,local_58 * 0xc + *(int *)(local_60 + 0xc),1,local_54);
          local_5c = local_14 * local_14 + local_10 * local_10 + local_c * local_c;
          if (param_3 < local_5c) {
            param_3 = local_5c;
          }
        }
      }
    }
    if (*(int *)(param_1 + 0x80) != 0) {
      fVar4 = (float10)FUN_0062e2b0(*(undefined4 *)(param_1 + 0x80),local_54,param_3);
      param_3 = (float)fVar4;
    }
    param_1 = *(int *)(param_1 + 0x7c);
  } while (param_1 != 0);
  FUN_0083e885();
  return;
}

