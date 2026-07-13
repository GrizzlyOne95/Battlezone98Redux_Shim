/*
 * Entry: 0044d2cd
 * Name: MultSTMission::Update
 * Namespace: MultSTMission
 * Signature: void Update(MultSTMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultSTMission::Update(MultSTMission *this)

{
  bool bVar1;
  ulong uVar2;
  uint uVar3;
  AiPath *pAVar4;
  DWORD DVar5;
  VECTOR_3D local_10;
  
  LuaMission::Update((LuaMission *)this);
  if (cockpitTimer.show != false) {
    uVar2 = Get_Time_Long();
    uVar3 = uVar2 / 1000;
    if (uVar3 + 2 < this->dwLastTime) {
      this->dwLastTime = uVar3 - 1;
    }
    if (this->dwLastTime < uVar3) {
      cockpitTimer.frac = 1.0;
      cockpitTimer.warn = 0x7fffffff;
      cockpitTimer.alert = 0x7fffffff;
      cockpitTimer.countdown = false;
      cockpitTimer.active = true;
      cockpitTimer.hours = true;
      cockpitTimer.timer = uVar3;
      this->dwLastTime = uVar3;
    }
  }
  if (this->camera == false) {
    if (this->recently_killed != false) {
      local_10.y = (this->pos).y;
      local_10.z = (this->pos).z;
      local_10.x = (this->pos).x + 10.0;
      this->recently_killed = false;
      this->height = 10;
      local_10.y = local_10.y + 10.0;
      this->speed = 10;
      local_10.z = local_10.z + 10.0;
      pAVar4 = operator_new(0x1c);
      if (pAVar4 == (AiPath *)0x0) {
        pAVar4 = (AiPath *)0x0;
      }
      else {
        pAVar4 = AiPath::AiPath(pAVar4,&local_10,&this->pos);
      }
      this->aipath = pAVar4;
      CameraReady();
      this->camera = true;
      DVar5 = Get_TimeNow();
      StopCamera = DVar5 + 2000;
    }
    if (this->camera == false) {
      return;
    }
  }
  fsm_camera_trans_path_dir(this->aipath,&this->height,&this->speed);
  bVar1 = CameraCancelled();
  if ((!bVar1) && (DVar5 = Get_TimeNow(), DVar5 <= StopCamera)) {
    return;
  }
  CameraFinish();
  pAVar4 = this->aipath;
  if (pAVar4 != (AiPath *)0x0) {
    AiPath::~AiPath(pAVar4);
    operator_delete(pAVar4);
  }
  this->camera = false;
  return;
}
