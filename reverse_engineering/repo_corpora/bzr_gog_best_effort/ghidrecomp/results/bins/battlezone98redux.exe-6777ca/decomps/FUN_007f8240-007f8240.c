
undefined4 FUN_007f8240(allocator<char> *param_1,undefined1 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined1 *puVar9;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  uVar5 = FUN_007f8960(param_2);
  uVar5 = FUN_007d74e0(uVar5);
  param_4 = param_4 + 1;
  param_2 = FUN_007f8980(&param_2,param_3,param_4,uVar5);
  cVar1 = FUN_007f89a0(param_2);
  if (cVar1 == '\0') {
    uVar6 = FUN_007f8960(param_2);
    uVar6 = FUN_007d74e0(uVar6);
    param_4 = param_4 + 1;
    param_2 = FUN_007f8980(&param_2,param_3,param_4,uVar5,uVar6);
    cVar1 = FUN_007f89a0(param_2);
    if (cVar1 == '\0') {
      uVar7 = FUN_007f8960(param_2);
      uVar7 = FUN_007d74e0(uVar7);
      param_4 = param_4 + 1;
      param_2 = FUN_007f8980(&param_2,param_3,param_4,uVar5,uVar6,uVar7);
      cVar1 = FUN_007f89a0(param_2);
      if (cVar1 == '\0') {
        uVar8 = FUN_007f8960(param_2);
        uVar8 = FUN_007d74e0(uVar8);
        param_4 = param_4 + 1;
        param_2 = FUN_007f8980(&param_2,param_3,param_4,uVar5,uVar6,uVar7,uVar8);
        local_8 = (undefined1)uVar8;
        cVar1 = FUN_007f89a0(param_2);
        if (cVar1 == '\0') {
          uVar8 = FUN_007f8960(param_2);
          uVar2 = FUN_007d74e0(uVar8);
          param_4 = param_4 + 1;
          param_2 = FUN_007f8980(&param_2,param_3,param_4);
          cVar1 = FUN_007f89a0(param_2);
          if (cVar1 == '\0') {
            uVar8 = FUN_007f8960(param_2);
            uVar3 = FUN_007d74e0(uVar8);
            param_4 = param_4 + 1;
            param_2 = FUN_007f8980(&param_2,param_3,param_4);
            cVar1 = FUN_007f89a0(param_2);
            if (cVar1 == '\0') {
              uVar8 = FUN_007f8960(param_2);
              uVar4 = FUN_007d74e0(uVar8);
              param_4 = param_4 + 1;
              param_2 = FUN_007f8980(&param_2,param_3,param_4);
              cVar1 = FUN_007f89a0(param_2);
              if (cVar1 == '\0') {
                FUN_007f8240(param_1,param_2,param_3,param_4);
              }
              puVar9 = &local_5;
              local_5 = uVar4;
              std::allocator<char>::allocator<char>(param_1);
              FUN_007f0750(puVar9);
              FUN_007efea0();
            }
            puVar9 = &local_6;
            local_6 = uVar3;
            std::allocator<char>::allocator<char>(param_1);
            FUN_007f0750(puVar9);
            FUN_007efea0();
          }
          puVar9 = &local_7;
          local_7 = uVar2;
          std::allocator<char>::allocator<char>(param_1);
          FUN_007f0750(puVar9);
          FUN_007efea0();
        }
        puVar9 = &local_8;
        std::allocator<char>::allocator<char>(param_1);
        FUN_007f0750(puVar9);
        FUN_007efea0();
      }
      local_9 = (undefined1)uVar7;
      puVar9 = &local_9;
      std::allocator<char>::allocator<char>(param_1);
      FUN_007f0750(puVar9);
      FUN_007efea0();
    }
    local_a = (undefined1)uVar6;
    puVar9 = &local_a;
    std::allocator<char>::allocator<char>(param_1);
    FUN_007f0750(puVar9);
    FUN_007efea0();
  }
  local_b = (undefined1)uVar5;
  puVar9 = &local_b;
  std::allocator<char>::allocator<char>(param_1);
  FUN_007f0750(puVar9);
  FUN_007efea0();
  return 1;
}

