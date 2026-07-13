/*
 * Entry: 0041597a
 * Name: Inst01Event::Execute
 * Namespace: Inst01Event
 * Signature: void Execute(Inst01Event * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst01Event::Execute(Inst01Event *this)

{
  int iVar1;
  AiPath *pAVar2;
  GameObject *pGVar3;
  _OBJ76 *p_Var4;
  Inst01Event *local_c;
  Inst01Event *local_8;
  
  local_c = this;
  local_8 = this;
  if (this->game_start == false) {
    SetScrap(1,5);
    SetScrap(2,0x28);
    SetAIP("inst01.aip",2);
    iVar1 = GetHandle("apdrop196_camerapod");
    this->pointa = iVar1;
    iVar1 = GetHandle("apcamr-1_camerapod");
    this->pointb = iVar1;
    iVar1 = GetHandle("player-1_hover");
    this->player = iVar1;
    iVar1 = GetHandle("eggeizr139_geyser");
    this->base_handle = iVar1;
    pAVar2 = AiPath::Find("camera1");
    this->path = pAVar2;
    this->game_start = true;
    this->camera_start1 = true;
    fsm_push_camera();
  }
  if (this->camera_start1 != false) {
    local_c = (Inst01Event *)0xdac;
    pGVar3 = GameObjectHandle::GetObj(this->player);
    p_Var4 = (_OBJ76 *)(**(code **)(pGVar3->_padding_ + 0x30))();
    local_8 = (Inst01Event *)0x1f4;
    fsm_camera_trans_obj(this->path,(int *)&local_c,(int *)&local_8,p_Var4);
    iVar1 = cameraIsArrived();
    if (iVar1 != 0) {
      this->camera_start1 = false;
      pAVar2 = AiPath::Find("camera2");
      this->path = pAVar2;
      this->camera_start2 = true;
    }
  }
  if (this->camera_start2 != false) {
    local_8 = (Inst01Event *)0xdac;
    pGVar3 = GameObjectHandle::GetObj(this->pointa);
    (**(code **)(pGVar3->_padding_ + 0x30))();
    pGVar3 = GameObjectHandle::GetObj(this->base_handle);
    p_Var4 = (_OBJ76 *)(**(code **)(pGVar3->_padding_ + 0x30))();
    local_c = (Inst01Event *)0x1388;
    fsm_camera_trans_obj(this->path,(int *)&local_8,(int *)&local_c,p_Var4);
    iVar1 = cameraIsArrived();
    if (iVar1 != 0) {
      this->camera_start2 = false;
      fsm_pop_camera();
    }
  }
  return;
}
