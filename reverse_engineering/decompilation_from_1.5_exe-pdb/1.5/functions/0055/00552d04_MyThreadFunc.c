/*
 * Entry: 00552d04
 * Name: MyThreadFunc
 * Namespace: Global
 * Signature: ulong MyThreadFunc(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl MyThreadFunc(void *param_1)

{
  modem_dp_result = dpCreate(&Net::dp,&dp_transport,&params,0);
  dpCreateDone = (modem_dp_result != 0) + 1;
                    /* WARNING: Subroutine does not return */
  ExitThread(0);
}
