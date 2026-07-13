/*
 * Entry: 0040d401
 * Name: ArtilleryEnemy::ArtilleryEnemy
 * Namespace: ArtilleryEnemy
 * Signature: ArtilleryEnemy * ArtilleryEnemy(ArtilleryEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ArtilleryEnemy * __thiscall ArtilleryEnemy::ArtilleryEnemy(ArtilleryEnemy *this)

{
  ArtilleryProcess::ArtilleryProcess((ArtilleryProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
