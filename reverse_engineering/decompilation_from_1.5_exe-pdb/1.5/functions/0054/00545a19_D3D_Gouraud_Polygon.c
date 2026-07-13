/*
 * Entry: 00545a19
 * Name: D3D_Gouraud_Polygon
 * Namespace: Global
 * Signature: void D3D_Gouraud_Polygon(POINT_3D * param_1, long param_2, POLYGON_SKIN param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3D_Gouraud_Polygon(POINT_3D *param_1,long param_2,POLYGON_SKIN param_3)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  TEXEL_u_8 TVar4;
  int iVar5;
  int iVar6;
  long unaff_ESI;
  uint uVar7;
  IDirect3DTexture9 *unaff_EDI;
  byte local_8;
  byte local_7;
  
  uVar2 = D3D_Current_Palette[param_3.Color].r;
  uVar3 = D3D_Current_Palette[param_3.Color].g;
  bVar1 = D3D_Current_Palette[param_3.Color].b;
  Set_Render_State(unaff_EDI,unaff_ESI);
  if (gD3DEB.ePrimitiveType != D3DPT_TRIANGLELIST) {
    Flush_Vertex_Buffer();
    gD3DEB.ePrimitiveType = D3DPT_TRIANGLELIST;
  }
  iVar6 = OpenTLExecuteBuffer(param_2,(param_2 + -2) * 3);
  iVar5 = param_2;
  if (iVar6 != 0) {
    for (; 0 < iVar5; iVar5 = iVar5 + -1) {
      TVar4 = (param_1->Texel).field2_0x8;
      *(float *)gD3DEB.lpVertexPointer = (param_1->Vector).x;
      uVar7 = (uint)TVar4 & 0xff;
      *(float *)((int)gD3DEB.lpVertexPointer + 4) = (param_1->Vector).y;
      *(float *)((int)gD3DEB.lpVertexPointer + 8) = (param_1->Vector).z * k1 + k0;
      tmpZ = (param_1->Vector).z * 0.099;
      *(float *)((int)gD3DEB.lpVertexPointer + 0xc) = tmpZ;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x18) = 0.0;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x1c) = 0.0;
      *(int *)((int)gD3DEB.lpVertexPointer + 0x10) =
           (((int)((byte)uVar2 * uVar7 | 0xff0000) >> 8) << 8 | (int)((byte)uVar3 * uVar7) >> 8) <<
           8 | (int)(bVar1 * uVar7) >> 8;
      *(int *)((int)gD3DEB.lpVertexPointer + 0x14) = ((int)TVar4 >> 8) << 0x18;
      gD3DEB.lpVertexPointer = (void *)((int)gD3DEB.lpVertexPointer + 0x20);
      param_1 = param_1 + 1;
    }
    Submit_D3D_Triangle(param_2);
  }
  return;
}
