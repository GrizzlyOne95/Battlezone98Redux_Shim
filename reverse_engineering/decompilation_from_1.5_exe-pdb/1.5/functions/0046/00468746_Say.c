/*
 * Entry: 00468746
 * Name: Say
 * Namespace: Global
 * Signature: void Say(Craft * param_1, UnitMsg param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Say(Craft *param_1,UnitMsg param_2,int param_3)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  _OBJ76 *p_Var6;
  int unaff_EBX;
  UnitMsg unaff_ESI;
  Craft *unaff_EDI;
  float fVar7;
  
  if (GameObject::userObject != (GameObject *)0x0) {
    piVar1 = &GameObject::userObject->_padding_;
    iVar3 = (**(code **)(*piVar1 + 4))();
    iVar4 = (**(code **)(param_1->_padding_ + 4))();
    if ((((iVar4 == iVar3) && ((param_1->_padding_ == 0 || (param_1->_padding_ == 0)))) &&
        ((param_2 != lastMsg ||
         ((bVar2 = IsSelectMsg(param_2), !bVar2 && (fVar7 = Get_Time(), 1.0 <= fVar7 - lastTime)))))
        ) && ((((param_2 != PACKED_MSG && (param_2 != DEPLOYED_MSG)) ||
               (fVar7 = Get_Time(), 5.0 <= fVar7 - scriptLoadTime)) &&
              ((((pcVar5 = GetUnitMsg(unaff_EDI,unaff_ESI,unaff_EBX), pcVar5 != (char *)0x0 &&
                 (*pcVar5 != '\0')) && (bVar2 = IsAudioMessagePlaying(), !bVar2)) &&
               (iVar3 = isCineractive(), iVar3 == 0)))))) {
      p_Var6 = (_OBJ76 *)(**(code **)(*piVar1 + 0x30))();
      QueueCB(pcVar5,p_Var6,iVar3);
      lastMsg = param_2;
      lastTime = Get_Time();
    }
  }
  return;
}
