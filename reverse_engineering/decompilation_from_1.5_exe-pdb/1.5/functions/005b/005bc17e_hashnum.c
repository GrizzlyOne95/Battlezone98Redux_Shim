/*
 * Entry: 005bc17e
 * Name: hashnum
 * Namespace: Global
 * Signature: Node * hashnum(Table * param_1, double param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Node * __cdecl hashnum(Table *param_1,double param_2)

{
  int unaff_ESI;
  int in_stack_00000008;
  
  if ((double)CONCAT44(in_stack_00000008,param_1) == 0.0) {
    return *(Node **)(unaff_ESI + 0x10);
  }
  return (Node *)(((uint)((int)&param_1->next + in_stack_00000008) %
                  ((1 << (*(byte *)(unaff_ESI + 7) & 0x1f)) - 1U | 1)) * 0x20 +
                 *(int *)(unaff_ESI + 0x10));
}
