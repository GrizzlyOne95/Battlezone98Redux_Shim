
void FUN_0067eef0(int param_1,int param_2)

{
  ResourceGroupManager *this;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  undefined1 local_b8 [8];
  undefined1 local_b0 [8];
  undefined1 local_a8 [8];
  int local_a0;
  uint local_9c;
  char local_95;
  undefined1 local_94 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_7c [24];
  undefined1 local_64 [24];
  undefined1 local_4c [24];
  char local_34 [32];
  char local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_008e8c0f == '\0') {
    sprintf(local_14,"%.8s",&param_1);
    basic_string<>(local_14);
    FUN_004222c0(local_b8,local_4c);
    ~basic_string<>();
    for (local_9c = 0; local_9c < 0xf; local_9c = local_9c + 1) {
      local_a0 = local_9c * 0x40;
      if ((param_1 == *(int *)(&DAT_008ed2e8 + local_a0)) &&
         (param_2 == *(int *)(&DAT_008ed2ec + local_a0))) {
        basic_string<>(s_avartl_c_008ed308 + local_9c * 0x40);
        FUN_004222c0(local_b0,local_94);
        ~basic_string<>();
        goto LAB_0067f079;
      }
    }
    sprintf(local_34,"%.9s_cockpit.mesh",local_14);
    basic_string<>(local_34);
    pbVar1 = local_7c;
    this = Ogre::ResourceGroupManager::getSingleton();
    local_95 = Ogre::ResourceGroupManager::resourceExistsInAnyGroup(this,pbVar1);
    ~basic_string<>();
    if (local_95 != '\0') {
      sprintf(local_34,"%.16s_cockpit",local_14);
      basic_string<>(local_34);
      FUN_004222c0(local_a8,local_64);
      ~basic_string<>();
    }
  }
LAB_0067f079:
  FUN_0083e885();
  return;
}

