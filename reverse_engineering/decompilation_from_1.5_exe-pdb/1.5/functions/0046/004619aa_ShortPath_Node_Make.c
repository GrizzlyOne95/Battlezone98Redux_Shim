/*
 * Entry: 004619aa
 * Name: ShortPath::Node::Make
 * Namespace: ShortPath::Node
 * Signature: Node * Make(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Node * __cdecl ShortPath::Node::Make(int param_1,int param_2)

{
  Node **ppNVar1;
  Node *pNVar2;
  
  ppNVar1 = Extents::cellNodes + Extents::dx * param_2 + param_1;
  if (*ppNVar1 == (Node *)0x0) {
    pNVar2 = operator_new(0x28);
    if (pNVar2 == (Node *)0x0) {
      pNVar2 = (Node *)0x0;
    }
    else {
      pNVar2 = Node(pNVar2,param_1,param_2);
    }
    *ppNVar1 = pNVar2;
  }
  return *ppNVar1;
}
