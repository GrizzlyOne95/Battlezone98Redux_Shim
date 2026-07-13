/*
 * Entry: 0046194a
 * Name: ShortPath::Node::Node
 * Namespace: ShortPath::Node
 * Signature: Node * Node(Node * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Node * __thiscall ShortPath::Node::Node(Node *this,int param_1,int param_2)

{
  float fVar1;
  
  (this->cell).x = param_1;
  (this->cell).z = param_2;
  (this->pos).x = (float)param_1 * 10.0 + Extents::e.x0 + 5.0;
  fVar1 = (float)param_2 * 10.0 + Extents::e.z0;
  this->visited = false;
  this->open = false;
  this->prev = (Node *)0x0;
  (this->pos).z = fVar1 + 5.0;
  this->g = -1.0;
  this->costFactor = 1.0;
  return this;
}
