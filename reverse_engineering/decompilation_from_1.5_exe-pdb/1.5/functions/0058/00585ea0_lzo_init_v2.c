/*
 * Entry: 00585ea0
 * Name: __lzo_init_v2
 * Namespace: Global
 * Signature: int __lzo_init_v2(uint param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
__lzo_init_v2(uint param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
             int param_8,int param_9,int param_10)

{
  int iVar1;
  
  if ((param_1 != 0) && ((param_2 == -1 || (param_2 == 2)))) {
    if (((param_3 == -1) || (param_3 == 4)) &&
       ((((((param_4 == -1 || (param_4 == 4)) && ((param_5 == -1 || (param_5 == 4)))) &&
          ((param_6 == -1 || (param_6 == 4)))) && ((param_7 == -1 || (param_7 == 4)))) &&
        ((((param_8 == -1 || (param_8 == 4)) && ((param_9 == -1 || (param_9 == 4)))) &&
         ((param_10 == -1 || (param_10 == 0x18)))))))) {
      iVar1 = _lzo_config_check();
      return iVar1;
    }
  }
  return -1;
}
