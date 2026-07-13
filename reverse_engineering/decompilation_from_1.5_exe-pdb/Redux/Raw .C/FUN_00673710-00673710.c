
undefined4 FUN_00673710(undefined4 param_1,uint param_2,uint param_3,undefined1 param_4)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  uVar3 = ((int)(param_3 - param_2) / 0x38) * 0x1c + param_2;
  FUN_00675c00(param_2,uVar3,param_3 - 0x1c,param_4);
  local_c = uVar3 + 0x1c;
  local_8 = uVar3;
  while (((param_2 < local_8 && (cVar1 = FUN_00669260(local_8 - 0x1c,local_8), cVar1 == '\0')) &&
         (cVar1 = FUN_00669260(local_8,local_8 - 0x1c), cVar1 == '\0'))) {
    local_8 = local_8 - 0x1c;
  }
  while (((local_c < param_3 && (cVar1 = FUN_00669260(local_c,local_8), cVar1 == '\0')) &&
         (cVar1 = FUN_00669260(local_8,local_c), cVar1 == '\0'))) {
    local_c = local_c + 0x1c;
  }
  local_14 = local_c;
  local_10 = local_8;
  do {
    while (param_3 <= local_14) {
LAB_00673875:
      for (; param_2 < local_10; local_10 = local_10 - 0x1c) {
        cVar1 = FUN_00669260(local_10 - 0x1c,local_8);
        if (cVar1 == '\0') {
          cVar1 = FUN_00669260(local_8,local_10 - 0x1c);
          if (cVar1 != '\0') break;
          local_8 = local_8 - 0x1c;
          if (local_8 != local_10 - 0x1c) {
            iter_swap<>(local_8,local_10 - 0x1c);
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
        local_c = local_c + 0x1c;
        local_8 = local_8 + 0x1c;
        iter_swap<>(uVar3,local_14);
        local_14 = local_14 + 0x1c;
      }
      else if (local_14 == param_3) {
        local_10 = local_10 - 0x1c;
        local_8 = local_8 - 0x1c;
        if (local_10 != local_8) {
          iter_swap<>(local_10,local_8);
        }
        local_c = local_c - 0x1c;
        iter_swap<>(local_8,local_c);
      }
      else {
        local_10 = local_10 - 0x1c;
        iter_swap<>(local_14,local_10);
        local_14 = local_14 + 0x1c;
      }
    }
    cVar1 = FUN_00669260(local_8,local_14);
    if (cVar1 == '\0') {
      cVar1 = FUN_00669260(local_14,local_8);
      uVar3 = local_c;
      if (cVar1 != '\0') goto LAB_00673875;
      uVar2 = local_c + 0x1c;
      bVar4 = local_c != local_14;
      local_c = uVar2;
      if (bVar4) {
        iter_swap<>(uVar3,local_14);
      }
    }
    local_14 = local_14 + 0x1c;
  } while( true );
}

