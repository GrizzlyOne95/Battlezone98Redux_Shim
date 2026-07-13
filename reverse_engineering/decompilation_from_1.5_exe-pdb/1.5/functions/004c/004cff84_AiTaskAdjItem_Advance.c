/*
 * Entry: 004cff84
 * Name: AiTaskAdjItem::Advance
 * Namespace: AiTaskAdjItem
 * Signature: bool Advance(AiTaskAdjItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AiTaskAdjItem::Advance(AiTaskAdjItem *this)

{
  this->var = this->var + 1;
  if (this->var == 0xd) {
    return false;
  }
  if (0xd < (uint)this->var) {
    this->var = 0;
  }
  return true;
}
