/*
 * Entry: 0050e978
 * Name: Debug_AtExit
 * Namespace: Global
 * Signature: void Debug_AtExit(_func___cdecl_void * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Debug_AtExit(_func___cdecl_void *param_1,char *param_2,int param_3)

{
  tagATEXITNODE *ptVar1;
  
  ptVar1 = calloc(1,8);
  ptVar1->next = atexitlist;
  ptVar1->func = param_1;
  atexitlist = ptVar1;
  return;
}
