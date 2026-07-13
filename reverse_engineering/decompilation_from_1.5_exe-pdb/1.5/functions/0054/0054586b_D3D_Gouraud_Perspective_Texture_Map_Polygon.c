/*
 * Entry: 0054586b
 * Name: D3D_Gouraud_Perspective_Texture_Map_Polygon
 * Namespace: Global
 * Signature: void D3D_Gouraud_Perspective_Texture_Map_Polygon(POINT_3D * param_1, long param_2, POLYGON_SKIN param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
D3D_Gouraud_Perspective_Texture_Map_Polygon(POINT_3D *param_1,long param_2,POLYGON_SKIN param_3)

{
  float fVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  long unaff_EBX;
  IDirect3DTexture9 *unaff_ESI;
  
  Get_Texture_Handle((TEXTURE *)0x0,(int)unaff_ESI);
  Set_Render_State(unaff_ESI,unaff_EBX);
  if (gD3DEB.ePrimitiveType != D3DPT_TRIANGLELIST) {
    Flush_Vertex_Buffer();
    gD3DEB.ePrimitiveType = D3DPT_TRIANGLELIST;
  }
  iVar4 = OpenTLExecuteBuffer(param_2,(param_2 + -2) * 3);
  iVar3 = param_2;
  if (iVar4 != 0) {
    for (; 0 < iVar3; iVar3 = iVar3 + -1) {
      uVar5 = (uint)(param_1->Texel).field2_0x8.l.intensity;
      bVar2 = (param_1->Texel).field2_0x8.l.fogginess;
      *(float *)gD3DEB.lpVertexPointer = (param_1->Vector).x;
      *(float *)((int)gD3DEB.lpVertexPointer + 4) = (param_1->Vector).y;
      *(float *)((int)gD3DEB.lpVertexPointer + 8) = (param_1->Vector).z * k1 + k0;
      fVar1 = (param_1->Vector).z;
      *(uint *)((int)gD3DEB.lpVertexPointer + 0x10) =
           ((uVar5 | 0xffffff00) << 8 | uVar5) << 8 | uVar5;
      tmpZ = fVar1 * 0.099;
      *(uint *)((int)gD3DEB.lpVertexPointer + 0x14) = (uint)bVar2 << 0x18;
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
