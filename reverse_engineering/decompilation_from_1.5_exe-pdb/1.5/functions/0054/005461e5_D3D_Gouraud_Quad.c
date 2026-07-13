/*
 * Entry: 005461e5
 * Name: D3D_Gouraud_Quad
 * Namespace: Global
 * Signature: void D3D_Gouraud_Quad(POINT_3D * param_1, long param_2, POLYGON_SKIN param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3D_Gouraud_Quad(POINT_3D *param_1,long param_2,POLYGON_SKIN param_3)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  uint extraout_EAX;
  uint uVar5;
  long unaff_EBX;
  IDirect3DTexture9 *unaff_ESI;
  float10 extraout_ST0;
  
  Set_Render_State(unaff_ESI,unaff_EBX);
  if (gD3DEB.ePrimitiveType != D3DPT_TRIANGLELIST) {
    Flush_Vertex_Buffer();
    gD3DEB.ePrimitiveType = D3DPT_TRIANGLELIST;
  }
  iVar4 = OpenTLExecuteBuffer(param_2,(param_2 + -2) * 3);
  iVar2 = param_2;
  pfVar3 = gD3DEB.lpVertexPointer;
  if (iVar4 != 0) {
    for (; 0 < iVar2; iVar2 = iVar2 + -1) {
      _ftol2_sse();
      *pfVar3 = (param_1->Vector).x;
      uVar5 = extraout_EAX & 0xff;
      pfVar3[1] = (param_1->Vector).y;
      pfVar3[2] = (param_1->Vector).z * k1 + k0;
      fVar1 = (param_1->Vector).z;
      pfVar3[5] = 0.0;
      tmpZ = fVar1 * 0.099;
      pfVar3[4] = (float)(((uVar5 | 0xffffbf00) << 8 | uVar5) << 8 | uVar5);
      pfVar3[3] = tmpZ;
      pfVar3[6] = (float)extraout_ST0;
      pfVar3[7] = (float)extraout_ST0;
      param_1 = param_1 + 1;
      pfVar3 = pfVar3 + 8;
    }
    gD3DEB.lpVertexPointer = pfVar3;
    Submit_D3D_Triangle(param_2);
  }
  return;
}
