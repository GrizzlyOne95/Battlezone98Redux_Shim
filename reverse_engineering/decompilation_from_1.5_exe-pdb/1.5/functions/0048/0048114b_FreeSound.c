/*
 * Entry: 0048114b
 * Name: FreeSound
 * Namespace: Global
 * Signature: void FreeSound(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FreeSound(_gas_object *param_1)

{
  _gas_object *p_Var1;
  _gas_object *in_ECX;
  
  p_Var1 = firstSound;
  if (in_ECX == firstSound) {
    firstSound = in_ECX->next;
  }
  else {
    for (; p_Var1->next != in_ECX; p_Var1 = p_Var1->next) {
    }
    p_Var1->next = in_ECX->next;
  }
  free(in_ECX);
  return;
}
