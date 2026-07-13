/*
 * Entry: 00527319
 * Name: EndBWD2Write
 * Namespace: Global
 * Signature: long EndBWD2Write(void * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl EndBWD2Write(void *param_1,char *param_2,int param_3)

{
  if (param_3 != 0) {
    AddChunkToBWD2(param_1,param_2,0x45584954,(void *)0x0,8);
  }
  fclose(param_1);
  return 1;
}
