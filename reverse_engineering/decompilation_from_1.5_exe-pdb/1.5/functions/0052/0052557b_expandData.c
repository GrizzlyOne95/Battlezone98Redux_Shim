/*
 * Entry: 0052557b
 * Name: expandData
 * Namespace: Global
 * Signature: int expandData(void * param_1, int param_2, int param_3, void * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl expandData(void *param_1,int param_2,int param_3,void *param_4,int param_5)

{
  int iVar1;
  undefined1 local_8 [4];
  
  if ((LZOIsInitialized == 0) && (iVar1 = initLZO(), iVar1 == 0)) {
    return 0;
  }
  if ((param_3 & 2U) == 0) {
    if ((param_3 & 4U) == 0) {
      return 0;
    }
    iVar1 = lzo1y_decompress_asm(param_1,param_2,param_4,local_8,0);
  }
  else {
    iVar1 = lzo1x_decompress_asm(param_1,param_2,param_4,local_8,0);
  }
  iVar1 = lzoCheck(iVar1,param_1);
  return iVar1;
}
