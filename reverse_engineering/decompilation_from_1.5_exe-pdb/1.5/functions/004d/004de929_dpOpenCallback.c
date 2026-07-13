/*
 * Entry: 004de929
 * Name: dpOpenCallback
 * Namespace: Global
 * Signature: int dpOpenCallback(dp_session_t * param_1, long * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl dpOpenCallback(dp_session_t *param_1,long *param_2,long param_3,void *param_4)

{
  *(uint *)param_4 = (uint)(param_1 == (dp_session_t *)0x0) * 4 + 5;
  return 0;
}
