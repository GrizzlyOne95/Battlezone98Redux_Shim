
bool __thiscall FUN_006ae780(undefined4 *param_1,SOCKET param_2)

{
  int iVar1;
  
  iVar1 = __WSAFDIsSet(param_2,(fd_set *)*param_1);
  return iVar1 != 0;
}

