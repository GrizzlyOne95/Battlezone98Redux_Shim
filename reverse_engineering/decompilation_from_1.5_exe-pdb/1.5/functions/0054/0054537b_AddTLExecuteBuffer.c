/*
 * Entry: 0054537b
 * Name: AddTLExecuteBuffer
 * Namespace: Global
 * Signature: int AddTLExecuteBuffer(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddTLExecuteBuffer(void)

{
  int iVar1;
  
  if (gD3DEB.nState != 0) {
LAB_0054546a:
    iVar1 = ResetTLExecuteBuffer();
    return iVar1;
  }
  iVar1 = (*(d3dappi.lpD3DDevice)->lpVtbl->CreateVertexBuffer)
                    (d3dappi.lpD3DDevice,D3VertexBufferSize,0x208,0x1c4,D3DPOOL_DEFAULT,
                     &gD3DEB.lpVertexBuffer,(void **)0x0);
  if (-1 < iVar1) {
    iVar1 = (*(d3dappi.lpD3DDevice)->lpVtbl->CreateIndexBuffer)
                      (d3dappi.lpD3DDevice,D3IndexBufferSize,0x208,D3DFMT_INDEX16,D3DPOOL_DEFAULT,
                       &gD3DEB.lpIndexBuffer,(void **)0x0);
    if (-1 < iVar1) {
      (*(d3dappi.lpD3DDevice)->lpVtbl->SetFVF)(d3dappi.lpD3DDevice,0x1c4);
      (*(d3dappi.lpD3DDevice)->lpVtbl->SetStreamSource)
                (d3dappi.lpD3DDevice,0,gD3DEB.lpVertexBuffer,0,0x20);
      (*(d3dappi.lpD3DDevice)->lpVtbl->SetIndices)(d3dappi.lpD3DDevice,gD3DEB.lpIndexBuffer);
      (*(d3dappi.lpD3DDevice)->lpVtbl->CreateQuery)
                (d3dappi.lpD3DDevice,D3DQUERYTYPE_OCCLUSION,&gD3DEB.lpQuery);
      gD3DEB.lpVertexStart = malloc(D3VertexBufferSize);
      gD3DEB.lpIndexStart = malloc(D3IndexBufferSize);
      gD3DEB.nState = 1;
      goto LAB_0054546a;
    }
    if (gD3DEB.lpIndexBuffer != (IDirect3DIndexBuffer9 *)0x0) {
      (*(gD3DEB.lpIndexBuffer)->lpVtbl->Release)(gD3DEB.lpIndexBuffer);
      gD3DEB.lpIndexBuffer = (IDirect3DIndexBuffer9 *)0x0;
    }
  }
  return 0;
}
