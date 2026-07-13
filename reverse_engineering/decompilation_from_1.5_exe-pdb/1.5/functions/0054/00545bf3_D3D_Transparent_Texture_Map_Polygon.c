/*
 * Entry: 00545bf3
 * Name: D3D_Transparent_Texture_Map_Polygon
 * Namespace: Global
 * Signature: void D3D_Transparent_Texture_Map_Polygon(POINT_3D * param_1, long param_2, POLYGON_SKIN param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
D3D_Transparent_Texture_Map_Polygon(POINT_3D *param_1,long param_2,POLYGON_SKIN param_3)

{
  float fVar1;
  int iVar2;
  int iVar3;
  IDirect3DTexture9 *unaff_ESI;
  long unaff_retaddr;
  
  Get_Texture_Handle((TEXTURE *)0x1,(int)unaff_ESI);
  Set_Render_State(unaff_ESI,unaff_retaddr);
  if (gD3DEB.ePrimitiveType != D3DPT_TRIANGLELIST) {
    Flush_Vertex_Buffer();
    gD3DEB.ePrimitiveType = D3DPT_TRIANGLELIST;
  }
  iVar3 = OpenTLExecuteBuffer(param_2,(param_2 + -2) * 3);
  iVar2 = param_2;
  if (iVar3 != 0) {
    for (; 0 < iVar2; iVar2 = iVar2 + -1) {
      *(float *)gD3DEB.lpVertexPointer = (param_1->Vector).x - 0.5;
      *(float *)((int)gD3DEB.lpVertexPointer + 4) = (param_1->Vector).y - 0.5;
      *(float *)((int)gD3DEB.lpVertexPointer + 8) = (param_1->Vector).z * k1 + k0;
      fVar1 = (param_1->Vector).z;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x10) = -NAN;
      tmpZ = fVar1 * 0.099;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x14) = 0.0;
      *(float *)((int)gD3DEB.lpVertexPointer + 0xc) = tmpZ;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x18) = (param_1->Texel).u;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x1c) = (param_1->Texel).v;
      param_1 = param_1 + 1;
      gD3DEB.lpVertexPointer = (float *)((int)gD3DEB.lpVertexPointer + 0x20);
    }
    Submit_D3D_Triangle(param_2);
  }
  return;
}
