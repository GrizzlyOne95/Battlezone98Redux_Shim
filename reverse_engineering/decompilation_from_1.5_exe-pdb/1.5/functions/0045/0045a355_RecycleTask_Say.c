/*
 * Entry: 0045a355
 * Name: RecycleTask::Say
 * Namespace: RecycleTask
 * Signature: void Say(RecycleTask * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::Say(RecycleTask *this,char *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  _OBJ76 *p_Var4;
  long lVar5;
  
  if ((param_1 != (char *)0x0) && (GameObject::userObject != (GameObject *)0x0)) {
    piVar1 = &GameObject::userObject->_padding_;
    iVar2 = (**(code **)(this->me->_padding_ + 4))();
    iVar3 = (**(code **)(*piVar1 + 4))();
    if (iVar2 == iVar3) {
      lVar5 = 3;
      p_Var4 = (_OBJ76 *)(**(code **)(*piVar1 + 0x30))();
      QueueCB(param_1,p_Var4,lVar5);
    }
  }
  return;
}
