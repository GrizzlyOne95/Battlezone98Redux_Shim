/*
 * Entry: 004ea20d
 * Name: find_empty_seqno
 * Namespace: Global
 * Signature: short find_empty_seqno(long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

short __cdecl find_empty_seqno(long64 param_1)

{
  short sVar1;
  tagENTITY *ptVar2;
  short sVar3;
  
  sVar1 = empty_seqno;
  ptVar2 = find_entity(param_1,empty_seqno);
  sVar3 = empty_seqno;
  while (ptVar2 != (tagENTITY *)0x0) {
    sVar3 = sVar1 + 1;
    ptVar2 = find_entity(param_1,sVar3);
    sVar1 = sVar3;
  }
  empty_seqno = sVar3;
  return sVar1;
}
