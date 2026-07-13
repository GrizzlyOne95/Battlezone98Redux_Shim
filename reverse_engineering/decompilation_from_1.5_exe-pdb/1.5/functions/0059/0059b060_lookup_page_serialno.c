/*
 * Entry: 0059b060
 * Name: _lookup_page_serialno
 * Namespace: Global
 * Signature: int _lookup_page_serialno(ogg_page * param_1, long * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _lookup_page_serialno(ogg_page *param_1,long *param_2,int param_3)

{
  long lVar1;
  int iVar2;
  
  lVar1 = ogg_page_serialno(param_1);
  iVar2 = _lookup_serialno(lVar1,param_2,param_3);
  return iVar2;
}
