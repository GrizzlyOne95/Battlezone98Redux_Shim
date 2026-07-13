/*
 * Entry: 0053be9e
 * Name: TerrainExposeClass::Build
 * Namespace: TerrainExposeClass
 * Signature: Weapon * Build(TerrainExposeClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall TerrainExposeClass::Build(TerrainExposeClass *this,_OBJ76 *param_1)

{
  TerrainExpose *pTVar1;
  
  pTVar1 = operator_new(200);
  if (pTVar1 == (TerrainExpose *)0x0) {
    pTVar1 = (TerrainExpose *)0x0;
  }
  else {
    pTVar1 = TerrainExpose::TerrainExpose(pTVar1,param_1,this);
  }
  return (Weapon *)pTVar1;
}
