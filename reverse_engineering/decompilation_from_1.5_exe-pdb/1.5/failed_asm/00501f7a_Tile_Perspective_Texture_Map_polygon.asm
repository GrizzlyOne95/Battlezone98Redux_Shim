; Entry: 00501f7a
; Name: Tile_Perspective_Texture_Map_polygon
; Signature: void Tile_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x005027b8
; Reason: Exception while decompiling 00501f7a: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x00501f7a --stop-address=0x005027b8 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  501f7a:      	pushl	%ebp
  501f7b:      	movl	%esp, %ebp
  501f7d:      	pushl	%ebx
  501f7e:      	pushl	%esi
  501f7f:      	pushl	%edi
  501f80:      	pushl	%ebp
  501f81:      	movl	0x14(%ebp), %ebx
  501f84:      	movl	0xcfdbc0, %eax
  501f89:      	subl	$0x6e0, %esp            # imm = 0x6E0
  501f8f:      	cmpl	%ebx, %eax
  501f91:      	je	0x502001 <.text+0x101001>
  501f93:      	movl	%ebx, 0xcfdbc0
  501f99:      	leal	0xcfdbd8, %edx
  501f9f:      	movl	(%ebx), %eax
  501fa1:      	movl	0x4(%ebx), %ecx
  501fa4:      	leal	0x8(%ebx), %esi
  501fa7:      	movl	%ecx, 0x4(%esp)
  501fab:      	movl	%eax, %edi
  501fad:      	addl	$0x3, %ecx
  501fb0:      	addl	%esi, %edi
  501fb2:      	leal	(%esi,%eax,2), %ebx
  501fb5:      	leal	(%eax,%eax,2), %eax
  501fb8:      	movl	%esi, -0x4(%edx)
  501fbb:      	movl	%esi, -0x8(%edx)
  501fbe:      	movl	%esi, -0xc(%edx)
  501fc1:      	movl	%esi, -0x10(%edx)
  501fc4:      	movl	%esi, (%edx)
  501fc6:      	movl	%edi, 0x4(%edx)
  501fc9:      	movl	%ebx, 0x8(%edx)
  501fcc:      	addl	%eax, %esi
  501fce:      	addl	%eax, %edi
  501fd0:      	addl	%eax, %ebx
  501fd2:      	addl	$0xc, %edx
  501fd5:      	subl	$0x3, %ecx
  501fd8:      	jge	0x501fc4 <.text+0x100fc4>
  501fda:      	movl	0x4(%esp), %edx
  501fde:      	movl	0xcfdbd4(,%edx,4), %eax
  501fe5:      	movl	%eax, 0xcfdbd8(,%edx,4)
  501fec:      	movl	%eax, 0xcfdbdc(,%edx,4)
  501ff3:      	movl	%eax, 0xcfdbe0(,%edx,4)
  501ffa:      	movl	%eax, 0xcfdbe4(,%edx,4)
  502001:      	movl	0x14(%ebp), %ebx
  502004:      	movl	$0x186a0, %edx          # imm = 0x186A0
  502009:      	movl	0xc(%ebp), %esi
  50200c:      	movl	0x10(%ebp), %eax
  50200f:      	movl	(%ebx), %ecx
  502011:      	movl	0x4(%ebx), %edi
  502014:      	decl	%ecx
  502015:      	decl	%edi
  502016:      	fildl	0x4(%ebx)
  502019:      	movl	%ecx, 0x18(%esp)
  50201d:      	movl	%edi, 0x1c(%esp)
  502021:      	incl	%ecx
  502022:      	movl	%esi, (%esp)
  502025:      	shll	$0x3, %eax
  502028:      	leal	0x8(%ebx), %edi
  50202b:      	fildl	(%ebx)
  50202d:      	movl	%ecx, 0x10(%esp)
  502031:      	leal	(%eax,%eax,2), %ecx
  502034:      	xorl	%eax, %eax
  502036:      	movl	%edi, 0x24(%esp)
  50203a:      	flds	0x4(%esi,%eax)
  50203e:      	faddl	0x632380
  502044:      	flds	0xc(%esi,%eax)
  502048:      	fmul	%st(2), %st
  50204a:      	flds	0x10(%esi,%eax)
  50204e:      	fmul	%st(4), %st
  502050:      	fxch	%st(2)
  502052:      	fstpl	0x648(%esp)
  502059:      	fstps	0xc(%esi,%eax)
  50205d:      	fstps	0x10(%esi,%eax)
  502061:      	movl	0x648(%esp), %edi
  502068:      	movl	%eax, 0x328(%esp,%eax)
  50206f:      	movl	%eax, 0x58(%esp,%eax)
  502073:      	movl	%edi, 0x344(%esp,%eax)
  50207a:      	addl	$0x18, %eax
  50207d:      	cmpl	%edx, %edi
  50207f:      	jg	0x502085 <.text+0x101085>
  502081:      	movl	%eax, %ebx
  502083:      	movl	%edi, %edx
  502085:      	cmpl	%ecx, %eax
  502087:      	jne	0x50203a <.text+0x10103a>
  502089:      	subl	$0x18, %ebx
  50208c:      	leal	-0x18(%eax), %ecx
  50208f:      	fcompp
  502091:      	movl	$0x0, 0x328(%esp,%eax)
  50209c:      	movl	%ecx, 0x40(%esp)
  5020a0:      	movl	0x8(%ebp), %edi
  5020a3:      	movl	%ebx, 0x6b8(%esp)
  5020aa:      	movl	%ebx, 0x690(%esp)
  5020b1:      	movl	%ebx, 0x6bc(%esp)
  5020b8:      	movl	%esi, %ebp
  5020ba:      	movl	0x20(%edi), %eax
  5020bd:      	movl	(%edi), %ecx
  5020bf:      	addl	%edx, %eax
  5020c1:      	movl	0x14(%edi), %esi
  5020c4:      	movl	0x1c(%edi), %edi
  5020c7:      	imull	%ecx
  5020c9:      	addl	%edi, %esi
  5020cb:      	movl	%ecx, 0xc(%esp)
  5020cf:      	addl	%eax, %esi
  5020d1:      	movl	0x344(%esp,%ebx), %edi
  5020d8:      	movl	%esi, 0x20(%esp)
  5020dc:      	movl	%ebx, 0x694(%esp)
  5020e3:      	movl	0x6bc(%esp), %ecx
  5020ea:      	movl	0x344(%esp,%ecx), %eax
  5020f1:      	movl	%edi, 0x4(%esp)
  5020f5:      	cmpl	%eax, %edi
  5020f7:      	jl	0x502201 <.text+0x101201>
  5020fd:      	movl	0x340(%esp,%ecx), %edx
  502104:      	movl	%ecx, %eax
  502106:      	movl	%edx, 0x6bc(%esp)
  50210d:      	cmpl	0x690(%esp), %edx
  502114:      	je	0x5027ac <.text+0x1017ac>
  50211a:      	movl	0x344(%esp,%edx), %esi
  502121:      	movl	%edx, %ecx
  502123:      	cmpl	%esi, %edi
  502125:      	jge	0x5020fd <.text+0x1010fd>
  502127:      	flds	0x4(%ebp,%edx)
  50212b:      	fsubs	0x4(%ebp,%eax)
  50212f:      	flds	0x10(%ebp,%edx)
  502133:      	fsubs	0x10(%ebp,%eax)
  502137:      	fxch	%st(1)
  502139:      	fdivrs	0x62c808
  50213f:      	flds	0xc(%ebp,%edx)
  502143:      	fsubs	0xc(%ebp,%eax)
  502147:      	fxch	%st(1)
  502149:      	fmul	%st, %st(2)
  50214b:      	flds	0x8(%ebp,%edx)
  50214f:      	fsubs	0x8(%ebp,%eax)
  502153:      	fxch	%st(2)
  502155:      	fmul	%st(1), %st
  502157:      	flds	(%ebp,%edx)
  50215b:      	fsubs	(%ebp,%eax)
  50215f:      	fxch	%st(3)
  502161:      	fmul	%st(2), %st
  502163:      	fxch	%st(4)
  502165:      	fstps	0x6d4(%esp)
  50216c:      	flds	0x4(%ebp,%eax)
  502170:      	faddl	0x632380
  502176:      	fxch	%st(3)
  502178:      	fmulp	%st, %st(2)
  50217a:      	fstps	0x6d0(%esp)
  502181:      	fxch	%st(1)
  502183:      	fstpl	0x648(%esp)
  50218a:      	fstps	0x6d8(%esp)
  502191:      	fildl	0x648(%esp)
  502198:      	fxch	%st(1)
  50219a:      	fstps	0x6dc(%esp)
  5021a1:      	fsubs	0x4(%ebp,%eax)
  5021a5:      	flds	0x6d8(%esp)
  5021ac:      	flds	0x6dc(%esp)
  5021b3:      	fmul	%st(2), %st
  5021b5:      	flds	0x6d0(%esp)
  5021bc:      	fmul	%st(3), %st
  5021be:      	fxch	%st(1)
  5021c0:      	fadds	0x8(%ebp,%eax)
  5021c4:      	flds	0x6d4(%esp)
  5021cb:      	fmul	%st(4), %st
  5021cd:      	fxch	%st(2)
  5021cf:      	fadds	0xc(%ebp,%eax)
  5021d3:      	fxch	%st(3)
  5021d5:      	fmulp	%st, %st(4)
  5021d7:      	fstps	0x6c4(%esp)
  5021de:      	fadds	0x10(%ebp,%eax)
  5021e2:      	fxch	%st(2)
  5021e4:      	fadds	(%ebp,%eax)
  5021e8:      	fxch	%st(1)
  5021ea:      	fstps	0x6c8(%esp)
  5021f1:      	fxch	%st(1)
  5021f3:      	fstps	0x6cc(%esp)
  5021fa:      	fstps	0x6c0(%esp)
  502201:      	movl	0x694(%esp), %ecx
  502208:      	cmpl	0x344(%esp,%ecx), %edi
  50220f:      	jl	0x502307 <.text+0x101307>
  502215:      	movl	0x40(%esp,%ecx), %edx
  502219:      	movl	%ecx, %eax
  50221b:      	movl	%edx, 0x694(%esp)
  502222:      	movl	%edx, %ecx
  502224:      	cmpl	0x344(%esp,%edx), %edi
  50222b:      	jge	0x502215 <.text+0x101215>
  50222d:      	flds	0x4(%ebp,%edx)
  502231:      	fsubs	0x4(%ebp,%eax)
  502235:      	flds	0x10(%ebp,%edx)
  502239:      	fsubs	0x10(%ebp,%eax)
  50223d:      	fxch	%st(1)
  50223f:      	fdivrs	0x62c808
  502245:      	flds	0xc(%ebp,%edx)
  502249:      	fsubs	0xc(%ebp,%eax)
  50224d:      	fxch	%st(1)
  50224f:      	fmul	%st, %st(2)
  502251:      	flds	0x8(%ebp,%edx)
  502255:      	fsubs	0x8(%ebp,%eax)
  502259:      	fxch	%st(2)
  50225b:      	fmul	%st(1), %st
  50225d:      	flds	(%ebp,%edx)
  502261:      	fsubs	(%ebp,%eax)
  502265:      	fxch	%st(3)
  502267:      	fmul	%st(2), %st
  502269:      	fxch	%st(4)
  50226b:      	fstps	0x6ac(%esp)
  502272:      	flds	0x4(%ebp,%eax)
  502276:      	faddl	0x632380
  50227c:      	fxch	%st(3)
  50227e:      	fmulp	%st, %st(2)
  502280:      	fstps	0x6a8(%esp)
  502287:      	fxch	%st(1)
  502289:      	fstpl	0x648(%esp)
  502290:      	fstps	0x6b0(%esp)
  502297:      	fildl	0x648(%esp)
  50229e:      	fxch	%st(1)
  5022a0:      	fstps	0x6b4(%esp)
  5022a7:      	fsubs	0x4(%ebp,%eax)
  5022ab:      	flds	0x6b0(%esp)
  5022b2:      	flds	0x6b4(%esp)
  5022b9:      	fmul	%st(2), %st
  5022bb:      	flds	0x6a8(%esp)
  5022c2:      	fmul	%st(3), %st
  5022c4:      	fxch	%st(1)
  5022c6:      	fadds	0x8(%ebp,%eax)
  5022ca:      	flds	0x6ac(%esp)
  5022d1:      	fmul	%st(4), %st
  5022d3:      	fxch	%st(2)
  5022d5:      	fadds	0xc(%ebp,%eax)
  5022d9:      	fxch	%st(3)
  5022db:      	fmulp	%st, %st(4)
  5022dd:      	fstps	0x69c(%esp)
  5022e4:      	fadds	0x10(%ebp,%eax)
  5022e8:      	fxch	%st(2)
  5022ea:      	fadds	(%ebp,%eax)
  5022ee:      	fxch	%st(1)
  5022f0:      	fstps	0x6a0(%esp)
  5022f7:      	fxch	%st(1)
  5022f9:      	fstps	0x6a4(%esp)
  502300:      	fstps	0x698(%esp)
  502307:      	flds	0x6c0(%esp)
  50230e:      	faddl	0x632380
  502314:      	flds	0x698(%esp)
  50231b:      	faddl	0x632380
  502321:      	fxch	%st(1)
  502323:      	fstpl	0x658(%esp)
  50232a:      	fstpl	0x650(%esp)
  502331:      	movl	0x658(%esp), %edx
  502338:      	movl	0x650(%esp), %ebx
  50233f:      	cmpl	%edx, %ebx
  502341:      	je	0x5026e5 <.text+0x1016e5>
  502347:      	jl	0x5023e9 <.text+0x1013e9>
  50234d:      	flds	0x698(%esp)
  502354:      	fsubs	0x6c0(%esp)
  50235b:      	flds	0x6a4(%esp)
  502362:      	fsubs	0x6cc(%esp)
  502369:      	fxch	%st(1)
  50236b:      	fdivrs	0x62c808
  502371:      	flds	0x6a0(%esp)
  502378:      	fsubs	0x6c8(%esp)
  50237f:      	fxch	%st(2)
  502381:      	fmul	%st(1), %st
  502383:      	flds	0x69c(%esp)
  50238a:      	fsubs	0x6c4(%esp)
  502391:      	fxch	%st(3)
  502393:      	fmul	%st(2), %st
  502395:      	fxch	%st(1)
  502397:      	fstps	0x2c(%esp)
  50239b:      	fxch	%st(1)
  50239d:      	fmulp	%st, %st(2)
  50239f:      	fstps	0x28(%esp)
  5023a3:      	fildl	0x658(%esp)
  5023aa:      	fxch	%st(1)
  5023ac:      	fstps	0x30(%esp)
  5023b0:      	fsubs	0x6c0(%esp)
  5023b7:      	flds	0x2c(%esp)
  5023bb:      	flds	0x28(%esp)
  5023bf:      	fmul	%st(2), %st
  5023c1:      	flds	0x30(%esp)
  5023c5:      	fmul	%st(3), %st
  5023c7:      	fxch	%st(1)
  5023c9:      	fadds	0x6c8(%esp)
  5023d0:      	fxch	%st(3)
  5023d2:      	fmulp	%st, %st(2)
  5023d4:      	fadds	0x6c4(%esp)
  5023db:      	fxch	%st(1)
  5023dd:      	fadds	0x6cc(%esp)
  5023e4:      	jmp	0x502490 <.text+0x101490>
  5023e9:      	movl	%ebx, 0x658(%esp)
  5023f0:      	movl	%edx, %ebx
  5023f2:      	movl	0x658(%esp), %edx
  5023f9:      	flds	0x6c0(%esp)
  502400:      	fsubs	0x698(%esp)
  502407:      	flds	0x6cc(%esp)
  50240e:      	fsubs	0x6a4(%esp)
  502415:      	fxch	%st(1)
  502417:      	fdivrs	0x62c808
  50241d:      	flds	0x6c8(%esp)
  502424:      	fsubs	0x6a0(%esp)
  50242b:      	fxch	%st(2)
  50242d:      	fmul	%st(1), %st
  50242f:      	flds	0x6c4(%esp)
  502436:      	fsubs	0x69c(%esp)
  50243d:      	fxch	%st(3)
  50243f:      	fmul	%st(2), %st
  502441:      	fxch	%st(1)
  502443:      	fstps	0x2c(%esp)
  502447:      	fxch	%st(1)
  502449:      	fmulp	%st, %st(2)
  50244b:      	fstps	0x28(%esp)
  50244f:      	fildl	0x658(%esp)
  502456:      	fxch	%st(1)
  502458:      	fstps	0x30(%esp)
  50245c:      	fsubs	0x698(%esp)
  502463:      	flds	0x2c(%esp)
  502467:      	flds	0x28(%esp)
  50246b:      	fmul	%st(2), %st
  50246d:      	flds	0x30(%esp)
  502471:      	fmul	%st(3), %st
  502473:      	fxch	%st(1)
  502475:      	fadds	0x6a0(%esp)
  50247c:      	fxch	%st(3)
  50247e:      	fmulp	%st, %st(2)
  502480:      	fadds	0x69c(%esp)
  502487:      	fxch	%st(1)
  502489:      	fadds	0x6a4(%esp)
  502490:      	movl	0x20(%esp), %edi
  502494:      	subl	%edx, %ebx
  502496:      	addl	%edx, %edi
  502498:      	flds	0x28(%esp)
  50249c:      	fmuls	0x62c814
  5024a2:      	flds	0x2c(%esp)
  5024a6:      	fmuls	0x62c814
  5024ac:      	flds	0x30(%esp)
  5024b0:      	fmuls	0x62c814
  5024b6:      	fxch	%st(2)
  5024b8:      	fstps	0x34(%esp)
  5024bc:      	fstps	0x38(%esp)
  5024c0:      	fstps	0x3c(%esp)
  5024c4:      	fxch	%st(1)
  5024c6:      	flds	0x62c80c
  5024cc:      	fdiv	%st(1), %st
  5024ce:      	fld	%st(2)
  5024d0:      	fmul	%st(1), %st
  5024d2:      	fld	%st(4)
  5024d4:      	fmulp	%st, %st(2)
  5024d6:      	faddl	0x632380
  5024dc:      	fxch	%st(1)
  5024de:      	faddl	0x632380
  5024e4:      	fxch	%st(2)
  5024e6:      	fadds	0x3c(%esp)
  5024ea:      	fxch	%st(1)
  5024ec:      	fstpl	0x688(%esp)
  5024f3:      	fxch	%st(1)
  5024f5:      	fstpl	0x680(%esp)
  5024fc:      	fxch	%st(2)
  5024fe:      	flds	0x62c80c
  502504:      	fdiv	%st(3), %st
  502506:      	decl	%ebx
  502507:      	jmp	0x5025e7 <.text+0x1015e7>
  50250c:      	flds	0x34(%esp)
  502510:      	faddp	%st, %st(2)
  502512:      	flds	0x38(%esp)
  502516:      	faddp	%st, %st(3)
  502518:      	fld	%st(1)
  50251a:      	fmul	%st(1), %st
  50251c:      	flds	0x3c(%esp)
  502520:      	fxch	%st(2)
  502522:      	fmul	%st(4), %st
  502524:      	fxch	%st(2)
  502526:      	faddp	%st, %st(5)
  502528:      	faddl	0x632380
  50252e:      	fxch	%st(1)
  502530:      	faddl	0x632380
  502536:      	fld	%st(4)
  502538:      	fxch	%st(2)
  50253a:      	fstpl	0x660(%esp)
  502541:      	fstpl	0x670(%esp)
  502548:      	fdivrs	0x62c80c
  50254e:      	movl	0x688(%esp), %ebp
  502555:      	movl	0x680(%esp), %esi
  50255c:      	movl	0x670(%esp), %eax
  502563:      	movl	0x660(%esp), %edx
  50256a:      	subl	%ebp, %eax
  50256c:      	subl	%esi, %edx
  50256e:      	sarl	$0x4, %eax
  502571:      	movl	%ebx, 0x8(%esp)
  502575:      	sarl	$0x4, %edx
  502578:      	movl	%eax, 0x678(%esp)
  50257f:      	movl	%edx, 0x668(%esp)
  502586:      	movl	$0x10, %ebx
  50258b:      	movl	%ebp, %eax
  50258d:      	movl	0x678(%esp), %ecx
  502594:      	sarl	$0x10, %eax
  502597:      	movl	0x1c(%esp), %edx
  50259b:      	addl	%ecx, %ebp
  50259d:      	andl	%edx, %eax
  50259f:      	movl	%esi, %edx
  5025a1:      	movl	0x668(%esp), %ecx
  5025a8:      	sarl	$0x10, %edx
  5025ab:      	movl	0xcfdbd8(,%eax,4), %eax
  5025b2:      	addl	%ecx, %esi
  5025b4:      	movl	0x18(%esp), %ecx
  5025b8:      	incl	%edi
  5025b9:      	andl	%ecx, %edx
  5025bb:      	movb	(%eax,%edx), %al
  5025be:      	decl	%ebx
  5025bf:      	movb	%al, -0x1(%edi)
  5025c2:      	jne	0x50258b <.text+0x10158b>
  5025c4:      	movl	0x8(%esp), %ebx
  5025c8:      	movl	0x660(%esp), %eax
  5025cf:      	movl	0x670(%esp), %edx
  5025d6:      	movl	%eax, 0x680(%esp)
  5025dd:      	movl	%edx, 0x688(%esp)
  5025e4:      	subl	$0x10, %ebx
  5025e7:      	cmpl	$0x10, %ebx
  5025ea:      	jge	0x50250c <.text+0x10150c>
  5025f0:      	cmpl	$0x0, %ebx
  5025f3:      	movl	0x688(%esp), %ebp
  5025fa:      	movl	0x680(%esp), %esi
  502601:      	je	0x5026c3 <.text+0x1016c3>
  502607:      	fxch	%st(3)
  502609:      	fsubs	0x3c(%esp)
  50260d:      	flds	0x30(%esp)
  502611:      	fmuls	0x62c810(,%ebx,8)
  502618:      	flds	0x28(%esp)
  50261c:      	fmuls	0x62c810(,%ebx,8)
  502623:      	flds	0x2c(%esp)
  502627:      	fmuls	0x62c810(,%ebx,8)
  50262e:      	fxch	%st(2)
  502630:      	faddp	%st, %st(3)
  502632:      	faddp	%st, %st(3)
  502634:      	faddp	%st, %st(3)
  502636:      	fdivrs	0x62c80c
  50263c:      	fmul	%st, %st(1)
  50263e:      	fildl	0x680(%esp)
  502645:      	fxch	%st(1)
  502647:      	fmul	%st(3), %st
  502649:      	fildl	0x688(%esp)
  502650:      	fxch	%st(2)
  502652:      	fsubrp	%st, %st(3)
  502654:      	fsubp	%st, %st(1)
  502656:      	fxch	%st(1)
  502658:      	fmuls	0x62c814(,%ebx,8)
  50265f:      	fxch	%st(1)
  502661:      	fmuls	0x62c814(,%ebx,8)
  502668:      	fxch	%st(1)
  50266a:      	faddl	0x632380
  502670:      	fxch	%st(1)
  502672:      	faddl	0x632380
  502678:      	fxch	%st(1)
  50267a:      	fstl	0x668(%esp)
  502681:      	fxch	%st(1)
  502683:      	fstl	0x678(%esp)
  50268a:      	movl	%ebp, %eax
  50268c:      	movl	0x678(%esp), %ecx
  502693:      	sarl	$0x10, %eax
  502696:      	movl	0x1c(%esp), %edx
  50269a:      	addl	%ecx, %ebp
  50269c:      	andl	%edx, %eax
  50269e:      	movl	%esi, %edx
  5026a0:      	movl	0x668(%esp), %ecx
  5026a7:      	sarl	$0x10, %edx
  5026aa:      	movl	0xcfdbd8(,%eax,4), %eax
  5026b1:      	addl	%ecx, %esi
  5026b3:      	movl	0x18(%esp), %ecx
  5026b7:      	incl	%edi
  5026b8:      	andl	%ecx, %edx
  5026ba:      	movb	(%eax,%edx), %al
  5026bd:      	decl	%ebx
  5026be:      	movb	%al, -0x1(%edi)
  5026c1:      	jne	0x50268a <.text+0x10168a>
  5026c3:      	sarl	$0x10, %ebp
  5026c6:      	movl	0x1c(%esp), %eax
  5026ca:      	sarl	$0x10, %esi
  5026cd:      	andl	%eax, %ebp
  5026cf:      	fcompp
  5026d1:      	movl	0x18(%esp), %ecx
  5026d5:      	movl	0xcfdbd8(,%ebp,4), %eax
  5026dc:      	andl	%ecx, %esi
  5026de:      	fcompp
  5026e0:      	movb	(%eax,%esi), %al
  5026e3:      	movb	%al, (%edi)
  5026e5:      	flds	0x69c(%esp)
  5026ec:      	fadds	0x6b4(%esp)
  5026f3:      	flds	0x6a4(%esp)
  5026fa:      	fadds	0x6ac(%esp)
  502701:      	flds	0x6a0(%esp)
  502708:      	fadds	0x6a8(%esp)
  50270f:      	flds	0x698(%esp)
  502716:      	fadds	0x6b0(%esp)
  50271d:      	fxch	%st(3)
  50271f:      	fstps	0x69c(%esp)
  502726:      	fstps	0x6a0(%esp)
  50272d:      	fstps	0x6a4(%esp)
  502734:      	fstps	0x698(%esp)
  50273b:      	flds	0x6c4(%esp)
  502742:      	fadds	0x6dc(%esp)
  502749:      	flds	0x6cc(%esp)
  502750:      	fadds	0x6d4(%esp)
  502757:      	flds	0x6c8(%esp)
  50275e:      	fadds	0x6d0(%esp)
  502765:      	flds	0x6c0(%esp)
  50276c:      	fadds	0x6d8(%esp)
  502773:      	fxch	%st(3)
  502775:      	fstps	0x6c4(%esp)
  50277c:      	fstps	0x6c8(%esp)
  502783:      	fstps	0x6cc(%esp)
  50278a:      	fstps	0x6c0(%esp)
  502791:      	movl	0x20(%esp), %esi
  502795:      	movl	0xc(%esp), %eax
  502799:      	movl	(%esp), %ebp
  50279c:      	addl	%eax, %esi
  50279e:      	movl	0x4(%esp), %edi
  5027a2:      	movl	%esi, 0x20(%esp)
  5027a6:      	incl	%edi
  5027a7:      	jmp	0x5020e3 <.text+0x1010e3>
  5027ac:      	addl	$0x6e0, %esp            # imm = 0x6E0
  5027b2:      	popl	%ebp
  5027b3:      	popl	%edi
  5027b4:      	popl	%esi
  5027b5:      	popl	%ebx
  5027b6:      	popl	%ebp
  5027b7:      	retl
