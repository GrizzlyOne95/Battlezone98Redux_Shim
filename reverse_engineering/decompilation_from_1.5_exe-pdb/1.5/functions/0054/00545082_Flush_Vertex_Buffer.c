/*
 * Entry: 00545082
 * Name: Flush_Vertex_Buffer
 * Namespace: Global
 * Signature: void Flush_Vertex_Buffer(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Flush_Vertex_Buffer(void)

{
  int iVar1;
  void *local_c;
  void *local_8;
  
  if (0 < gD3DEB.nIndexCount) {
    (*(gD3DEB.lpVertexBuffer)->lpVtbl->Lock)
              (gD3DEB.lpVertexBuffer,gD3DEB.nVertexStart << 5,gD3DEB.nVertexCount << 5,&local_8,
               ((gD3DEB.nVertexStart < 1) - 1 & 0xfffff000) + 0x2000);
    memcpy(local_8,(void *)(gD3DEB.nVertexStart * 0x20 + (int)gD3DEB.lpVertexStart),
           gD3DEB.nVertexCount << 5);
    (*(gD3DEB.lpVertexBuffer)->lpVtbl->Unlock)(gD3DEB.lpVertexBuffer);
    (*(gD3DEB.lpIndexBuffer)->lpVtbl->Lock)
              (gD3DEB.lpIndexBuffer,gD3DEB.nIndexStart * 2,gD3DEB.nIndexCount * 2,&local_c,
               ((gD3DEB.nIndexStart < 1) - 1 & 0xfffff000) + 0x2000);
    memcpy(local_c,(void *)((int)gD3DEB.lpIndexStart + gD3DEB.nIndexStart * 2),
           gD3DEB.nIndexCount * 2);
    (*(gD3DEB.lpIndexBuffer)->lpVtbl->Unlock)(gD3DEB.lpIndexBuffer);
    CloseTLExecuteBuffer();
    iVar1 = 2;
    if (gD3DEB.ePrimitiveType != D3DPT_LINELIST) {
      if (gD3DEB.ePrimitiveType == D3DPT_TRIANGLELIST) {
        iVar1 = 3;
      }
      else {
        iVar1 = 1;
      }
    }
    (*(d3dappi.lpD3DDevice)->lpVtbl->DrawIndexedPrimitive)
              (d3dappi.lpD3DDevice,gD3DEB.ePrimitiveType,gD3DEB.nVertexStart,0,gD3DEB.nVertexCount,
               gD3DEB.nIndexStart,gD3DEB.nIndexCount / iVar1);
    gD3DEB.nVertexStart = gD3DEB.nVertexStart + gD3DEB.nVertexCount;
    gD3DEB.nIndexStart = gD3DEB.nIndexStart + gD3DEB.nIndexCount;
    gD3DEB.nVertexCount = 0;
    gD3DEB.nIndexCount = 0;
    Batch_Counter = Batch_Counter + 1;
  }
  return;
}
