/*
 * Entry: 0050e92b
 * Name: Debug_Fopen
 * Namespace: Global
 * Signature: _iobuf * Debug_Fopen(char * param_1, char * param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_iobuf * __cdecl Debug_Fopen(char *param_1,char *param_2,char *param_3,int param_4)

{
  FILE *pFVar1;
  
  pFVar1 = fopen(param_1,param_2);
  return (_iobuf *)pFVar1;
}
