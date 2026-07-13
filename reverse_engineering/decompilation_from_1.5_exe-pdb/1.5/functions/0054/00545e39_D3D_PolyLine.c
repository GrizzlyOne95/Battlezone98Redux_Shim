/*
 * Entry: 00545e39
 * Name: D3D_PolyLine
 * Namespace: Global
 * Signature: void D3D_PolyLine(tagPOINT * param_1, long param_2, POLYGON_SKIN param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3D_PolyLine(tagPOINT *param_1,long param_2,POLYGON_SKIN param_3)

{
  float fVar1;
  short sVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  long lVar6;
  int iVar7;
  long unaff_ESI;
  IDirect3DTexture9 *unaff_EDI;
  
  lVar6 = param_2;
  fVar1 = (float)D3D_Current_RGBA[param_3.Color];
  Set_Render_State(unaff_EDI,unaff_ESI);
  if (gD3DEB.ePrimitiveType != D3DPT_LINELIST) {
    Flush_Vertex_Buffer();
    gD3DEB.ePrimitiveType = D3DPT_LINELIST;
  }
  iVar3 = param_2 * 2;
  iVar7 = OpenTLExecuteBuffer(param_2,iVar3 + -2);
  if (iVar7 != 0) {
    fVar5 = k1 * (1.0 / spriteZ) + k0;
    fVar4 = (1.0 / spriteZ) * 0.099;
    tmpZ = fVar4;
    for (; 0 < param_2; param_2 = param_2 + -1) {
      *(float *)gD3DEB.lpVertexPointer = (float)param_1->x;
      iVar7 = param_1->y;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x14) = 0.0;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x10) = fVar1;
      *(float *)((int)gD3DEB.lpVertexPointer + 4) = (float)iVar7;
      *(float *)((int)gD3DEB.lpVertexPointer + 8) = fVar5;
      *(float *)((int)gD3DEB.lpVertexPointer + 0xc) = fVar4;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x18) = 0.0;
      *(float *)((int)gD3DEB.lpVertexPointer + 0x1c) = 0.0;
      param_1 = param_1 + 1;
      gD3DEB.lpVertexPointer = (float *)((int)gD3DEB.lpVertexPointer + 0x20);
    }
    param_2 = 0;
    iVar7 = lVar6 + -1;
    sVar2 = (short)gD3DEB.nVertexCount;
    if (0 < iVar7) {
      do {
        *(short *)gD3DEB.lpIndexPointer = (short)param_2 + sVar2;
        *(short *)((int)gD3DEB.lpIndexPointer + 2) = (short)param_2 + sVar2 + 1;
        gD3DEB.lpIndexPointer = (void *)((int)gD3DEB.lpIndexPointer + 4);
        param_2 = param_2 + 1;
      } while (param_2 < iVar7);
    }
    gD3DEB.nVertexCount = gD3DEB.nVertexCount + lVar6;
    gD3DEB.nIndexCount = gD3DEB.nIndexCount + -2 + iVar3;
    CloseTLExecuteBuffer();
  }
  return;
}
