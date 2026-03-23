
undefined4 FUN_00756ca0(undefined4 param_1,uint param_2,uint param_3,undefined1 param_4)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  uVar3 = ((int)(param_3 - param_2) / 0xa0) * 0x50 + param_2;
  FUN_00757190(param_2,uVar3,param_3 - 0x50,param_4);
  local_c = uVar3 + 0x50;
  local_8 = uVar3;
  while (((param_2 < local_8 && (cVar1 = FUN_00754c60(local_8 - 0x50,local_8), cVar1 == '\0')) &&
         (cVar1 = FUN_00754c60(local_8,local_8 - 0x50), cVar1 == '\0'))) {
    local_8 = local_8 - 0x50;
  }
  while (((local_c < param_3 && (cVar1 = FUN_00754c60(local_c,local_8), cVar1 == '\0')) &&
         (cVar1 = FUN_00754c60(local_8,local_c), cVar1 == '\0'))) {
    local_c = local_c + 0x50;
  }
  local_14 = local_c;
  local_10 = local_8;
  do {
    while (param_3 <= local_14) {
LAB_00756e05:
      for (; param_2 < local_10; local_10 = local_10 - 0x50) {
        cVar1 = FUN_00754c60(local_10 - 0x50,local_8);
        if (cVar1 == '\0') {
          cVar1 = FUN_00754c60(local_8,local_10 - 0x50);
          if (cVar1 != '\0') break;
          local_8 = local_8 - 0x50;
          if (local_8 != local_10 - 0x50) {
            FUN_00757280(local_8,local_10 - 0x50);
          }
        }
      }
      if ((local_10 == param_2) && (local_14 == param_3)) {
        FUN_0044fd40(&local_8,&local_c);
        return param_1;
      }
      if (local_10 == param_2) {
        if (local_c != local_14) {
          FUN_00757280(local_8,local_c);
        }
        uVar3 = local_8;
        local_c = local_c + 0x50;
        local_8 = local_8 + 0x50;
        FUN_00757280(uVar3,local_14);
        local_14 = local_14 + 0x50;
      }
      else if (local_14 == param_3) {
        local_10 = local_10 - 0x50;
        local_8 = local_8 - 0x50;
        if (local_10 != local_8) {
          FUN_00757280(local_10,local_8);
        }
        local_c = local_c - 0x50;
        FUN_00757280(local_8,local_c);
      }
      else {
        local_10 = local_10 - 0x50;
        FUN_00757280(local_14,local_10);
        local_14 = local_14 + 0x50;
      }
    }
    cVar1 = FUN_00754c60(local_8,local_14);
    if (cVar1 == '\0') {
      cVar1 = FUN_00754c60(local_14,local_8);
      uVar3 = local_c;
      if (cVar1 != '\0') goto LAB_00756e05;
      uVar2 = local_c + 0x50;
      bVar4 = local_c != local_14;
      local_c = uVar2;
      if (bVar4) {
        FUN_00757280(uVar3,local_14);
      }
    }
    local_14 = local_14 + 0x50;
  } while( true );
}

