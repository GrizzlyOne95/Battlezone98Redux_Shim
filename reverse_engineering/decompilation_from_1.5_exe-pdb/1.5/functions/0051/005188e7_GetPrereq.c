/*
 * Entry: 005188e7
 * Name: GetPrereq
 * Namespace: Global
 * Signature: int GetPrereq(GameObjectClass * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPrereq(GameObjectClass *param_1)

{
  bool bVar1;
  GameObjectClass *in_EAX;
  tagBUILDINGTYPE *ptVar2;
  tagUNITTYPE *ptVar3;
  GameObjectClass *unaff_EBX;
  GameObjectClass *unaff_ESI;
  
  bVar1 = IsBuilding(in_EAX);
  if (bVar1) {
    ptVar2 = Class2BuildingType(unaff_ESI,(tagBUILDINGTYPE *)unaff_EBX);
    return (uint)ptVar2->prereqtype;
  }
  ptVar3 = Class2UnitType(unaff_EBX);
  return (uint)(ptVar3->prereq).prereqtype;
}
