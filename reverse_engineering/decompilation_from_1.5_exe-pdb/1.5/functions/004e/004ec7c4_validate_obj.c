/*
 * Entry: 004ec7c4
 * Name: validate_obj
 * Namespace: Global
 * Signature: _OBJ76 * validate_obj(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl validate_obj(_OBJ76 *param_1,char *param_2)

{
  if (param_1 != (_OBJ76 *)0x0) {
    if (param_1->gravestone != 1) {
      return param_1;
    }
    release_obj(param_1,param_2);
  }
  return (_OBJ76 *)0x0;
}
