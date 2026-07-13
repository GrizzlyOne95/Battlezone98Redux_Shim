/*
 * Entry: 004a6975
 * Name: Person::PostSimulate
 * Namespace: Person
 * Signature: void PostSimulate(Person * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Person::PostSimulate(Person *this,float param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  MAT_3D local_44;
  
  if (((*(byte *)(this->_padding_ + 0x10c) & 4) != 0) &&
     (fVar2 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].x,
     fVar3 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].y,
     fVar4 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].z,
     fVar4 * fVar4 + fVar3 * fVar3 + fVar2 * fVar2 < 22500.0)) {
    iVar1 = this->_padding_;
    local_44.right_x = *(float *)(iVar1 + 0x20);
    local_44.right_y = *(float *)(iVar1 + 0x24);
    local_44.right_z = *(float *)(iVar1 + 0x28);
    local_44.up_x = *(float *)(iVar1 + 0x38);
    local_44.up_y = *(float *)(iVar1 + 0x3c);
    local_44.up_z = *(float *)(iVar1 + 0x40);
    local_44.front_x = -*(float *)(iVar1 + 0x2c);
    local_44.front_y = -*(float *)(iVar1 + 0x30);
    local_44.front_z = -*(float *)(iVar1 + 0x34);
    local_44.posit_x = *(double *)(iVar1 + 0x48);
    local_44.posit_y = *(double *)(iVar1 + 0x50);
    local_44.posit_z = *(double *)(iVar1 + 0x58);
    EngineFlame::AddFlame(&engineFlame,&local_44,0.1);
  }
  return;
}
