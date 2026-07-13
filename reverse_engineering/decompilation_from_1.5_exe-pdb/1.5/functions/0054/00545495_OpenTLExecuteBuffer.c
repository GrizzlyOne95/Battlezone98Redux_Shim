/*
 * Entry: 00545495
 * Name: OpenTLExecuteBuffer
 * Namespace: Global
 * Signature: int OpenTLExecuteBuffer(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl OpenTLExecuteBuffer(long param_1,long param_2)

{
  if ((gnMaxTLVNum < gD3DEB.nVertexCount + gD3DEB.nVertexStart + param_1) ||
     (gnMaxTLINum < gD3DEB.nIndexCount + gD3DEB.nIndexStart + param_2)) {
    RenderExB(d3dappi.lpD3DDevice);
  }
  if (gD3DEB.nState != 2) {
    gD3DEB.lpVertexPointer =
         (void *)((gD3DEB.nVertexCount + gD3DEB.nVertexStart) * 0x20 + (int)gD3DEB.lpVertexStart);
    gD3DEB.nState = 2;
    gD3DEB.lpIndexPointer =
         (void *)((int)gD3DEB.lpIndexStart + (gD3DEB.nIndexCount + gD3DEB.nIndexStart) * 2);
  }
  return 1;
}
