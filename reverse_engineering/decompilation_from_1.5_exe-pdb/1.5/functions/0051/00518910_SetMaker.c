/*
 * Entry: 00518910
 * Name: SetMaker
 * Namespace: Global
 * Signature: void SetMaker(GameObjectClass * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetMaker(GameObjectClass *param_1,int param_2)

{
  bool bVar1;
  GameObjectClass *in_EAX;
  tagBUILDINGTYPE *ptVar2;
  tagUNITTYPE *ptVar3;
  GameObjectClass *unaff_EBX;
  GameObjectClass *unaff_ESI;
  ushort unaff_DI;
  
  bVar1 = IsBuilding(in_EAX);
  if (bVar1) {
    ptVar2 = Class2BuildingType(unaff_ESI,(tagBUILDINGTYPE *)unaff_EBX);
    ptVar2->makers[0] = unaff_DI;
    return;
  }
  ptVar3 = Class2UnitType(unaff_EBX);
  (ptVar3->prereq).makers[0] = unaff_DI;
  return;
}
