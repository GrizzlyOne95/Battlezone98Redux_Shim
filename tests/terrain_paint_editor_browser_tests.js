// Optional browser qualification against a generated local paint editor.
// node tests/terrain_paint_editor_browser_tests.js <editor.html> <output-dir> [browser.exe]
// Requires Playwright; no game, server or proprietary test assets in Git.
"use strict";
const {chromium}=require('playwright');
const fs=require('node:fs/promises');
const path=require('node:path');
const {pathToFileURL}=require('node:url');
const assert=require('node:assert/strict');
const codec=require('../scripts/terrain-paint-codec.js');
(async()=>{
 const [editor,output,executablePath]=process.argv.slice(2);
 if(!editor||!output)throw Error('Usage: <generated editor.html> <output-dir> [browser.exe]');
 await fs.mkdir(output,{recursive:true});
 const browser=await chromium.launch({headless:true,...(executablePath?{executablePath}:{})});
 try{
  const page=await browser.newPage({viewport:{width:1200,height:1500},deviceScaleFactor:1});
  const errors=[];page.on('pageerror',e=>errors.push(e.message));
  await page.goto(pathToFileURL(path.resolve(editor)).href);
  await page.locator('#status').waitFor();
  assert.equal(await page.locator('#layers button').count(),4);
  const size=Number((await page.locator('#status').textContent()).split(' ')[0]);
  assert(size>=64&&size<=2048);
  await page.screenshot({path:path.join(output,'editor-preview.png'),fullPage:true});
  const download=async(name)=>{
   const pending=page.waitForEvent('download');
   await page.getByRole('button',{name:'Save weights PNG',exact:true}).click();
   const result=await pending,filename=path.join(output,name);await result.saveAs(filename);
   return codec.decode(new Uint8Array(await fs.readFile(filename)),size);
  };
  const initial=await download('initial.png');
  await page.locator('#radius').press('End');await page.locator('#strength').press('End');
  // Choose a minority layer at the target point, then use actual brush input.
  const x=.4,z=.46,p=(Math.floor(z*size)*size+Math.floor(x*size))*4;
  let layer=0;for(let i=1;i<4;i++)if(initial[p+i]<initial[p+layer])layer=i;
  await page.locator('#layers button').nth(layer).click();
  const box=await page.locator('#map').boundingBox();
  await page.locator('#map').click({position:{x:box.width*x,y:box.height*z}});
  const edited=await download('edited.png');assert.notDeepEqual(edited,initial);
  await page.getByRole('button',{name:'Undo',exact:true}).click();assert.deepEqual(await download('undone.png'),initial);
  await page.getByRole('button',{name:'Redo',exact:true}).click();assert.deepEqual(await download('redone.png'),edited);
  await page.getByRole('button',{name:'Undo',exact:true}).click();
  await page.locator('#load').setInputFiles(path.join(output,'edited.png'));
  // Poll by exporting through the UI, allowing the asynchronous PNG decode to complete.
  await assert.doesNotReject(async()=>{
   for(let i=0;i<5;i++){
    const loaded=await download('loaded.png');if(Buffer.from(loaded).equals(Buffer.from(edited)))return;
   }
   throw Error('Edited PNG did not reload exactly.');
  });
  assert.deepEqual(errors,[]);
  console.log('PASS: offline browser brush, raw PNG export, exact undo/redo and PNG reload');
 }finally{await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
