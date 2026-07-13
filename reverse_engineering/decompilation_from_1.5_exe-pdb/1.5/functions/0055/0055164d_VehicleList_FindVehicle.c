/*
 * Entry: 0055164d
 * Name: VehicleList::FindVehicle
 * Namespace: VehicleList
 * Signature: char * FindVehicle(VehicleList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall VehicleList::FindVehicle(VehicleList *this,char *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  _s *p_Var6;
  bool bVar7;
  
  iVar5 = 0;
  if (0 < this->count) {
    p_Var6 = this->s;
    do {
      pbVar2 = (byte *)p_Var6->name;
      pbVar4 = (byte *)param_1;
      do {
        bVar1 = *pbVar4;
        bVar7 = bVar1 < *pbVar2;
        if (bVar1 != *pbVar2) {
LAB_00551688:
          iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_0055168d;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar4[1];
        bVar7 = bVar1 < pbVar2[1];
        if (bVar1 != pbVar2[1]) goto LAB_00551688;
        pbVar4 = pbVar4 + 2;
        pbVar2 = pbVar2 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_0055168d:
      if (iVar3 == 0) {
        return this->s[iVar5].label;
      }
      iVar5 = iVar5 + 1;
      p_Var6 = p_Var6 + 1;
    } while (iVar5 < this->count);
  }
  return (char *)0x0;
}
