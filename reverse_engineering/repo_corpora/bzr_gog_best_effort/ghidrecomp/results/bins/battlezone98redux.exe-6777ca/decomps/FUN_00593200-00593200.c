
undefined4 FUN_00593200(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,code *param_4)

{
  undefined4 *puVar1;
  char cVar2;
  undefined4 *puVar3;
  bool bVar4;
  undefined4 *local_14;
  undefined4 *local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  puVar1 = param_2 + (((int)param_3 - (int)param_2 >> 2) - ((int)param_3 - (int)param_2 >> 0x1f) >>
                     1);
  FUN_00593750(param_2,puVar1,param_3 + -1,param_4);
  local_c = puVar1 + 1;
  local_8 = puVar1;
  while (((param_2 < local_8 && (cVar2 = (*param_4)(local_8[-1],*local_8), cVar2 == '\0')) &&
         (cVar2 = (*param_4)(*local_8,local_8[-1]), cVar2 == '\0'))) {
    local_8 = local_8 + -1;
  }
  while (((local_c < param_3 && (cVar2 = (*param_4)(*local_c,*local_8), cVar2 == '\0')) &&
         (cVar2 = (*param_4)(*local_8,*local_c), cVar2 == '\0'))) {
    local_c = local_c + 1;
  }
  local_14 = local_c;
  local_10 = local_8;
  do {
    while (param_3 <= local_14) {
LAB_00593367:
      for (; param_2 < local_10; local_10 = local_10 + -1) {
        cVar2 = (*param_4)(local_10[-1],*local_8);
        if (cVar2 == '\0') {
          cVar2 = (*param_4)(*local_8,local_10[-1]);
          if (cVar2 != '\0') break;
          local_8 = local_8 + -1;
          if (local_8 != local_10 + -1) {
            _Swap_adl<>(local_8,local_10 + -1);
          }
        }
      }
      if ((local_10 == param_2) && (local_14 == param_3)) {
        FUN_0044fd40(&local_8,&local_c);
        return param_1;
      }
      if (local_10 == param_2) {
        if (local_c != local_14) {
          _Swap_adl<>(local_8,local_c);
        }
        puVar1 = local_8;
        local_c = local_c + 1;
        local_8 = local_8 + 1;
        _Swap_adl<>(puVar1,local_14);
        local_14 = local_14 + 1;
      }
      else if (local_14 == param_3) {
        local_10 = local_10 + -1;
        local_8 = local_8 + -1;
        if (local_10 != local_8) {
          _Swap_adl<>(local_10,local_8);
        }
        local_c = local_c + -1;
        _Swap_adl<>(local_8,local_c);
      }
      else {
        local_10 = local_10 + -1;
        _Swap_adl<>(local_14,local_10);
        local_14 = local_14 + 1;
      }
    }
    cVar2 = (*param_4)(*local_8,*local_14);
    if (cVar2 == '\0') {
      cVar2 = (*param_4)(*local_14,*local_8);
      puVar1 = local_c;
      if (cVar2 != '\0') goto LAB_00593367;
      puVar3 = local_c + 1;
      bVar4 = local_c != local_14;
      local_c = puVar3;
      if (bVar4) {
        _Swap_adl<>(puVar1,local_14);
      }
    }
    local_14 = local_14 + 1;
  } while( true );
}

