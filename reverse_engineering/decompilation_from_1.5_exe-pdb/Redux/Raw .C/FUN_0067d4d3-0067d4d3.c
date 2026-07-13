
void FUN_0067d4d3(void)

{
  char cVar1;
  bool bVar2;
  SkeletonInstance *pSVar3;
  undefined4 uVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  char *pcVar6;
  AnimationState *pAVar7;
  int unaff_EBP;
  float10 fVar8;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (DAT_00920ec0 != (int *)0x0) {
    pSVar3 = Ogre::Entity::getSkeleton((Entity *)DAT_00920ec0);
    *(SkeletonInstance **)(unaff_EBP + -0xe4) = pSVar3;
    basic_string<>("uinode");
    *(undefined4 *)(unaff_EBP + -4) = 3;
    uVar4 = (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x164))();
    *(undefined4 *)(unaff_EBP + -0xe8) = uVar4;
    DAT_00920e98 = (int *)(**(code **)(**(int **)(unaff_EBP + -0xe8) + 0x17c))
                                    (unaff_EBP + -0xb4,ZERO_exref,IDENTITY_exref);
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    ~basic_string<>();
    (**(code **)(*DAT_00920e98 + 0x124))(DAT_00920ec0);
    Ogre::MovableObject::setCastShadows((MovableObject *)DAT_00920ec0,true);
    fVar8 = (float10)(**(code **)(*DAT_00920ec0 + 0x78))();
    *(float *)(unaff_EBP + -0xec) = (float)fVar8;
    DAT_008ed0dc = *(float *)(unaff_EBP + -0xec) * 2.0;
    (**(code **)(*DAT_00920e98 + 0x38))(0x3f800000,0x3f800000,0x3f800000);
    (**(code **)(*DAT_00920e98 + 0x24))(&DAT_025f8e70);
    (**(code **)(*DAT_00920e98 + 0x2c))(0,-DAT_008ed0dc * 0.125,0);
    (**(code **)(*DAT_00920ec0 + 200))(8);
    if (*(int *)(unaff_EBP + -0xe4) != 0) {
      (**(code **)(**(int **)(unaff_EBP + -0xe4) + 0xd0))(unaff_EBP + -0x108);
      while (cVar1 = FUN_006624a0(), cVar1 != '\0') {
        uVar4 = FUN_00662470();
        *(undefined4 *)(unaff_EBP + -0xd4) = uVar4;
        pbVar5 = Ogre::Node::getName(*(Node **)(unaff_EBP + -0xd4));
        *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
         (unaff_EBP + -0xf0) = pbVar5;
        pcVar6 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              **)(unaff_EBP + -0xf0),3);
        if (*pcVar6 == '2') {
          uVar4 = (**(code **)(**(int **)(unaff_EBP + -0xd4) + 0x18))();
          *(undefined4 *)(unaff_EBP + -0xe0) = uVar4;
          if (*(int *)(unaff_EBP + -0xe0) != 0) {
            (**(code **)(**(int **)(unaff_EBP + -0xe0) + 0xa8))(*(undefined4 *)(unaff_EBP + -0xd4));
          }
          Ogre::Bone::setManuallyControlled(*(Bone **)(unaff_EBP + -0xd4),true);
          (**(code **)(**(int **)(unaff_EBP + -0xd4) + 0x38))(0,0,0);
        }
      }
    }
    DAT_00920eb0 = (int)Ogre::Entity::getAllAnimationStates((Entity *)DAT_00920ec0);
    if ((AnimationStateSet *)DAT_00920eb0 != (AnimationStateSet *)0x0) {
      basic_string<>(&DAT_00885794);
      *(undefined4 *)(unaff_EBP + -4) = 4;
      bVar2 = Ogre::AnimationStateSet::hasAnimationState
                        ((AnimationStateSet *)DAT_00920eb0,
                         (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          *)(unaff_EBP + -0x9c));
      *(bool *)(unaff_EBP + -0xcd) = bVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      ~basic_string<>();
      if (*(char *)(unaff_EBP + -0xcd) != '\0') {
        basic_string<>(&DAT_00885794);
        *(undefined4 *)(unaff_EBP + -4) = 5;
        pAVar7 = Ogre::AnimationStateSet::getAnimationState
                           ((AnimationStateSet *)DAT_00920eb0,
                            (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)(unaff_EBP + -0x6c));
        *(AnimationState **)(unaff_EBP + -0xf8) = pAVar7;
        *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
        ~basic_string<>();
        if (*(int *)(unaff_EBP + -0xf8) != 0) {
          basic_string<>(&DAT_00885794);
          *(undefined4 *)(unaff_EBP + -4) = 6;
          pAVar7 = Ogre::Entity::getAnimationState
                             ((Entity *)DAT_00920ec0,
                              (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                               *)(unaff_EBP + -0x84));
          *(AnimationState **)(unaff_EBP + -0xdc) = pAVar7;
          *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
          ~basic_string<>();
          if (*(int *)(unaff_EBP + -0xdc) != 0) {
            Ogre::AnimationState::setEnabled(*(AnimationState **)(unaff_EBP + -0xdc),true);
            Ogre::AnimationState::setLoop(*(AnimationState **)(unaff_EBP + -0xdc),true);
            fVar8 = (float10)FUN_00822d60();
            Ogre::AnimationState::addTime(*(AnimationState **)(unaff_EBP + -0xdc),(float)fVar8);
          }
        }
      }
    }
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

