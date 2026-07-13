/*
 * Entry: 00545d84
 * Name: D3D_Transparent_Texture_Mesh_Polygon
 * Namespace: Global
 * Signature: void D3D_Transparent_Texture_Mesh_Polygon(POINT_3D * param_1, long param_2, POLYGON_SKIN param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
D3D_Transparent_Texture_Mesh_Polygon(POINT_3D *param_1,long param_2,POLYGON_SKIN param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int unaff_EDI;
  IDirect3DTexture9 *pIVar6;
  
  pIVar6 = (IDirect3DTexture9 *)0x1;
  fVar3 = k1 * (param_1->Vector).z + k0;
  fVar2 = (param_1->Vector).z * 0.099;
  tmpZ = fVar2;
  Get_Texture_Handle((TEXTURE *)0x1,unaff_EDI);
  Set_Render_State(pIVar6,unaff_EDI);
  iVar5 = OpenTLExecuteBuffer(param_2,(param_2 + -2) * 3);
  iVar4 = param_2;
  if (iVar5 != 0) {
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(float *)gD3DEB.lpVertexPointer = (param_1->Vector).x;
      fVar1 = (param_1->Vector).y;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x10) = -NAN;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x14) = 0.0;
      *(float *)((int)gD3DEB.lpVertexPointer + 4) = fVar1;
      *(float *)((int)gD3DEB.lpVertexPointer + 8) = fVar3;
      *(float *)((int)gD3DEB.lpVertexPointer + 0xc) = fVar2;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x18) = (param_1->Texel).u;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x1c) = (param_1->Texel).v;
      param_1 = param_1 + 1;
      gD3DEB.lpVertexPointer = (float *)((int)gD3DEB.lpVertexPointer + 0x20);
    }
    Submit_D3D_Triangle(param_2);
  }
  return;
}
