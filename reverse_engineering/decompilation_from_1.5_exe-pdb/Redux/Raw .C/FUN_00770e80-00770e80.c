
undefined4 * __thiscall FUN_00770e80(int param_1,undefined4 *param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  int local_8;
  
  local_8 = param_1;
  while (cVar1 = operator!=<>(&param_3,&stack0x0000000c), cVar1 != '\0') {
    pcVar2 = (char *)FUN_00771580();
    local_8 = (int)*pcVar2;
    cVar1 = FUN_00771520(&local_8);
    if (cVar1 != '\0') break;
    FUN_00771560();
  }
  *param_2 = param_3;
  return param_2;
}

