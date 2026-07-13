/*
 * Entry: 00481361
 * Name: IncCopy
 * Namespace: Global
 * Signature: int IncCopy(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IncCopy(_gas_object *param_1)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(in_EAX + 0x6c);
  iVar3 = 0;
  while ((copies[iVar2].prev != -1 && (iVar3 < 0x65))) {
    iVar2 = copies[iVar2].prev;
    iVar3 = iVar3 + 1;
  }
  iVar1 = copies[iVar2].count + 1;
  iVar3 = 0;
  while ((iVar2 != -1 && (iVar3 < 0x65))) {
    copies[iVar2].count = iVar1;
    iVar2 = copies[iVar2].next;
    iVar3 = iVar3 + 1;
  }
  return iVar1;
}
