/*
 * Entry: 0044ead0
 * Name: Strip::operator=
 * Namespace: Strip
 * Signature: Strip * operator=(Strip * this, Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip * __thiscall Strip::operator=(Strip *this,Strip *param_1)

{
  this->x0 = param_1->x0;
  this->z0 = param_1->z0;
  this->x1 = param_1->x1;
  this->z1 = param_1->z1;
  this->material = param_1->material;
  this->seqNo = param_1->seqNo;
  this->neighbor = param_1->neighbor;
  this->edge = param_1->edge;
  this->link = param_1->link;
  this->open = param_1->open;
  this->backward = param_1->backward;
  this->detour = param_1->detour;
  this->visited = param_1->visited;
  this->x = param_1->x;
  this->z = param_1->z;
  this->g = param_1->g;
  this->prev = param_1->prev;
  this->next = param_1->next;
  return this;
}
