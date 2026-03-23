
bool __fastcall FUN_005b5ce0(int *param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_004cf880(param_1[0x10]);
  param_1[0x10] = iVar2;
  iVar2 = FUN_004cf880(param_1[0x11]);
  param_1[0x11] = iVar2;
  cVar1 = FUN_00435a30();
  (**(code **)(*param_1 + 0x28))();
  return cVar1 != '\0';
}

