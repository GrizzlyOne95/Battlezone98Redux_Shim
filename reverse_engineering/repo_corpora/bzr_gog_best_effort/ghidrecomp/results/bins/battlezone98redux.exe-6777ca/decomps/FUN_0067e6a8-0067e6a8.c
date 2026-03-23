
void FUN_0067e6a8(void)

{
  char cVar1;
  bool bVar2;
  SkeletonInstance *pSVar3;
  Mesh *this;
  undefined4 uVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  char *pcVar6;
  AnimationState *pAVar7;
  int iVar8;
  int unaff_EBP;
  float10 fVar9;
  AxisAlignedBox *pAVar10;
  undefined1 uVar11;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (*(int *)(unaff_EBP + -0xb4) != 0) {
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xac) = 0;
    Ogre::MovableObject::setCastShadows(*(MovableObject **)(unaff_EBP + -0xb4),false);
    (**(code **)(**(int **)(unaff_EBP + -0xb4) + 0xa8))(DAT_008ed6a8);
    pSVar3 = Ogre::Entity::getSkeleton(*(Entity **)(unaff_EBP + -0xb4));
    *(SkeletonInstance **)(unaff_EBP + -0xd4) = pSVar3;
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xc0) = *(undefined4 *)(unaff_EBP + -0xb4);
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 200) = 0;
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xcc) = *(undefined4 *)(unaff_EBP + -0xd4);
    Ogre::AxisAlignedBox::AxisAlignedBox((AxisAlignedBox *)(unaff_EBP + -0x11c),2);
    *(undefined4 *)(unaff_EBP + -4) = 4;
    uVar11 = 1;
    pAVar10 = (AxisAlignedBox *)(unaff_EBP + -0x11c);
    Ogre::Entity::getMesh(*(Entity **)(unaff_EBP + -0xb4));
    this = (Mesh *)get();
    Ogre::Mesh::_setBounds(this,pAVar10,(bool)uVar11);
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    Ogre::AxisAlignedBox::~AxisAlignedBox((AxisAlignedBox *)(unaff_EBP + -0x11c));
    if (*(char *)(unaff_EBP + 0x10) == '\0') {
      pSVar3 = Ogre::Entity::getSkeleton(*(Entity **)(unaff_EBP + -0xb4));
      *(SkeletonInstance **)(unaff_EBP + -0xbc) = pSVar3;
      if (*(int *)(unaff_EBP + -0xbc) != 0) {
        (**(code **)(**(int **)(unaff_EBP + -0xbc) + 0xd0))(unaff_EBP + -0xf4);
        while (cVar1 = FUN_006624a0(), cVar1 != '\0') {
          uVar4 = FUN_00662470();
          *(undefined4 *)(unaff_EBP + -0xb0) = uVar4;
          pbVar5 = Ogre::Node::getName(*(Node **)(unaff_EBP + -0xb0));
          *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
           (unaff_EBP + -0xcc) = pbVar5;
          pcVar6 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  **)(unaff_EBP + -0xcc),3);
          if (*pcVar6 == '1') {
            uVar4 = (**(code **)(**(int **)(unaff_EBP + -0xb0) + 0x18))();
            *(undefined4 *)(unaff_EBP + -200) = uVar4;
            if (*(int *)(unaff_EBP + -200) != 0) {
              (**(code **)(**(int **)(unaff_EBP + -200) + 0xa8))(*(undefined4 *)(unaff_EBP + -0xb0))
              ;
            }
            Ogre::Bone::setManuallyControlled(*(Bone **)(unaff_EBP + -0xb0),true);
            (**(code **)(**(int **)(unaff_EBP + -0xb0) + 0x38))(0,0,0);
          }
          else {
            pcVar6 = std::
                     basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                     operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  **)(unaff_EBP + -0xcc),3);
            if (*pcVar6 == '2') {
              Ogre::Bone::setManuallyControlled(*(Bone **)(unaff_EBP + -0xb0),false);
              (**(code **)(**(int **)(unaff_EBP + -0xb0) + 0x38))(0x3f800000,0x3f800000,0x3f800000);
            }
          }
        }
      }
    }
    else {
      *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xc4) = 0;
      DAT_00920eb0 = (int)Ogre::Entity::getAllAnimationStates(*(Entity **)(unaff_EBP + -0xb4));
      if ((AnimationStateSet *)DAT_00920eb0 != (AnimationStateSet *)0x0) {
        basic_string<>(&DAT_00885794);
        *(undefined4 *)(unaff_EBP + -4) = 5;
        bVar2 = Ogre::AnimationStateSet::hasAnimationState
                          ((AnimationStateSet *)DAT_00920eb0,
                           (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            *)(unaff_EBP + -0x94));
        *(bool *)(unaff_EBP + -0xbd) = bVar2;
        *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
        ~basic_string<>();
        if (*(char *)(unaff_EBP + -0xbd) != '\0') {
          basic_string<>(&DAT_00885794);
          *(undefined4 *)(unaff_EBP + -4) = 6;
          pAVar7 = Ogre::AnimationStateSet::getAnimationState
                             ((AnimationStateSet *)DAT_00920eb0,
                              (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                               *)(unaff_EBP + -100));
          *(AnimationState **)(unaff_EBP + -0xd0) = pAVar7;
          *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
          ~basic_string<>();
          if (*(int *)(unaff_EBP + -0xd0) != 0) {
            basic_string<>(&DAT_00885794);
            *(undefined4 *)(unaff_EBP + -4) = 7;
            pAVar7 = Ogre::Entity::getAnimationState
                               (*(Entity **)(unaff_EBP + -0xb4),
                                (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 *)(unaff_EBP + -0x4c));
            *(AnimationState **)(unaff_EBP + -0xc4) = pAVar7;
            *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
            ~basic_string<>();
            if (*(int *)(unaff_EBP + -0xc4) != 0) {
              Ogre::AnimationState::setEnabled(*(AnimationState **)(unaff_EBP + -0xc4),true);
              Ogre::AnimationState::setLoop(*(AnimationState **)(unaff_EBP + -0xc4),true);
              fVar9 = (float10)FUN_00822d60();
              Ogre::AnimationState::addTime(*(AnimationState **)(unaff_EBP + -0xc4),(float)fVar9);
              *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xc4) = *(undefined4 *)(unaff_EBP + -0xc4);
            }
          }
        }
      }
      pSVar3 = Ogre::Entity::getSkeleton(*(Entity **)(unaff_EBP + -0xb4));
      *(SkeletonInstance **)(unaff_EBP + -0xbc) = pSVar3;
      if (*(int *)(unaff_EBP + -0xbc) != 0) {
        (**(code **)(**(int **)(unaff_EBP + -0xbc) + 0xd0))(unaff_EBP + -0xe8);
LAB_0067ea98:
        cVar1 = FUN_006624a0();
        if (cVar1 != '\0') {
          uVar4 = FUN_00662470();
          *(undefined4 *)(unaff_EBP + -0xb0) = uVar4;
          pbVar5 = Ogre::Node::getName(*(Node **)(unaff_EBP + -0xb0));
          *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
           (unaff_EBP + -0xb8) = pbVar5;
          pcVar6 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  **)(unaff_EBP + -0xb8),5);
          iVar8 = tolower((int)*pcVar6);
          if (iVar8 == 0x70) {
            pcVar6 = std::
                     basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                     operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  **)(unaff_EBP + -0xb8),6);
            iVar8 = tolower((int)*pcVar6);
            if (iVar8 == 0x6f) {
              pcVar6 = std::
                       basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                      **)(unaff_EBP + -0xb8),7);
              iVar8 = tolower((int)*pcVar6);
              if (iVar8 == 0x76) {
                *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xe0) = *(undefined4 *)(unaff_EBP + -0xb0)
                ;
                Ogre::Bone::setManuallyControlled(*(Bone **)(unaff_EBP + -0xb0),false);
                goto LAB_0067ea98;
              }
            }
          }
          pcVar6 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  **)(unaff_EBP + -0xb8),3);
          if (*pcVar6 == '2') {
            uVar4 = FUN_0041f870(unaff_EBP + -0x34);
            FUN_007d6a70("FOUND Cockpit Bone %s in model %s\n",uVar4);
            Ogre::Bone::setManuallyControlled(*(Bone **)(unaff_EBP + -0xb0),false);
            (**(code **)(**(int **)(unaff_EBP + -0xb0) + 0x38))(0x3f800000,0x3f800000,0x3f800000);
          }
          else {
            pcVar6 = std::
                     basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                     operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  **)(unaff_EBP + -0xb8),5);
            iVar8 = tolower((int)*pcVar6);
            if (iVar8 == 0x67) {
              pcVar6 = std::
                       basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                      **)(unaff_EBP + -0xb8),6);
              iVar8 = tolower((int)*pcVar6);
              if (iVar8 == 99) {
                pcVar6 = std::
                         basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                        **)(unaff_EBP + -0xb8),7);
                iVar8 = tolower((int)*pcVar6);
                if ((iVar8 == 0x31) && (*(int *)(**(int **)(unaff_EBP + 8) + 0x84) == 4)) {
                  *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xac) =
                       *(undefined4 *)(unaff_EBP + -0xb0);
                }
              }
            }
          }
          goto LAB_0067ea98;
        }
      }
    }
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

