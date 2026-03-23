
undefined4
FUN_007f6520(allocator<char> *param_1,shared_ptr<class___ExceptionPtr> *param_2,
            __ExceptionPtr *param_3,undefined4 param_4,int param_5)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined4 extraout_EAX;
  undefined4 uVar5;
  undefined4 extraout_EAX_00;
  undefined4 uVar6;
  undefined4 extraout_EAX_01;
  undefined4 uVar7;
  undefined4 extraout_EAX_02;
  undefined4 uVar8;
  undefined4 extraout_EAX_03;
  undefined4 extraout_EAX_04;
  undefined4 extraout_EAX_05;
  undefined8 uVar9;
  undefined1 *puVar10;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(param_2,param_3);
  uVar5 = FUN_0070d5f0(extraout_EAX);
  param_5 = param_5 + 1;
  _param_2 = FUN_007f7740(&param_2,param_4,param_5,uVar5);
  cVar1 = FUN_007f7770(_param_2);
  if (cVar1 == '\0') {
    std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(param_2,param_3);
    uVar6 = FUN_0070d5f0(extraout_EAX_00);
    param_5 = param_5 + 1;
    uVar9 = FUN_007f7740(&param_2,param_4,param_5,uVar5,uVar6);
    _param_2 = uVar9;
    cVar1 = FUN_007f7770(uVar9);
    if (cVar1 == '\0') {
      std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(param_2,param_3);
      uVar7 = FUN_0070d5f0(extraout_EAX_01);
      param_5 = param_5 + 1;
      uVar9 = FUN_007f7740(&param_2,param_4,param_5,uVar5,uVar6,uVar7);
      _param_2 = uVar9;
      cVar1 = FUN_007f7770(uVar9);
      if (cVar1 == '\0') {
        std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(param_2,param_3);
        uVar8 = FUN_0070d5f0(extraout_EAX_02);
        param_5 = param_5 + 1;
        uVar9 = FUN_007f7740(&param_2,param_4,param_5,uVar5,uVar6,uVar7,uVar8);
        local_8 = (undefined1)uVar8;
        _param_2 = uVar9;
        cVar1 = FUN_007f7770(uVar9);
        if (cVar1 == '\0') {
          std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(param_2,param_3);
          uVar2 = FUN_0070d5f0(extraout_EAX_03);
          param_5 = param_5 + 1;
          uVar9 = FUN_007f7740(&param_2,param_4,param_5);
          _param_2 = uVar9;
          cVar1 = FUN_007f7770(uVar9);
          if (cVar1 == '\0') {
            std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                      (param_2,param_3);
            uVar3 = FUN_0070d5f0(extraout_EAX_04);
            param_5 = param_5 + 1;
            uVar9 = FUN_007f7740(&param_2,param_4,param_5);
            _param_2 = uVar9;
            cVar1 = FUN_007f7770(uVar9);
            if (cVar1 == '\0') {
              std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                        (param_2,param_3);
              uVar4 = FUN_0070d5f0(extraout_EAX_05);
              param_5 = param_5 + 1;
              uVar9 = FUN_007f7740(&param_2,param_4,param_5);
              _param_2 = uVar9;
              cVar1 = FUN_007f7770(uVar9);
              if (cVar1 == '\0') {
                FUN_007f6520(param_1,_param_2,param_4,param_5);
              }
              puVar10 = &local_5;
              local_5 = uVar4;
              std::allocator<char>::allocator<char>(param_1);
              FUN_007f0750(puVar10);
              FUN_007efea0();
            }
            puVar10 = &local_6;
            local_6 = uVar3;
            std::allocator<char>::allocator<char>(param_1);
            FUN_007f0750(puVar10);
            FUN_007efea0();
          }
          puVar10 = &local_7;
          local_7 = uVar2;
          std::allocator<char>::allocator<char>(param_1);
          FUN_007f0750(puVar10);
          FUN_007efea0();
        }
        puVar10 = &local_8;
        std::allocator<char>::allocator<char>(param_1);
        FUN_007f0750(puVar10);
        FUN_007efea0();
      }
      local_9 = (undefined1)uVar7;
      puVar10 = &local_9;
      std::allocator<char>::allocator<char>(param_1);
      FUN_007f0750(puVar10);
      FUN_007efea0();
    }
    local_a = (undefined1)uVar6;
    puVar10 = &local_a;
    std::allocator<char>::allocator<char>(param_1);
    FUN_007f0750(puVar10);
    FUN_007efea0();
  }
  local_b = (undefined1)uVar5;
  puVar10 = &local_b;
  std::allocator<char>::allocator<char>(param_1);
  FUN_007f0750(puVar10);
  FUN_007efea0();
  return 1;
}

