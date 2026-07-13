/*
 * Entry: 004810f6
 * Name: InitGASObject
 * Namespace: Global
 * Signature: void InitGASObject(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitGASObject(_gas_object *param_1)

{
  _gas_object *p_Var1;
  
  p_Var1 = param_1->next;
  memset(param_1,0,0x84);
  param_1->next = p_Var1;
  InitGASCtrl(&param_1->gc);
  InitGASPrep(&param_1->gpi);
  param_1->Duplicated = 0;
  param_1->count = -1;
  (param_1->storage).gsBytes.gsChar1 = -1;
  return;
}
