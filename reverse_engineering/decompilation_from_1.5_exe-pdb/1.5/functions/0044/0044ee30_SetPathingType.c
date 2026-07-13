/*
 * Entry: 0044ee30
 * Name: SetPathingType
 * Namespace: Global
 * Signature: void SetPathingType(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetPathingType(int param_1,int param_2)

{
  Team *this;
  ulong uVar1;
  
  curPathingType = param_1;
  curPathingTeam = param_2;
  this = Team::GetTeam(param_2);
  uVar1 = Team::GetAllies(this);
  materialCost[0] = 1.0;
  curPathingEnemies = ~(ushort)uVar1;
  materialCost[1] = 2.0;
  materialCost[2] = 10.0;
  materialCost[6] = 99999.0;
  materialCost[5] = 99999.0;
  materialCost[4] = 10.0;
  materialCost[3] = 99999.0;
  if ((curPathingType != 1) && (curPathingType != 2)) {
    if (curPathingType != 3) {
      materialCost[3] = lavaFactor;
      return;
    }
    materialCost[3] = 1.1;
  }
  return;
}
