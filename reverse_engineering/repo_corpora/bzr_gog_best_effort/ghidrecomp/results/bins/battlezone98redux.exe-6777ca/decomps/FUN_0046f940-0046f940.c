
undefined1 __thiscall FUN_0046f940(int param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = FUN_004ccd10(param_2,"[AOI]");
  if ((((cVar1 != '\0') && (cVar1 = FUN_004cf520(param_2,param_1,4,"undefptr"), cVar1 != '\0')) &&
      (cVar1 = FUN_004cd1b0(param_2,param_1 + 4,4,&DAT_008757b0), cVar1 != '\0')) &&
     (((cVar1 = FUN_004ccf20(param_2,param_1 + 8,1,"interesting"), cVar1 != '\0' &&
       (cVar1 = FUN_004ccf20(param_2,param_1 + 9,1,"inside"), cVar1 != '\0')) &&
      ((cVar1 = FUN_004cd1b0(param_2,param_1 + 0xc,4,"value"), cVar1 != '\0' &&
       (cVar1 = FUN_004cd1b0(param_2,param_1 + 0x10,4,"force"), cVar1 != '\0')))))) {
    return 1;
  }
  return 0;
}

