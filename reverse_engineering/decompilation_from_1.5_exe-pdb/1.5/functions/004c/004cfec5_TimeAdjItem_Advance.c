/*
 * Entry: 004cfec5
 * Name: TimeAdjItem::Advance
 * Namespace: TimeAdjItem
 * Signature: bool Advance(TimeAdjItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TimeAdjItem::Advance(TimeAdjItem *this)

{
  bool bVar1;
  
  bVar1 = this->in == false;
  this->in = bVar1;
  return bVar1;
}
