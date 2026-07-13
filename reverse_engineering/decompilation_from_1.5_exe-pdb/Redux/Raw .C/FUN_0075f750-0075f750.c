
/* WARNING: Removing unreachable block (ram,0x0075f7de) */

void __thiscall FUN_0075f750(_Container_base0 *param_1,_Container_base0 *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
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
    _Swap_adl<>(param_1,param_2);
    _Swap_adl<>(param_1 + 4,param_2 + 4);
    _Swap_adl<>(param_1 + 8,param_2 + 8);
  }
  return;
}

