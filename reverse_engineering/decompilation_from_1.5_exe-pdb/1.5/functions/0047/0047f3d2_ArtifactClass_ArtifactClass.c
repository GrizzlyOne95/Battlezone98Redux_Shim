/*
 * Entry: 0047f3d2
 * Name: ArtifactClass::ArtifactClass
 * Namespace: ArtifactClass
 * Signature: ArtifactClass * ArtifactClass(ArtifactClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ArtifactClass * __thiscall ArtifactClass::ArtifactClass(ArtifactClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x41525449;
  *(char **)&this->field_0x24 = "artifact";
  return this;
}
