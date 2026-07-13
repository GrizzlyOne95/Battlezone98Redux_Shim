/*
 * Entry: 00481f38
 * Name: DeleteGASObject
 * Namespace: Global
 * Signature: void DeleteGASObject(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DeleteGASObject(_gas_object *param_1)

{
  _gas_object *p_Var1;
  
  StopGASObject(param_1);
  CloseGASObject(param_1);
  p_Var1 = firstSound;
  if (param_1 == firstSound) {
    firstSound = param_1->next;
  }
  else {
    for (; p_Var1->next != param_1; p_Var1 = p_Var1->next) {
    }
    p_Var1->next = param_1->next;
  }
  free(param_1);
  return;
}
