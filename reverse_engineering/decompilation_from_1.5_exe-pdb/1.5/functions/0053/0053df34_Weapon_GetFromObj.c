/*
 * Entry: 0053df34
 * Name: Weapon::GetFromObj
 * Namespace: Weapon
 * Signature: Weapon * GetFromObj(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __cdecl Weapon::GetFromObj(_OBJ76 *param_1)

{
  if (param_1 != (_OBJ76 *)0x0) {
    return param_1->class_ptr;
  }
  return (Weapon *)0x0;
}
