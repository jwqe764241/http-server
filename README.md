HTTP 통신
통신기록

인증
정적 콘텐츠 관리
HTTPS 지원
콘텐츠 압축
가상 호스팅
대용량 파일 지원
대역폭 스로틀링


abstract of server
	|	|	|
http
 -> packet wrapper
 -> web content template when error occure

utils
 -> excetion
 -> socket wrapper

server
 -> url mapper
 -> port selection
 
HTTP/1.1 200 OK
Date: Sun, 28 Jul 2013 15:37:37 GMT
Server: Apache
Last-Modified: Sun, 07 Jul 2013 06:13:43 GMT
Transfer-Encoding: chunked
Connection: Keep-Alive
Content-Type: text/html; charset=UTF-8
(한줄띄우고)


Webpage Content <- 여기에 에러 페이지 템플릿 넣을것





구현목록

Parser

Option

Socket

Server

Errorpage mapper

Exceptions

