/*
 * Entry: 005196a6
 * Name: AISchedule_PostLoad
 * Namespace: Global
 * Signature: void AISchedule_PostLoad(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AISchedule_PostLoad(void)

{
  Team *this;
  long lVar1;
  int iVar2;
  
  unitcycles = 0;
  prereqTypeCount = 0;
  iVar2 = 1;
  if (GameObject::userObject == (GameObject *)0x0) {
    myteam = 1;
  }
  else {
    myteam = (**(code **)(GameObject::userObject->_padding_ + 4))();
  }
  GetWorldExtents();
  FindPathStart();
  mapsizex = aiGridX1 - aiGridX0;
  mapsizey = aiGridZ1 - aiGridZ0;
  InitGameSpecifics();
  do {
    this = Team::GetTeam(iVar2);
    lVar1 = Team::GetScrap(this);
    Team_ChangeCredits(iVar2,lVar1);
    AI_UnspentCreditAdd(iVar2,lVar1);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  grid_rows = AI_map->AI_map_rows;
  grid_columns = AI_map->AI_map_columns;
  AOI::Init(aiGridX0,aiGridZ0,8,grid_rows,grid_columns);
  return;
}
