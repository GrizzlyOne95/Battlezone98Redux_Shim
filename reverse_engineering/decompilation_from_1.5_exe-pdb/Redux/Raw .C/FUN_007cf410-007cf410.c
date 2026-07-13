
void FUN_007cf410(undefined1 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  float fVar4;
  undefined8 uVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 local_40;
  float local_3c;
  float local_38;
  float local_34;
  undefined4 *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086287a;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_007cc390(param_4,param_5,param_6,param_7,param_8,param_9,param_10,0);
  local_8 = 0;
  *local_30 = cUI_TextEntry::vftable;
  basic_string<>(uVar1);
  local_8._0_1_ = 1;
  local_30[0x253] = 0;
  *(undefined1 *)(local_30 + 0x254) = param_2;
  local_30[0x256] = 0;
  local_30[599] = 0;
  *(undefined1 *)(local_30 + 600) = param_1;
  local_30[0x259] = 0xffffffff;
  local_30[0x252] = param_3;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (local_30 + 0x24c),"");
  FUN_007d3f20(2);
  uVar5 = FUN_00689eb0();
  FUN_00689ec0((float)uVar5 * (float)local_30[0x248],
               (float)((ulonglong)uVar5 >> 0x20) * (float)local_30[0x248]);
  fVar4 = ((float)local_30[3] * 2.0) / (float)local_30[0x3d];
  local_3c = 0.0;
  FUN_00689ab0(DAT_0091552c,&DAT_00894668,0,&local_3c,uVar1,fVar4);
  local_34 = local_3c * 1.2;
  if (local_30[0x245] == 1) {
    local_38 = ((float)local_30[4] * 0.5 + local_3c * 0.5) - local_34;
  }
  else if (local_30[0x245] == 2) {
    local_38 = (float)local_30[4] - local_34;
  }
  else {
    local_38 = local_3c - local_34;
  }
  uVar11 = 0;
  FUN_00689ec0(uVar5,uVar1,fVar4,0);
  basic_string<>(param_4);
  local_8._0_1_ = 2;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,"_textInputCursor");
  pvVar2 = operator_new(0x144);
  local_8._0_1_ = 3;
  if (pvVar2 == (void *)0x0) {
    local_40 = 0;
  }
  else {
    uVar10 = 0;
    uVar8 = 8;
    fVar6 = local_38;
    fVar7 = local_34;
    puVar9 = local_30;
    uVar3 = FUN_0041f870(uVar11,local_38,fVar4,local_34,8,local_30,0);
    local_40 = FUN_007d1cc0(uVar3,uVar11,fVar6,fVar4,fVar7,uVar8,puVar9,uVar10);
  }
  local_8._0_1_ = 2;
  local_30[0x255] = local_40;
  FUN_007d3f20(7);
  FUN_007d2870("textInputCursor.png");
  FUN_007d2110(local_30[0x255],0);
  local_8 = CONCAT31(local_8._1_3_,1);
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

