/*
 * Entry: 00517c44
 * Name: Squad_Send_Attack
 * Namespace: Global
 * Signature: void Squad_Send_Attack(Mapgrid_Goal * param_1, SquadUnitInfo * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Squad_Send_Attack(Mapgrid_Goal *param_1,SquadUnitInfo *param_2,int param_3)

{
  int in_EAX;
  int iVar1;
  Mapgrid_Goal *pMVar2;
  SquadUnitInfo *unaff_EDI;
  bool bVar3;
  VECTOR_3D local_1c;
  float local_10;
  GameObject *local_c;
  Mapgrid_Goal *local_8;
  
  pMVar2 = (Mapgrid_Goal *)0x0;
  bVar3 = param_1 == (Mapgrid_Goal *)0x0;
  local_8 = (Mapgrid_Goal *)0x0;
  if (0 < (int)param_1) {
    do {
      pMVar2 = local_8;
      if ((unaff_EDI[(int)local_8].send != false) &&
         (iVar1 = (**(code **)(unaff_EDI[(int)local_8].craft)->_padding_)(),
         *(int *)(iVar1 + 0x20) == 0x57494e47)) break;
      pMVar2 = (Mapgrid_Goal *)((int)&pMVar2->_padding_ + 1);
      local_8 = pMVar2;
    } while ((int)pMVar2 < (int)param_1);
    bVar3 = pMVar2 == param_1;
  }
  if (!bVar3) {
    local_c = (GameObject *)(aiGridX0 + *(int *)(in_EAX + 0x44) * 8);
    ScheduleGlue_Compute_Staging_Area
              (unaff_EDI,(int)param_1,(float)(int)local_c * 10.0 + 40.0,
               (float)(aiGridZ0 + *(int *)(in_EAX + 0x40) * 8) * 10.0 + 40.0,&local_1c,&local_10);
    local_c = GameObjectHandle::GetObj(*(int *)(in_EAX + 0x84));
    if ((local_c != (GameObject *)0x0) && (local_c->aiProcess != (AiProcess *)0x0)) {
      while ((int)pMVar2 < (int)param_1) {
        if (unaff_EDI[(int)pMVar2].send != false) {
          iVar1 = (**(code **)(unaff_EDI[(int)pMVar2].craft)->_padding_)();
          if (*(int *)(iVar1 + 0x20) == 0x57494e47) {
            GameObject::SetCommand((GameObject *)unaff_EDI[(int)pMVar2].craft,CMD_ATTACK,local_c);
            unaff_EDI[(int)pMVar2].send = false;
          }
        }
        pMVar2 = (Mapgrid_Goal *)((int)&local_8->_padding_ + 1);
        local_8 = pMVar2;
      }
    }
  }
  return;
}
