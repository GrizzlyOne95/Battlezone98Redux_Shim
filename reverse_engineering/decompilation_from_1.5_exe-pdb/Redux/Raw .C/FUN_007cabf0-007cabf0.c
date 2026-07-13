
void __thiscall FUN_007cabf0(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  float10 fVar10;
  undefined8 uVar11;
  float local_84;
  undefined1 local_5c [24];
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862518;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar3;
  basic_string<>(param_2);
  local_8 = 0;
  uVar11 = FUN_00689eb0(uVar3);
  FUN_00689ec0((float)uVar11 * *(float *)(param_1 + 0x174),
               (float)((ulonglong)uVar11 >> 0x20) * *(float *)(param_1 + 0x174));
  uVar4 = FUN_0041f870();
  fVar10 = (float10)FUN_00689cb0(DAT_0091552c,uVar4);
  while (local_84 = (float)fVar10, *(float *)(param_1 + 0xc) <= local_84) {
    cVar2 = FUN_0041f890();
    if (cVar2 != '\0') break;
    iVar5 = FUN_004170c0();
    uVar4 = FUN_0045e1d0(local_5c,0,iVar5 + -1);
    FUN_0045e0f0(uVar4);
    ~basic_string<>();
    uVar4 = FUN_0041f870();
    fVar10 = (float10)FUN_00689cb0(DAT_0091552c,uVar4);
  }
  pcVar6 = (char *)FUN_0041f870();
  iVar5 = FUN_0066b150();
  if (param_3 == iVar5) {
    basic_string<>(pcVar6);
    local_8._0_1_ = 1;
    uVar4 = FUN_007c9d40(local_44,param_4);
    local_8._0_1_ = 2;
    FUN_007cb640(uVar4);
    local_8._0_1_ = 1;
    FUN_00430320();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
  }
  else {
    this = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_0066b170(param_3);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (this,pcVar6);
    iVar5 = FUN_0066b170(param_3);
    *(undefined4 *)(iVar5 + 0x18) = param_4;
  }
  cVar2 = FUN_007d3360();
  if (cVar2 != '\0') {
    uVar3 = FUN_0066b150();
    uVar7 = size();
    if (uVar7 < uVar3) {
      (**(code **)(**(int **)(param_1 + 0x178) + 0x24))(1);
      (**(code **)(**(int **)(param_1 + 0x17c) + 0x24))(1);
      goto LAB_007cae78;
    }
  }
  (**(code **)(**(int **)(param_1 + 0x178) + 0x24))(0);
  (**(code **)(**(int **)(param_1 + 0x17c) + 0x24))(0);
LAB_007cae78:
  iVar5 = param_3 - *(int *)(param_1 + 0x150);
  if (-1 < iVar5) {
    iVar8 = size();
    if (iVar5 < iVar8) {
      puVar9 = (undefined4 *)FUN_004200d0(iVar5);
      piVar1 = (int *)*puVar9;
      FUN_0066b170(param_3);
      uVar4 = FUN_0041f870();
      (**(code **)(*piVar1 + 0x3c))(uVar4);
      uVar4 = *(undefined4 *)(param_1 + 0x174);
      FUN_004200d0(iVar5);
      FUN_007cc6b0(uVar4);
      FUN_004200d0(iVar5);
      uVar4 = FUN_007ccaf0();
      FUN_004200d0(iVar5);
      FUN_007cca20(uVar4);
    }
  }
  FUN_00689ec0(uVar11);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

