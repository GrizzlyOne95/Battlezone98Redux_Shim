/*
 * Entry: 004685e2
 * Name: GetUnitMsg
 * Namespace: Global
 * Signature: char * GetUnitMsg(Craft * param_1, UnitMsg param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl GetUnitMsg(Craft *param_1,UnitMsg param_2,int param_3)

{
  int in_EAX;
  int iVar1;
  undefined4 unaff_EDI;
  
  iVar1 = (*(code *)**(undefined4 **)(in_EAX + 0x20))();
  switch(unaff_EDI) {
  case 0:
    return (char *)(iVar1 + 0x160);
  case 1:
    return (char *)(iVar1 + 0x170);
  case 2:
    return (char *)(iVar1 + 0x180);
  case 3:
    return (char *)(iVar1 + 400);
  case 4:
    return (char *)(iVar1 + 0x1a0);
  case 5:
    return (char *)(iVar1 + 0x1b0);
  case 6:
    return (char *)(iVar1 + 0x1c0);
  case 7:
    return (char *)(iVar1 + 0x1d0);
  case 8:
    return (char *)(iVar1 + 0x1e0);
  case 9:
    return (char *)(iVar1 + 0x1f0);
  case 10:
    return (char *)(iVar1 + 0x200);
  case 0xb:
    return (char *)(iVar1 + 0x210);
  case 0xc:
    return (char *)(iVar1 + 0x220);
  case 0xd:
    return (char *)(iVar1 + 0x230);
  case 0xe:
    return (char *)(iVar1 + 0x240);
  case 0xf:
    return (char *)(iVar1 + 0x250);
  case 0x10:
    return (char *)(iVar1 + 0x260);
  case 0x11:
    return (char *)(iVar1 + 0x270);
  case 0x12:
    return (char *)(iVar1 + 0x280);
  case 0x13:
    return (char *)(iVar1 + 0x290);
  case 0x14:
    return (char *)(iVar1 + 0x2a0);
  case 0x15:
    return (char *)(iVar1 + 0x2b0);
  case 0x16:
    return (char *)(iVar1 + 0x2c0);
  case 0x17:
    return (char *)(iVar1 + 0x2d0);
  case 0x18:
    return (char *)(iVar1 + 0x2e0);
  case 0x19:
    return (char *)(iVar1 + 0x2f0);
  case 0x1a:
    iVar1 = (*(code *)**(undefined4 **)(in_EAX + 0x20))();
    return (char *)(iVar1 + 0x41c);
  default:
    return (char *)0x0;
  }
}
