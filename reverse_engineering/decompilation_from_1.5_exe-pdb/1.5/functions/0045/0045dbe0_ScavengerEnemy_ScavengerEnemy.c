/*
 * Entry: 0045dbe0
 * Name: ScavengerEnemy::ScavengerEnemy
 * Namespace: ScavengerEnemy
 * Signature: ScavengerEnemy * ScavengerEnemy(ScavengerEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScavengerEnemy * __thiscall ScavengerEnemy::ScavengerEnemy(ScavengerEnemy *this)

{
  ScavengerProcess::ScavengerProcess((ScavengerProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
