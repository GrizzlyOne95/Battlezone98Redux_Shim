/*
 * Entry: 0044e840
 * Name: ContainerNeighbor::Clean
 * Namespace: ContainerNeighbor
 * Signature: void Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ContainerNeighbor::Clean(void)

{
  if (neighbors != (ContainerNeighbor *)0x0) {
    operator_delete__(neighbors);
  }
  pathMem = pathMem + maxNeighbors * -0x10;
  firstFree = -1;
  neighbors = (ContainerNeighbor *)0x0;
  maxNeighbors = 0;
  return;
}
