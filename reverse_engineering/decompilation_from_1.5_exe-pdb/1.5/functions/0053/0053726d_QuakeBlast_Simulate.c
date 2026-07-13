/*
 * Entry: 0053726d
 * Name: QuakeBlast::Simulate
 * Namespace: QuakeBlast
 * Signature: void Simulate(QuakeBlast * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall QuakeBlast::Simulate(QuakeBlast *this,float param_1)

{
  EarthQuake::UpdateQuake(&earthQuake,this->magnitude);
  this->magnitude = this->magnitude - this->dropoff * param_1;
  Explosion::Simulate((Explosion *)this,param_1);
  return;
}
