/*
 * Entry: 0051fdf0
 * Name: AddVertex
 * Namespace: Global
 * Signature: int AddVertex(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddVertex(int param_1,int param_2)

{
  VECTOR_3D *pVVar1;
  ushort uVar2;
  int iVar3;
  int in_ECX;
  int in_EDX;
  
  iVar3 = Terrain.Vertex_Counter;
  uVar2 = *(ushort *)
           (*(int *)(((int)(in_ECX + 0xc00U) >> 5 & 0xfffffffcU) + 0xcc3964 +
                    ((int)(in_EDX + 0xc00U) >> 7) * 0x200) +
           ((in_EDX + 0xc00U & 0x7f) * 0x80 + (in_ECX + 0xc00U & 0x7f)) * 2);
  pVVar1 = Vertex_Pool + Terrain.Vertex_Counter;
  Terrain.Vertex_Counter = Terrain.Vertex_Counter + 1;
  pVVar1->z = (float)in_EDX;
  pVVar1->x = (float)in_ECX;
  pVVar1->y = (float)(uVar2 & 0xfff);
  return iVar3;
}
