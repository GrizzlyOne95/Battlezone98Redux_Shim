/*
 * Entry: 004caacb
 * Name: EditTerrain::CreateMenu
 * Namespace: EditTerrain
 * Signature: void CreateMenu(EditTerrain * this, tagIconMenu * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::CreateMenu(EditTerrain *this,tagIconMenu *param_1)

{
  int iVar1;
  tagIconMenu *ptVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int local_1c;
  int local_18;
  int local_14;
  tagIconMenu *local_10;
  int local_c;
  int local_8;
  
  ptVar2 = param_1;
  iVar1 = param_1->icon->index;
  iVar5 = param_1->icons / 2;
  local_c = GetSpriteWidth(iVar1);
  iVar3 = GetSpriteHeight(iVar1);
  local_10 = (tagIconMenu *)0x0;
  iVar1 = local_c + 0xb;
  local_c = local_c + 0x1a;
  local_8 = 0x11;
  local_1c = 2;
  do {
    local_14 = 0x11;
    if (0 < iVar5) {
      param_1 = local_10;
      local_18 = iVar5;
      do {
        puVar6 = (undefined4 *)((int)&param_1->icon + (int)ptVar2->icon);
        iVar4 = GetSpriteIndex((char *)*puVar6);
        param_1 = (tagIconMenu *)&param_1[1].rect;
        puVar6[4] = iVar4;
        puVar6[5] = local_8;
        puVar6[7] = local_c;
        iVar4 = iVar3 + 9 + local_14;
        puVar6[6] = local_14;
        local_14 = local_14 + iVar3 + 0xb;
        local_18 = local_18 + -1;
        puVar6[8] = iVar4;
      } while (local_18 != 0);
    }
    local_8 = local_8 + iVar1;
    local_c = local_c + iVar1;
    local_10 = (tagIconMenu *)((int)local_10 + iVar5 * 0x24);
    local_1c = local_1c + -1;
  } while (local_1c != 0);
  (ptVar2->rect).right = iVar1 * 2 + 0x10;
  iVar1 = ptVar2->icons;
  ptVar2->down = 0;
  (ptVar2->rect).left = 0x10;
  (ptVar2->rect).top = 0x10;
  (ptVar2->rect).bottom = (iVar3 + 0xb) * (iVar1 / 2) + 0x10;
  return;
}
