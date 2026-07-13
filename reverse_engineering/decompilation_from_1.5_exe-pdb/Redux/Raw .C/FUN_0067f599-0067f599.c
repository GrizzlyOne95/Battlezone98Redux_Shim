
void FUN_0067f599(void)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  char cVar4;
  SkeletonInstance *pSVar5;
  undefined4 uVar6;
  AxisAlignedBox *pAVar7;
  SharedPtr<class_Ogre::Mesh> *pSVar8;
  Mesh *pMVar9;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar10;
  char *pcVar11;
  int iVar12;
  undefined4 *puVar13;
  Quaternion *this;
  Vector3 *pVVar14;
  AnimationState *pAVar15;
  ResourceGroupManager *this_00;
  int unaff_EBP;
  float10 fVar16;
  float fVar17;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (*(int *)(unaff_EBP + -0xe0) != 0) {
    pSVar5 = Ogre::Entity::getSkeleton(*(Entity **)(unaff_EBP + -0xe0));
    *(SkeletonInstance **)(unaff_EBP + -0x168) = pSVar5;
    uVar6 = (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x164))();
    *(undefined4 *)(unaff_EBP + -0x140) = uVar6;
    uVar6 = (**(code **)(**(int **)(unaff_EBP + -0x140) + 0x180))(ZERO_exref,IDENTITY_exref);
    *(undefined4 *)(unaff_EBP + -0xf0) = uVar6;
    (**(code **)(**(int **)(unaff_EBP + -0xf0) + 0x124))(*(undefined4 *)(unaff_EBP + -0xe0));
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0x94) = *(undefined4 *)(unaff_EBP + -0xe0);
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0x98) = *(undefined4 *)(unaff_EBP + -0xf0);
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xa4) = *(undefined4 *)(unaff_EBP + -0x168);
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xe0) = 0;
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xac) = 0;
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xb0) = 0;
    bVar3 = Ogre::MovableObject::getReceivesShadows(*(MovableObject **)(unaff_EBP + -0xe0));
    *(uint *)(unaff_EBP + -0x194) = (uint)bVar3;
    Ogre::MovableObject::setCastShadows(*(MovableObject **)(unaff_EBP + -0xe0),true);
    (**(code **)(**(int **)(unaff_EBP + -0xf0) + 0x38))(0xbf800000,0x3f800000,0xbf800000);
    *(char **)(unaff_EBP + -0x10c) = "abspow";
    *(undefined4 *)(unaff_EBP + -0x114) = *(undefined4 *)(unaff_EBP + -0xec);
    do {
      bVar1 = **(byte **)(unaff_EBP + -0x114);
      *(byte *)(unaff_EBP + -0xf6) = bVar1;
      bVar3 = bVar1 < **(byte **)(unaff_EBP + -0x10c);
      if (bVar1 != **(byte **)(unaff_EBP + -0x10c)) {
LAB_0067f758:
        *(uint *)(unaff_EBP + -0x13c) = -(uint)bVar3 | 1;
        goto LAB_0067f763;
      }
      if (*(char *)(unaff_EBP + -0xf6) == '\0') break;
      bVar1 = *(byte *)(*(int *)(unaff_EBP + -0x114) + 1);
      *(byte *)(unaff_EBP + -0xf5) = bVar1;
      bVar2 = *(byte *)(*(int *)(unaff_EBP + -0x10c) + 1);
      bVar3 = bVar1 < bVar2;
      if (bVar1 != bVar2) goto LAB_0067f758;
      *(int *)(unaff_EBP + -0x114) = *(int *)(unaff_EBP + -0x114) + 2;
      *(int *)(unaff_EBP + -0x10c) = *(int *)(unaff_EBP + -0x10c) + 2;
    } while (*(char *)(unaff_EBP + -0xf5) != '\0');
    *(undefined4 *)(unaff_EBP + -0x13c) = 0;
