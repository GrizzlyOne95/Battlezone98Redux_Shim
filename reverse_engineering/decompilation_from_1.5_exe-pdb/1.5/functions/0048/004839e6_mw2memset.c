/*
 * Entry: 004839e6
 * Name: mw2memset
 * Namespace: Global
 * Signature: void * mw2memset(void * param_1, int param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl mw2memset(void *param_1,int param_2,uint param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c6dfc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = memset(param_1,param_2,param_3);
  return pvVar1;
}
