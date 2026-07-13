
undefined1 __thiscall FUN_0046f840(int param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = FUN_004ce1c0(param_2,"[AOI]");
  if ((((cVar1 != '\0') &&
       (cVar1 = FUN_004cf640(param_2,param_1,4,"AOI::path",param_1), cVar1 != '\0')) &&
      (cVar1 = FUN_004ce910(param_2,param_1 + 4,4), cVar1 != '\0')) &&
     (((cVar1 = FUN_004ce5e0(param_2,param_1 + 8,1), cVar1 != '\0' &&
       (cVar1 = FUN_004ce5e0(param_2,param_1 + 9,1), cVar1 != '\0')) &&
      ((cVar1 = FUN_004ce910(param_2,param_1 + 0xc,4), cVar1 != '\0' &&
       (cVar1 = FUN_004ce910(param_2,param_1 + 0x10,4), cVar1 != '\0')))))) {
    return 1;
  }
  return 0;
}

