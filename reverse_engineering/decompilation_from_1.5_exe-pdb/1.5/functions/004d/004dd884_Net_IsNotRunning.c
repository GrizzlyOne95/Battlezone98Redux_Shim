/*
 * Entry: 004dd884
 * Name: Net_IsNotRunning
 * Namespace: Global
 * Signature: int Net_IsNotRunning(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Net_IsNotRunning(void)

{
  return (uint)(theNet->state != NET_IS_RUNNING);
}
