/*
 * Entry: 0050e999
 * Name: Debug_Assert
 * Namespace: Global
 * Signature: void Debug_Assert(int param_1, int param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Debug_Assert(int param_1,int param_2,char *param_3,char *param_4)

{
  FILE *pFVar1;
  
  if (param_1 == 0) {
    printf("ASSERTION FAILED\n\n%s(%d): ASSERT (%s);\n",param_3,param_2,param_4);
    pFVar1 = __iob_func();
    fflush(pFVar1 + 1);
    LogError(-1,"ASSERTION FAILED\n\n%s(%d): ASSERT (%s);\n");
  }
  return;
}
