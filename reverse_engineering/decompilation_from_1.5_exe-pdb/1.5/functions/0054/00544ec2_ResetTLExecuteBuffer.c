/*
 * Entry: 00544ec2
 * Name: ResetTLExecuteBuffer
 * Namespace: Global
 * Signature: int ResetTLExecuteBuffer(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ResetTLExecuteBuffer(void)

{
  if (gD3DEB.nState == 0) {
    return 0;
  }
  gD3DEB.nVertexStart = 0;
  gD3DEB.nVertexCount = 0;
  gD3DEB.nIndexStart = 0;
  gD3DEB.nIndexCount = 0;
  gD3DEB.ePrimitiveType = D3DPT_TRIANGLELIST;
  return 1;
}
