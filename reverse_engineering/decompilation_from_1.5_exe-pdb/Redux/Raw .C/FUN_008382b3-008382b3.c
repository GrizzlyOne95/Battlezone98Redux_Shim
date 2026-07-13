
void FUN_008382b3(undefined4 param_1,undefined4 param_2,char *param_3,undefined4 param_4)

{
  char *pcVar1;
  undefined4 uVar2;
  
  pcVar1 = getenv(param_3);
  if (pcVar1 == (char *)0x0) {
    FUN_0082cd77(param_1,param_4);
  }
  else {
    uVar2 = FUN_0082bd93(param_1,pcVar1,&DAT_00870120,&DAT_0087011c);
    FUN_0082bd93(param_1,uVar2,&DAT_00870124,param_4);
    FUN_0082cf99(param_1,0xfffffffe);
  }
  FUN_00838317(param_1);
  FUN_0082d102(param_1,0xfffffffe,param_2);
  return;
}

