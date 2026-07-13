
bool __fastcall FUN_004a82e0(int *param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_004cf880(param_1[0x8b]);
  param_1[0x8b] = iVar2;
  cVar1 = FUN_004dce20();
  (**(code **)(*param_1 + 0xa4))(param_1[0x80]);
  return cVar1 != '\0';
}

