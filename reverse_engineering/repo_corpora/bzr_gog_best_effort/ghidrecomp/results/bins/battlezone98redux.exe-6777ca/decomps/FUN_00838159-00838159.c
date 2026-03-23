
void FUN_00838159(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  
  FUN_0082cdd2(param_1,0xffffffff);
  FUN_0082d102(param_1,0xfffffffe,&DAT_00870104);
  FUN_0082cd77(param_1,param_2);
  FUN_0082d102(param_1,0xfffffffe,"_NAME");
  pcVar1 = strrchr(param_2,0x2e);
  pcVar2 = param_2;
  if (pcVar1 != (char *)0x0) {
    pcVar2 = pcVar1 + 1;
  }
  FUN_0082cd08(param_1,param_2,(int)pcVar2 - (int)param_2);
  FUN_0082d102(param_1,0xfffffffe,"_PACKAGE");
  return;
}

