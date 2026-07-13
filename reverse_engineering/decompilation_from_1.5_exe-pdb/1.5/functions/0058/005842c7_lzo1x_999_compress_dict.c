/*
 * Entry: 005842c7
 * Name: lzo1x_999_compress_dict
 * Namespace: Global
 * Signature: int lzo1x_999_compress_dict(uchar * param_1, ulong param_2, uchar * param_3, ulong * param_4, void * param_5, uchar * param_6, ulong param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
lzo1x_999_compress_dict
          (uchar *param_1,ulong param_2,uchar *param_3,ulong *param_4,void *param_5,uchar *param_6,
          ulong param_7)

{
  int iVar1;
  
  iVar1 = lzo1x_999_compress_level
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,(lzo_callback_t *)0x0,8
                    );
  return iVar1;
}
