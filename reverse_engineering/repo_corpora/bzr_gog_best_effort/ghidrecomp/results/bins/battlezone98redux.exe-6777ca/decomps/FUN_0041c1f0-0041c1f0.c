
undefined4 FUN_0041c1f0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = FUN_00427270(param_1,"WHITE");
  if (cVar1 == '\0') {
    cVar1 = FUN_00427270(param_1,&DAT_0087129c);
    if (cVar1 == '\0') {
      cVar1 = FUN_00427270(param_1,&DAT_008712a4);
      if (cVar1 == '\0') {
        cVar1 = FUN_00427270(param_1,"DARK RED");
        if (cVar1 == '\0') {
          cVar1 = FUN_00427270(param_1,"GREEN");
          if (cVar1 == '\0') {
            cVar1 = FUN_00427270(param_1,"DARK GREEN");
            if (cVar1 == '\0') {
              cVar1 = FUN_00427270(param_1,"YELLOW");
              if (cVar1 == '\0') {
                cVar1 = FUN_00427270(param_1,"DARK YELLOW");
                if (cVar1 != '\0') {
                  param_2 = 0xff808000;
                }
              }
              else {
                param_2 = 0xffffff00;
              }
            }
            else {
              param_2 = 0xff008000;
            }
          }
          else {
            param_2 = 0xff00ff00;
          }
        }
        else {
          param_2 = 0xff800000;
        }
      }
      else {
        param_2 = 0xffff0000;
      }
    }
    else {
      param_2 = 0xff808080;
    }
  }
  else {
    param_2 = 0xffffffff;
  }
  return param_2;
}

