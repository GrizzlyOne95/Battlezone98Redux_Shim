/*
 * Entry: 00518d1d
 * Name: Units_SOrderMove
 * Namespace: Global
 * Signature: void Units_SOrderMove(tagUNIT * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Units_SOrderMove(tagUNIT *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  VECTOR_3D local_18;
  GameObject *local_c;
  int local_8;
  
  local_c = (GameObject *)param_1->id;
  Obj2Unit(local_c);
  iVar1 = (param_1->tilepos).x;
  iVar2 = (param_1->tilepos).y;
  local_8 = (int)(iVar2 + (iVar2 >> 0x1f & 7U)) >> 3;
  iVar2 = (int)(param_3 + (param_3 >> 0x1f & 7U)) >> 3;
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 7U)) >> 3;
  AI_Team_GridCell_Debug(AI_map->team[param_1->team],iVar3,iVar2);
  if (((int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3 != iVar3) || (local_8 != iVar2)) {
    local_18.x = (float)(aiGridX0 + param_2) * 10.0;
    local_18.y = 0.0;
    local_18.z = (float)(aiGridZ0 + param_3) * 10.0;
    GameObject::SetCommand(local_c,CMD_GO,&local_18,0);
  }
  return;
}
