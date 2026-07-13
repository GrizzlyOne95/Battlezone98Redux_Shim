/*
 * Entry: 00478d75
 * Name: start_net_loop
 * Namespace: Global
 * Signature: void start_net_loop(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl start_net_loop(void)

{
  net_stop = 0;
  net_stopped = 0;
  _beginthread(threadfunc,0,(void *)0x0);
  return;
}
