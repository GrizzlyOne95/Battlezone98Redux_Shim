; Entry: 0050606e
; Name: Translucent_Perspective_Texture_Map_polygon
; Signature: void Translucent_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x005068a0
; Reason: Exception while decompiling 0050606e: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x0050606e --stop-address=0x005068a0 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  50606e:      	pushl	%ebp
  50606f:      	movl	%esp, %ebp
  506071:      	pushl	%ebx
  506072:      	pushl	%esi
  506073:      	pushl	%edi
  506074:      	movl	0x14(%ebp), %ebx
  506077:      	pushl	%ebp
  506078:      	movl	0xcfdbc0, %eax
  50607d:      	subl	$0x7d8, %esp            # imm = 0x7D8
  506083:      	cmpl	%ebx, %eax
  506085:      	je	0x5060f5 <.text+0x1050f5>
  506087:      	movl	%ebx, 0xcfdbc0
  50608d:      	leal	0xcfdbd8, %edx
  506093:      	movl	(%ebx), %eax
  506095:      	movl	0x4(%ebx), %ecx
  506098:      	leal	0x8(%ebx), %esi
  50609b:      	movl	%ecx, 0x4(%esp)
  50609f:      	movl	%eax, %edi
  5060a1:      	addl	$0x3, %ecx
  5060a4:      	addl	%esi, %edi
  5060a6:      	leal	(%esi,%eax,2), %ebx
  5060a9:      	leal	(%eax,%eax,2), %eax
  5060ac:      	movl	%esi, -0x4(%edx)
  5060af:      	movl	%esi, -0x8(%edx)
  5060b2:      	movl	%esi, -0xc(%edx)
  5060b5:      	movl	%esi, -0x10(%edx)
  5060b8:      	movl	%esi, (%edx)
  5060ba:      	movl	%edi, 0x4(%edx)
  5060bd:      	movl	%ebx, 0x8(%edx)
  5060c0:      	addl	%eax, %esi
  5060c2:      	addl	%eax, %edi
  5060c4:      	addl	%eax, %ebx
  5060c6:      	addl	$0xc, %edx
  5060c9:      	subl	$0x3, %ecx
  5060cc:      	jge	0x5060b8 <.text+0x1050b8>
  5060ce:      	movl	0x4(%esp), %edx
  5060d2:      	movl	0xcfdbd4(,%edx,4), %eax
  5060d9:      	movl	%eax, 0xcfdbd8(,%edx,4)
  5060e0:      	movl	%eax, 0xcfdbdc(,%edx,4)
  5060e7:      	movl	%eax, 0xcfdbe0(,%edx,4)
  5060ee:      	movl	%eax, 0xcfdbe4(,%edx,4)
  5060f5:      	movl	0x14(%ebp), %ebx
  5060f8:      	movl	$0x186a0, %edx          # imm = 0x186A0
  5060fd:      	movl	0xc(%ebp), %esi
  506100:      	movl	0x10(%ebp), %eax
  506103:      	fildl	0x4(%ebx)
  506106:      	movl	(%ebx), %ecx
  506108:      	movl	%esi, (%esp)
  50610b:      	shll	$0x3, %eax
  50610e:      	leal	0x8(%ebx), %edi
  506111:      	fsubs	0x62c808
  506117:      	fildl	(%ebx)
  506119:      	movl	%ecx, 0x10(%esp)
  50611d:      	leal	(%eax,%eax,2), %ecx
  506120:      	xorl	%eax, %eax
  506122:      	movl	%edi, 0x1c(%esp)
  506126:      	fsubs	0x62c808
  50612c:      	flds	0x4(%esi,%eax)
  506130:      	faddl	0x632380
  506136:      	flds	0xc(%esi,%eax)
  50613a:      	fmul	%st(2), %st
  50613c:      	flds	0x10(%esi,%eax)
  506140:      	fmul	%st(4), %st
  506142:      	fxch	%st(2)
  506144:      	fstpl	0x640(%esp)
  50614b:      	fstps	0xc(%esi,%eax)
  50614f:      	fstps	0x10(%esi,%eax)
  506153:      	movl	0x640(%esp), %edi
  50615a:      	movl	%eax, 0x320(%esp,%eax)
  506161:      	movl	%eax, 0x50(%esp,%eax)
  506165:      	movl	%edi, 0x33c(%esp,%eax)
  50616c:      	addl	$0x18, %eax
  50616f:      	cmpl	%edx, %edi
  506171:      	jg	0x506177 <.text+0x105177>
  506173:      	movl	%eax, %ebx
  506175:      	movl	%edi, %edx
  506177:      	cmpl	%ecx, %eax
  506179:      	jne	0x50612c <.text+0x10512c>
  50617b:      	subl	$0x18, %ebx
  50617e:      	leal	-0x18(%eax), %ecx
  506181:      	fcompp
  506183:      	movl	$0x0, 0x320(%esp,%eax)
  50618e:      	movl	%ecx, 0x38(%esp)
  506192:      	movl	0x8(%ebp), %edi
  506195:      	movl	%ebx, 0x6b0(%esp)
  50619c:      	movl	%ebx, 0x688(%esp)
  5061a3:      	movl	%ebx, 0x6b4(%esp)
  5061aa:      	movl	%esi, %ebp
  5061ac:      	movl	0x20(%edi), %eax
  5061af:      	movl	(%edi), %ecx
  5061b1:      	addl	%edx, %eax
  5061b3:      	movl	0x14(%edi), %esi
  5061b6:      	movl	0x1c(%edi), %edi
  5061b9:      	imull	%ecx
  5061bb:      	addl	%edi, %esi
  5061bd:      	movl	%ecx, 0xc(%esp)
  5061c1:      	addl	%eax, %esi
  5061c3:      	movl	0x33c(%esp,%ebx), %edi
  5061ca:      	movl	%esi, 0x18(%esp)
  5061ce:      	movl	%ebx, 0x68c(%esp)
  5061d5:      	movl	0x6b4(%esp), %ecx
  5061dc:      	movl	0x33c(%esp,%ecx), %eax
  5061e3:      	movl	%edi, 0x4(%esp)
  5061e7:      	cmpl	%eax, %edi
  5061e9:      	jl	0x5062f3 <.text+0x1052f3>
  5061ef:      	movl	0x338(%esp,%ecx), %edx
  5061f6:      	movl	%ecx, %eax
  5061f8:      	movl	%edx, 0x6b4(%esp)
  5061ff:      	cmpl	0x688(%esp), %edx
  506206:      	je	0x506894 <.text+0x105894>
  50620c:      	movl	0x33c(%esp,%edx), %esi
  506213:      	movl	%edx, %ecx
  506215:      	cmpl	%esi, %edi
  506217:      	jge	0x5061ef <.text+0x1051ef>
  506219:      	flds	0x4(%ebp,%edx)
  50621d:      	fsubs	0x4(%ebp,%eax)
  506221:      	flds	0x10(%ebp,%edx)
  506225:      	fsubs	0x10(%ebp,%eax)
  506229:      	fxch	%st(1)
  50622b:      	fdivrs	0x62c808
  506231:      	flds	0xc(%ebp,%edx)
  506235:      	fsubs	0xc(%ebp,%eax)
  506239:      	fxch	%st(1)
  50623b:      	fmul	%st, %st(2)
  50623d:      	flds	0x8(%ebp,%edx)
  506241:      	fsubs	0x8(%ebp,%eax)
  506245:      	fxch	%st(2)
  506247:      	fmul	%st(1), %st
  506249:      	flds	(%ebp,%edx)
  50624d:      	fsubs	(%ebp,%eax)
  506251:      	fxch	%st(3)
  506253:      	fmul	%st(2), %st
  506255:      	fxch	%st(4)
  506257:      	fstps	0x6cc(%esp)
  50625e:      	flds	0x4(%ebp,%eax)
  506262:      	faddl	0x632380
  506268:      	fxch	%st(3)
  50626a:      	fmulp	%st, %st(2)
  50626c:      	fstps	0x6c8(%esp)
  506273:      	fxch	%st(1)
  506275:      	fstpl	0x640(%esp)
  50627c:      	fstps	0x6d0(%esp)
  506283:      	fildl	0x640(%esp)
  50628a:      	fxch	%st(1)
  50628c:      	fstps	0x6d4(%esp)
  506293:      	fsubs	0x4(%ebp,%eax)
  506297:      	flds	0x6d0(%esp)
  50629e:      	flds	0x6d4(%esp)
  5062a5:      	fmul	%st(2), %st
  5062a7:      	flds	0x6c8(%esp)
  5062ae:      	fmul	%st(3), %st
  5062b0:      	fxch	%st(1)
  5062b2:      	fadds	0x8(%ebp,%eax)
  5062b6:      	flds	0x6cc(%esp)
  5062bd:      	fmul	%st(4), %st
  5062bf:      	fxch	%st(2)
  5062c1:      	fadds	0xc(%ebp,%eax)
  5062c5:      	fxch	%st(3)
  5062c7:      	fmulp	%st, %st(4)
  5062c9:      	fstps	0x6bc(%esp)
  5062d0:      	fadds	0x10(%ebp,%eax)
  5062d4:      	fxch	%st(2)
  5062d6:      	fadds	(%ebp,%eax)
  5062da:      	fxch	%st(1)
  5062dc:      	fstps	0x6c0(%esp)
  5062e3:      	fxch	%st(1)
  5062e5:      	fstps	0x6c4(%esp)
  5062ec:      	fstps	0x6b8(%esp)
  5062f3:      	movl	0x68c(%esp), %ecx
  5062fa:      	cmpl	0x33c(%esp,%ecx), %edi
  506301:      	jl	0x5063f9 <.text+0x1053f9>
  506307:      	movl	0x38(%esp,%ecx), %edx
  50630b:      	movl	%ecx, %eax
  50630d:      	movl	%edx, 0x68c(%esp)
  506314:      	movl	%edx, %ecx
  506316:      	cmpl	0x33c(%esp,%edx), %edi
  50631d:      	jge	0x506307 <.text+0x105307>
  50631f:      	flds	0x4(%ebp,%edx)
  506323:      	fsubs	0x4(%ebp,%eax)
  506327:      	flds	0x10(%ebp,%edx)
  50632b:      	fsubs	0x10(%ebp,%eax)
  50632f:      	fxch	%st(1)
  506331:      	fdivrs	0x62c808
  506337:      	flds	0xc(%ebp,%edx)
  50633b:      	fsubs	0xc(%ebp,%eax)
  50633f:      	fxch	%st(1)
  506341:      	fmul	%st, %st(2)
  506343:      	flds	0x8(%ebp,%edx)
  506347:      	fsubs	0x8(%ebp,%eax)
  50634b:      	fxch	%st(2)
  50634d:      	fmul	%st(1), %st
  50634f:      	flds	(%ebp,%edx)
  506353:      	fsubs	(%ebp,%eax)
  506357:      	fxch	%st(3)
  506359:      	fmul	%st(2), %st
  50635b:      	fxch	%st(4)
  50635d:      	fstps	0x6a4(%esp)
  506364:      	flds	0x4(%ebp,%eax)
  506368:      	faddl	0x632380
  50636e:      	fxch	%st(3)
  506370:      	fmulp	%st, %st(2)
  506372:      	fstps	0x6a0(%esp)
  506379:      	fxch	%st(1)
  50637b:      	fstpl	0x640(%esp)
  506382:      	fstps	0x6a8(%esp)
  506389:      	fildl	0x640(%esp)
  506390:      	fxch	%st(1)
  506392:      	fstps	0x6ac(%esp)
  506399:      	fsubs	0x4(%ebp,%eax)
  50639d:      	flds	0x6a8(%esp)
  5063a4:      	flds	0x6ac(%esp)
  5063ab:      	fmul	%st(2), %st
  5063ad:      	flds	0x6a0(%esp)
  5063b4:      	fmul	%st(3), %st
  5063b6:      	fxch	%st(1)
  5063b8:      	fadds	0x8(%ebp,%eax)
  5063bc:      	flds	0x6a4(%esp)
  5063c3:      	fmul	%st(4), %st
  5063c5:      	fxch	%st(2)
  5063c7:      	fadds	0xc(%ebp,%eax)
  5063cb:      	fxch	%st(3)
  5063cd:      	fmulp	%st, %st(4)
  5063cf:      	fstps	0x694(%esp)
  5063d6:      	fadds	0x10(%ebp,%eax)
  5063da:      	fxch	%st(2)
  5063dc:      	fadds	(%ebp,%eax)
  5063e0:      	fxch	%st(1)
  5063e2:      	fstps	0x698(%esp)
  5063e9:      	fxch	%st(1)
  5063eb:      	fstps	0x69c(%esp)
  5063f2:      	fstps	0x690(%esp)
  5063f9:      	flds	0x6b8(%esp)
  506400:      	faddl	0x632380
  506406:      	flds	0x690(%esp)
  50640d:      	faddl	0x632380
  506413:      	fxch	%st(1)
  506415:      	fstpl	0x650(%esp)
  50641c:      	fstpl	0x648(%esp)
  506423:      	movl	0x650(%esp), %edx
  50642a:      	movl	0x648(%esp), %ebx
  506431:      	cmpl	%edx, %ebx
  506433:      	je	0x5067cd <.text+0x1057cd>
  506439:      	jl	0x5064db <.text+0x1054db>
  50643f:      	flds	0x690(%esp)
  506446:      	fsubs	0x6b8(%esp)
  50644d:      	flds	0x69c(%esp)
  506454:      	fsubs	0x6c4(%esp)
  50645b:      	fxch	%st(1)
  50645d:      	fdivrs	0x62c808
  506463:      	flds	0x698(%esp)
  50646a:      	fsubs	0x6c0(%esp)
  506471:      	fxch	%st(2)
  506473:      	fmul	%st(1), %st
  506475:      	flds	0x694(%esp)
  50647c:      	fsubs	0x6bc(%esp)
  506483:      	fxch	%st(3)
  506485:      	fmul	%st(2), %st
  506487:      	fxch	%st(1)
  506489:      	fstps	0x24(%esp)
  50648d:      	fxch	%st(1)
  50648f:      	fmulp	%st, %st(2)
  506491:      	fstps	0x20(%esp)
  506495:      	fildl	0x650(%esp)
  50649c:      	fxch	%st(1)
  50649e:      	fstps	0x28(%esp)
  5064a2:      	fsubs	0x6b8(%esp)
  5064a9:      	flds	0x24(%esp)
  5064ad:      	flds	0x20(%esp)
  5064b1:      	fmul	%st(2), %st
  5064b3:      	flds	0x28(%esp)
  5064b7:      	fmul	%st(3), %st
  5064b9:      	fxch	%st(1)
  5064bb:      	fadds	0x6c0(%esp)
  5064c2:      	fxch	%st(3)
  5064c4:      	fmulp	%st, %st(2)
  5064c6:      	fadds	0x6bc(%esp)
  5064cd:      	fxch	%st(1)
  5064cf:      	fadds	0x6c4(%esp)
  5064d6:      	jmp	0x506582 <.text+0x105582>
  5064db:      	movl	%ebx, 0x650(%esp)
  5064e2:      	movl	%edx, %ebx
  5064e4:      	movl	0x650(%esp), %edx
  5064eb:      	flds	0x6b8(%esp)
  5064f2:      	fsubs	0x690(%esp)
  5064f9:      	flds	0x6c4(%esp)
  506500:      	fsubs	0x69c(%esp)
  506507:      	fxch	%st(1)
  506509:      	fdivrs	0x62c808
  50650f:      	flds	0x6c0(%esp)
  506516:      	fsubs	0x698(%esp)
  50651d:      	fxch	%st(2)
  50651f:      	fmul	%st(1), %st
  506521:      	flds	0x6bc(%esp)
  506528:      	fsubs	0x694(%esp)
  50652f:      	fxch	%st(3)
  506531:      	fmul	%st(2), %st
  506533:      	fxch	%st(1)
  506535:      	fstps	0x24(%esp)
  506539:      	fxch	%st(1)
  50653b:      	fmulp	%st, %st(2)
  50653d:      	fstps	0x20(%esp)
  506541:      	fildl	0x650(%esp)
  506548:      	fxch	%st(1)
  50654a:      	fstps	0x28(%esp)
  50654e:      	fsubs	0x690(%esp)
  506555:      	flds	0x24(%esp)
  506559:      	flds	0x20(%esp)
  50655d:      	fmul	%st(2), %st
  50655f:      	flds	0x28(%esp)
  506563:      	fmul	%st(3), %st
  506565:      	fxch	%st(1)
  506567:      	fadds	0x698(%esp)
  50656e:      	fxch	%st(3)
  506570:      	fmulp	%st, %st(2)
  506572:      	fadds	0x694(%esp)
  506579:      	fxch	%st(1)
  50657b:      	fadds	0x69c(%esp)
  506582:      	movl	0x18(%esp), %edi
  506586:      	subl	%edx, %ebx
  506588:      	addl	%edx, %edi
  50658a:      	flds	0x20(%esp)
  50658e:      	fmuls	0x62c814
  506594:      	flds	0x24(%esp)
  506598:      	fmuls	0x62c814
  50659e:      	flds	0x28(%esp)
  5065a2:      	fmuls	0x62c814
  5065a8:      	fxch	%st(2)
  5065aa:      	fstps	0x2c(%esp)
  5065ae:      	fstps	0x30(%esp)
  5065b2:      	fstps	0x34(%esp)
  5065b6:      	fxch	%st(1)
  5065b8:      	flds	0x62c80c
  5065be:      	fdiv	%st(1), %st
  5065c0:      	fld	%st(2)
  5065c2:      	fmul	%st(1), %st
  5065c4:      	fld	%st(4)
  5065c6:      	fmulp	%st, %st(2)
  5065c8:      	faddl	0x632380
  5065ce:      	fxch	%st(1)
  5065d0:      	faddl	0x632380
  5065d6:      	fxch	%st(2)
  5065d8:      	fadds	0x34(%esp)
  5065dc:      	fxch	%st(1)
  5065de:      	fstpl	0x680(%esp)
  5065e5:      	fxch	%st(1)
  5065e7:      	fstpl	0x678(%esp)
  5065ee:      	fxch	%st(2)
  5065f0:      	flds	0x62c80c
  5065f6:      	fdiv	%st(3), %st
  5065f8:      	decl	%ebx
  5065f9:      	jmp	0x5066d5 <.text+0x1056d5>
  5065fe:      	flds	0x2c(%esp)
  506602:      	faddp	%st, %st(2)
  506604:      	flds	0x30(%esp)
  506608:      	faddp	%st, %st(3)
  50660a:      	fld	%st(1)
  50660c:      	fmul	%st(1), %st
  50660e:      	flds	0x34(%esp)
  506612:      	fxch	%st(2)
  506614:      	fmul	%st(4), %st
  506616:      	fxch	%st(2)
  506618:      	faddp	%st, %st(5)
  50661a:      	faddl	0x632380
  506620:      	fxch	%st(1)
  506622:      	faddl	0x632380
  506628:      	fld	%st(4)
  50662a:      	fxch	%st(2)
  50662c:      	fstpl	0x658(%esp)
  506633:      	fstpl	0x668(%esp)
  50663a:      	fdivrs	0x62c80c
  506640:      	movl	0x680(%esp), %ebp
  506647:      	movl	0x678(%esp), %esi
  50664e:      	movl	0x668(%esp), %eax
  506655:      	movl	0x658(%esp), %edx
  50665c:      	subl	%ebp, %eax
  50665e:      	subl	%esi, %edx
  506660:      	sarl	$0x4, %eax
  506663:      	movl	%ebx, 0x8(%esp)
  506667:      	sarl	$0x4, %edx
  50666a:      	movl	%eax, 0x670(%esp)
  506671:      	movl	%edx, 0x660(%esp)
  506678:      	movl	$0x10, %ebx
  50667d:      	movl	%ebp, %eax
  50667f:      	movl	%esi, %edx
  506681:      	sarl	$0x10, %eax
  506684:      	movl	0x670(%esp), %ecx
  50668b:      	sarl	$0x10, %edx
  50668e:      	addl	%ecx, %ebp
  506690:      	movl	0xcfdbd8(,%eax,4), %eax
  506697:      	movl	0x660(%esp), %ecx
  50669e:      	movb	(%eax,%edx), %dh
  5066a1:      	addl	%ecx, %esi
  5066a3:      	movb	(%edi), %dl
  5066a5:      	incl	%edi
  5066a6:      	movb	0xd0e460(%edx), %al
  5066ac:      	decl	%ebx
  5066ad:      	movb	%al, -0x1(%edi)
  5066b0:      	jne	0x50667d <.text+0x10567d>
  5066b2:      	movl	0x8(%esp), %ebx
  5066b6:      	movl	0x658(%esp), %eax
  5066bd:      	movl	0x668(%esp), %edx
  5066c4:      	movl	%eax, 0x678(%esp)
  5066cb:      	movl	%edx, 0x680(%esp)
  5066d2:      	subl	$0x10, %ebx
  5066d5:      	cmpl	$0x10, %ebx
  5066d8:      	jge	0x5065fe <.text+0x1055fe>
  5066de:      	cmpl	$0x0, %ebx
  5066e1:      	movl	0x680(%esp), %ebp
  5066e8:      	movl	0x678(%esp), %esi
  5066ef:      	je	0x5067ad <.text+0x1057ad>
  5066f5:      	fxch	%st(3)
  5066f7:      	fsubs	0x34(%esp)
  5066fb:      	flds	0x28(%esp)
  5066ff:      	fmuls	0x62c810(,%ebx,8)
  506706:      	flds	0x20(%esp)
  50670a:      	fmuls	0x62c810(,%ebx,8)
  506711:      	flds	0x24(%esp)
  506715:      	fmuls	0x62c810(,%ebx,8)
  50671c:      	fxch	%st(2)
  50671e:      	faddp	%st, %st(3)
  506720:      	faddp	%st, %st(3)
  506722:      	faddp	%st, %st(3)
  506724:      	fdivrs	0x62c80c
  50672a:      	fmul	%st, %st(1)
  50672c:      	fildl	0x678(%esp)
  506733:      	fxch	%st(1)
  506735:      	fmul	%st(3), %st
  506737:      	fildl	0x680(%esp)
  50673e:      	fxch	%st(2)
  506740:      	fsubrp	%st, %st(3)
  506742:      	fsubp	%st, %st(1)
  506744:      	fxch	%st(1)
  506746:      	fmuls	0x62c814(,%ebx,8)
  50674d:      	fxch	%st(1)
  50674f:      	fmuls	0x62c814(,%ebx,8)
  506756:      	fxch	%st(1)
  506758:      	faddl	0x632380
  50675e:      	fxch	%st(1)
  506760:      	faddl	0x632380
  506766:      	fxch	%st(1)
  506768:      	fstl	0x660(%esp)
  50676f:      	fxch	%st(1)
  506771:      	fstl	0x670(%esp)
  506778:      	movl	%ebp, %eax
  50677a:      	movl	%esi, %edx
  50677c:      	sarl	$0x10, %eax
  50677f:      	movl	0x670(%esp), %ecx
  506786:      	sarl	$0x10, %edx
  506789:      	addl	%ecx, %ebp
  50678b:      	movl	0xcfdbd8(,%eax,4), %eax
  506792:      	movl	0x660(%esp), %ecx
  506799:      	movb	(%eax,%edx), %dh
  50679c:      	addl	%ecx, %esi
  50679e:      	movb	(%edi), %dl
  5067a0:      	incl	%edi
  5067a1:      	movb	0xd0e460(%edx), %al
  5067a7:      	decl	%ebx
  5067a8:      	movb	%al, -0x1(%edi)
  5067ab:      	jne	0x506778 <.text+0x105778>
  5067ad:      	sarl	$0x10, %ebp
  5067b0:      	xorl	%edx, %edx
  5067b2:      	sarl	$0x10, %esi
  5067b5:      	movb	(%edi), %dl
  5067b7:      	movl	0xcfdbd8(,%ebp,4), %eax
  5067be:      	fcompp
  5067c0:      	movb	(%eax,%esi), %dh
  5067c3:      	fcompp
  5067c5:      	movb	0xd0e460(%edx), %al
  5067cb:      	movb	%al, (%edi)
  5067cd:      	flds	0x694(%esp)
  5067d4:      	fadds	0x6ac(%esp)
  5067db:      	flds	0x69c(%esp)
  5067e2:      	fadds	0x6a4(%esp)
  5067e9:      	flds	0x698(%esp)
  5067f0:      	fadds	0x6a0(%esp)
  5067f7:      	flds	0x690(%esp)
  5067fe:      	fadds	0x6a8(%esp)
  506805:      	fxch	%st(3)
  506807:      	fstps	0x694(%esp)
  50680e:      	fstps	0x698(%esp)
  506815:      	fstps	0x69c(%esp)
  50681c:      	fstps	0x690(%esp)
  506823:      	flds	0x6bc(%esp)
  50682a:      	fadds	0x6d4(%esp)
  506831:      	flds	0x6c4(%esp)
  506838:      	fadds	0x6cc(%esp)
  50683f:      	flds	0x6c0(%esp)
  506846:      	fadds	0x6c8(%esp)
  50684d:      	flds	0x6b8(%esp)
  506854:      	fadds	0x6d0(%esp)
  50685b:      	fxch	%st(3)
  50685d:      	fstps	0x6bc(%esp)
  506864:      	fstps	0x6c0(%esp)
  50686b:      	fstps	0x6c4(%esp)
  506872:      	fstps	0x6b8(%esp)
  506879:      	movl	0x18(%esp), %esi
  50687d:      	movl	0xc(%esp), %eax
  506881:      	movl	(%esp), %ebp
  506884:      	addl	%eax, %esi
  506886:      	movl	0x4(%esp), %edi
  50688a:      	movl	%esi, 0x18(%esp)
  50688e:      	incl	%edi
  50688f:      	jmp	0x5061d5 <.text+0x1051d5>
  506894:      	addl	$0x7d8, %esp            # imm = 0x7D8
  50689a:      	popl	%ebp
  50689b:      	popl	%edi
  50689c:      	popl	%esi
  50689d:      	popl	%ebx
  50689e:      	popl	%ebp
  50689f:      	retl
