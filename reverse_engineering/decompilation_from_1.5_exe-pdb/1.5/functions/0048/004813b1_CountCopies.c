/*
 * Entry: 004813b1
 * Name: CountCopies
 * Namespace: Global
 * Signature: int CountCopies(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CountCopies(_gas_object *param_1)

{
  bool bVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(in_EAX + 0x6c);
  iVar2 = 0;
  do {
    iVar3 = iVar4;
    if (copies[iVar3].prev == -1) break;
    bVar1 = iVar2 < 0x65;
    iVar4 = copies[iVar3].prev;
    iVar2 = iVar2 + 1;
  } while (bVar1);
  iVar2 = 0;
  iVar4 = 0;
  while ((iVar3 != -1 && (iVar4 < 0x65))) {
    iVar2 = iVar2 + 1;
    iVar3 = copies[iVar3].next;
    iVar4 = iVar4 + 1;
  }
  return iVar2;
}
