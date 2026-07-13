/*
 * Entry: 004033c9
 * Name: AiPath::ShrinkPoints
 * Namespace: AiPath
 * Signature: void ShrinkPoints(AiPath * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiPath::ShrinkPoints(AiPath *this)

{
  SetPoints(this,this->pointCount);
  return;
}
