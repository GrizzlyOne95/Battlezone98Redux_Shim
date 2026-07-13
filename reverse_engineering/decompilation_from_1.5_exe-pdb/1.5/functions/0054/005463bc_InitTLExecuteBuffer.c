/*
 * Entry: 005463bc
 * Name: InitTLExecuteBuffer
 * Namespace: Global
 * Signature: int InitTLExecuteBuffer(IDirect3DDevice9 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl InitTLExecuteBuffer(IDirect3DDevice9 *param_1)

{
  gnMaxTLVNum = (uint)D3VertexBufferSize >> 5;
  gnMaxTLINum = (uint)D3IndexBufferSize >> 1;
  memset(&gD3DEB,0,0x38);
  AddTLExecuteBuffer();
  return 1;
}
