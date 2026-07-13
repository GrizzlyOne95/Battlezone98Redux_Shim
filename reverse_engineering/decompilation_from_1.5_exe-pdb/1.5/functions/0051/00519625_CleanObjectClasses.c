/*
 * Entry: 00519625
 * Name: CleanObjectClasses
 * Namespace: Global
 * Signature: void CleanObjectClasses(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CleanObjectClasses(void)

{
  uint uVar1;
  ObjectClassInfo **ppOVar2;
  
  uVar1 = (int)vehicleClassList._Mylast - (int)vehicleClassList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppOVar2 = std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::back
                        (&vehicleClassList);
    operator_delete(*ppOVar2);
    std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::pop_back(&vehicleClassList);
    uVar1 = (int)vehicleClassList._Mylast - (int)vehicleClassList._Myfirst;
  }
  uVar1 = (int)buildingClassList._Mylast - (int)buildingClassList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppOVar2 = std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::back
                        (&buildingClassList);
    operator_delete(*ppOVar2);
    std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::pop_back(&buildingClassList);
    uVar1 = (int)buildingClassList._Mylast - (int)buildingClassList._Myfirst;
  }
  return;
}
