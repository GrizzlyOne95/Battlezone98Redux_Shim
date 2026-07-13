/*
 * Entry: 0053bddd
 * Name: TerrainExposeClass::TerrainExposeClass
 * Namespace: TerrainExposeClass
 * Signature: TerrainExposeClass * TerrainExposeClass(TerrainExposeClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TerrainExposeClass * __thiscall TerrainExposeClass::TerrainExposeClass(TerrainExposeClass *this)

{
  SpecialItemClass::SpecialItemClass((SpecialItemClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x54525850;
  *(char **)&this->field_0x10 = "terrainexpose";
  return this;
}
