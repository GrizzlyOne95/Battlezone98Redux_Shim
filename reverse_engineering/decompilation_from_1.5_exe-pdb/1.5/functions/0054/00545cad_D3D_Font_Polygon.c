/*
 * Entry: 00545cad
 * Name: D3D_Font_Polygon
 * Namespace: Global
 * Signature: void D3D_Font_Polygon(POINT_3D * param_1, long param_2, POLYGON_SKIN param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3D_Font_Polygon(POINT_3D *param_1,long param_2,POLYGON_SKIN param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  long unaff_ESI;
  IDirect3DTexture9 *unaff_EDI;
  
  fVar2 = (float)D3D_Current_RGBA[Foreground_Color];
  fVar4 = k1 * (param_1->Vector).z + k0;
  fVar3 = (param_1->Vector).z * 0.099;
  tmpZ = fVar3;
  Get_Texture_Handle((TEXTURE *)0x1,(int)unaff_EDI);
  Set_Render_State(unaff_EDI,unaff_ESI);
  if (gD3DEB.ePrimitiveType != D3DPT_TRIANGLELIST) {
    Flush_Vertex_Buffer();
    gD3DEB.ePrimitiveType = D3DPT_TRIANGLELIST;
  }
  iVar6 = OpenTLExecuteBuffer(param_2,(param_2 + -2) * 3);
  iVar5 = param_2;
  if (iVar6 != 0) {
    for (; 0 < iVar5; iVar5 = iVar5 + -1) {
      *(float *)gD3DEB.lpVertexPointer = (param_1->Vector).x - 0.5;
      fVar1 = (param_1->Vector).y;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x14) = 0.0;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x10) = fVar2;
      *(float *)((int)gD3DEB.lpVertexPointer + 4) = fVar1 - 0.5;
      *(float *)((int)gD3DEB.lpVertexPointer + 8) = fVar4;
      *(float *)((int)gD3DEB.lpVertexPointer + 0xc) = fVar3;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x18) = (param_1->Texel).u;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x1c) = (param_1->Texel).v;
      param_1 = param_1 + 1;
      gD3DEB.lpVertexPointer = (float *)((int)gD3DEB.lpVertexPointer + 0x20);
    }
    Submit_D3D_Triangle(param_2);
  }
  return;
}
