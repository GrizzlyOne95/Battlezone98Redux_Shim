
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0061c260(void)

{
  float fVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined4 local_48 [6];
  float local_30;
  float local_2c;
  float local_28;
  undefined8 local_20;
  double local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar6 = (float10)FUN_00822d60();
  fVar1 = (float)fVar6;
  DAT_008eacbc = (float)_DAT_009198dc * 0.17453292 * fVar1 + DAT_008eacbc;
  if (DAT_008eacbc < -1.5707963) {
    DAT_008eacbc = -1.5707963;
  }
  if (1.5707963 < DAT_008eacbc) {
    DAT_008eacbc = 1.5707963;
  }
  DAT_008eacc4 = (float)_DAT_009198e4 * 0.17453292 * fVar1 + DAT_008eacc4;
  if (DAT_008eacc4 <= 3.1415927) {
    if (DAT_008eacc4 < -3.1415927) {
      DAT_008eacc4 = DAT_008eacc4 + 6.2831855;
      DAT_008eacc8 = DAT_008eacc8 + 6.2831855;
    }
  }
  else {
    DAT_008eacc4 = DAT_008eacc4 - 6.2831855;
    DAT_008eacc8 = DAT_008eacc8 - 6.2831855;
  }
  fVar6 = (float10)FUN_004c1050();
  DAT_008eacc0 = (float)fVar6;
  fVar6 = (float10)FUN_004c1050();
  DAT_008eacc8 = (float)fVar6;
  fVar6 = (float10)FUN_004c1050();
  DAT_02a13e8c = (float)fVar6;
  puVar2 = (undefined4 *)FUN_0081ed60();
  puVar5 = local_48;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar5 = puVar5 + 1;
  }
  FUN_004fef00(local_48,(double)(fVar1 * local_30 * DAT_02a13e8c) + _DAT_02a13ec8,
               (double)(fVar1 * local_2c * DAT_02a13e8c) + _DAT_02a13ed0,
               (double)(fVar1 * local_28 * DAT_02a13e8c) + _DAT_02a13ed8);
  fVar6 = (float10)FUN_007855e0(local_20,local_10);
  if (local_18 < (double)((float)fVar6 + 1.0)) {
    local_18 = (double)((float)fVar6 + 1.0);
  }
  uVar3 = FUN_00439e60();
  FUN_00689090(uVar3);
  puVar2 = local_48;
  puVar5 = &DAT_02a13ea0;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar5 = puVar5 + 1;
  }
  FUN_0083e885();
  return;
}

