
undefined4 FUN_007c3720(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  float local_18;
  float local_14;
  undefined4 local_10;
  undefined1 *local_c;
  int *local_8;
  
  local_14 = 1.14074e-38;
  cVar1 = FUN_007d3360();
  if ((cVar1 != '\0') && ((char)local_8[0x78] != '\0')) {
    local_14 = (float)param_2;
    local_18 = (float)param_1;
    cVar1 = FUN_007d2810();
    if ((cVar1 != '\0') && (*(char *)((int)local_8 + 0x145) != '\0')) {
      if (*(char *)((int)local_8 + 0x145) != '\0') {
        *(undefined1 *)((int)local_8 + 0x145) = 0;
        if (((local_8[5] & 0x10U) == 0) || ((local_8[5] & 0x100U) == 0)) {
          local_14 = 0.0;
          local_18 = 1.1407671e-38;
          (**(code **)(*local_8 + 0x24))();
        }
        else {
          local_c = (undefined1 *)&local_18;
          local_10 = FUN_004498d0(local_8 + 0x52);
          FUN_007d2b70();
        }
        if (param_3 == 0) {
          local_8[0x77] = local_8[0x77] + 1;
          local_14 = 1.1407728e-38;
          iVar2 = size();
          if (iVar2 <= local_8[0x77]) {
            local_8[0x77] = 0;
          }
        }
        if ((param_3 == 1) && (local_8[0x77] = local_8[0x77] + -1, local_8[0x77] < 0)) {
          local_14 = 1.1407836e-38;
          iVar2 = size();
          local_8[0x77] = iVar2 + -1;
        }
        local_14 = (float)local_8[0x77];
        local_18 = 1.1407887e-38;
        puVar3 = (undefined4 *)FUN_004200d0();
        local_14 = 1.1407897e-38;
        local_14 = (float)std::allocator<char>::allocator<char>((allocator<char> *)*puVar3);
        local_18 = 1.1407933e-38;
        (**(code **)(*(int *)local_8[0x7c] + 0x3c))();
        if (local_8[0x76] != 0) {
          local_18 = 1.1407965e-38;
          (*(code *)local_8[0x76])();
        }
      }
      return 1;
    }
  }
  return 0;
}

