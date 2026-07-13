/*
 * Entry: 004061e1
 * Name: MayHitFriends
 * Namespace: Global
 * Signature: bool MayHitFriends(GameObject * param_1, float param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl MayHitFriends(GameObject *param_1,float param_2,float param_3,float param_4)

{
  float fVar1;
  bool bVar2;
  float *pfVar3;
  GameObject *pGVar4;
  GameObject *unaff_EDI;
  float fVar5;
  Range_Search_Results local_44;
  float local_18;
  float fStack_14;
  float local_10;
  float local_c;
  GameObject *local_8;
  
  local_8 = (GameObject *)0x0;
  local_c = 1.0;
  if ((param_1->who_i_shot != 0) &&
     (local_8 = GameObjectHandle::GetObj(param_1->who_i_shot), local_8 != (GameObject *)0x0)) {
    bVar2 = ImportantFriend(param_1,unaff_EDI);
    if (bVar2) {
      fVar1 = param_1->when_i_shot;
      fVar5 = Get_Time();
      local_c = ConeFactor(fVar5 - fVar1);
    }
    else {
      local_8 = (GameObject *)0x0;
    }
  }
  pfVar3 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  fVar1 = SQRT(param_2);
  local_18 = *pfVar3;
  fStack_14 = pfVar3[1];
  local_10 = pfVar3[2];
  Range::Search(GameObject::objectRange,(double)local_18,(double)local_10,(double)fVar1,&local_44);
  bVar2 = Range_Search_Results::Get_Next_Object(&local_44,(int **)&param_2);
  do {
    if (bVar2 == false) {
      return false;
    }
    pGVar4 = GameObjectHandle::GetObj(*(int *)param_2);
    if (((pGVar4 != (GameObject *)0x0) && (pGVar4 != param_1)) &&
       (bVar2 = ImportantFriend(param_1,unaff_EDI), bVar2)) {
      fVar5 = param_3;
      if (pGVar4 == local_8) {
        fVar5 = local_c * param_3;
      }
      bVar2 = MayHit(param_1,pGVar4,fVar1,fVar5,local_c * 0.25 + 0.75);
      if (bVar2) {
        return true;
      }
    }
    bVar2 = Range_Search_Results::Get_Next_Object(&local_44,(int **)&param_2);
  } while( true );
}
