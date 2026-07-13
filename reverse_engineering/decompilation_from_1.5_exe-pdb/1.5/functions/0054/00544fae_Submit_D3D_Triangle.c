/*
 * Entry: 00544fae
 * Name: Submit_D3D_Triangle
 * Namespace: Global
 * Signature: void Submit_D3D_Triangle(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_D3D_Triangle(long param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined2 local_8;
  
  iVar1 = gD3DEB.nVertexCount;
  Polygon_Counter = Polygon_Counter + 1;
  iVar4 = gD3DEB.nVertexCount + 2;
  iVar5 = param_1 + -2;
  iVar2 = gD3DEB.nVertexCount;
  for (iVar3 = iVar5; 0 < iVar3; iVar3 = iVar3 + -1) {
    iVar2 = iVar2 + 1;
    local_8 = (undefined2)iVar1;
    *(undefined2 *)gD3DEB.lpIndexPointer = local_8;
    *(short *)((int)gD3DEB.lpIndexPointer + 2) = (short)iVar2;
    *(short *)((int)gD3DEB.lpIndexPointer + 4) = (short)iVar4;
    gD3DEB.lpIndexPointer = (void *)((int)gD3DEB.lpIndexPointer + 6);
    iVar4 = iVar4 + 1;
    Triangle_Counter = Triangle_Counter + 1;
  }
  gD3DEB.nVertexCount = gD3DEB.nVertexCount + param_1;
  TriCounter = TriCounter + iVar5;
  gD3DEB.nIndexCount = gD3DEB.nIndexCount + iVar5 * 3;
  CloseTLExecuteBuffer();
  return;
}
