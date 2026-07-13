/*
 * Entry: 0051893a
 * Name: Units_GetTypePtr
 * Namespace: Global
 * Signature: tagUNITTYPE * Units_GetTypePtr(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagUNITTYPE * __cdecl Units_GetTypePtr(int param_1)

{
  tagUNITTYPE *ptVar1;
  
  std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator[]
            (&vehicleClassList,param_1);
  ptVar1 = Class2UnitType((GameObjectClass *)param_1);
  return ptVar1;
}
