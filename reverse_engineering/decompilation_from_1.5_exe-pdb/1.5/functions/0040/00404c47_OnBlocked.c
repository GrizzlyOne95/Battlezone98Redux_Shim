/*
 * Entry: 00404c47
 * Name: OnBlocked
 * Namespace: Global
 * Signature: bool OnBlocked(VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl OnBlocked(VECTOR_3D *param_1)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = CellType(param_1->x,param_1->z);
  iVar2 = Material((uint)bVar1);
  if ((iVar2 != 6) && (iVar2 != 5)) {
    return false;
  }
  return true;
}
