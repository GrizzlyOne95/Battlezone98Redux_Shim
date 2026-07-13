/*
 * Entry: 0044f320
 * Name: PathPoint::PathPoint
 * Namespace: PathPoint
 * Signature: PathPoint * PathPoint(PathPoint * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __thiscall PathPoint::PathPoint(PathPoint *this)

{
  (this->point).z = 0.0;
  (this->point).x = 0.0;
  this->strip = (Strip *)0x0;
  this->seqNo = 0;
  return this;
}
