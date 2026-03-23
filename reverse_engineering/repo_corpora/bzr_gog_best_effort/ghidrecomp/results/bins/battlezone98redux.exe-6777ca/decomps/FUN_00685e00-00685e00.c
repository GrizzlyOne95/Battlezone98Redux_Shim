
MovableObject * FUN_00685e00(undefined4 param_1,undefined4 param_2)

{
  MovableObject *this;
  uint uVar1;
  SubEntity *pSVar2;
  undefined4 local_c;
  
  this = (MovableObject *)(**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x178))(param_1);
  Ogre::MovableObject::setCastShadows(this,false);
  (**(code **)(*(int *)this + 200))(param_2);
  local_c = 0;
  while( true ) {
    uVar1 = Ogre::Entity::getNumSubEntities((Entity *)this);
    if (uVar1 <= local_c) break;
    pSVar2 = Ogre::Entity::getSubEntity((Entity *)this,local_c);
    (**(code **)(*(int *)pSVar2 + 0x54))(5,0xffff - local_c);
    local_c = local_c + 1;
  }
  return this;
}

