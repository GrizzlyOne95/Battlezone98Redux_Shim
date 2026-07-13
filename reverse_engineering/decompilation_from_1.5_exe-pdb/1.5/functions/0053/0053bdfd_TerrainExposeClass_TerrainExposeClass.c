/*
 * Entry: 0053bdfd
 * Name: TerrainExposeClass::TerrainExposeClass
 * Namespace: TerrainExposeClass
 * Signature: TerrainExposeClass * TerrainExposeClass(TerrainExposeClass * this, TerrainExposeClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TerrainExposeClass * __thiscall
TerrainExposeClass::TerrainExposeClass
          (TerrainExposeClass *this,TerrainExposeClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  SpecialItemClass::SpecialItemClass
            ((SpecialItemClass *)this,(SpecialItemClass *)param_1,
             CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
