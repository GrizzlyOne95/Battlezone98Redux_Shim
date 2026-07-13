/*
 * Entry: 004ee0c7
 * Name: Spinner_RegClsn
 * Namespace: Global
 * Signature: int Spinner_RegClsn(_OBJ76 * param_1, _OBJ76 * param_2, CLSN_INFO * param_3, CLSN_INFO * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Spinner_RegClsn(_OBJ76 *param_1,_OBJ76 *param_2,CLSN_INFO *param_3,CLSN_INFO *param_4)

{
  EULER *pEVar1;
  EULER local_58;
  VECTOR_3D local_10;
  
  pEVar1 = ClassGetEuler(&local_58,param_2);
  local_10.x = (pEVar1->v).x;
  local_10.y = (pEVar1->v).y;
  local_10.z = (pEVar1->v).z;
  Damage_Resolve(param_1,param_2,&local_10,&param_3->normal,&param_3->point);
  return 1;
}
