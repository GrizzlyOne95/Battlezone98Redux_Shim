/*
 * Entry: 00585817
 * Name: lzo1y_999_compress
 * Namespace: Global
 * Signature: int lzo1y_999_compress(uchar * param_1, ulong param_2, uchar * param_3, ulong * param_4, void * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
lzo1y_999_compress(uchar *param_1,ulong param_2,uchar *param_3,ulong *param_4,void *param_5)

{
  int iVar1;
  
  iVar1 = lzo1y_999_compress_level
                    (param_1,param_2,param_3,param_4,param_5,(uchar *)0x0,0,(lzo_callback_t *)0x0,8)
  ;
  return iVar1;
}
