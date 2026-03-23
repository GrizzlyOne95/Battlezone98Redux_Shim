
undefined4 __thiscall
FUN_008146f0(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  cVar1 = FUN_00814be0(param_1);
  if (cVar1 == '\0') {
    local_c = *param_2;
    while( true ) {
      cVar1 = FUN_00809970(param_2,param_3,param_4,param_5,&DAT_0260c0e5);
      if (cVar1 == '\0') break;
      cVar1 = FUN_00814be0(param_1);
      if (cVar1 != '\0') break;
      local_c = *param_2;
    }
    *param_2 = local_c;
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

