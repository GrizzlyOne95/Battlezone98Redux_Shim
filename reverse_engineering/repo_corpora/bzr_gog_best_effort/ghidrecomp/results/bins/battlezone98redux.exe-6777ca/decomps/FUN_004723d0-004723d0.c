
bool __fastcall FUN_004723d0(int *param_1)

{
  char cVar1;
  
  if (((char)param_1[0xc2] != '\0') && (cVar1 = (**(code **)(*param_1 + 0x68))(), cVar1 == '\0')) {
    return false;
  }
  return param_1[0xc0] != 0;
}

