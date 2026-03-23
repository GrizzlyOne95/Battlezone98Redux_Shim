
undefined4
FUN_00814390(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = *param_1;
  cVar1 = FUN_008097f0(param_1,param_2,param_3,param_4,&DAT_0260c0e5);
  if (cVar1 == '\0') {
    uVar2 = FUN_00814300(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    *param_1 = uVar2;
    uVar2 = 0;
  }
  return uVar2;
}

