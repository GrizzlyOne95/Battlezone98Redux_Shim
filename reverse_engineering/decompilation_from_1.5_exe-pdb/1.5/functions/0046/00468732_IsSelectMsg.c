/*
 * Entry: 00468732
 * Name: IsSelectMsg
 * Namespace: Global
 * Signature: bool IsSelectMsg(UnitMsg param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsSelectMsg(UnitMsg param_1)

{
  if ((-1 < (int)param_1) && ((int)param_1 < 10)) {
    return true;
  }
  return false;
}
