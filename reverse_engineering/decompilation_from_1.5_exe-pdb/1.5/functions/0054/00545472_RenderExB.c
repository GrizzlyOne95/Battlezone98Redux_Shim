/*
 * Entry: 00545472
 * Name: RenderExB
 * Namespace: Global
 * Signature: int RenderExB(IDirect3DDevice9 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl RenderExB(IDirect3DDevice9 *param_1)

{
  if (gD3DEB.nState == 0) {
    return 0;
  }
  Flush_Vertex_Buffer();
  gD3DEB.nVertexStart = 0;
  gD3DEB.nIndexStart = 0;
  return 1;
}
