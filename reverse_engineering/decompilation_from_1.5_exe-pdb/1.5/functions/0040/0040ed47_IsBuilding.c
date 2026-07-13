/*
 * Entry: 0040ed47
 * Name: IsBuilding
 * Namespace: Global
 * Signature: int IsBuilding(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsBuilding(_OBJ76 *param_1)

{
  OBJECT_CLASS_T OVar1;
  
  OVar1 = param_1->class_id;
  if ((((OVar1 != CLASS_ID_STRUCTURE1) && (OVar1 != CLASS_ID_SIGN)) && (OVar1 != CLASS_ID_SCRAP)) &&
     (OVar1 != CLASS_ID_STRUCTURE2)) {
    return 0;
  }
  return 1;
}
