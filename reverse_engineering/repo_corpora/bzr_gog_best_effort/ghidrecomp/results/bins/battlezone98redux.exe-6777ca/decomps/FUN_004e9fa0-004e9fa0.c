
undefined1 __thiscall FUN_004e9fa0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_14;
  char local_10;
  undefined1 local_c [7];
  char local_5;
  
  local_5 = '\x01';
  if ((0x3e9 < DAT_00917b20) && (DAT_00917b20 < 0x402)) {
    cVar1 = FUN_004ceb10(param_2,local_c,4,param_1);
    if (((((cVar1 == '\0') ||
          ((((cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0' ||
             (cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0')) ||
            (cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0')) ||
           ((cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0' ||
            (cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0')))))) ||
         (cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0')) ||
        (((cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0' ||
          (cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0')) ||
         ((cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0' ||
          (((cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0' ||
            (cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0')) ||
           (cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0')))))))) ||
       (((cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0' ||
         (cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0')) ||
        ((cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0' ||
         (((cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0' ||
           (cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0')) ||
          ((cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0' ||
           ((cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0' ||
            (cVar1 = FUN_004ceb10(param_2,local_c,4), cVar1 == '\0')))))))))))) {
      local_10 = '\0';
    }
    else {
      local_10 = '\x01';
    }
    local_5 = local_10;
  }
  if ((local_5 == '\0') || (cVar1 = FUN_004a7ff0(param_2), cVar1 == '\0')) {
    local_14 = 0;
  }
  else {
    local_14 = 1;
  }
  return local_14;
}

