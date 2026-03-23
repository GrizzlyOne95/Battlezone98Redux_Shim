
void FUN_00454c00(float param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_18 [4];
  int local_14;
  undefined1 local_c [4];
  int local_8;
  
  FUN_00447e20(local_c);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_18);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_14 = FUN_00447e70();
    local_8 = local_14;
    FUN_00447e90();
    *(float *)(local_8 + 0x70) =
         *(float *)(*(int *)(local_8 + 0x18) + 0x198) * param_1 + *(float *)(local_8 + 0x70);
    *(float *)(local_8 + 0x78) =
         *(float *)(*(int *)(local_8 + 0x18) + 0x1a0) * param_1 + *(float *)(local_8 + 0x78);
    *(float *)(local_8 + 0x74) =
         *(float *)(*(int *)(local_8 + 0x18) + 0x19c) * param_1 + *(float *)(local_8 + 0x74);
  }
  FUN_004495d0(param_1);
  return;
}

