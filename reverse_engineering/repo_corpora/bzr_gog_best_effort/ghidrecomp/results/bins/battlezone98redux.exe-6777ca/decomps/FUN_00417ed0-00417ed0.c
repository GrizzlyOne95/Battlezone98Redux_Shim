
bool FUN_00417ed0(byte *param_1,FILE *param_2)

{
  int iVar1;
  
  iVar1 = ungetc((uint)*param_1,param_2);
  return iVar1 != -1;
}

