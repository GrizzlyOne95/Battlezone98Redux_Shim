/*
 * Entry: 005cc740
 * Name: `dynamic_atexit_destructor_for_'NodeNeighbor::neighbors''
 * Namespace: `dynamic_atexit_destructor_for_'NodeNeighbor
 * Signature: void neighbors''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'NodeNeighbor::neighbors__(void)

{
  if (NodeNeighbor::neighbors.array != (NodeNeighbor *)0x0) {
    operator_delete__(NodeNeighbor::neighbors.array);
  }
  NodeNeighbor::neighbors.size = 0;
  NodeNeighbor::neighbors.array = (NodeNeighbor *)0x0;
  return;
}
