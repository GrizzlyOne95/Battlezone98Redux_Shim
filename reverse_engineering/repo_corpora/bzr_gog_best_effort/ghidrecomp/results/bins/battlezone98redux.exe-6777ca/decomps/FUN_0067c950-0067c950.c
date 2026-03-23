
void FUN_0067c950(void)

{
  char cVar1;
  Root *this;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  undefined4 uVar3;
  RenderSystem *local_24;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  this = Ogre::Root::getSingletonPtr();
  local_24 = (RenderSystem *)0x0;
  if (this != (Root *)0x0) {
    local_24 = Ogre::Root::getRenderSystem(this);
  }
  if (local_24 != (RenderSystem *)0x0) {
    pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (**(code **)(*(int *)local_24 + 4))();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_20,pbVar2);
    uVar3 = (**(code **)(*(int *)local_24 + 4))("Direct3D9 Rendering Subsystem");
    cVar1 = FUN_00427270(uVar3);
    if (cVar1 == '\0') {
      uVar3 = (**(code **)(*(int *)local_24 + 4))("Direct3D11 Rendering Subsystem");
      cVar1 = FUN_00427270(uVar3);
      if (cVar1 == '\0') {
        uVar3 = (**(code **)(*(int *)local_24 + 4))("OpenGL Rendering Subsystem");
        cVar1 = FUN_00427270(uVar3);
        if (cVar1 == '\0') {
          ~basic_string<>();
        }
        else {
          ~basic_string<>();
        }
      }
      else {
        ~basic_string<>();
      }
    }
    else {
      ~basic_string<>(2);
    }
  }
  FUN_0083e885();
  return;
}

