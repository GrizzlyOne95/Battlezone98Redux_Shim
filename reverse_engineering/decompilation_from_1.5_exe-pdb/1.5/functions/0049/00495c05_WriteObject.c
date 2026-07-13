/*
 * Entry: 00495c05
 * Name: WriteObject
 * Namespace: Global
 * Signature: bool WriteObject(_iobuf * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __cdecl WriteObject(_iobuf *param_1,GameObject *param_2)

{
  _OBJ76 *p_Var1;
  _iobuf *p_Var2;
  bool bVar3;
  char cVar4;
  int iVar5;
  GameObjectClass *pGVar6;
  char *pcVar7;
  GameObject *unaff_EBX;
  MAT_3D *pMVar8;
  MAT_3D *pMVar9;
  MAT_3D local_98;
  VECTOR_3D local_58;
  _iobuf *local_4c;
  uint local_48;
  int local_44;
  undefined8 local_3c;
  uint local_34;
  char local_30 [40];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_4c = param_1;
  iVar5 = (**(code **)(unaff_EBX->_padding_ + 0x30))();
  local_3c._0_4_ = *(undefined4 *)(iVar5 + 8);
  local_3c._4_4_ = *(undefined4 *)(iVar5 + 0xc);
  local_34 = (uint)(ushort)unaff_EBX->seqNo;
  p_Var1 = unaff_EBX->obj;
  local_58.x = (float)(p_Var1->transform).posit_x;
  local_58.y = (float)(p_Var1->transform).posit_y;
  local_58.z = (float)(p_Var1->transform).posit_z;
  local_44 = (**(code **)(unaff_EBX->_padding_ + 4))();
  local_48 = (uint)(unaff_EBX == GameObject::userObject);
  pMVar8 = &unaff_EBX->obj->transform;
  pMVar9 = &local_98;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    pMVar9->right_x = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pMVar9 = (MAT_3D *)&pMVar9->right_y;
  }
  iVar5 = (**(code **)unaff_EBX->_padding_)();
  pGVar6 = GameObjectClass::Find(CONCAT44(local_3c._4_4_,(undefined4)local_3c));
  pcVar7 = unaff_EBX->label;
  if (pcVar7 == (char *)0x0) {
    sprintf(local_30,"%.8s%d_%s",&local_3c,(int)(short)local_34,*(undefined4 *)(iVar5 + 0x24));
  }
  else {
    iVar5 = -(int)pcVar7;
    do {
      cVar4 = *pcVar7;
      pcVar7[(int)(local_30 + iVar5)] = cVar4;
      pcVar7 = pcVar7 + 1;
    } while (cVar4 != '\0');
  }
  p_Var2 = local_4c;
  bVar3 = out(local_4c,"[GameObject]");
  if ((((((bVar3) && (bVar3 = out(p_Var2,&local_3c,8,"PrjID"), bVar3)) &&
        (bVar3 = out(p_Var2,(short *)&local_34,2,"seqno"), bVar3)) &&
       ((bVar3 = out(p_Var2,&local_58,0xc,"pos"), bVar3 &&
        (bVar3 = out(p_Var2,&local_44,4,"team"), bVar3)))) &&
      ((bVar3 = out(p_Var2,local_30,0x28,"label"), bVar3 &&
       ((bVar3 = out(p_Var2,(int *)&local_48,4,"isUser"), bVar3 &&
        (bVar3 = out_ptr(p_Var2,&stack0xffffffc0,4,"obj_addr"), bVar3)))))) &&
     (bVar3 = out(p_Var2,&local_98,0x40,"transform"), bVar3)) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (pGVar6 != (GameObjectClass *)0x0) {
    if ((bVar3 == false) ||
       (cVar4 = (**(code **)(unaff_EBX->_padding_ + 0x50))(p_Var2), cVar4 == '\0')) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
  }
  return bVar3;
}
