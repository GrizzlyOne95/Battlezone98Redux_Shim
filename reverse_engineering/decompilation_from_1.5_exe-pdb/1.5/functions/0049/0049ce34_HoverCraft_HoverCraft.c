/*
 * Entry: 0049ce34
 * Name: HoverCraft::HoverCraft
 * Namespace: HoverCraft
 * Signature: HoverCraft * HoverCraft(HoverCraft * this, _OBJ76 * param_1, HoverCraftClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HoverCraft * __thiscall
HoverCraft::HoverCraft(HoverCraft *this,_OBJ76 *param_1,HoverCraftClass *param_2)

{
  float fVar1;
  int iVar2;
  VECTOR_3D_LONG VVar3;
  VEHICLE *pVVar4;
  int iVar5;
  _OBJ76 *p_Var6;
  _OBJ76 *p_Var7;
  int iVar8;
  int iVar9;
  float fVar10;
  int aiStack_28 [2];
  undefined8 local_20;
  ulonglong local_18;
  undefined8 local_10;
  float local_8;
  
  Craft::Craft((Craft *)this,param_1,(CraftClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  pVVar4 = get_obj_vhcl(param_1);
  pVVar4->flags = 1;
  iVar2 = this->_padding_;
  iVar9 = 0;
  this->_padding_ = 0;
  if ((*(byte *)(iVar2 + 0x14) & 0x20) == 0) {
    fVar1 = param_2->setAltitude;
    local_20 = *(undefined8 *)*(undefined1 (*) [12])(iVar2 + 0x48);
    local_18 = *(ulonglong *)(iVar2 + 0x50);
    local_10 = *(undefined8 *)(iVar2 + 0x58);
    VVar3.y._4_4_ = (int)(local_18 >> 0x20);
    VVar3._0_12_ = *(undefined1 (*) [12])(iVar2 + 0x48);
    VVar3.z._0_4_ = (int)local_10;
    VVar3.z._4_4_ = (int)((ulonglong)local_10 >> 0x20);
    fVar10 = FindFloor(VVar3);
    iVar2 = this->_padding_;
    *(undefined8 *)(iVar2 + 0x48) = local_20;
    *(double *)(iVar2 + 0x50) = (double)(fVar10 + fVar1);
    *(undefined8 *)(iVar2 + 0x58) = local_10;
  }
  this->airBorne = 0.0;
  this->hi = (HoverInterface *)0x0;
  this->throttle = 0.0;
  param_1 = (_OBJ76 *)0x0;
  iVar8 = 0;
  param_2 = (HoverCraftClass *)0x0;
  iVar2 = this->_padding_;
  do {
    do {
      iVar5 = iVar2;
      iVar2 = *(int *)(iVar5 + 0xac);
      if (iVar2 == 0x43) {
        aiStack_28[(int)param_1] = iVar5;
        param_1 = (_OBJ76 *)((int)&param_1->objHandle + 1);
      }
      else if (iVar2 == 0x4b) {
        iVar8 = iVar8 + 1;
      }
      else if (iVar2 == 0x4d) {
        param_2 = (HoverCraftClass *)((int)&param_2->_padding_ + 1);
      }
      iVar2 = *(int *)(iVar5 + 0xa8);
    } while (*(int *)(iVar5 + 0xa8) != 0);
    while (*(int *)(iVar5 + 0xa4) == 0) {
      iVar5 = *(int *)(iVar5 + 0xa0);
      if (iVar5 == 0) {
        if ((iVar8 == 0) && (0 < (int)param_1)) {
          do {
            p_Var7 = (_OBJ76 *)aiStack_28[iVar9];
            local_8 = (p_Var7->bBox).min.y;
            p_Var6 = create_obj(p_Var7,".\\fun3d\\HoverCraft.cpp");
            p_Var6->class_id = CLASS_ID_FLAME_EMITTER;
            (p_Var6->transform).right_x = 1.0;
            iVar9 = iVar9 + 1;
            (p_Var6->transform).right_y = 0.0;
            (p_Var6->transform).right_z = 0.0;
            (p_Var6->transform).up_x = 0.0;
            (p_Var6->transform).up_y = 0.0;
            (p_Var6->transform).front_x = 0.0;
            (p_Var6->transform).up_z = 1.0;
            (p_Var6->transform).front_y = -1.0;
            (p_Var6->transform).front_z = 0.0;
            (p_Var6->transform).posit_x = (double)((p_Var7->transform).up_x * local_8);
            (p_Var6->transform).posit_y = (double)((p_Var7->transform).up_y * local_8);
            (p_Var6->transform).posit_z = (double)(local_8 * (p_Var7->transform).up_z);
          } while (iVar9 < (int)param_1);
        }
        if ((((byte)useD3D & 4) != 0) && (param_2 == (HoverCraftClass *)0x0)) {
          p_Var7 = create_obj(*(_OBJ76 **)(this->_padding_ + 0xa8),".\\fun3d\\HoverCraft.cpp");
          p_Var7->class_id = CLASS_ID_DUST_EMITTER;
        }
        this->dustTimer = 0.0;
        local_18 = local_18 & 0xffffffff;
        local_10 = 0;
        (this->omegaEye).x = 0.0;
        (this->omegaEye).y = 0.0;
        (this->omegaEye).z = 0.0;
        InitSound(this);
        return this;
      }
    }
    iVar2 = *(int *)(iVar5 + 0xa4);
  } while( true );
}
