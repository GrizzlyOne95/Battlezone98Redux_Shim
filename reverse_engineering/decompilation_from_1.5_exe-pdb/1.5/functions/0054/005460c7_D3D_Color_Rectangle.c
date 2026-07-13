/*
 * Entry: 005460c7
 * Name: D3D_Color_Rectangle
 * Namespace: Global
 * Signature: void D3D_Color_Rectangle(ulong param_1, long param_2, long param_3, long param_4, long param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
D3D_Color_Rectangle(ulong param_1,long param_2,long param_3,long param_4,long param_5,int param_6)

{
  float fVar1;
  float fVar2;
  void *pvVar3;
  int iVar4;
  long unaff_EBP;
  IDirect3DTexture9 *unaff_EDI;
  
  Set_Render_State(unaff_EDI,unaff_EBP);
  if (gD3DEB.ePrimitiveType != D3DPT_TRIANGLELIST) {
    Flush_Vertex_Buffer();
    gD3DEB.ePrimitiveType = D3DPT_TRIANGLELIST;
  }
  iVar4 = OpenTLExecuteBuffer(4,6);
  pvVar3 = gD3DEB.lpVertexPointer;
  if (iVar4 != 0) {
    ClampZ();
    fVar1 = 1.0 / spriteZ;
    *(ulong *)((int)pvVar3 + 0x10) = param_1;
    *(undefined4 *)((int)pvVar3 + 0x14) = 0xff000000;
    *(ulong *)((int)pvVar3 + 0x30) = param_1;
    *(undefined4 *)((int)pvVar3 + 0x34) = 0xff000000;
    *(ulong *)((int)pvVar3 + 0x50) = param_1;
    *(undefined4 *)((int)pvVar3 + 0x54) = 0xff000000;
    *(ulong *)((int)pvVar3 + 0x70) = param_1;
    *(undefined4 *)((int)pvVar3 + 0x74) = 0xff000000;
    fVar2 = fVar1 * 0.099;
    fVar1 = fVar1 * k1 + k0;
    tmpZ = fVar1;
    *(float *)pvVar3 = (float)param_2;
    gD3DEB.lpVertexPointer = (void *)((int)pvVar3 + 0x80);
    *(float *)((int)pvVar3 + 4) = (float)param_3;
    *(float *)((int)pvVar3 + 8) = fVar1;
    *(float *)((int)pvVar3 + 0xc) = fVar2;
    *(undefined4 *)((int)pvVar3 + 0x18) = 0;
    *(undefined4 *)((int)pvVar3 + 0x1c) = 0;
    *(float *)((int)pvVar3 + 0x20) = (float)param_4;
    *(float *)((int)pvVar3 + 0x24) = (float)param_3;
    *(float *)((int)pvVar3 + 0x28) = fVar1;
    *(float *)((int)pvVar3 + 0x2c) = fVar2;
    *(undefined4 *)((int)pvVar3 + 0x38) = 0;
    *(undefined4 *)((int)pvVar3 + 0x3c) = 0;
    *(float *)((int)pvVar3 + 0x40) = (float)param_4;
    *(float *)((int)pvVar3 + 0x44) = (float)param_5;
    *(float *)((int)pvVar3 + 0x48) = fVar1;
    *(float *)((int)pvVar3 + 0x4c) = fVar2;
    *(undefined4 *)((int)pvVar3 + 0x58) = 0;
    *(undefined4 *)((int)pvVar3 + 0x5c) = 0;
    *(float *)((int)pvVar3 + 0x60) = (float)param_2;
    *(float *)((int)pvVar3 + 100) = (float)param_5;
    *(float *)((int)pvVar3 + 0x68) = fVar1;
    *(float *)((int)pvVar3 + 0x6c) = fVar2;
    *(undefined4 *)((int)pvVar3 + 0x78) = 0;
    *(undefined4 *)((int)pvVar3 + 0x7c) = 0;
    Submit_D3D_Triangle(4);
  }
  return;
}
