
void __fastcall FUN_007d1eb0(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  MaterialManager *pMVar7;
  int local_34;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00862aea;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_View::vftable;
  local_8 = 3;
  DAT_009456d4 = DAT_009456d4 + -1;
  local_14 = uVar2;
  for (local_34 = 0; iVar3 = size(uVar2), local_34 < iVar3; local_34 = local_34 + 1) {
    piVar4 = (int *)FUN_004200d0(local_34);
    if ((undefined4 *)*piVar4 != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)*piVar4)(1);
    }
  }
  FUN_0041ff50();
  if (param_1[0x48] != 0) {
    (**(code **)(*(int *)param_1[0x48] + 100))();
    (**(code **)(*(int *)param_1[0x48] + 0x100))();
    iVar3 = FUN_0044d2a0();
    piVar4 = *(int **)(iVar3 + 8);
    uVar5 = (**(code **)(*(int *)param_1[0x48] + 0x48))();
    (**(code **)(*piVar4 + 0x1ac))(uVar5);
    param_1[0x48] = 0;
  }
  if (param_1[0x50] != 0) {
    if ((undefined4 *)param_1[0x50] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)param_1[0x50])(1);
    }
    param_1[0x50] = 0;
    cVar1 = FUN_004c85a0();
    if (cVar1 == '\0') {
      piVar4 = (int *)get();
      pbVar6 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (**(code **)(*piVar4 + 0x58))();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar6);
      local_8._0_1_ = 4;
      FUN_004c85d0();
      pMVar7 = Ogre::MaterialManager::getSingleton();
      (**(code **)(*(int *)pMVar7 + 0x38))(local_2c);
      local_8 = CONCAT31(local_8._1_3_,3);
      ~basic_string<>();
    }
  }
  local_8._0_1_ = 2;
  FUN_0041fe20();
  local_8._0_1_ = 1;
  FUN_004499a0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004499a0();
  local_8 = 0xffffffff;
  FUN_007c5450();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

