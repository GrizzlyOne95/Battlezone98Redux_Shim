/*
 * Entry: 0049598b
 * Name: GameObject::LoadAll
 * Namespace: GameObject
 * Signature: bool LoadAll(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __cdecl GameObject::LoadAll(_iobuf *param_1)

{
  _OBJ76 *p_Var1;
  float fVar2;
  bool bVar3;
  GameObjectClass *this;
  GameObject *pGVar4;
  OldNew *this_00;
  tagENTITY *ptVar5;
  MAT_3D *pMVar6;
  int iVar7;
  VECTOR_3D *unaff_EBX;
  VECTOR_3D *unaff_ESI;
  float *pfVar8;
  MAT_3D *pMVar9;
  MAT_3D local_158;
  float local_118 [10];
  double local_f0;
  double local_e8;
  double local_e0;
  MAT_3D local_d8;
  float local_98;
  float fStack_94;
  float fStack_90;
  float local_8c;
  float fStack_88;
  float fStack_84;
  float local_80;
  float local_7c;
  float local_78;
  VECTOR_3D local_74;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_5c;
  undefined4 local_58;
  int local_54;
  _iobuf *local_50;
  GameObject *local_4c;
  int local_48;
  void *local_44;
  int local_40;
  short local_3c [2];
  int local_38;
  int local_34;
  char local_30 [40];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_78;
  local_50 = param_1;
  ::in(param_1,&local_38,4);
  local_34 = 0;
  if (0 < local_38) {
    local_40 = 0;
    do {
      do_load_bar(shell_hwnd,local_40 / local_38 + 0xf);
      ::in(param_1,"[GameObject]");
      bVar3 = ::in(param_1,(long64 *)&local_5c,8);
      if ((((bVar3) && (bVar3 = ::in(param_1,local_3c,2), bVar3)) &&
          (bVar3 = ::in(param_1,&local_74,0xc), bVar3)) &&
         (((bVar3 = ::in(param_1,&local_54,4), bVar3 && (bVar3 = ::in(param_1,local_30,0x28), bVar3)
           ) && (bVar3 = ::in(param_1,&local_48,4), bVar3)))) {
        if (version < 0x3ea) {
          ::in(param_1,&local_44,4);
          fVar2 = local_74.x;
          pMVar6 = &Identity_Matrix;
          pMVar9 = &local_d8;
          for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
            pMVar9->right_x = pMVar6->right_x;
            pMVar6 = (MAT_3D *)&pMVar6->right_y;
            pMVar9 = (MAT_3D *)&pMVar9->right_y;
          }
          local_d8.posit_x = (double)fVar2;
          local_d8.posit_y = (double)local_74.y;
          local_d8.posit_z = (double)local_74.z;
        }
        else {
          bVar3 = in_sptr(param_1,&local_44,4);
          if (bVar3) {
            ::in(param_1,&local_d8,0x40);
          }
        }
      }
      this = GameObjectClass::Find(CONCAT44(local_58,local_5c));
      if (this != (GameObjectClass *)0x0) {
        pGVar4 = GameObjectClass::Build(this,&local_d8,local_54,local_48,(int)local_3c[0],local_30);
        local_4c = pGVar4;
        this_00 = ::operator_new(8);
        if (this_00 != (OldNew *)0x0) {
          OldNew::OldNew(this_00,local_44,pGVar4);
        }
        (**(code **)(pGVar4->_padding_ + 0x4c))(param_1);
        if (local_48 != 0) {
          userObject = pGVar4;
          ptVar5 = (tagENTITY *)(**(code **)(pGVar4->_padding_ + 0x2c))();
          Set_User_Entity(ptVar5);
        }
        p_Var1 = pGVar4->obj;
        local_98 = (p_Var1->transform).front_x;
        fStack_94 = (p_Var1->transform).front_y;
        fStack_90 = (p_Var1->transform).front_z;
        local_8c = (p_Var1->transform).up_x;
        fStack_88 = (p_Var1->transform).up_y;
        fStack_84 = (p_Var1->transform).up_z;
        local_80 = local_98;
        local_7c = fStack_94;
        local_78 = fStack_90;
        local_68 = local_8c;
        local_64 = fStack_88;
        local_60 = fStack_84;
        pMVar6 = Build_Orthogonal_Matrix(&local_158,unaff_ESI,unaff_EBX);
        local_f0 = (p_Var1->transform).posit_x;
        pfVar8 = local_118;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pfVar8 = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pfVar8 = pfVar8 + 1;
        }
        local_e8 = (p_Var1->transform).posit_y;
        local_e0 = (p_Var1->transform).posit_z;
        pfVar8 = local_118;
        pMVar6 = &p_Var1->transform;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          pMVar6->right_x = *pfVar8;
          pfVar8 = pfVar8 + 1;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
        }
        UpdatePosition(local_4c);
        param_1 = local_50;
      }
      local_34 = local_34 + 1;
      local_40 = local_40 + 0x46;
    } while (local_34 < local_38);
  }
  return true;
}
