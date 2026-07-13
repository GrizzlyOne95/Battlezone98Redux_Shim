/*
 * Entry: 0047bfdb
 * Name: AnimBuildingClass::AnimBuildingClass
 * Namespace: AnimBuildingClass
 * Signature: AnimBuildingClass * AnimBuildingClass(AnimBuildingClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimBuildingClass * __thiscall AnimBuildingClass::AnimBuildingClass(AnimBuildingClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x414e4d42;
  *(char **)&this->field_0x24 = "animbuilding";
  return this;
}