LAB_0067f763:
    *(undefined4 *)(unaff_EBP + -0x150) = *(undefined4 *)(unaff_EBP + -0x13c);
    if (*(int *)(unaff_EBP + -0x150) == 0) {
      fVar16 = (float10)(**(code **)(**(int **)(unaff_EBP + -0xe0) + 0x78))();
      *(float *)(unaff_EBP + -0x144) = (float)fVar16;
      pAVar7 = (AxisAlignedBox *)(**(code **)(**(int **)(unaff_EBP + -0xe0) + 0x74))();
      Ogre::AxisAlignedBox::AxisAlignedBox((AxisAlignedBox *)(unaff_EBP + -0x1dc),pAVar7);
      *(undefined4 *)(unaff_EBP + -4) = 4;
      Ogre::Vector3::Vector3((Vector3 *)(unaff_EBP + -0x1a8),2.0,2.0,2.0);
      Ogre::AxisAlignedBox::scale
                ((AxisAlignedBox *)(unaff_EBP + -0x1dc),(Vector3 *)(unaff_EBP + -0x1a8));
      pSVar8 = Ogre::Entity::getMesh(*(Entity **)(unaff_EBP + -0xe0));
      FUN_004498d0(pSVar8);
      *(undefined1 *)(unaff_EBP + -4) = 5;
      fVar17 = *(float *)(unaff_EBP + -0x144) * 1.5;
      pMVar9 = (Mesh *)get();
      Ogre::Mesh::_setBoundingSphereRadius(pMVar9,fVar17);
      bVar3 = true;
      pAVar7 = (AxisAlignedBox *)(unaff_EBP + -0x1dc);
      pMVar9 = (Mesh *)get();
      Ogre::Mesh::_setBounds(pMVar9,pAVar7,bVar3);
      *(undefined1 *)(unaff_EBP + -4) = 4;
      FUN_004499a0();
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      Ogre::AxisAlignedBox::~AxisAlignedBox((AxisAlignedBox *)(unaff_EBP + -0x1dc));
    }
    *(undefined4 *)(unaff_EBP + -0xfc) = 0;
    pSVar5 = Ogre::Entity::getSkeleton(*(Entity **)(unaff_EBP + -0xe0));
    *(SkeletonInstance **)(unaff_EBP + -0x118) = pSVar5;
    if (*(int *)(unaff_EBP + -0x118) != 0) {
      (**(code **)(**(int **)(unaff_EBP + -0x118) + 0xd0))(unaff_EBP + -0x188);
LAB_0067f8ce:
      cVar4 = FUN_006624a0();
      if (cVar4 != '\0') {
        uVar6 = FUN_00662470();
        *(undefined4 *)(unaff_EBP + -0xdc) = uVar6;
        pbVar10 = Ogre::Node::getName(*(Node **)(unaff_EBP + -0xdc));
        *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
         (unaff_EBP + -0xd8) = pbVar10;
        pcVar11 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 **)(unaff_EBP + -0xd8),0);
        iVar12 = tolower((int)*pcVar11);
        if (iVar12 == 0x68) {
          pcVar11 = std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 **)(unaff_EBP + -0xd8),1);
          iVar12 = tolower((int)*pcVar11);
          if (iVar12 == 0x6c) {
            pcVar11 = std::
                      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                      operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                   **)(unaff_EBP + -0xd8),2);
            iVar12 = tolower((int)*pcVar11);
            if (iVar12 == 0x67) {
              pcVar11 = std::
                        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                       **)(unaff_EBP + -0xd8),3);
              iVar12 = tolower((int)*pcVar11);
              if (iVar12 == 0x74) {
                pcVar11 = std::
                          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                         **)(unaff_EBP + -0xd8),6);
                iVar12 = tolower((int)*pcVar11);
                *(char *)(unaff_EBP + -0x124) = (char)iVar12;
                pcVar11 = std::
                          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                         **)(unaff_EBP + -0xd8),7);
                iVar12 = tolower((int)*pcVar11);
                *(char *)(unaff_EBP + -0x123) = (char)iVar12;
                *(undefined4 *)(unaff_EBP + -300) = 0x3f800000;
                pcVar11 = std::
                          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                         **)(unaff_EBP + -0xd8),8);
                iVar12 = tolower((int)*pcVar11);
                *(char *)(unaff_EBP + -0x11c) = (char)iVar12;
                pcVar11 = std::
                          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                         **)(unaff_EBP + -0xd8),9);
                iVar12 = tolower((int)*pcVar11);
                *(char *)(unaff_EBP + -0x11b) = (char)iVar12;
                *(undefined4 *)(unaff_EBP + -0x138) = 0x3f800000;
                pcVar11 = std::
                          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                         **)(unaff_EBP + -0xd8),10);
                iVar12 = tolower((int)*pcVar11);
                *(char *)(unaff_EBP + -0x120) = (char)iVar12;
                pcVar11 = std::
                          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                         **)(unaff_EBP + -0xd8),0xb);
                iVar12 = tolower((int)*pcVar11);
                *(char *)(unaff_EBP + -0x11f) = (char)iVar12;
                *(undefined4 *)(unaff_EBP + -0x130) = 0x3f800000;
                uVar6 = (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x11c))();
                *(undefined4 *)(unaff_EBP + -0xe8) = uVar6;
                *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xa8) = *(undefined4 *)(unaff_EBP + -0xe8)
                ;
                Ogre::Light::setDiffuseColour
                          (*(Light **)(unaff_EBP + -0xe8),*(float *)(unaff_EBP + -300),
                           *(float *)(unaff_EBP + -0x138),*(float *)(unaff_EBP + -0x130));
                Ogre::Light::setSpecularColour
                          (*(Light **)(unaff_EBP + -0xe8),*(float *)(unaff_EBP + -300),
                           *(float *)(unaff_EBP + -0x138),*(float *)(unaff_EBP + -0x130));
                Ogre::Light::setAttenuation(*(Light **)(unaff_EBP + -0xe8),600.0,1.0,0.007,0.0002);
                Ogre::Light::setType(*(Light **)(unaff_EBP + -0xe8),2);
                puVar13 = (undefined4 *)(**(code **)(**(int **)(unaff_EBP + -0xdc) + 0x1c))();
                *(undefined4 *)(unaff_EBP + -0x17c) = *puVar13;
                *(undefined4 *)(unaff_EBP + -0x178) = puVar13[1];
                *(undefined4 *)(unaff_EBP + -0x174) = puVar13[2];
                *(undefined4 *)(unaff_EBP + -0x170) = puVar13[3];
                if ((DAT_02cc3344 & 1) == 0) {
                  DAT_02cc3344 = DAT_02cc3344 | 1;
                  *(undefined4 *)(unaff_EBP + -4) = 6;
                  uVar6 = FUN_0044c7a0(0xc0a00000);
                  FUN_00662df0(uVar6);
                  Ogre::Quaternion::Quaternion
                            ((Quaternion *)&DAT_02cc3334,(Radian *)(unaff_EBP + -0x158),
                             (Vector3 *)UNIT_X_exref);
                  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
                }
                pVVar14 = (Vector3 *)(unaff_EBP + -0x1b4);
                this = (Quaternion *)
                       Ogre::Quaternion::operator*
                                 ((Quaternion *)(unaff_EBP + -0x17c),
                                  (Quaternion *)(unaff_EBP + -0x1ec));
                Ogre::Quaternion::operator*(this,pVVar14);
                Ogre::Light::setDirection
                          (*(Light **)(unaff_EBP + -0xe8),(Vector3 *)(unaff_EBP + -0x1b4));
                pVVar14 = (Vector3 *)(**(code **)(**(int **)(unaff_EBP + -0xdc) + 0x34))();
                Ogre::Light::setPosition(*(Light **)(unaff_EBP + -0xe8),pVVar14);
                uVar6 = FUN_0044c7a0(0x41a00000);
                FUN_00662df0(uVar6);
                uVar6 = FUN_0044c7a0(0x41200000);
                FUN_00662df0(uVar6);
                Ogre::Light::setSpotlightRange
                          (*(Light **)(unaff_EBP + -0xe8),(Radian *)(unaff_EBP + -0x14c),
                           (Radian *)(unaff_EBP + -0x148),1.0);
                Ogre::MovableObject::setCastShadows(*(MovableObject **)(unaff_EBP + -0xe8),false);
                (**(code **)(**(int **)(unaff_EBP + -0xf0) + 0x124))
                          (*(undefined4 *)(unaff_EBP + -0xe8));
                goto LAB_0067f8ce;
              }
            }
          }
        }
        pcVar11 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 **)(unaff_EBP + -0xd8),3);
        if (*pcVar11 == '2') {
          uVar6 = (**(code **)(**(int **)(unaff_EBP + -0xdc) + 0x18))();
          *(undefined4 *)(unaff_EBP + -0x128) = uVar6;
          if (*(int *)(unaff_EBP + -0x128) != 0) {
            (**(code **)(**(int **)(unaff_EBP + -0x128) + 0xa8))(*(undefined4 *)(unaff_EBP + -0xdc))
            ;
          }
          Ogre::Bone::setManuallyControlled(*(Bone **)(unaff_EBP + -0xdc),true);
          (**(code **)(**(int **)(unaff_EBP + -0xdc) + 0x38))(0,0,0);
          *(undefined4 *)(unaff_EBP + -0xfc) = *(undefined4 *)(unaff_EBP + -0xec);
          goto LAB_0067f8ce;
        }
        pcVar11 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 **)(unaff_EBP + -0xd8),5);
        iVar12 = tolower((int)*pcVar11);
        if (iVar12 != 0x70) {
LAB_0067fe78:
          pcVar11 = std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 **)(unaff_EBP + -0xd8),5);
          iVar12 = tolower((int)*pcVar11);
          if (iVar12 == 0x67) {
            pcVar11 = std::
                      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                      operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                   **)(unaff_EBP + -0xd8),6);
            iVar12 = tolower((int)*pcVar11);
            if (iVar12 == 99) {
              pcVar11 = std::
                        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                       **)(unaff_EBP + -0xd8),7);
              iVar12 = tolower((int)*pcVar11);
              if (iVar12 == 0x31) {
                if (*(int *)(**(int **)(unaff_EBP + 8) + 0x84) == 4) {
                  *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xac) =
                       *(undefined4 *)(unaff_EBP + -0xdc);
                }
                goto LAB_0067f8ce;
              }
            }
          }
          pcVar11 = std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 **)(unaff_EBP + -0xd8),5);
          iVar12 = tolower((int)*pcVar11);
          if (iVar12 == 0x73) {
            pcVar11 = std::
                      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                      operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                   **)(unaff_EBP + -0xd8),6);
            iVar12 = tolower((int)*pcVar11);
            if (iVar12 == 0x6d) {
              pcVar11 = std::
                        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                       **)(unaff_EBP + -0xd8),7);
              iVar12 = tolower((int)*pcVar11);
              if (iVar12 == 0x31) {
                *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xb0) = *(undefined4 *)(unaff_EBP + -0xdc)
                ;
              }
            }
          }
          goto LAB_0067f8ce;
        }
        pcVar11 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 **)(unaff_EBP + -0xd8),6);
        iVar12 = tolower((int)*pcVar11);
        if (iVar12 != 0x6f) goto LAB_0067fe78;
        pcVar11 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ::operator[](*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 **)(unaff_EBP + -0xd8),7);
        iVar12 = tolower((int)*pcVar11);
        if (iVar12 != 0x76) goto LAB_0067fe78;
        *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xe0) = *(undefined4 *)(unaff_EBP + -0xdc);
        Ogre::Bone::setManuallyControlled(*(Bone **)(unaff_EBP + -0xdc),false);
        goto LAB_0067f8ce;
      }
    }
    *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xb8) = 0;
    DAT_00920eb0 = (int)Ogre::Entity::getAllAnimationStates(*(Entity **)(unaff_EBP + -0xe0));
    if ((AnimationStateSet *)DAT_00920eb0 != (AnimationStateSet *)0x0) {
      basic_string<>(&DAT_00885794);
      *(undefined4 *)(unaff_EBP + -4) = 7;
      bVar3 = Ogre::AnimationStateSet::hasAnimationState
                        ((AnimationStateSet *)DAT_00920eb0,
                         (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          *)(unaff_EBP + -0xd4));
      *(bool *)(unaff_EBP + -0xf4) = bVar3;
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      ~basic_string<>();
      if (*(char *)(unaff_EBP + -0xf4) != '\0') {
        basic_string<>(&DAT_00885794);
        *(undefined4 *)(unaff_EBP + -4) = 8;
        pAVar15 = Ogre::AnimationStateSet::getAnimationState
                            ((AnimationStateSet *)DAT_00920eb0,
                             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              *)(unaff_EBP + -0xbc));
        *(AnimationState **)(unaff_EBP + -0x154) = pAVar15;
        *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
        ~basic_string<>();
        if (*(int *)(unaff_EBP + -0x154) != 0) {
          basic_string<>(&DAT_00885794);
          *(undefined4 *)(unaff_EBP + -4) = 9;
          pAVar15 = Ogre::Entity::getAnimationState
                              (*(Entity **)(unaff_EBP + -0xe0),
                               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)(unaff_EBP + -0x5c));
          *(AnimationState **)(unaff_EBP + -0x100) = pAVar15;
          *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
          ~basic_string<>();
          if (*(int *)(unaff_EBP + -0x100) != 0) {
            Ogre::AnimationState::setEnabled(*(AnimationState **)(unaff_EBP + -0x100),true);
            Ogre::AnimationState::setLoop(*(AnimationState **)(unaff_EBP + -0x100),true);
            fVar16 = (float10)FUN_00822d60();
            Ogre::AnimationState::addTime(*(AnimationState **)(unaff_EBP + -0x100),(float)fVar16);
            *(undefined4 *)(*(int *)(unaff_EBP + 8) + 0xb8) = *(undefined4 *)(unaff_EBP + -0x100);
          }
        }
      }
    }
    *(undefined1 *)(unaff_EBP + -0xe1) = 0;
    *(undefined4 *)(unaff_EBP + -0x104) = 0;
    while (*(uint *)(unaff_EBP + -0x104) < 0xf) {
      *(undefined **)(unaff_EBP + -0x110) = &DAT_008ed2e8 + *(int *)(unaff_EBP + -0x104) * 0x40;
      *(undefined4 *)(unaff_EBP + -0x108) = *(undefined4 *)(unaff_EBP + -0xec);
      do {
        bVar1 = **(byte **)(unaff_EBP + -0x108);
        *(byte *)(unaff_EBP + -0xf2) = bVar1;
        bVar3 = bVar1 < **(byte **)(unaff_EBP + -0x110);
        if (bVar1 != **(byte **)(unaff_EBP + -0x110)) {
LAB_0068015f:
          *(uint *)(unaff_EBP + -0x134) = -(uint)bVar3 | 1;
          goto LAB_0068016a;
        }
        if (*(char *)(unaff_EBP + -0xf2) == '\0') break;
        bVar1 = *(byte *)(*(int *)(unaff_EBP + -0x108) + 1);
        *(byte *)(unaff_EBP + -0xf1) = bVar1;
        bVar2 = *(byte *)(*(int *)(unaff_EBP + -0x110) + 1);
        bVar3 = bVar1 < bVar2;
        if (bVar1 != bVar2) goto LAB_0068015f;
        *(int *)(unaff_EBP + -0x108) = *(int *)(unaff_EBP + -0x108) + 2;
        *(int *)(unaff_EBP + -0x110) = *(int *)(unaff_EBP + -0x110) + 2;
      } while (*(char *)(unaff_EBP + -0xf1) != '\0');
      *(undefined4 *)(unaff_EBP + -0x134) = 0;
LAB_0068016a:
      *(undefined4 *)(unaff_EBP + -0x15c) = *(undefined4 *)(unaff_EBP + -0x134);
      if (*(int *)(unaff_EBP + -0x15c) == 0) {
        *(char **)(unaff_EBP + -0xfc) = s_avartl_c_008ed308 + *(int *)(unaff_EBP + -0x104) * 0x40;
        *(undefined1 *)(unaff_EBP + -0xe1) = 1;
        break;
      }
      *(int *)(unaff_EBP + -0x104) = *(int *)(unaff_EBP + -0x104) + 1;
    }
    if (*(char *)(unaff_EBP + -0xe1) == '\0') {
      sprintf((char *)(unaff_EBP + -0x44),"%.16s_cockpit.mesh",*(undefined4 *)(unaff_EBP + -0xec));
      basic_string<>(unaff_EBP + -0x44);
      *(undefined4 *)(unaff_EBP + -4) = 10;
      pbVar10 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                (unaff_EBP + -0x8c);
      this_00 = Ogre::ResourceGroupManager::getSingleton();
      bVar3 = Ogre::ResourceGroupManager::resourceExistsInAnyGroup(this_00,pbVar10);
      *(bool *)(unaff_EBP + -0xf3) = bVar3;
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      ~basic_string<>();
      if (*(char *)(unaff_EBP + -0xf3) != '\0') {
        sprintf((char *)(unaff_EBP + -0x44),"%.16s_cockpit",*(undefined4 *)(unaff_EBP + -0xec));
        *(int *)(unaff_EBP + -0xfc) = unaff_EBP + -0x44;
      }
    }
    if (*(int *)(unaff_EBP + -0xfc) != 0) {
      if (*(int *)(unaff_EBP + -0xfc) == *(int *)(unaff_EBP + -0xec)) {
        *(undefined1 *)(unaff_EBP + -0xe2) = 0;
      }
      else {
        *(undefined1 *)(unaff_EBP + -0xe2) = 1;
      }
      FUN_0067e5a0(*(undefined4 *)(unaff_EBP + 8),*(undefined4 *)(unaff_EBP + -0xfc),
                   *(undefined1 *)(unaff_EBP + -0xe2));
    }
    iVar12 = FUN_0062c840();
    if (*(int *)(unaff_EBP + 8) == iVar12) {
      FUN_00680920(*(undefined4 *)(unaff_EBP + 8));
    }
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

