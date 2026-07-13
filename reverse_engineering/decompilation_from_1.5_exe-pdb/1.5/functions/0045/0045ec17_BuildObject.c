/*
 * Entry: 0045ec17
 * Name: BuildObject
 * Namespace: Global
 * Signature: int BuildObject(char * param_1, int param_2, MAT_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BuildObject(char *param_1,int param_2,MAT_3D *param_3)

{
  bool bVar1;
  GameObjectClass *this;
  GameObject *this_00;
  AiMission *pAVar2;
  int iVar3;
  
  this = GameObjectClass::Find(param_1);
  if (this == (GameObjectClass *)0x0) {
    return 0;
  }
  this_00 = GameObjectClass::Build(this,param_3,param_2,0,-1,(char *)0x0);
  if (this_00 == (GameObject *)0x0) {
    return 0;
  }
  bVar1 = Net::GetHosting();
  if (bVar1) {
    DistributedObject::SetLocal((DistributedObject *)&this_00->_padding_);
  }
  pAVar2 = AiMission::GetCurrent();
  (**(code **)(pAVar2->_padding_ + 0x18))(this_00);
  iVar3 = GameObject::GetHandle(this_00);
  return iVar3;
}
