
void FUN_00451250(float param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_20 [4];
  undefined4 local_1c;
  int local_18;
  int local_14;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  FUN_00447e20(local_10);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_20);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_8 = FUN_00447e70();
    FUN_00447e90();
    *(float *)(local_8 + 0x68) = *(float *)(local_8 + 0x68) - param_1;
    if ((*(float *)(local_8 + 0x68) <= 0.0 && *(float *)(local_8 + 0x68) != 0.0) ||
       (*(int *)(local_8 + 0x6c) == 0)) {
      FUN_0044dc60(0,param_1 + *(float *)(local_8 + 0x68));
      FUN_0044e950(local_8);
      local_18 = local_8;
      local_14 = local_8;
      if (local_8 == 0) {
        local_1c = 0;
      }
      else {
        local_1c = FUN_00451190(1);
      }
      iVar1 = FUN_004170c0();
      if (iVar1 == 0) {
        FUN_0044e950(local_c + 4);
      }
    }
  }
  return;
}

