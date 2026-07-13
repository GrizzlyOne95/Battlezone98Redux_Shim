/*
 * Entry: 0050e93c
 * Name: Debug_Fclose
 * Namespace: Global
 * Signature: int Debug_Fclose(_iobuf * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Debug_Fclose(_iobuf *param_1,char *param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = fclose((FILE *)param_1);
  if (iVar1 != 0) {
    piVar2 = _errno();
    strerror(*piVar2);
    LogError(-1,"Debug error: Could not close file in source file %s, line %d : %s\n");
  }
  return iVar1;
}
