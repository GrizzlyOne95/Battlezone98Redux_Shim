
void FUN_0044e7f0(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int *local_c;
  undefined4 local_8;
  
  FUN_00423890();
  DAT_0091552a = 1;
  if (DAT_00915654 != 0) {
    puVar1 = (undefined4 *)FUN_00447e20(local_10);
    local_8 = *puVar1;
    while( true ) {
      iVar2 = FUN_00447e70();
      FUN_00447e50(local_14);
      iVar3 = FUN_00447e70();
      if (iVar2 == iVar3) break;
      local_c = (int *)FUN_00447e70();
      (**(code **)(*local_c + 0x10))(param_1);
      FUN_00447e90();
    }
  }
  return;
}

