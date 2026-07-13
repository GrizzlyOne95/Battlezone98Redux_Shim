/*
 * Entry: 00461a4d
 * Name: ShortPath::Neighbors::HeightChange
 * Namespace: ShortPath::Neighbors
 * Signature: float HeightChange(Node * param_1, Node * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ShortPath::Neighbors::HeightChange(Node *param_1,Node *param_2)

{
  float fVar1;
  float fVar2;
  
  fVar1 = Terrain_FindFloor((double)(param_1->pos).x,(double)(param_1->pos).z);
  fVar2 = Terrain_FindFloor((double)(param_2->pos).x,(double)(param_2->pos).z);
  return fVar2 - fVar1;
}
