/*
 * Entry: 0047889c
 * Name: stop_net_loop
 * Namespace: Global
 * Signature: void stop_net_loop(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl stop_net_loop(void)

{
  net_stop = 1;
  while (net_stopped == 0) {
    Sleep(1);
  }
  return;
}
