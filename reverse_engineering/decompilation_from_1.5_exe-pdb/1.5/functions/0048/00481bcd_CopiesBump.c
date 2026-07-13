/*
 * Entry: 00481bcd
 * Name: CopiesBump
 * Namespace: Global
 * Signature: int CopiesBump(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CopiesBump(_gas_object *param_1)

{
  int iVar1;
  int unaff_ESI;
  _gas_object *unaff_retaddr;
  
  if (*(int *)(unaff_ESI + 0x3c) == 1) {
    return 0;
  }
  iVar1 = CountCopies(unaff_retaddr);
  return (uint)(*(int *)(unaff_ESI + 0x38) < iVar1);
}
