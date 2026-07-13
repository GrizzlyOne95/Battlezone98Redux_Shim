
bool FUN_006b6470(byte *param_1,byte *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = tolower((uint)*param_1);
  iVar2 = tolower((uint)*param_2);
  return iVar1 < iVar2;
}

