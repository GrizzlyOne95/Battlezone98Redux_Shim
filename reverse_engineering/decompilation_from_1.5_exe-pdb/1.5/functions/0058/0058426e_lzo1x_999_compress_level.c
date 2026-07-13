/*
 * Entry: 0058426e
 * Name: lzo1x_999_compress_level
 * Namespace: Global
 * Signature: int lzo1x_999_compress_level(uchar * param_1, ulong param_2, uchar * param_3, ulong * param_4, void * param_5, uchar * param_6, ulong param_7, lzo_callback_t * param_8, int param_9)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
lzo1x_999_compress_level
          (uchar *param_1,ulong param_2,uchar *param_3,ulong *param_4,void *param_5,uchar *param_6,
          ulong param_7,lzo_callback_t *param_8,int param_9)

{
  int iVar1;
  
  if (param_9 - 1U < 9) {
    iVar1 = param_9 + -1;
    iVar1 = lzo1x_999_compress_internal
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       c[iVar1].try_lazy_parm,c[iVar1].good_length,c[iVar1].max_lazy,0,
                       c[iVar1].max_chain,c[iVar1].flags);
    return iVar1;
  }
  return -1;
}
