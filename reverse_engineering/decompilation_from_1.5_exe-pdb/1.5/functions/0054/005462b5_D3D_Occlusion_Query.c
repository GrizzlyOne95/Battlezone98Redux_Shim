/*
 * Entry: 005462b5
 * Name: D3D_Occlusion_Query
 * Namespace: Global
 * Signature: int D3D_Occlusion_Query(VECTOR_3D * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3D_Occlusion_Query(VECTOR_3D *param_1,long param_2)

{
  int iVar1;
  IDirect3DTexture9 *unaff_ESI;
  int iVar2;
  
  iVar2 = -1;
  Set_Render_State(unaff_ESI,-1);
  if (gD3DEB.ePrimitiveType != D3DPT_TRIANGLELIST) {
    Flush_Vertex_Buffer();
    gD3DEB.ePrimitiveType = D3DPT_TRIANGLELIST;
  }
  if (((gD3DEB.nQueryScale < 1) || (gD3DEB.lpQuery == (IDirect3DQuery9 *)0x0)) ||
     (iVar1 = OpenTLExecuteBuffer(param_2,(param_2 + -2) * 3), iVar1 == 0)) {
    iVar2 = -1;
  }
  else {
    (*(gD3DEB.lpQuery)->lpVtbl->Issue)(gD3DEB.lpQuery,2);
    for (iVar1 = param_2; 0 < iVar1; iVar1 = iVar1 + -1) {
      *(float *)gD3DEB.lpVertexPointer = param_1->x;
      *(float *)((int)gD3DEB.lpVertexPointer + 4) = param_1->y;
      *(float *)((int)gD3DEB.lpVertexPointer + 8) = k1 / param_1->z + k0;
      tmpZ = 0.099 / param_1->z;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x10) = 0.0;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x14) = -1.7014118e+38;
      *(float *)((int)gD3DEB.lpVertexPointer + 0xc) = tmpZ;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x18) = 0.0;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x1c) = 0.0;
      param_1 = param_1 + 1;
      gD3DEB.lpVertexPointer = (float *)((int)gD3DEB.lpVertexPointer + 0x20);
    }
    Submit_D3D_Triangle(param_2);
    Flush_Vertex_Buffer();
    (*(gD3DEB.lpQuery)->lpVtbl->Issue)(gD3DEB.lpQuery,1);
    do {
      iVar1 = (*(gD3DEB.lpQuery)->lpVtbl->GetData)(gD3DEB.lpQuery,&stack0xfffffff8,4,1);
    } while (iVar1 == 1);
    iVar2 = iVar2 / gD3DEB.nQueryScale;
  }
  return iVar2;
}
