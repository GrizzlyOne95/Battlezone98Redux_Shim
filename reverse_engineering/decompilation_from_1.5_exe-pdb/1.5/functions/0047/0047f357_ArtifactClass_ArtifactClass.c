/*
 * Entry: 0047f357
 * Name: ArtifactClass::ArtifactClass
 * Namespace: ArtifactClass
 * Signature: ArtifactClass * ArtifactClass(ArtifactClass * this, ArtifactClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ArtifactClass * __thiscall
ArtifactClass::ArtifactClass(ArtifactClass *this,ArtifactClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}
