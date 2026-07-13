
/* WARNING: Removing unreachable block (ram,0x0074d53d) */

void __thiscall FUN_0074d4b0(_Container_base0 *param_1,_Container_base0 *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  if (param_1 != param_2) {
    uVar2 = Getal(&local_5);
    uVar3 = Getal(&local_6);
    cVar1 = operator==<>(uVar3,uVar2);
    if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
      terminate();
    }
    std::_Container_base0::_Swap_all(param_1,param_2);
    uVar2 = FUN_00422f60(&local_7);
    FUN_004178a0(uVar2);
    _Swap_adl<>(param_1,param_2);
    swap<>(param_1 + 4,param_2 + 4);
  }
  return;
}

