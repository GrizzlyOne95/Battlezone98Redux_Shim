/*
 * Entry: 0052579b
 * Name: GetObjectPtrs
 * Namespace: Global
 * Signature: void GetObjectPtrs(ObjectType * param_1, ObjectType * * param_2, long param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetObjectPtrs(ObjectType *param_1,ObjectType **param_2,long param_3,long param_4)

{
  for (; param_3 != 0; param_3 = param_3 + -1) {
    *param_2 = param_1;
    param_1 = param_1 + param_4;
    param_2 = param_2 + 1;
  }
  return;
}
