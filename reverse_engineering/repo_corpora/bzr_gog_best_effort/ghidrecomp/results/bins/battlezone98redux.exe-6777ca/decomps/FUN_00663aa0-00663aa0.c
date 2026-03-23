
void __fastcall FUN_00663aa0(int param_1)

{
  int iVar1;
  uint uVar2;
  CompositorManager *pCVar3;
  CompositorInstance *pCVar4;
  void *pvVar5;
  Viewport *pVVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar7;
  bool bVar8;
  undefined4 local_7c;
  bool local_78;
  undefined4 local_6c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084dda0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar1 = FUN_00684ce0(0,local_14);
  if (iVar1 != 0) {
    if (((*(char *)(DAT_0094672c + 0x28) == '\x01') && (DAT_008fe240 == 1)) &&
       (uVar2 = Ogre::Viewport::getVisibilityMask(*(Viewport **)(param_1 + 0x1c)), uVar2 == 1)) {
      local_78 = true;
    }
    else {
      local_78 = false;
    }
    iVar1 = FUN_00434160();
    if ((iVar1 != 9) &&
       (((bool)*(char *)(param_1 + 0x40) != local_78 ||
        ((*(char *)(param_1 + 0x41) == '\0' && (local_78 != false)))))) {
      if (*(char *)(param_1 + 0x41) == '\0') {
        basic_string<>(&DAT_00892138);
        local_8 = 0;
        iVar1 = 0;
        pbVar7 = local_5c;
        pVVar6 = *(Viewport **)(param_1 + 0x1c);
        pCVar3 = Ogre::CompositorManager::getSingleton();
        pCVar4 = Ogre::CompositorManager::addCompositor(pCVar3,pVVar6,pbVar7,iVar1);
        local_8 = 0xffffffff;
        ~basic_string<>();
        if (pCVar4 != (CompositorInstance *)0x0) {
          basic_string<>(&DAT_00892138);
          local_8 = 1;
          pbVar7 = local_44;
          pVVar6 = *(Viewport **)(param_1 + 0x1c);
          bVar8 = local_78;
          pCVar3 = Ogre::CompositorManager::getSingleton();
          Ogre::CompositorManager::setCompositorEnabled(pCVar3,pVVar6,pbVar7,bVar8);
          local_8 = 0xffffffff;
          ~basic_string<>();
          pvVar5 = operator_new(0xc);
          local_8 = 2;
          if (pvVar5 == (void *)0x0) {
            local_7c = 0;
          }
          else {
            local_7c = FUN_00662f60();
          }
          local_8 = 0xffffffff;
          *(undefined4 *)(param_1 + 0x44) = local_7c;
          pvVar5 = operator_new(0x1c);
          local_8 = 3;
          if (pvVar5 == (void *)0x0) {
            local_6c = 0;
          }
          else {
            local_6c = FUN_00663210(pCVar4);
          }
          local_8 = 0xffffffff;
          *(undefined4 *)(param_1 + 0x48) = local_6c;
          *(undefined1 *)(param_1 + 0x41) = 1;
        }
      }
      else {
        basic_string<>(&DAT_00892138);
        local_8 = 4;
        pbVar7 = local_2c;
        pVVar6 = *(Viewport **)(param_1 + 0x1c);
        bVar8 = local_78;
        pCVar3 = Ogre::CompositorManager::getSingleton();
        Ogre::CompositorManager::setCompositorEnabled(pCVar3,pVVar6,pbVar7,bVar8);
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      *(bool *)(param_1 + 0x40) = local_78;
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

