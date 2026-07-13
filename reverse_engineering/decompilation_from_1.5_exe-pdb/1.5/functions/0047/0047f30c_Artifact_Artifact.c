/*
 * Entry: 0047f30c
 * Name: Artifact::Artifact
 * Namespace: Artifact
 * Signature: Artifact * Artifact(Artifact * this, _OBJ76 * param_1, ArtifactClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Artifact * __thiscall Artifact::Artifact(Artifact *this,_OBJ76 *param_1,ArtifactClass *param_2)

{
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  *(undefined4 *)&this->field_0x218 = *(undefined4 *)&this->field_0xe8;
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  return this;
}
