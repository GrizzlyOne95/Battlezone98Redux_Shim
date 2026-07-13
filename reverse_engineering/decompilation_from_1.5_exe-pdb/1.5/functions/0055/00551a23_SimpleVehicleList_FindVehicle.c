/*
 * Entry: 00551a23
 * Name: SimpleVehicleList::FindVehicle
 * Namespace: SimpleVehicleList
 * Signature: char * FindVehicle(SimpleVehicleList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall SimpleVehicleList::FindVehicle(SimpleVehicleList *this,char *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  _s *p_Var5;
  bool bVar6;
  int local_8;
  
  local_8 = 0;
  if (0 < this->count) {
    p_Var5 = this->s;
    do {
      pbVar2 = (byte *)p_Var5->name;
      pbVar4 = (byte *)param_1;
      do {
        bVar1 = *pbVar4;
        bVar6 = bVar1 < *pbVar2;
        if (bVar1 != *pbVar2) {
LAB_00551a5c:
          iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_00551a61;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar4[1];
        bVar6 = bVar1 < pbVar2[1];
        if (bVar1 != pbVar2[1]) goto LAB_00551a5c;
        pbVar4 = pbVar4 + 2;
        pbVar2 = pbVar2 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_00551a61:
      if (iVar3 == 0) {
        return this->s[local_8].label;
      }
      local_8 = local_8 + 1;
      p_Var5 = p_Var5 + 1;
    } while (local_8 < this->count);
  }
  return (char *)0x0;
}
