/*
 * Entry: 004849f4
 * Name: CameraPod::Simulate
 * Namespace: CameraPod
 * Signature: void Simulate(CameraPod * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CameraPod::Simulate(CameraPod *this,float param_1)

{
  _OBJ76 *p_Var1;
  int iVar2;
  GameObject *pGVar3;
  bool bVar4;
  CameraPod *pCVar5;
  float fVar6;
  
  pGVar3 = GameObject::userObject;
  if ((*(byte *)(*(int *)&this->field_0x220 + 0x10c) & 4) != 0) goto LAB_00484aa9;
  if (GameObject::userObject == (GameObject *)0x0) {
LAB_00484a8a:
    fVar6 = *(float *)(*(int *)&this->field_0xec + 0x170) * 0.1;
  }
  else {
    bVar4 = GameObject::FriendP((GameObject *)this,GameObject::userObject);
    if (!bVar4) goto LAB_00484a8a;
    pCVar5 = (CameraPod *)GameObject::GetObj(pGVar3->targetHandle);
    if (pCVar5 != this) goto LAB_00484a8a;
    p_Var1 = pGVar3->obj;
    iVar2 = *(int *)&this->field_0xe8;
    fVar6 = Clamp((*(float *)(iVar2 + 0x20) * (p_Var1->transform).front_x +
                  *(float *)(iVar2 + 0x28) * (p_Var1->transform).front_z +
                  *(float *)(iVar2 + 0x24) * (p_Var1->transform).front_y) * -5.0,-1.0,1.0);
  }
  *(float *)(*(int *)&this->field_0x220 + 0xc4) = fVar6;
LAB_00484aa9:
  PowerUp::Simulate((PowerUp *)this,param_1);
  return;
}
