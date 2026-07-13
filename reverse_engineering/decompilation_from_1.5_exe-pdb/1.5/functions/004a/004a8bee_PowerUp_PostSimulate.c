/*
 * Entry: 004a8bee
 * Name: PowerUp::PostSimulate
 * Namespace: PowerUp
 * Signature: void PostSimulate(PowerUp * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUp::PostSimulate(PowerUp *this,float param_1)

{
  int iVar1;
  MAT_3D local_44;
  
  if ((this->vhcl->flags & 1) != 0) {
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
    EngineFlame::AddFlame(&engineFlame,&local_44,0.2);
  }
  return;
}
