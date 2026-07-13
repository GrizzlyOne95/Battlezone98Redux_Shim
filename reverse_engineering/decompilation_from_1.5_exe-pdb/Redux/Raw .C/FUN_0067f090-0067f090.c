
void FUN_0067f090(undefined4 param_1,undefined4 param_2)

{
  uint uStack_98;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_88 [8];
  undefined1 local_80 [20];
  undefined4 local_6c;
  undefined4 local_68;
  MeshManager *local_64;
  SubMesh *local_60;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_5c;
  Mesh *local_58;
  undefined4 local_54;
  MaterialManager *local_50;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_4c;
  SubMesh *local_48;
  QuickBitSet local_44 [8];
  MaterialManager *local_3c;
  undefined4 local_38;
  char local_31;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [24];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f744;
  local_10 = ExceptionList;
  uStack_98 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_98;
  ExceptionList = &local_10;
  local_38 = 0;
  local_18 = uStack_98;
  Concurrency::details::QuickBitSet::QuickBitSet(local_44);
  local_8._0_1_ = 2;
  local_8._1_3_ = 0;
  local_6c = basic_string<>(param_2);
  local_8._0_1_ = 3;
  local_64 = Ogre::MeshManager::getSingleton();
  local_68 = Ogre::MeshManager::load
                       (local_64,local_88,local_30,(Usage)AUTODETECT_RESOURCE_GROUP_NAME_exref,1,
                        true,false);
  local_8._0_1_ = 4;
  local_54 = local_68;
  FUN_00449910(local_68);
  local_8._0_1_ = 3;
  FUN_004499a0();
  local_8 = CONCAT31(local_8._1_3_,2);
  ~basic_string<>();
  local_58 = (Mesh *)get();
  Ogre::Mesh::getSubMeshIterator(local_58);
  while( true ) {
    local_31 = FUN_006624a0();
    if (local_31 == '\0') break;
    local_60 = (SubMesh *)FUN_00662470();
    local_48 = local_60;
    local_5c = Ogre::SubMesh::getMaterialName(local_60);
    local_4c = local_5c;
    local_50 = Ogre::MaterialManager::getSingleton();
    local_3c = local_50;
    (**(code **)(*(int *)local_50 + 0x68))
              (local_80,local_4c,AUTODETECT_RESOURCE_GROUP_NAME_exref,0,0,0,0);
    FUN_004499a0();
  }
  FUN_0067f1f0();
  return;
}

