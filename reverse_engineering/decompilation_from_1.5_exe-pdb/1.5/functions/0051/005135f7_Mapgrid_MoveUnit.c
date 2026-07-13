/*
 * Entry: 005135f7
 * Name: Mapgrid_MoveUnit
 * Namespace: Global
 * Signature: void Mapgrid_MoveUnit(tagUNIT * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_MoveUnit(tagUNIT *param_1,int param_2,int param_3,int param_4,int param_5)

{
  if (((int)(param_4 + (param_4 >> 0x1f & 0xfU)) >> 4 !=
       (int)(param_2 + (param_2 >> 0x1f & 0xfU)) >> 4) ||
     ((int)(param_5 + (param_5 >> 0x1f & 0xfU)) >> 4 !=
      (int)(param_3 + (param_3 >> 0x1f & 0xfU)) >> 4)) {
    Mapgrid_RemoveUnit(param_1,param_4,param_5);
    Mapgrid_PutUnit(param_1,param_2,param_3);
  }
  return;
}
