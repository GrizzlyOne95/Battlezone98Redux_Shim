/*
 * Entry: 0040dd5b
 * Name: ActionInfo::ActionInfo
 * Namespace: ActionInfo
 * Signature: ActionInfo * ActionInfo(ActionInfo * this, _OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ActionInfo * __thiscall ActionInfo::ActionInfo(ActionInfo *this,_OBJ76 *param_1,_OBJ76 *param_2)

{
  RingState RVar1;
  QuadState QVar2;
  int iVar3;
  VEHICLE *pVVar4;
  float fVar5;
  
  this->me = param_1;
  this->him = param_2;
  fVar5 = get_obj_dist2D(param_1,param_2);
  if (10.0 <= fVar5) {
    if (25.0 <= fVar5) {
      if (60.0 <= fVar5) {
        if (200.0 <= fVar5) {
          RVar1 = RING_4;
        }
        else {
          RVar1 = RING_3;
        }
      }
      else {
        RVar1 = RING_2;
      }
    }
    else {
      RVar1 = RING_1;
    }
  }
  else {
    RVar1 = RING_0;
  }
  this->ring = RVar1;
  fVar5 = get_obj_heading(param_1);
  this->my_head = fVar5;
  fVar5 = get_obj_aim2D(param_1,param_2);
  this->my_aim = fVar5;
  QVar2 = get_weapon_quad(this->my_head,fVar5);
  this->my_quad = QVar2;
  iVar3 = is_vhcl(param_2);
  if (iVar3 == 0) {
    this->his_head = 0.0;
    this->his_aim = 0.0;
  }
  else {
    pVVar4 = get_obj_vhcl(param_2);
    fVar5 = get_obj_heading(param_2);
    this->his_head = fVar5;
    fVar5 = get_obj_aim2D(param_2,param_1);
    this->his_aim = fVar5;
    if ((pVVar4->flags & 2) == 0) {
      QVar2 = get_weapon_quad(this->his_head,fVar5);
      this->his_quad = QVar2;
      return this;
    }
  }
  this->his_quad = QUAD_BackBack;
  return this;
}
