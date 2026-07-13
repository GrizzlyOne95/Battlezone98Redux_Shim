
bool FUN_00417e60(undefined1 *param_1,FILE *param_2)

{
  int iVar1;
  undefined1 local_8;
  
  iVar1 = fgetc(param_2);
  if (iVar1 != -1) {
    local_8 = (undefined1)iVar1;
    *param_1 = local_8;
  }
  return iVar1 != -1;
}

