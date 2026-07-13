/*
 * Entry: 00532c1c
 * Name: Ordnance::GetFromObj
 * Namespace: Ordnance
 * Signature: Ordnance * GetFromObj(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __cdecl Ordnance::GetFromObj(_OBJ76 *param_1)

{
  if (param_1 != (_OBJ76 *)0x0) {
    return param_1->class_ptr;
  }
  return (Ordnance *)0x0;
}
