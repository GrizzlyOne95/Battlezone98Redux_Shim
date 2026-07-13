/*
 * Entry: 00462b4b
 * Name: ShortPath::Search
 * Namespace: ShortPath
 * Signature: void Search(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Search(void)

{
  Node *pNVar1;
  Node *pNVar2;
  int iVar3;
  float fVar4;
  int local_10;
  float local_c;
  Node **local_8;
  
  startNode = Neighbors::Make(start.x,start.z);
  goalNode = Neighbors::Make(goal.x,goal.z);
  pNVar1 = startNode;
  fVar4 = GuessCost(startNode);
  pNVar1->g = 0.0;
  OpenList::Insert(startNode,0.0,fVar4);
  startNode->visited = true;
  curNode = (Node *)0x0;
  do {
    if ((OpenList::g_OpenNodes._28_4_ == 0) || (curNode = OpenList::First(), curNode == goalNode)) {
      OpenList::Clean();
      return;
    }
    Neighbors::Enumerate(&local_10,&local_8);
    iVar3 = local_10;
    if (0 < local_10) {
      do {
        pNVar1 = *local_8;
        local_8 = local_8 + 1;
        local_c = ActualCost(curNode,pNVar1);
        local_c = local_c + curNode->g;
        fVar4 = GuessCost(pNVar1);
        pNVar2 = curNode;
        if (pNVar1->visited == false) {
          pNVar1->visited = true;
          pNVar2 = curNode;
          pNVar1->g = local_c;
          pNVar1->prev = pNVar2;
LAB_00462c51:
          OpenList::Insert(pNVar1,local_c,fVar4);
        }
        else if (local_c < pNVar1->g) {
          pNVar1->g = local_c;
          pNVar1->prev = pNVar2;
          if (pNVar1->open == false) goto LAB_00462c51;
          OpenList::Update(pNVar1,local_c);
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    Neighbors::count = 0;
  } while( true );
}
