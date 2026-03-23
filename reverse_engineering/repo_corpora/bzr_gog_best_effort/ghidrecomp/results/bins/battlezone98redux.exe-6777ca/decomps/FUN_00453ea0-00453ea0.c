
void FUN_00453ea0(float param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_14 [4];
  undefined1 local_10 [8];
  int local_8;
  
  FUN_00451250(param_1);
  FUN_00447e20(local_10);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_14);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_8 = FUN_00447e70();
    FUN_00447e90();
    *(double *)(local_8 + 0x38) =
         (double)(param_1 * *(float *)(local_8 + 0x50)) + *(double *)(local_8 + 0x38);
    *(double *)(local_8 + 0x40) =
         (double)(param_1 * *(float *)(local_8 + 0x54)) + *(double *)(local_8 + 0x40);
    *(double *)(local_8 + 0x48) =
         (double)(param_1 * *(float *)(local_8 + 0x58)) + *(double *)(local_8 + 0x48);
  }
  return;
}

