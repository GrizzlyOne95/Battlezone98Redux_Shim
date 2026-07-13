/*
 * Entry: 004ed399
 * Name: Pointer_Ordering
 * Namespace: Global
 * Signature: int Pointer_Ordering(_OBJ76 * * param_1, _OBJ76 * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Pointer_Ordering(_OBJ76 **param_1,_OBJ76 **param_2)

{
  uint uVar1;
  uint uVar2;
  uint *unaff_ESI;
  uint *unaff_EDI;
  
  uVar1 = *unaff_ESI;
  uVar2 = *unaff_EDI;
  if (uVar1 < uVar2) {
    *unaff_EDI = uVar1;
    *unaff_ESI = uVar2;
  }
  return (uint)(uVar1 < uVar2);
}
