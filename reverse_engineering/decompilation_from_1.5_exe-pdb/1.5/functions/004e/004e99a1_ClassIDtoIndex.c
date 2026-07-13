/*
 * Entry: 004e99a1
 * Name: ClassIDtoIndex
 * Namespace: Global
 * Signature: int ClassIDtoIndex(OBJECT_CLASS_T param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ClassIDtoIndex(OBJECT_CLASS_T param_1)

{
  uint uVar1;
  CLASS_FUNCTIONS *pCVar2;
  OBJECT_CLASS_T in_EDX;
  
  if ((in_EDX < (CLASS_ID_BRIDGE|CLASS_ID_VEHICLE)) && (funk[in_EDX].class_id == in_EDX)) {
    return in_EDX;
  }
  pCVar2 = funk;
  uVar1 = 0;
  do {
    if (pCVar2->class_id == in_EDX) {
      return uVar1;
    }
    uVar1 = uVar1 + 1;
    pCVar2 = pCVar2 + 1;
  } while (uVar1 < 0xe);
  return 0;
}
