/*
 * Entry: 00544f14
 * Name: ReleaseTLExecuteBuffer
 * Namespace: Global
 * Signature: int ReleaseTLExecuteBuffer(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ReleaseTLExecuteBuffer(void)

{
  if (gD3DEB.nState != 0) {
    CloseTLExecuteBuffer();
    if (gD3DEB.lpVertexBuffer != (IDirect3DVertexBuffer9 *)0x0) {
      (*(gD3DEB.lpVertexBuffer)->lpVtbl->Release)(gD3DEB.lpVertexBuffer);
      gD3DEB.lpVertexBuffer = (IDirect3DVertexBuffer9 *)0x0;
    }
    free(gD3DEB.lpVertexStart);
    gD3DEB.lpVertexStart = (void *)0x0;
    if (gD3DEB.lpIndexBuffer != (IDirect3DIndexBuffer9 *)0x0) {
      (*(gD3DEB.lpIndexBuffer)->lpVtbl->Release)(gD3DEB.lpIndexBuffer);
      gD3DEB.lpIndexBuffer = (IDirect3DIndexBuffer9 *)0x0;
    }
    free(gD3DEB.lpIndexStart);
    gD3DEB.lpIndexStart = (void *)0x0;
    if (gD3DEB.lpQuery != (IDirect3DQuery9 *)0x0) {
      (*(gD3DEB.lpQuery)->lpVtbl->Release)(gD3DEB.lpQuery);
      gD3DEB.lpQuery = (IDirect3DQuery9 *)0x0;
    }
    gD3DEB.nState = 0;
  }
  return 1;
}
