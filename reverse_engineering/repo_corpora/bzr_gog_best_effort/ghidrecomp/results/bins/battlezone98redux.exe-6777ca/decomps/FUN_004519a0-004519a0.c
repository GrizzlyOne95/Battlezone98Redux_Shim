
void FUN_004519a0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_10 [4];
  int *local_c;
  undefined1 local_8 [4];
  
  if (DAT_0091565c != 0) {
    FUN_00447e20(local_8);
    while( true ) {
      iVar1 = FUN_00447e70();
      FUN_00447e50(local_10);
      iVar2 = FUN_00447e70();
      if (iVar1 == iVar2) break;
      local_c = (int *)FUN_00447e70();
      FUN_00447e90();
      (**(code **)(*local_c + 8))(param_1);
      FUN_00451370();
    }
  }
  return;
}

