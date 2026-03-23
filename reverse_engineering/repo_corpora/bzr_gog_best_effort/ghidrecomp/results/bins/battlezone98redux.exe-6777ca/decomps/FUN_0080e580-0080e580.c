
char FUN_0080e580(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = *param_1;
  cVar1 = FUN_0080fb70(param_1,param_2,param_3,uVar2);
  if (cVar1 != '\0') {
    uVar2 = distance<>(uVar2,*param_1);
    *param_4 = uVar2;
    FUN_0080fc10(param_1,param_2,&DAT_0260c0e5);
  }
  return cVar1;
}

