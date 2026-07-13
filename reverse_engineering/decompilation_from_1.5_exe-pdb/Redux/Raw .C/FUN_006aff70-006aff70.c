
undefined4 *
FUN_006aff70(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 *param_7)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 local_c [8];
  
  cVar2 = FUN_006c9460();
  if (cVar2 == '\0') {
    FUN_006afec0(local_c,param_3,param_4,param_5,param_6,param_7);
  }
  else {
    FUN_006d8cf0(0x3e3);
  }
  uVar1 = param_7[1];
  *param_1 = *param_7;
  param_1[1] = uVar1;
  return param_1;
}

