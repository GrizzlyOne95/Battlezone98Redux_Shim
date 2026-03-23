
void __fastcall FUN_00777ef0(void *param_1)

{
  uint uVar1;
  Mesh *this;
  int *piVar2;
  MeshManager *pMVar3;
  undefined4 uVar4;
  ushort uVar5;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085e3ab;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
    for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
      (**(code **)(**(int **)((int)param_1 + local_18 * 4 + local_14 * 0x10 + 0x80) + 0x138))
                (*(undefined4 *)((int)param_1 + local_18 * 4 + local_14 * 0x10 + 0xc0),uVar1);
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x194))
                (*(undefined4 *)((int)param_1 + local_18 * 4 + local_14 * 0x10 + 0xc0));
      uVar5 = 0;
      this = (Mesh *)get();
      Ogre::Mesh::destroySubMesh(this,uVar5);
      piVar2 = (int *)get();
      pMVar3 = Ogre::MeshManager::getSingleton();
      uVar4 = (**(code **)(*piVar2 + 0x58))();
      (**(code **)(*(int *)pMVar3 + 0x38))(uVar4);
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x15c))
                (*(undefined4 *)((int)param_1 + local_18 * 4 + local_14 * 0x10 + 0x80));
      *(undefined4 *)((int)param_1 + local_18 * 4 + local_14 * 0x10 + 0x80) = 0;
      FUN_004c85d0();
      *(undefined4 *)((int)param_1 + local_18 * 4 + local_14 * 0x10 + 0xc0) = 0;
    }
  }
  local_8 = 0xffffffff;
  _eh_vector_destructor_iterator_(param_1,8,0x10,FUN_004499a0);
  ExceptionList = local_10;
  return;
}

