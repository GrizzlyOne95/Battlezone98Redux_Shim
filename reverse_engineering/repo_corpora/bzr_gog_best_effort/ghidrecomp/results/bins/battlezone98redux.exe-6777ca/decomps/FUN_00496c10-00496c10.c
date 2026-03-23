
undefined4 FUN_00496c10(undefined4 param_1,uint param_2,uint param_3,undefined1 param_4)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  bool bVar4;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  uVar1 = param_2 + (((int)(param_3 - param_2) >> 3) - ((int)(param_3 - param_2) >> 0x1f) >> 1) * 8;
  FUN_00497010(param_2,uVar1,param_3 - 8,param_4);
  local_c = uVar1 + 8;
  local_8 = uVar1;
  while (((param_2 < local_8 && (cVar2 = FUN_00497100(local_8 - 8,local_8), cVar2 == '\0')) &&
         (cVar2 = FUN_00497100(local_8,local_8 - 8), cVar2 == '\0'))) {
    local_8 = local_8 - 8;
  }
  while (((local_c < param_3 && (cVar2 = FUN_00497100(local_c,local_8), cVar2 == '\0')) &&
         (cVar2 = FUN_00497100(local_8,local_c), cVar2 == '\0'))) {
    local_c = local_c + 8;
  }
  local_14 = local_c;
  local_10 = local_8;
  do {
    while (param_3 <= local_14) {
LAB_00496d70:
      for (; param_2 < local_10; local_10 = local_10 - 8) {
        cVar2 = FUN_00497100(local_10 - 8,local_8);
        if (cVar2 == '\0') {
          cVar2 = FUN_00497100(local_8,local_10 - 8);
          if (cVar2 != '\0') break;
          local_8 = local_8 - 8;
          if (local_8 != local_10 - 8) {
            FUN_00497120(local_8,local_10 - 8);
          }
        }
      }
      if ((local_10 == param_2) && (local_14 == param_3)) {
        FUN_0044fd40(&local_8,&local_c);
        return param_1;
      }
      if (local_10 == param_2) {
        if (local_c != local_14) {
          FUN_00497120(local_8,local_c);
        }
        uVar1 = local_8;
        local_c = local_c + 8;
        local_8 = local_8 + 8;
        FUN_00497120(uVar1,local_14);
        local_14 = local_14 + 8;
      }
      else if (local_14 == param_3) {
        local_10 = local_10 - 8;
        local_8 = local_8 - 8;
        if (local_10 != local_8) {
          FUN_00497120(local_10,local_8);
        }
        local_c = local_c - 8;
        FUN_00497120(local_8,local_c);
      }
      else {
        local_10 = local_10 - 8;
        FUN_00497120(local_14,local_10);
        local_14 = local_14 + 8;
      }
    }
    cVar2 = FUN_00497100(local_8,local_14);
    if (cVar2 == '\0') {
      cVar2 = FUN_00497100(local_14,local_8);
      uVar1 = local_c;
      if (cVar2 != '\0') goto LAB_00496d70;
      uVar3 = local_c + 8;
      bVar4 = local_c != local_14;
      local_c = uVar3;
      if (bVar4) {
        FUN_00497120(uVar1,local_14);
      }
    }
    local_14 = local_14 + 8;
  } while( true );
}

