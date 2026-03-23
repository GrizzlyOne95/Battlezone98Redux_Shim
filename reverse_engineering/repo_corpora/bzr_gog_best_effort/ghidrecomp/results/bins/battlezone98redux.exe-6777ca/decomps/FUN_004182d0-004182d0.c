
bool FUN_004182d0(void)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  uint local_18;
  int local_c;
  
  iVar1 = FUN_00417c70();
  if (iVar1 == 0) {
    bVar3 = false;
  }
  else {
    iVar1 = FUN_00417ca0();
    if (iVar1 == 0) {
      bVar3 = false;
    }
    else {
      if (iVar1 == 0) {
        local_18 = 0;
      }
      else {
        local_18 = FUN_00417f90();
      }
      for (local_c = 0; local_c < 5; local_c = local_c + 1) {
        if ((1 << ((byte)local_c & 0x1f) & local_18) != 0) {
          iVar1 = FUN_00417f60(local_c);
          iVar2 = FUN_00417f40(local_c);
          if ((iVar2 != 0) && (*(int *)(iVar2 + 0x84) == 0x4a)) {
            return false;
          }
          if ((iVar1 != 0) && (*(char *)(*(int *)(iVar1 + 8) + 0x79) == '\0')) {
            return false;
          }
        }
      }
      bVar3 = local_18 != 0;
    }
  }
  return bVar3;
}

