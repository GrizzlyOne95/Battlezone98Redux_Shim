/*
 * Entry: 00457443
 * Name: PersonGetIn::PersonGetIn
 * Namespace: PersonGetIn
 * Signature: PersonGetIn * PersonGetIn(PersonGetIn * this, Craft * param_1, GameObject * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PersonGetIn * __thiscall
PersonGetIn::PersonGetIn(PersonGetIn *this,Craft *param_1,GameObject *param_2,VECTOR_3D *param_3)

{
  int iVar1;
  
  GotoTask::GotoTask((GotoTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  *(float *)&this->field_0x144 = param_3->x;
  *(float *)&this->field_0x148 = param_3->y;
  *(float *)&this->field_0x14c = param_3->z;
  iVar1 = *(int *)&this->field_0x138;
  *(float *)(*(int *)(iVar1 + 8) + -8 + *(int *)(iVar1 + 4) * 8) = param_3->x;
  iVar1 = *(int *)&this->field_0x138;
  *(float *)(*(int *)(iVar1 + 8) + -4 + *(int *)(iVar1 + 4) * 8) = param_3->z;
  return this;
}
