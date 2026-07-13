/*
 * Entry: 004619ec
 * Name: ShortPath::Node::Make
 * Namespace: ShortPath::Node
 * Signature: Node * Make(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Node * __cdecl ShortPath::Node::Make(float param_1,float param_2)

{
  int extraout_EAX;
  int extraout_EAX_00;
  Node *pNVar1;
  int iVar2;
  float fVar3;
  
  fVar3 = (param_1 - Extents::e.x0) * 0.1;
  floor((double)((param_2 - Extents::e.z0) * 0.1),fVar3);
  _ftol2_sse();
  iVar2 = extraout_EAX;
  floor((double)fVar3);
  _ftol2_sse();
  pNVar1 = Make(extraout_EAX_00,iVar2);
  (pNVar1->pos).x = param_1;
  (pNVar1->pos).z = param_2;
  return pNVar1;
}
