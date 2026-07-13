/*
 * Entry: 00517b24
 * Name: Units_SOrderConstruct
 * Namespace: Global
 * Signature: void Units_SOrderConstruct(tagUNIT * param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Removing unreachable block (ram,0x00517ba6) */
/* WARNING: Removing unreachable block (ram,0x00517beb) */

void __cdecl Units_SOrderConstruct(tagUNIT *param_1,int param_2,int param_3,int param_4)

{
  ConstructionRig *this;
  tagBUILDINGTYPE *ptVar1;
  GameObjectClass *pGVar2;
  int iVar3;
  VECTOR_3D local_18;
  undefined4 local_c;
  undefined4 local_8;
  
  ptVar1 = buildingtypes;
  local_c = 0;
  local_8 = 0;
  this = (ConstructionRig *)param_1->id;
  strncpy((char *)&local_c,buildingtypes[param_2].symbol,8);
  pGVar2 = GameObjectClass::Find(CONCAT44(local_8,local_c));
  AI_Team_GridCell_Debug
            (AI_map->team[param_1->team],(int)(param_3 + (param_3 >> 0x1f & 7U)) >> 3,
             (int)(param_4 + (param_4 >> 0x1f & 7U)) >> 3);
  local_18.x = (float)(*(uint *)&ptVar1[param_2].field_0x24 >> 0x12 & 0xf) * 5.0 +
               (float)(aiGridX0 + param_3) * 10.0;
  local_18.y = 0.0;
  local_18.z = (float)(*(uint *)&ptVar1[param_2].field_0x24 >> 0x16 & 0xf) * 5.0 +
               (float)(aiGridZ0 + param_4) * 10.0;
  iVar3 = (**(code **)this->_padding_)();
  if (*(int *)(iVar3 + 0x20) == 0x434e5354) {
    ConstructionRig::SetConstructionMatrix(this,&local_18,(VECTOR_3D *)(this->_padding_ + 0x38));
  }
  GameObject::SetCommand((GameObject *)this,CMD_BUILD,&local_18,(long)pGVar2);
  return;
}
