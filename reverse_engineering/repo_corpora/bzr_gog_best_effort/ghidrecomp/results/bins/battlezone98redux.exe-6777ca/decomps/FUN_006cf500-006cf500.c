
/* WARNING: Removing unreachable block (ram,0x006cf546) */

int __thiscall FUN_006cf500(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 local_9 [2];
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  if (param_1 != param_2) {
    FUN_00425fd0();
    uVar1 = Getal(&local_6);
    uVar2 = Getal(&local_7);
    operator!=<>(uVar2,uVar1);
    uVar1 = FUN_00422f60(local_9);
    FUN_004178a0(uVar1);
    local_5 = 0;
    FUN_006dd660(param_2,0);
  }
  return param_1;
}

