/*
 * Entry: 00545f65
 * Name: D3D_Flat_Polygon
 * Namespace: Global
 * Signature: void D3D_Flat_Polygon(POINT_3D * param_1, long param_2, POLYGON_SKIN param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3D_Flat_Polygon(POINT_3D *param_1,long param_2,POLYGON_SKIN param_3)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  long unaff_ESI;
  IDirect3DTexture9 *unaff_EDI;
  
  fVar2 = (float)D3D_Current_RGBA[param_3.Color];
  Set_Render_State(unaff_EDI,unaff_ESI);
  if (gD3DEB.ePrimitiveType != D3DPT_TRIANGLELIST) {
    Flush_Vertex_Buffer();
    gD3DEB.ePrimitiveType = D3DPT_TRIANGLELIST;
  }
  iVar4 = OpenTLExecuteBuffer(param_2,(param_2 + -2) * 3);
  iVar3 = param_2;
  if (iVar4 != 0) {
    for (; 0 < iVar3; iVar3 = iVar3 + -1) {
      *(float *)gD3DEB.lpVertexPointer = (param_1->Vector).x - 0.5;
      *(float *)((int)gD3DEB.lpVertexPointer + 4) = (param_1->Vector).y - 0.5;
      *(float *)((int)gD3DEB.lpVertexPointer + 8) = (param_1->Vector).z * k1 + k0;
      fVar1 = (param_1->Vector).z;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x14) = 0.0;
      tmpZ = fVar1 * 0.099;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x10) = fVar2;
      *(float *)((int)gD3DEB.lpVertexPointer + 0xc) = tmpZ;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x18) = 0.0;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x1c) = 0.0;
      param_1 = param_1 + 1;
      gD3DEB.lpVertexPointer = (float *)((int)gD3DEB.lpVertexPointer + 0x20);
    }
    Submit_D3D_Triangle(param_2);
  }
  return;
}
