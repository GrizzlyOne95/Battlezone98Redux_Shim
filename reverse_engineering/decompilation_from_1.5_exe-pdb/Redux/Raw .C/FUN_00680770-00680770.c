
void FUN_00680770(int param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5,
                 float param_6)

{
  Entity *this;
  AnimationState *pAVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_38 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(undefined4 *)(param_1 + 0xd0) = param_3;
  *(undefined4 *)(param_1 + 0xd4) = param_5;
  this = *(Entity **)(param_1 + 0xc0);
  if (*(int *)(param_1 + 0xc4) != 0) {
    basic_string<>(param_2);
    pAVar1 = Ogre::Entity::getAnimationState(this,local_38);
    ~basic_string<>();
    Ogre::AnimationState::setEnabled(pAVar1,false);
    basic_string<>(param_3);
    pAVar1 = Ogre::Entity::getAnimationState(this,local_20);
    ~basic_string<>();
    Ogre::AnimationState::setEnabled(pAVar1,true);
    Ogre::AnimationState::setLoop(pAVar1,param_4 != 0);
    Ogre::Entity::refreshAvailableAnimationState(this);
    Ogre::AnimationState::setTimePosition(pAVar1,param_6);
  }
  FUN_0083e885();
  return;
}

