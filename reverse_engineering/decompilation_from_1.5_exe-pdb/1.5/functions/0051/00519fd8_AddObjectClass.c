/*
 * Entry: 00519fd8
 * Name: AddObjectClass
 * Namespace: Global
 * Signature: void AddObjectClass(GameObjectClass * param_1, GameObjectClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddObjectClass(GameObjectClass *param_1,GameObjectClass *param_2)

{
  GameObjectClass *pGVar1;
  bool bVar2;
  ObjectClassInfo *pOVar3;
  vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this;
  GameObjectClass *unaff_EDI;
  int iVar4;
  ObjectClassInfo *local_8;
  
  bVar2 = FindObjectClass(param_2,unaff_EDI);
  if (!bVar2) {
    pOVar3 = operator_new(8);
    local_8 = (ObjectClassInfo *)0x0;
    if (pOVar3 != (ObjectClassInfo *)0x0) {
      pOVar3->objClass = (GameObjectClass *)0x0;
      pOVar3->buildClass = (GameObjectClass *)0x0;
      local_8 = pOVar3;
    }
    local_8->objClass = param_1;
    local_8->buildClass = param_2;
    bVar2 = IsBuilding(param_1);
    this = &buildingClassList;
    if (!bVar2) {
      this = &vehicleClassList;
    }
    std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::push_back(this,&local_8);
    if ((param_1->sig != 0x434e5354) && (bVar2 = BuildingVehicle(param_1->sig), !bVar2)) {
      return;
    }
    iVar4 = 0;
    do {
      pGVar1 = (GameObjectClass *)param_1[2].weaponClass[iVar4 + 0xe];
      if (((pGVar1 != (GameObjectClass *)0x0) && (pGVar1->class_id != CLASS_ID_SIGN)) &&
         (pGVar1->class_id != CLASS_ID_SCRAP)) {
        AddObjectClass(pGVar1,param_1);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 9);
  }
  return;
}
