/*
 * Entry: 004aa540
 * Name: Producer::Producer
 * Namespace: Producer
 * Signature: Producer * Producer(Producer * this, _OBJ76 * param_1, ProducerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Producer * __thiscall Producer::Producer(Producer *this,_OBJ76 *param_1,ProducerClass *param_2)

{
  _OBJ76 *p_Var1;
  MAT_3D *pMVar2;
  int iVar3;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar4;
  float fVar5;
  char *__return_storage_ptr__;
  MAT_3D local_104;
  MAT_3D local_c4;
  MAT_3D local_84;
  MAT_3D local_44;
  
  HoverCraft::HoverCraft((HoverCraft *)this,param_1,(HoverCraftClass *)param_2);
  this->animHandle = -1;
  this->delayTimer = -1e+30;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->_padding_ = 0;
  this->powerHandle = 0;
  this->powerSource = (Geizer *)0x0;
  fVar5 = Get_TimeLocal();
  this->nextRepair = fVar5 + 10.0;
  this->buildClass = (GameObjectClass *)0x0;
  this->deployedBuilder = true;
  this->poweredBuilder = true;
  this->smokeCount = 0;
  this->smoke = SMOKE_OFF;
  FindSmokeSource(this,param_1);
  __return_storage_ptr__ = "GS1";
  this->smokeEmitter = smokeEffect.sprayEmitter;
  p_Var1 = FindHardpoint((_OBJ76 *)this->_padding_,"GS1");
  this->ejectVehicle = p_Var1;
  if (p_Var1 == (_OBJ76 *)0x0) {
    p_Var1 = *(_OBJ76 **)(this->_padding_ + 0xa8);
    pMVar2 = Build_Pitch_Yaw_Matrix(&local_84,-1.0471976,-1.5707963);
    pMVar4 = &local_44;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
    local_44.posit_x = 0.0;
    local_44.posit_y = 5.0;
    local_44.posit_z = 0.0;
    __return_storage_ptr__ = (char *)&local_84;
    pMVar2 = Matrix_Inverse((MAT_3D *)__return_storage_ptr__,unaff_EDI);
    pMVar4 = &local_c4;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
    p_Var1 = create_obj(p_Var1,".\\fun3d\\Producer.cpp");
    this->ejectVehicle = p_Var1;
    p_Var1->class_id = CLASS_ID_SPECIAL_HARDPOINT;
    pMVar2 = Matrix_Multiply(&local_104,&local_44,&local_c4);
    pMVar4 = &local_84;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
    pMVar2 = &local_84;
    pMVar4 = &this->ejectVehicle->transform;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
  }
  p_Var1 = FindHardpoint((_OBJ76 *)this->_padding_,"GS2");
  this->ejectPowerup = p_Var1;
  if (p_Var1 == (_OBJ76 *)0x0) {
    p_Var1 = *(_OBJ76 **)(this->_padding_ + 0xa8);
    pMVar2 = Build_Pitch_Yaw_Matrix(&local_104,-1.0471976,1.5707963);
    pMVar4 = &local_44;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
    local_44.posit_x = 0.0;
    local_44.posit_y = 5.0;
    local_44.posit_z = 0.0;
    pMVar2 = Matrix_Inverse(&local_104,(MAT_3D *)__return_storage_ptr__);
    pMVar4 = &local_84;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
    p_Var1 = create_obj(p_Var1,".\\fun3d\\Producer.cpp");
    this->ejectPowerup = p_Var1;
    p_Var1->class_id = CLASS_ID_SPECIAL_HARDPOINT;
    pMVar2 = Matrix_Multiply(&local_104,&local_44,&local_84);
    pMVar4 = &local_c4;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
    pMVar2 = &local_c4;
    pMVar4 = &this->ejectPowerup->transform;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
  }
  return this;
}
