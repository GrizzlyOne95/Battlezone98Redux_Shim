
void FUN_0044e380(void)

{
  int iVar1;
  int iVar2;
  undefined1 local_20 [4];
  undefined4 local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  undefined4 *local_c;
  undefined1 local_8 [4];
  
  FUN_00447e20(local_8);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_20);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_14 = (undefined4 *)FUN_00447e70();
    FUN_00447e90();
    if (*(char *)(local_14 + 7) == '\0') {
      local_18 = local_14;
      local_c = local_14;
      if (local_14 == (undefined4 *)0x0) {
        local_1c = 0;
      }
      else {
        local_1c = (**(code **)*local_14)(1);
      }
    }
  }
  return;
}

