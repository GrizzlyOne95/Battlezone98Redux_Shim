; Entry: 004f5020
; Name: Gouraud_Perspective_Texture_Map_polygon
; Signature: void Gouraud_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004f5a39
; Reason: Exception while decompiling 004f5020: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004f5020 --stop-address=0x004f5a39 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4f5020:      	pushl	%ebp
  4f5021:      	movl	%esp, %ebp
  4f5023:      	cmpl	$0x0, 0xc5e6d0
  4f502a:      	movl	0x14(%ebp), %ecx
  4f502d:      	movzwl	(%ecx), %eax
  4f5030:      	pushl	%ebx
  4f5031:      	pushl	%esi
  4f5032:      	pushl	%edi
  4f5033:      	movl	$0x100, %edx            # imm = 0x100
  4f5038:      	je	0x4f509f <.text+0xf409f>
  4f503a:      	cmpw	%dx, %ax
  4f503d:      	jne	0x4f5056 <.text+0xf4056>
  4f503f:      	pushl	%ecx
  4f5040:      	pushl	0x10(%ebp)
  4f5043:      	pushl	0xc(%ebp)
  4f5046:      	pushl	0x8(%ebp)
  4f5049:      	calll	0x5010d3 <.text+0x1000d3>
  4f504e:      	addl	$0x10, %esp
  4f5051:      	jmp	0x4f5a34 <.text+0xf4a34>
  4f5056:      	movl	$0x80, %edx
  4f505b:      	cmpw	%dx, %ax
  4f505e:      	jne	0x4f5071 <.text+0xf4071>
  4f5060:      	pushl	%ecx
  4f5061:      	pushl	0x10(%ebp)
  4f5064:      	pushl	0xc(%ebp)
  4f5067:      	pushl	0x8(%ebp)
  4f506a:      	calll	0x4ff666 <.text+0xfe666>
  4f506f:      	jmp	0x4f504e <.text+0xf404e>
  4f5071:      	cmpw	$0x40, %ax
  4f5075:      	jne	0x4f5088 <.text+0xf4088>
  4f5077:      	pushl	%ecx
  4f5078:      	pushl	0x10(%ebp)
  4f507b:      	pushl	0xc(%ebp)
  4f507e:      	pushl	0x8(%ebp)
  4f5081:      	calll	0x4fff35 <.text+0xfef35>
  4f5086:      	jmp	0x4f504e <.text+0xf404e>
  4f5088:      	cmpw	$0x20, %ax
  4f508c:      	jne	0x4f5107 <.text+0xf4107>
  4f508e:      	pushl	%ecx
  4f508f:      	pushl	0x10(%ebp)
  4f5092:      	pushl	0xc(%ebp)
  4f5095:      	pushl	0x8(%ebp)
  4f5098:      	calll	0x500804 <.text+0xff804>
  4f509d:      	jmp	0x4f504e <.text+0xf404e>
  4f509f:      	cmpw	%dx, %ax
  4f50a2:      	jne	0x4f50b5 <.text+0xf40b5>
  4f50a4:      	pushl	%ecx
  4f50a5:      	pushl	0x10(%ebp)
  4f50a8:      	pushl	0xc(%ebp)
  4f50ab:      	pushl	0x8(%ebp)
  4f50ae:      	calll	0x4fed59 <.text+0xfdd59>
  4f50b3:      	jmp	0x4f504e <.text+0xf404e>
  4f50b5:      	movl	$0x80, %edx
  4f50ba:      	cmpw	%dx, %ax
  4f50bd:      	jne	0x4f50d3 <.text+0xf40d3>
  4f50bf:      	pushl	%ecx
  4f50c0:      	pushl	0x10(%ebp)
  4f50c3:      	pushl	0xc(%ebp)
  4f50c6:      	pushl	0x8(%ebp)
  4f50c9:      	calll	0x4fd31f <.text+0xfc31f>
  4f50ce:      	jmp	0x4f504e <.text+0xf404e>
  4f50d3:      	cmpw	$0x40, %ax
  4f50d7:      	jne	0x4f50ed <.text+0xf40ed>
  4f50d9:      	pushl	%ecx
  4f50da:      	pushl	0x10(%ebp)
  4f50dd:      	pushl	0xc(%ebp)
  4f50e0:      	pushl	0x8(%ebp)
  4f50e3:      	calll	0x4fdbd9 <.text+0xfcbd9>
  4f50e8:      	jmp	0x4f504e <.text+0xf404e>
  4f50ed:      	cmpw	$0x20, %ax
  4f50f1:      	jne	0x4f5107 <.text+0xf4107>
  4f50f3:      	pushl	%ecx
  4f50f4:      	pushl	0x10(%ebp)
  4f50f7:      	pushl	0xc(%ebp)
  4f50fa:      	pushl	0x8(%ebp)
  4f50fd:      	calll	0x4fe493 <.text+0xfd493>
  4f5102:      	jmp	0x4f504e <.text+0xf404e>
  4f5107:      	movl	0x14(%ebp), %ebx
  4f510a:      	pushl	%ebp
  4f510b:      	movl	0xcfdbc0, %eax
  4f5110:      	subl	$0x700, %esp            # imm = 0x700
  4f5116:      	cmpl	%ebx, %eax
  4f5118:      	je	0x4f5188 <.text+0xf4188>
  4f511a:      	movl	%ebx, 0xcfdbc0
  4f5120:      	leal	0xcfdbd8, %edx
  4f5126:      	movl	(%ebx), %eax
  4f5128:      	movl	0x4(%ebx), %ecx
  4f512b:      	leal	0x8(%ebx), %esi
  4f512e:      	movl	%ecx, 0x4(%esp)
  4f5132:      	movl	%eax, %edi
  4f5134:      	addl	$0x3, %ecx
  4f5137:      	addl	%esi, %edi
  4f5139:      	leal	(%esi,%eax,2), %ebx
  4f513c:      	leal	(%eax,%eax,2), %eax
  4f513f:      	movl	%esi, -0x4(%edx)
  4f5142:      	movl	%esi, -0x8(%edx)
  4f5145:      	movl	%esi, -0xc(%edx)
  4f5148:      	movl	%esi, -0x10(%edx)
  4f514b:      	movl	%esi, (%edx)
  4f514d:      	movl	%edi, 0x4(%edx)
  4f5150:      	movl	%ebx, 0x8(%edx)
  4f5153:      	addl	%eax, %esi
  4f5155:      	addl	%eax, %edi
  4f5157:      	addl	%eax, %ebx
  4f5159:      	addl	$0xc, %edx
  4f515c:      	subl	$0x3, %ecx
  4f515f:      	jge	0x4f514b <.text+0xf414b>
  4f5161:      	movl	0x4(%esp), %edx
  4f5165:      	movl	0xcfdbd4(,%edx,4), %eax
  4f516c:      	movl	%eax, 0xcfdbd8(,%edx,4)
  4f5173:      	movl	%eax, 0xcfdbdc(,%edx,4)
  4f517a:      	movl	%eax, 0xcfdbe0(,%edx,4)
  4f5181:      	movl	%eax, 0xcfdbe4(,%edx,4)
  4f5188:      	movl	0x14(%ebp), %ebx
  4f518b:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4f5190:      	movl	0xc(%ebp), %esi
  4f5193:      	movl	0x10(%ebp), %eax
  4f5196:      	fildl	0x4(%ebx)
  4f5199:      	movl	(%ebx), %ecx
  4f519b:      	movl	%esi, (%esp)
  4f519e:      	shll	$0x3, %eax
  4f51a1:      	leal	0x8(%ebx), %edi
  4f51a4:      	fildl	(%ebx)
  4f51a6:      	movl	%ecx, 0x10(%esp)
  4f51aa:      	leal	(%eax,%eax,2), %ecx
  4f51ad:      	xorl	%eax, %eax
  4f51af:      	movl	%edi, 0x50(%esp)
  4f51b3:      	flds	0x62c808
  4f51b9:      	fsubs	0x14(%esi,%eax)
  4f51bd:      	flds	0x4(%esi,%eax)
  4f51c1:      	faddl	0x632380
  4f51c7:      	fxch	%st(1)
  4f51c9:      	flds	0xc(%esi,%eax)
  4f51cd:      	fmul	%st(3), %st
  4f51cf:      	flds	0x10(%esi,%eax)
  4f51d3:      	fmul	%st(5), %st
  4f51d5:      	fxch	%st(3)
  4f51d7:      	fstpl	0x38(%esp)
  4f51db:      	fxch	%st(1)
  4f51dd:      	fmuls	0x62c810
  4f51e3:      	fxch	%st(2)
  4f51e5:      	fstps	0x10(%esi,%eax)
  4f51e9:      	fstps	0xc(%esi,%eax)
  4f51ed:      	fstps	0x14(%esi,%eax)
  4f51f1:      	movl	0x38(%esp), %edi
  4f51f5:      	movl	%eax, 0x3e4(%esp,%eax)
  4f51fc:      	movl	%eax, 0x114(%esp,%eax)
  4f5203:      	movl	%edi, 0x400(%esp,%eax)
  4f520a:      	addl	$0x18, %eax
  4f520d:      	cmpl	%edx, %edi
  4f520f:      	jg	0x4f5215 <.text+0xf4215>
  4f5211:      	movl	%eax, %ebx
  4f5213:      	movl	%edi, %edx
  4f5215:      	cmpl	%ecx, %eax
  4f5217:      	jne	0x4f51b3 <.text+0xf41b3>
  4f5219:      	subl	$0x18, %ebx
  4f521c:      	leal	-0x18(%eax), %ecx
  4f521f:      	fcompp
  4f5221:      	movl	$0x0, 0x3e4(%esp,%eax)
  4f522c:      	movl	%ecx, 0xfc(%esp)
  4f5233:      	movl	0x8(%ebp), %edi
  4f5236:      	movl	%ebx, 0xcc(%esp)
  4f523d:      	movl	%ebx, 0x9c(%esp)
  4f5244:      	movl	%ebx, 0xd0(%esp)
  4f524b:      	movl	%esi, %ebp
  4f524d:      	movl	0x20(%edi), %eax
  4f5250:      	movl	(%edi), %ecx
  4f5252:      	addl	%edx, %eax
  4f5254:      	movl	0x14(%edi), %esi
  4f5257:      	movl	0x1c(%edi), %edi
  4f525a:      	imull	%ecx
  4f525c:      	addl	%edi, %esi
  4f525e:      	movl	%ecx, 0xc(%esp)
  4f5262:      	addl	%eax, %esi
  4f5264:      	movl	0x400(%esp,%ebx), %edi
  4f526b:      	movl	%esi, 0x98(%esp)
  4f5272:      	movl	%ebx, 0xa0(%esp)
  4f5279:      	movl	0xd0(%esp), %ecx
  4f5280:      	movl	0x400(%esp,%ecx), %eax
  4f5287:      	movl	%edi, 0x4(%esp)
  4f528b:      	cmpl	%eax, %edi
  4f528d:      	jl	0x4f53b6 <.text+0xf43b6>
  4f5293:      	movl	0x3fc(%esp,%ecx), %edx
  4f529a:      	movl	%ecx, %eax
  4f529c:      	movl	%edx, 0xd0(%esp)
  4f52a3:      	cmpl	0x9c(%esp), %edx
  4f52aa:      	je	0x4f5a2d <.text+0xf4a2d>
  4f52b0:      	movl	0x400(%esp,%edx), %esi
  4f52b7:      	movl	%edx, %ecx
  4f52b9:      	cmpl	%esi, %edi
  4f52bb:      	jge	0x4f5293 <.text+0xf4293>
  4f52bd:      	flds	0x14(%ebp,%edx)
  4f52c1:      	fsubs	0x14(%ebp,%eax)
  4f52c5:      	flds	0x4(%ebp,%edx)
  4f52c9:      	fsubs	0x4(%ebp,%eax)
  4f52cd:      	flds	0x10(%ebp,%edx)
  4f52d1:      	fsubs	0x10(%ebp,%eax)
  4f52d5:      	fxch	%st(1)
  4f52d7:      	fdivrs	0x62c808
  4f52dd:      	flds	0xc(%ebp,%edx)
  4f52e1:      	fsubs	0xc(%ebp,%eax)
  4f52e5:      	fxch	%st(1)
  4f52e7:      	fmul	%st, %st(2)
  4f52e9:      	flds	0x8(%ebp,%edx)
  4f52ed:      	fsubs	0x8(%ebp,%eax)
  4f52f1:      	fxch	%st(2)
  4f52f3:      	fmul	%st(1), %st
  4f52f5:      	flds	(%ebp,%edx)
  4f52f9:      	fsubs	(%ebp,%eax)
  4f52fd:      	fxch	%st(3)
  4f52ff:      	fmul	%st(2), %st
  4f5301:      	fxch	%st(4)
  4f5303:      	fstps	0xec(%esp)
  4f530a:      	fstps	0xe8(%esp)
  4f5311:      	fmul	%st, %st(3)
  4f5313:      	flds	0x4(%ebp,%eax)
  4f5317:      	faddl	0x632380
  4f531d:      	fxch	%st(2)
  4f531f:      	fmulp	%st, %st(1)
  4f5321:      	fxch	%st(3)
  4f5323:      	fstps	0xf8(%esp)
  4f532a:      	fstpl	0x38(%esp)
  4f532e:      	fstps	0xf4(%esp)
  4f5335:      	fildl	0x38(%esp)
  4f5339:      	fxch	%st(1)
  4f533b:      	fstps	0xf0(%esp)
  4f5342:      	fsubs	0x4(%ebp,%eax)
  4f5346:      	flds	0xf0(%esp)
  4f534d:      	flds	0xf4(%esp)
  4f5354:      	fmul	%st(2), %st
  4f5356:      	flds	0xe8(%esp)
  4f535d:      	fmul	%st(3), %st
  4f535f:      	flds	0xf8(%esp)
  4f5366:      	fmul	%st(4), %st
  4f5368:      	fxch	%st(2)
  4f536a:      	fadds	0x8(%ebp,%eax)
  4f536e:      	flds	0xec(%esp)
  4f5375:      	fmul	%st(5), %st
  4f5377:      	fxch	%st(2)
  4f5379:      	fadds	0xc(%ebp,%eax)
  4f537d:      	fxch	%st(4)
  4f537f:      	fmulp	%st, %st(5)
  4f5381:      	fstps	0xd8(%esp)
  4f5388:      	fadds	0x10(%ebp,%eax)
  4f538c:      	fxch	%st(3)
  4f538e:      	fadds	(%ebp,%eax)
  4f5392:      	fxch	%st(2)
  4f5394:      	fstps	0xdc(%esp)
  4f539b:      	fadds	0x14(%ebp,%eax)
  4f539f:      	fxch	%st(2)
  4f53a1:      	fstps	0xe0(%esp)
  4f53a8:      	fstps	0xd4(%esp)
  4f53af:      	fstps	0xe4(%esp)
  4f53b6:      	movl	0xa0(%esp), %ecx
  4f53bd:      	cmpl	0x400(%esp,%ecx), %edi
  4f53c4:      	jl	0x4f54de <.text+0xf44de>
  4f53ca:      	movl	0xfc(%esp,%ecx), %edx
  4f53d1:      	movl	%ecx, %eax
  4f53d3:      	movl	%edx, 0xa0(%esp)
  4f53da:      	movl	%edx, %ecx
  4f53dc:      	cmpl	0x400(%esp,%edx), %edi
  4f53e3:      	jge	0x4f53ca <.text+0xf43ca>
  4f53e5:      	flds	0x14(%ebp,%edx)
  4f53e9:      	fsubs	0x14(%ebp,%eax)
  4f53ed:      	flds	0x4(%ebp,%edx)
  4f53f1:      	fsubs	0x4(%ebp,%eax)
  4f53f5:      	flds	0x10(%ebp,%edx)
  4f53f9:      	fsubs	0x10(%ebp,%eax)
  4f53fd:      	fxch	%st(1)
  4f53ff:      	fdivrs	0x62c808
  4f5405:      	flds	0xc(%ebp,%edx)
  4f5409:      	fsubs	0xc(%ebp,%eax)
  4f540d:      	fxch	%st(1)
  4f540f:      	fmul	%st, %st(2)
  4f5411:      	flds	0x8(%ebp,%edx)
  4f5415:      	fsubs	0x8(%ebp,%eax)
  4f5419:      	fxch	%st(2)
  4f541b:      	fmul	%st(1), %st
  4f541d:      	flds	(%ebp,%edx)
  4f5421:      	fsubs	(%ebp,%eax)
  4f5425:      	fxch	%st(3)
  4f5427:      	fmul	%st(2), %st
  4f5429:      	fxch	%st(4)
  4f542b:      	fstps	0xbc(%esp)
  4f5432:      	fstps	0xb8(%esp)
  4f5439:      	fmul	%st, %st(3)
  4f543b:      	flds	0x4(%ebp,%eax)
  4f543f:      	faddl	0x632380
  4f5445:      	fxch	%st(2)
  4f5447:      	fmulp	%st, %st(1)
  4f5449:      	fxch	%st(3)
  4f544b:      	fstps	0xc8(%esp)
  4f5452:      	fstpl	0x38(%esp)
  4f5456:      	fstps	0xc4(%esp)
  4f545d:      	fildl	0x38(%esp)
  4f5461:      	fxch	%st(1)
  4f5463:      	fstps	0xc0(%esp)
  4f546a:      	fsubs	0x4(%ebp,%eax)
  4f546e:      	flds	0xc0(%esp)
  4f5475:      	flds	0xc4(%esp)
  4f547c:      	fmul	%st(2), %st
  4f547e:      	flds	0xb8(%esp)
  4f5485:      	fmul	%st(3), %st
  4f5487:      	flds	0xc8(%esp)
  4f548e:      	fmul	%st(4), %st
  4f5490:      	fxch	%st(2)
  4f5492:      	fadds	0x8(%ebp,%eax)
  4f5496:      	flds	0xbc(%esp)
  4f549d:      	fmul	%st(5), %st
  4f549f:      	fxch	%st(2)
  4f54a1:      	fadds	0xc(%ebp,%eax)
  4f54a5:      	fxch	%st(4)
  4f54a7:      	fmulp	%st, %st(5)
  4f54a9:      	fstps	0xa8(%esp)
  4f54b0:      	fadds	0x10(%ebp,%eax)
  4f54b4:      	fxch	%st(3)
  4f54b6:      	fadds	(%ebp,%eax)
  4f54ba:      	fxch	%st(2)
  4f54bc:      	fstps	0xac(%esp)
  4f54c3:      	fadds	0x14(%ebp,%eax)
  4f54c7:      	fxch	%st(2)
  4f54c9:      	fstps	0xb0(%esp)
  4f54d0:      	fstps	0xa4(%esp)
  4f54d7:      	fstps	0xb4(%esp)
  4f54de:      	flds	0xd4(%esp)
  4f54e5:      	faddl	0x632380
  4f54eb:      	flds	0xa4(%esp)
  4f54f2:      	faddl	0x632380
  4f54f8:      	fxch	%st(1)
  4f54fa:      	fstpl	0x48(%esp)
  4f54fe:      	fstpl	0x40(%esp)
  4f5502:      	movl	0x48(%esp), %edx
  4f5506:      	movl	0x40(%esp), %ebx
  4f550a:      	cmpl	%edx, %ebx
  4f550c:      	je	0x4f5936 <.text+0xf4936>
  4f5512:      	jl	0x4f55f1 <.text+0xf45f1>
  4f5518:      	flds	0xb4(%esp)
  4f551f:      	fsubs	0xe4(%esp)
  4f5526:      	flds	0xa4(%esp)
  4f552d:      	fsubs	0xd4(%esp)
  4f5534:      	flds	0xb0(%esp)
  4f553b:      	fsubs	0xe0(%esp)
  4f5542:      	fxch	%st(1)
  4f5544:      	fdivrs	0x62c808
  4f554a:      	flds	0xac(%esp)
  4f5551:      	fsubs	0xdc(%esp)
  4f5558:      	fxch	%st(2)
  4f555a:      	fmul	%st(1), %st
  4f555c:      	flds	0xa8(%esp)
  4f5563:      	fsubs	0xd8(%esp)
  4f556a:      	fxch	%st(3)
  4f556c:      	fmul	%st(2), %st
  4f556e:      	fxch	%st(1)
  4f5570:      	fstps	0x1c(%esp)
  4f5574:      	fxch	%st(1)
  4f5576:      	fmul	%st, %st(2)
  4f5578:      	fxch	%st(1)
  4f557a:      	fstps	0x18(%esp)
  4f557e:      	fmulp	%st, %st(2)
  4f5580:      	fildl	0x48(%esp)
  4f5584:      	fxch	%st(1)
  4f5586:      	fstps	0x20(%esp)
  4f558a:      	fsubs	0xd4(%esp)
  4f5591:      	fld	%st(1)
  4f5593:      	faddl	0x632380
  4f5599:      	fxch	%st(2)
  4f559b:      	fmul	%st(1), %st
  4f559d:      	flds	0x1c(%esp)
  4f55a1:      	fxch	%st(3)
  4f55a3:      	fstpl	0x68(%esp)
  4f55a7:      	fadds	0xe4(%esp)
  4f55ae:      	fxch	%st(2)
  4f55b0:      	flds	0x18(%esp)
  4f55b4:      	fmul	%st(2), %st
  4f55b6:      	fxch	%st(3)
  4f55b8:      	faddl	0x632380
  4f55be:      	fxch	%st(3)
  4f55c0:      	flds	0x20(%esp)
  4f55c4:      	fmul	%st(3), %st
  4f55c6:      	fxch	%st(4)
  4f55c8:      	fstpl	0x90(%esp)
  4f55cf:      	fadds	0xdc(%esp)
  4f55d6:      	fxch	%st(2)
  4f55d8:      	fmulp	%st, %st(1)
  4f55da:      	fxch	%st(2)
  4f55dc:      	fadds	0xd8(%esp)
  4f55e3:      	fxch	%st(2)
  4f55e5:      	fadds	0xe0(%esp)
  4f55ec:      	jmp	0x4f56cf <.text+0xf46cf>
  4f55f1:      	movl	%ebx, 0x48(%esp)
  4f55f5:      	movl	%edx, %ebx
  4f55f7:      	movl	0x48(%esp), %edx
  4f55fb:      	flds	0xe4(%esp)
  4f5602:      	fsubs	0xb4(%esp)
  4f5609:      	flds	0xd4(%esp)
  4f5610:      	fsubs	0xa4(%esp)
  4f5617:      	flds	0xe0(%esp)
  4f561e:      	fsubs	0xb0(%esp)
  4f5625:      	fxch	%st(1)
  4f5627:      	fdivrs	0x62c808
  4f562d:      	flds	0xdc(%esp)
  4f5634:      	fsubs	0xac(%esp)
  4f563b:      	fxch	%st(2)
  4f563d:      	fmul	%st(1), %st
  4f563f:      	flds	0xd8(%esp)
  4f5646:      	fsubs	0xa8(%esp)
  4f564d:      	fxch	%st(3)
  4f564f:      	fmul	%st(2), %st
  4f5651:      	fxch	%st(1)
  4f5653:      	fstps	0x1c(%esp)
  4f5657:      	fxch	%st(1)
  4f5659:      	fmul	%st, %st(2)
  4f565b:      	fxch	%st(1)
  4f565d:      	fstps	0x18(%esp)
  4f5661:      	fmulp	%st, %st(2)
  4f5663:      	fildl	0x48(%esp)
  4f5667:      	fxch	%st(1)
  4f5669:      	fstps	0x20(%esp)
  4f566d:      	fsubs	0xa4(%esp)
  4f5674:      	fld	%st(1)
  4f5676:      	faddl	0x632380
  4f567c:      	fxch	%st(2)
  4f567e:      	fmul	%st(1), %st
  4f5680:      	flds	0x1c(%esp)
  4f5684:      	fxch	%st(3)
  4f5686:      	fstpl	0x68(%esp)
  4f568a:      	fadds	0xb4(%esp)
  4f5691:      	fxch	%st(2)
  4f5693:      	flds	0x18(%esp)
  4f5697:      	fmul	%st(2), %st
  4f5699:      	fxch	%st(3)
  4f569b:      	faddl	0x632380
  4f56a1:      	fxch	%st(3)
  4f56a3:      	flds	0x20(%esp)
  4f56a7:      	fmul	%st(3), %st
  4f56a9:      	fxch	%st(4)
  4f56ab:      	fstpl	0x90(%esp)
  4f56b2:      	fadds	0xac(%esp)
  4f56b9:      	fxch	%st(2)
  4f56bb:      	fmulp	%st, %st(1)
  4f56bd:      	fxch	%st(2)
  4f56bf:      	fadds	0xa8(%esp)
  4f56c6:      	fxch	%st(2)
  4f56c8:      	fadds	0xb0(%esp)
  4f56cf:      	movl	0x68(%esp), %eax
  4f56d3:      	movl	0x98(%esp), %edi
  4f56da:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4f56df:      	subl	%edx, %ebx
  4f56e1:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  4f56e6:      	addl	%edx, %edi
  4f56e8:      	movl	%eax, 0x68(%esp)
  4f56ec:      	flds	0x18(%esp)
  4f56f0:      	fmuls	0x62c814
  4f56f6:      	flds	0x1c(%esp)
  4f56fa:      	fmuls	0x62c814
  4f5700:      	flds	0x20(%esp)
  4f5704:      	fmuls	0x62c814
  4f570a:      	fxch	%st(2)
  4f570c:      	fstps	0x24(%esp)
  4f5710:      	fstps	0x28(%esp)
  4f5714:      	fstps	0x2c(%esp)
  4f5718:      	fxch	%st(2)
  4f571a:      	flds	0x62c80c
  4f5720:      	fdiv	%st(1), %st
  4f5722:      	fld	%st(3)
  4f5724:      	fmul	%st(1), %st
  4f5726:      	fld	%st(3)
  4f5728:      	fmulp	%st, %st(2)
  4f572a:      	faddl	0x632380
  4f5730:      	fxch	%st(1)
  4f5732:      	faddl	0x632380
  4f5738:      	fxch	%st(2)
  4f573a:      	fadds	0x2c(%esp)
  4f573e:      	fxch	%st(1)
  4f5740:      	fstpl	0x78(%esp)
  4f5744:      	fxch	%st(1)
  4f5746:      	fstpl	0x70(%esp)
  4f574a:      	flds	0x62c80c
  4f5750:      	fdiv	%st(1), %st
  4f5752:      	decl	%ebx
  4f5753:      	jmp	0x4f5837 <.text+0xf4837>
  4f5758:      	flds	0x24(%esp)
  4f575c:      	faddp	%st, %st(3)
  4f575e:      	flds	0x28(%esp)
  4f5762:      	faddp	%st, %st(4)
  4f5764:      	fld	%st(2)
  4f5766:      	fmul	%st(1), %st
  4f5768:      	flds	0x2c(%esp)
  4f576c:      	fxch	%st(2)
  4f576e:      	fmul	%st(5), %st
  4f5770:      	fxch	%st(2)
  4f5772:      	faddp	%st, %st(3)
  4f5774:      	faddl	0x632380
  4f577a:      	fxch	%st(1)
  4f577c:      	faddl	0x632380
  4f5782:      	fld	%st(2)
  4f5784:      	fxch	%st(2)
  4f5786:      	fstpl	0x80(%esp)
  4f578d:      	fstpl	0x88(%esp)
  4f5794:      	fdivrs	0x62c80c
  4f579a:      	movl	0x78(%esp), %ebp
  4f579e:      	movl	0x70(%esp), %esi
  4f57a2:      	movl	0x88(%esp), %eax
  4f57a9:      	movl	0x80(%esp), %edx
  4f57b0:      	subl	%ebp, %eax
  4f57b2:      	subl	%esi, %edx
  4f57b4:      	sarl	$0x4, %eax
  4f57b7:      	movl	%ebx, 0x8(%esp)
  4f57bb:      	sarl	$0x4, %edx
  4f57be:      	movl	0x90(%esp), %ebx
  4f57c5:      	movl	%edx, 0x58(%esp)
  4f57c9:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  4f57cf:      	movl	%eax, 0x60(%esp)
  4f57d3:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  4f57d9:      	movl	%ebp, %eax
  4f57db:      	movl	%esi, %edx
  4f57dd:      	sarl	$0x10, %eax
  4f57e0:      	movl	0x60(%esp), %ecx
  4f57e4:      	sarl	$0x10, %edx
  4f57e7:      	addl	%ecx, %ebp
  4f57e9:      	movl	0xcfdbd8(,%eax,4), %eax
  4f57f0:      	movl	0x58(%esp), %ecx
  4f57f4:      	movb	(%eax,%edx), %dl
  4f57f7:      	incl	%edi
  4f57f8:      	movb	%bh, %dh
  4f57fa:      	addl	%ecx, %esi
  4f57fc:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4f5802:      	movl	0x68(%esp), %ecx
  4f5806:      	movb	0xd1e480(%edx), %al
  4f580c:      	addl	%ecx, %ebx
  4f580e:      	movb	%al, -0x1(%edi)
  4f5811:      	jge	0x4f57d9 <.text+0xf47d9>
  4f5813:      	movl	%ebx, 0x90(%esp)
  4f581a:      	movl	0x8(%esp), %ebx
  4f581e:      	movl	0x80(%esp), %eax
  4f5825:      	movl	0x88(%esp), %edx
  4f582c:      	movl	%eax, 0x70(%esp)
  4f5830:      	movl	%edx, 0x78(%esp)
  4f5834:      	subl	$0x10, %ebx
  4f5837:      	cmpl	$0x10, %ebx
  4f583a:      	jge	0x4f5758 <.text+0xf4758>
  4f5840:      	movl	0x90(%esp), %eax
  4f5847:      	movl	%ebx, %ecx
  4f5849:      	decl	%ebx
  4f584a:      	movl	0x78(%esp), %ebp
  4f584e:      	shll	$0x11, %ebx
  4f5851:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4f5856:      	movl	0x70(%esp), %esi
  4f585a:      	orl	%eax, %ebx
  4f585c:      	cmpl	$0x0, %ecx
  4f585f:      	je	0x4f5916 <.text+0xf4916>
  4f5865:      	fxch	%st(1)
  4f5867:      	fsubs	0x2c(%esp)
  4f586b:      	flds	0x20(%esp)
  4f586f:      	fmuls	0x62c810(,%ecx,8)
  4f5876:      	flds	0x18(%esp)
  4f587a:      	fmuls	0x62c810(,%ecx,8)
  4f5881:      	flds	0x1c(%esp)
  4f5885:      	fmuls	0x62c810(,%ecx,8)
  4f588c:      	fxch	%st(2)
  4f588e:      	faddp	%st, %st(3)
  4f5890:      	faddp	%st, %st(4)
  4f5892:      	faddp	%st, %st(4)
  4f5894:      	fdivrs	0x62c80c
  4f589a:      	fmul	%st, %st(2)
  4f589c:      	fildl	0x70(%esp)
  4f58a0:      	fxch	%st(1)
  4f58a2:      	fmul	%st(4), %st
  4f58a4:      	fildl	0x78(%esp)
  4f58a8:      	fxch	%st(2)
  4f58aa:      	fsubrp	%st, %st(4)
  4f58ac:      	fsubp	%st, %st(1)
  4f58ae:      	fxch	%st(2)
  4f58b0:      	fmuls	0x62c814(,%ecx,8)
  4f58b7:      	fxch	%st(2)
  4f58b9:      	fmuls	0x62c814(,%ecx,8)
  4f58c0:      	fxch	%st(2)
  4f58c2:      	faddl	0x632380
  4f58c8:      	fxch	%st(2)
  4f58ca:      	faddl	0x632380
  4f58d0:      	fxch	%st(2)
  4f58d2:      	fstl	0x58(%esp)
  4f58d6:      	fxch	%st(2)
  4f58d8:      	fstl	0x60(%esp)
  4f58dc:      	movl	%ebp, %eax
  4f58de:      	movl	%esi, %edx
  4f58e0:      	sarl	$0x10, %eax
  4f58e3:      	movl	0x60(%esp), %ecx
  4f58e7:      	sarl	$0x10, %edx
  4f58ea:      	addl	%ecx, %ebp
  4f58ec:      	movl	0xcfdbd8(,%eax,4), %eax
  4f58f3:      	movl	0x58(%esp), %ecx
  4f58f7:      	movb	(%eax,%edx), %dl
  4f58fa:      	incl	%edi
  4f58fb:      	movb	%bh, %dh
  4f58fd:      	addl	%ecx, %esi
  4f58ff:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4f5905:      	movl	0x68(%esp), %ecx
  4f5909:      	movb	0xd1e480(%edx), %al
  4f590f:      	addl	%ecx, %ebx
  4f5911:      	movb	%al, -0x1(%edi)
  4f5914:      	jge	0x4f58dc <.text+0xf48dc>
  4f5916:      	sarl	$0x10, %ebp
  4f5919:      	xorl	%edx, %edx
  4f591b:      	sarl	$0x10, %esi
  4f591e:      	movb	%bh, %dh
  4f5920:      	movl	0xcfdbd8(,%ebp,4), %eax
  4f5927:      	fcompp
  4f5929:      	movb	(%eax,%esi), %dl
  4f592c:      	fcompp
  4f592e:      	movb	0xd1e480(%edx), %al
  4f5934:      	movb	%al, (%edi)
  4f5936:      	flds	0xb4(%esp)
  4f593d:      	fadds	0xc8(%esp)
  4f5944:      	flds	0xa8(%esp)
  4f594b:      	fadds	0xc4(%esp)
  4f5952:      	flds	0xb0(%esp)
  4f5959:      	fadds	0xbc(%esp)
  4f5960:      	flds	0xac(%esp)
  4f5967:      	fadds	0xb8(%esp)
  4f596e:      	flds	0xa4(%esp)
  4f5975:      	fadds	0xc0(%esp)
  4f597c:      	fxch	%st(3)
  4f597e:      	fstps	0xa8(%esp)
  4f5985:      	fstps	0xac(%esp)
  4f598c:      	fstps	0xb0(%esp)
  4f5993:      	fstps	0xa4(%esp)
  4f599a:      	fstps	0xb4(%esp)
  4f59a1:      	flds	0xe4(%esp)
  4f59a8:      	fadds	0xf8(%esp)
  4f59af:      	flds	0xd8(%esp)
  4f59b6:      	fadds	0xf4(%esp)
  4f59bd:      	flds	0xe0(%esp)
  4f59c4:      	fadds	0xec(%esp)
  4f59cb:      	flds	0xdc(%esp)
  4f59d2:      	fadds	0xe8(%esp)
  4f59d9:      	flds	0xd4(%esp)
  4f59e0:      	fadds	0xf0(%esp)
  4f59e7:      	fxch	%st(3)
  4f59e9:      	fstps	0xd8(%esp)
  4f59f0:      	fstps	0xdc(%esp)
  4f59f7:      	fstps	0xe0(%esp)
  4f59fe:      	fstps	0xd4(%esp)
  4f5a05:      	fstps	0xe4(%esp)
  4f5a0c:      	movl	0x98(%esp), %esi
  4f5a13:      	movl	0xc(%esp), %eax
  4f5a17:      	movl	(%esp), %ebp
  4f5a1a:      	addl	%eax, %esi
  4f5a1c:      	movl	0x4(%esp), %edi
  4f5a20:      	movl	%esi, 0x98(%esp)
  4f5a27:      	incl	%edi
  4f5a28:      	jmp	0x4f5279 <.text+0xf4279>
  4f5a2d:      	addl	$0x700, %esp            # imm = 0x700
  4f5a33:      	popl	%ebp
  4f5a34:      	popl	%edi
  4f5a35:      	popl	%esi
  4f5a36:      	popl	%ebx
  4f5a37:      	popl	%ebp
  4f5a38:      	retl
