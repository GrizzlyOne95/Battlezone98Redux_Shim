/*
 * Entry: 004d49a4
 * Name: PathDisplay::DrawSlabs
 * Namespace: PathDisplay
 * Signature: void DrawSlabs(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawSlabs(PathDisplay *this)

{
  DrawStrips((float)grid_rect.left,(float)grid_rect.top,(float)grid_rect.right,
             (float)grid_rect.bottom,this->cellColorMap + 2);
  return;
}
