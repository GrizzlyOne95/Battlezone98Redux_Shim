/*
 * Entry: 0046045c
 * Name: BuildAt
 * Namespace: Global
 * Signature: void BuildAt(int param_1, char * param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildAt(int param_1,char *param_2,char *param_3,int param_4)

{
  ConstructionRig *this;
  AiPath *pAVar1;
  int iVar2;
  VECTOR_3D *pVVar3;
  int unaff_EBX;
  AiPath *unaff_EDI;
  VECTOR_3D *pVVar4;
  AiCmdInfo local_48;
  VECTOR_3D local_30;
  float local_24;
  undefined4 local_20;
  float local_1c;
  VECTOR_3D local_18;
  GameObjectClass *local_c;
  ConstructionRig *local_8;
  
  this = (ConstructionRig *)GameObjectHandle::GetObj(param_1);
  if (((this != (ConstructionRig *)0x0) &&
      (local_8 = this, local_c = GameObjectClass::Find(param_2), local_c != (GameObjectClass *)0x0))
     && (pAVar1 = AiPath::Find(param_3), pAVar1 != (AiPath *)0x0)) {
    iVar2 = (**(code **)this->_padding_)();
    if (*(int *)(iVar2 + 0x20) == 0x434e5354) {
      local_24 = pAVar1->points[pAVar1->pointCount + -1].x;
      local_1c = pAVar1->points[pAVar1->pointCount + -1].z;
      local_20 = 0;
      local_18.y = 0.0;
      local_18.x = local_24;
      local_18.z = local_1c;
      ConstructionRig::SetConstructionMatrix
                (local_8,&local_18,(VECTOR_3D *)(local_8->_padding_ + 0x38));
      this = local_8;
    }
    GetPosition((VECTOR_3D *)0x0,unaff_EDI,unaff_EBX);
    local_48.who = 0;
    local_48.priority = param_4;
    local_48.what = CMD_BUILD;
    pAVar1 = operator_new(0x1c);
    if (pAVar1 == (AiPath *)0x0) {
      local_48.where = (AiPath *)0x0;
    }
    else {
      pVVar4 = &local_30;
      pVVar3 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
      local_48.where = AiPath::AiPath(pAVar1,pVVar3,pVVar4);
    }
    local_48.param = (long)local_c;
    GameObject::SetCommand((GameObject *)this,&local_48);
  }
  return;
}
