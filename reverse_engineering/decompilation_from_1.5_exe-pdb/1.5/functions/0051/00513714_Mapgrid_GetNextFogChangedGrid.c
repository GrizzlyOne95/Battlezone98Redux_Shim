/*
 * Entry: 00513714
 * Name: Mapgrid_GetNextFogChangedGrid
 * Namespace: Global
 * Signature: int Mapgrid_GetNextFogChangedGrid(int * param_1, int * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Mapgrid_GetNextFogChangedGrid(int *param_1,int *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  int iVar6;
  int local_8;
  
  iVar2 = curfoggridcell;
  local_8 = 0;
  iVar6 = mapgridysize * mapgridxsize;
  bVar5 = '\x01' << ((byte)param_3 & 0x1f);
  Debug_Assert((uint)((uint)param_3 < 0x10),0x10d,".\\Schedule\\Mapgrid.c",
               "team>=0 && team<TEAM_MAXTEAMS");
  while( true ) {
    iVar3 = curfoggridcell / mapgridxsize;
    iVar4 = curfoggridcell % mapgridxsize;
    bVar1 = mapgrid[iVar3][iVar4].fogchanged;
    if ((bVar5 & bVar1) != 0) {
      local_8 = 1;
      mapgrid[iVar3][iVar4].fogchanged = ~bVar5 & bVar1;
    }
    curfoggridcell = curfoggridcell + 1U & -(uint)(curfoggridcell != iVar6 - 1U);
    if (local_8 != 0) break;
    if (curfoggridcell == iVar2) {
      return 0;
    }
  }
  *param_1 = iVar4;
  *param_2 = iVar3;
  return local_8;
}
