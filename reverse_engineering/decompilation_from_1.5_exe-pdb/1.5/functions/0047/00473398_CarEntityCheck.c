/*
 * Entry: 00473398
 * Name: CarEntityCheck
 * Namespace: Global
 * Signature: int CarEntityCheck(tagENTITY * param_1, tagENTITY * param_2, float param_3, CLSN_INFO * param_4, CLSN_INFO * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
CarEntityCheck(tagENTITY *param_1,tagENTITY *param_2,float param_3,CLSN_INFO *param_4,
              CLSN_INFO *param_5)

{
  CLSN_TYPE CVar1;
  int iVar2;
  
  CVar1 = param_2->cType;
  if (CVar1 == CLSN_TYPE_CAR) {
    iVar2 = CarCarCheck(param_1,param_2,param_3,param_4,param_5);
  }
  else if (CVar1 == CLSN_TYPE_SPHERE) {
    iVar2 = CarSphereCheck(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    if (CVar1 != CLSN_TYPE_CHILDREN) {
      return 0;
    }
    iVar2 = CarHierarchyCheck(param_1,param_2,param_3,param_4,param_5);
  }
  return iVar2;
}
