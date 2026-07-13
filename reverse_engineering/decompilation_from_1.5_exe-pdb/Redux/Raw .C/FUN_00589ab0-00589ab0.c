
undefined4 FUN_00589ab0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,char *param_4)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  char *local_24;
  char *local_20;
  char *local_18;
  char *local_14;
  char *local_10;
  char *local_c;
  
  local_20 = (char *)FUN_00589620(param_1,param_2);
  if (local_20 == (char *)0x0) {
    if (param_3 != (undefined4 *)0x0) {
      if (param_4 == (char *)0x0) {
        *param_3 = 0;
      }
      else {
        local_10 = param_4;
        do {
          cVar1 = *local_10;
          local_10 = local_10 + 1;
        } while (cVar1 != '\0');
        pcVar2 = (char *)FUN_0083d92c(local_10 + (1 - (int)(param_4 + 1)));
        local_24 = param_4;
        local_18 = pcVar2;
        do {
          cVar1 = *local_24;
          *local_18 = cVar1;
          local_24 = local_24 + 1;
          local_18 = local_18 + 1;
        } while (cVar1 != '\0');
        *param_3 = pcVar2;
      }
    }
    uVar3 = 0;
  }
  else {
    if (param_3 != (undefined4 *)0x0) {
      local_c = local_20;
      do {
        cVar1 = *local_c;
        local_c = local_c + 1;
      } while (cVar1 != '\0');
      pcVar2 = (char *)FUN_0083d92c(local_c + (1 - (int)(local_20 + 1)));
      local_14 = pcVar2;
      do {
        cVar1 = *local_20;
        *local_14 = cVar1;
        local_20 = local_20 + 1;
        local_14 = local_14 + 1;
      } while (cVar1 != '\0');
      *param_3 = pcVar2;
    }
    uVar3 = 1;
  }
  return uVar3;
}

