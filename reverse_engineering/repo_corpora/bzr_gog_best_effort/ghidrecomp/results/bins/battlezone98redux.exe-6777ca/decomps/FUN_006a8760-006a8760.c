
undefined4 FUN_006a8760(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  for (local_8 = 0; local_8 < *(int *)(param_1 + 8); local_8 = local_8 + 1) {
    FUN_0069d590(param_1,local_8);
  }
  do {
    bVar1 = true;
    for (local_8 = 0; (bVar1 && (local_c = local_8, local_8 < *(int *)(param_1 + 8)));
        local_8 = local_8 + 1) {
      while ((local_c = local_c + 1, bVar1 && (local_c < *(int *)(param_1 + 8)))) {
        iVar2 = FUN_0069d590(param_1,local_8);
        iVar3 = FUN_0069d590(param_1,local_c);
        if (iVar2 == iVar3) {
          FUN_0069d520(param_1,iVar2);
          bVar1 = false;
        }
      }
    }
  } while (!bVar1);
  return 1;
}

