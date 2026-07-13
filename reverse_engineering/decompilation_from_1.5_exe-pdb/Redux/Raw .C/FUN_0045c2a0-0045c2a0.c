
undefined1 __thiscall FUN_0045c2a0(int param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = FUN_004cd1b0(param_2,param_1,4,"priority");
  if ((((cVar1 != '\0') &&
       (cVar1 = FUN_0045c3c0(param_2,param_1 + 4,4,&DAT_008751c0), cVar1 != '\0')) &&
      (cVar1 = FUN_004cd1b0(param_2,param_1 + 8,4,&DAT_008751bc), cVar1 != '\0')) &&
     ((cVar1 = FUN_004cf520(param_2,param_1 + 0xc,4,"where"), cVar1 != '\0' &&
      (cVar1 = FUN_004cda70(param_2,param_1 + 0x18,8,"param"), cVar1 != '\0')))) {
    return 1;
  }
  return 0;
}

