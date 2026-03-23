
void __thiscall FUN_007c27f0(int *param_1,byte param_2)

{
  undefined4 *puStack_28;
  uint uStack_24;
  undefined4 local_20;
  undefined4 *local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *local_c;
  int *local_8;
  
  local_8 = param_1;
  if ((param_1[0x48] == 0) || (param_2 == 0)) {
    if (param_1[0x48] != 0) {
      uStack_24 = 0;
      puStack_28 = (undefined4 *)0x7c28d7;
      (**(code **)(*(int *)param_1[0x48] + 0x84))();
    }
  }
  else if (((param_1[5] & 0x20000U) == 0) || (*(char *)((int)param_1 + 0x149) == '\0')) {
    if ((param_1[5] & 0x10U) == 0) {
      if (param_1[0x48] != 0) {
        uStack_24 = 0;
        puStack_28 = (undefined4 *)0x7c28ab;
        (**(code **)(*(int *)param_1[0x48] + 0x84))();
      }
    }
    else {
      local_14 = (undefined1 *)&puStack_28;
      local_18 = FUN_004498d0(param_1 + 0x45);
      FUN_007d2b70();
    }
  }
  else {
    local_c = (undefined1 *)&puStack_28;
    local_10 = FUN_004498d0(param_1 + 0x57);
    FUN_007d2b70();
  }
  *(byte *)((int)local_8 + 0xe9) = param_2;
  uStack_24 = (uint)param_2;
  puStack_28 = (undefined4 *)0x7c2901;
  (**(code **)(*(int *)local_8[0x51] + 0x24))();
  puStack_28 = (undefined4 *)(uint)param_2;
  FUN_007cc5c0();
  if (local_8[0x4e] != 0) {
    puStack_28 = &local_20;
    FUN_007c62e0();
    puStack_28 = local_1c;
    (**(code **)(*local_8 + 0x18))(local_20);
  }
  return;
}

