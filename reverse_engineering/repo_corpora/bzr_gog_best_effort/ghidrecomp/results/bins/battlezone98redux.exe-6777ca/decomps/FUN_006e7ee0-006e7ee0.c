
undefined1
FUN_006e7ee0(undefined1 *param_1,undefined1 *param_2,undefined1 *param_3,undefined1 *param_4)

{
  char cVar1;
  undefined1 local_c;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  while( true ) {
    if ((param_1 == param_2) || (param_3 == param_4)) {
      if ((param_1 == param_2) && (param_3 != param_4)) {
        local_c = 1;
      }
      else {
        local_c = 0;
      }
      return local_c;
    }
    local_5 = *param_3;
    local_6 = *param_1;
    cVar1 = FUN_006b6470(&local_6,&local_5);
    if (cVar1 != '\0') {
      return 1;
    }
    local_7 = *param_1;
    local_8 = *param_3;
    cVar1 = FUN_006b6470(&local_8,&local_7);
    if (cVar1 != '\0') break;
    param_1 = param_1 + 1;
    param_3 = param_3 + 1;
  }
  return 0;
}

