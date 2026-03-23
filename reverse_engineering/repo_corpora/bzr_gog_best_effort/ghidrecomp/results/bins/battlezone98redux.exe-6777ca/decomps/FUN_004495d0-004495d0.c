
void FUN_004495d0(float param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  undefined4 *local_10;
  undefined1 local_c [4];
  undefined4 *local_8;
  
  FUN_00447e20(local_c);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_24);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_18 = (undefined4 *)FUN_00447e70();
    FUN_00447e90();
    local_8 = local_18;
    if (*(char *)(local_18 + 7) == '\0') {
      local_1c = local_18;
      local_10 = local_18;
      if (local_18 == (undefined4 *)0x0) {
        local_20 = 0;
      }
      else {
        local_20 = (**(code **)*local_18)(1);
      }
    }
    else {
      local_18[0x18] = (float)local_18[0x18] + param_1;
    }
  }
  return;
}

