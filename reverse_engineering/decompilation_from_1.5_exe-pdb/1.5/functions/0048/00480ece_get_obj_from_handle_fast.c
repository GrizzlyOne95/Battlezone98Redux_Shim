/*
 * Entry: 00480ece
 * Name: get_obj_from_handle_fast
 * Namespace: Global
 * Signature: _OBJ76 * get_obj_from_handle_fast(int param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl get_obj_from_handle_fast(int param_1,_OBJ76 *param_2)

{
  if ((param_1 != 0) && (param_2 != (_OBJ76 *)0x0)) {
    return (_OBJ76 *)(~-(uint)((param_2->objHandle).handle != param_1) & (uint)param_2);
  }
  return (_OBJ76 *)0x0;
}
