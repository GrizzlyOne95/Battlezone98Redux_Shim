
undefined4 FUN_00675850(undefined4 param_1,uint param_2,uint param_3,undefined1 param_4)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  uVar3 = ((int)(param_3 - param_2) / 0x30) * 0x18 + param_2;
  FUN_00676450(param_2,uVar3,param_3 - 0x18,param_4);
  local_c = uVar3 + 0x18;
  local_8 = uVar3;
  while (((param_2 < local_8 && (cVar1 = FUN_00422f40(local_8 - 0x18,local_8), cVar1 == '\0')) &&
         (cVar1 = FUN_00422f40(local_8,local_8 - 0x18), cVar1 == '\0'))) {
    local_8 = local_8 - 0x18;
  }
  while (((local_c < param_3 && (cVar1 = FUN_00422f40(local_c,local_8), cVar1 == '\0')) &&
         (cVar1 = FUN_00422f40(local_8,local_c), cVar1 == '\0'))) {
    local_c = local_c + 0x18;
  }
  local_14 = local_c;
  local_10 = local_8;
  do {
    while (param_3 <= local_14) {
LAB_006759b5:
      for (; param_2 < local_10; local_10 = local_10 - 0x18) {
        cVar1 = FUN_00422f40(local_10 - 0x18,local_8);
        if (cVar1 == '\0') {
          cVar1 = FUN_00422f40(local_8,local_10 - 0x18);
          if (cVar1 != '\0') break;
          local_8 = local_8 - 0x18;
          if (local_8 != local_10 - 0x18) {
            iter_swap<>(local_8,local_10 - 0x18);
          }
        }
      }
      if ((local_10 == param_2) && (local_14 == param_3)) {
        FUN_0044fd40(&local_8,&local_c);
        return param_1;
      }
      if (local_10 == param_2) {
        if (local_c != local_14) {
          iter_swap<>(local_8,local_c);
        }
        uVar3 = local_8;
        local_c = local_c + 0x18;
        local_8 = local_8 + 0x18;
        iter_swap<>(uVar3,local_14);
        local_14 = local_14 + 0x18;
      }
      else if (local_14 == param_3) {
        local_10 = local_10 - 0x18;
        local_8 = local_8 - 0x18;
        if (local_10 != local_8) {
          iter_swap<>(local_10,local_8);
        }
        local_c = local_c - 0x18;
        iter_swap<>(local_8,local_c);
      }
      else {
        local_10 = local_10 - 0x18;
        iter_swap<>(local_14,local_10);
        local_14 = local_14 + 0x18;
      }
    }
    cVar1 = FUN_00422f40(local_8,local_14);
    if (cVar1 == '\0') {
      cVar1 = FUN_00422f40(local_14,local_8);
      uVar3 = local_c;
      if (cVar1 != '\0') goto LAB_006759b5;
      uVar2 = local_c + 0x18;
      bVar4 = local_c != local_14;
      local_c = uVar2;
      if (bVar4) {
        iter_swap<>(uVar3,local_14);
      }
    }
    local_14 = local_14 + 0x18;
  } while( true );
}

