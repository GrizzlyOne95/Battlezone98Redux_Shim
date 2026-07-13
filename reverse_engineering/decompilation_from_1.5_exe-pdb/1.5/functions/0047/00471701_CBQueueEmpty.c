/*
 * Entry: 00471701
 * Name: CBQueueEmpty
 * Namespace: Global
 * Signature: int CBQueueEmpty(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CBQueueEmpty(void)

{
  return (uint)(q_list == (_cb_queue *)0x0);
}
