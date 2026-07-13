/*
 * Entry: 00537258
 * Name: QuakeBlast::Cleanup
 * Namespace: QuakeBlast
 * Signature: void Cleanup(QuakeBlast * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall QuakeBlast::Cleanup(QuakeBlast *this)

{
  EarthQuake::StopQuake(&earthQuake);
  Explosion::Cleanup((Explosion *)this);
  return;
}
