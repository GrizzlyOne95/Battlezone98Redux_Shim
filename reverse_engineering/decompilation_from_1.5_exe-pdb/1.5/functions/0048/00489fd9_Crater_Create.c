/*
 * Entry: 00489fd9
 * Name: Crater_Create
 * Namespace: Global
 * Signature: void Crater_Create(float param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Crater_Create(float param_1,float param_2,float param_3)

{
  Crater *pCVar1;
  
  pCVar1 = operator_new(0xa0);
  if (pCVar1 == (Crater *)0x0) {
    pCVar1 = (Crater *)0x0;
  }
  else {
    pCVar1 = Crater::Crater(pCVar1,param_1,param_2,param_3);
  }
  DistributedObject::SetLocal((DistributedObject *)pCVar1);
  return;
}
