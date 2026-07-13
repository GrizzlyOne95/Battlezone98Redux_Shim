/*
 * Entry: 00544eef
 * Name: CloseTLExecuteBuffer
 * Namespace: Global
 * Signature: int CloseTLExecuteBuffer(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CloseTLExecuteBuffer(void)

{
  if (gD3DEB.nState == 2) {
    gD3DEB.lpVertexPointer = (void *)0x0;
    gD3DEB.lpIndexPointer = (void *)0x0;
    gD3DEB.nState = 3;
  }
  return 1;
}
