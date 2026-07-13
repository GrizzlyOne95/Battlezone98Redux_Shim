/*
 * Entry: 005bc654
 * Name: getfreepos
 * Namespace: Global
 * Signature: Node * getfreepos(Table * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Node * __cdecl getfreepos(Table *param_1)

{
  Node *pNVar1;
  int in_ECX;
  
  pNVar1 = *(Node **)(in_ECX + 0x14);
  do {
    if (pNVar1 <= *(Node **)(in_ECX + 0x10)) {
      *(int *)(in_ECX + 0x14) = *(int *)(in_ECX + 0x14) + -0x20;
      return (Node *)0x0;
    }
    *(int *)(in_ECX + 0x14) = *(int *)(in_ECX + 0x14) + -0x20;
    pNVar1 = *(Node **)(in_ECX + 0x14);
  } while ((pNVar1->i_key).nk.tt != 0);
  return pNVar1;
}
