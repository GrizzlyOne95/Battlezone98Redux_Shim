
void FUN_00446b50(float param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  undefined1 local_10 [4];
  int local_c;
  undefined4 *local_8;
  
  FUN_00447e20(local_10);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_24);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_18 = (undefined4 *)FUN_00447e70();
    local_8 = local_18;
    FUN_00447e90();
    if ((*(char *)(local_8 + 7) == '\0') || (param_1 <= 0.0)) {
      local_8[0x18] = (float)local_8[0x18] + param_1;
      if (*(float *)(local_c + 0x174) <= (float)local_8[0x18] &&
          (float)local_8[0x18] != *(float *)(local_c + 0x174)) {
        local_1c = local_8;
        local_14 = local_8;
        if (local_8 == (undefined4 *)0x0) {
          local_20 = 0;
        }
        else {
          local_20 = (**(code **)*local_8)(1);
        }
      }
    }
    else {
      FUN_00447530(local_8);
    }
  }
  return;
}

