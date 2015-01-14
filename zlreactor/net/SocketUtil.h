﻿// ***********************************************************************
// Filename         : SocketUtil.h
// Author           : LIZHENG
// Created          : 2014-09-17
// Description      : socket辅助宏定义、工具函数
//
// Last Modified By : LIZHENG
// Last Modified On : 2015-01-06
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_SOCKETUTIL_H
#define ZL_SOCKETUTIL_H
#include "Define.h"
#ifdef OS_WINDOWS
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#endif

#ifdef OS_WINDOWS
typedef SOCKET       ZL_SOCKET;
typedef sockaddr_in  ZL_SOCKADDR_IN;
typedef int          ZL_SOCKLEN;
typedef int          ssize_t;

#define ZL_INVALID_SOCKET         INVALID_SOCKET
#define RECV_FLAGS                MSG_WAITALL
#define SEND_FLAGS                0
#define SOCKET_ERROR              ::WSAGetLastError()
#define SOCK_ERR_EINTR            WSAEINTR
#define SOCK_ERR_EAGAIN           EAGAIN
#define SOCK_ERR_EINPROGRESS      WSAEINPROGRESS
#define SOCK_ERR_EWOULDBLOCK      WSAEWOULDBLOCK
#define SOCK_ERR_ECONNABORTED     WSAECONNABORTED
#define SOCK_ERR_ECONNREFUSED     WSAECONNREFUSED
#define SOCK_ERR_EBADF            WSAEBADF
#define SOCK_ERR_EADDRINUSE       WSAEADDRINUSE
#define SOCK_ERR_NOTSOCK          WSAENOTSOCK
#define SOCK_ERR_EINVAL           WSAEINVAL
#define SOCK_ERR_EMFILE           WSAEMFILE

#define SHUT_RD                   0
#define SHUT_WR                   1
#define SHUT_RDWR                 2

#define ZL_CREATE_SOCKET(a,b,c)   ::socket(a,b,c)
#define ZL_BIND(a,b,c)            ::bind(a,b,c)
#define ZL_LISTEN(a,b)            ::listen(a,b)
#define ZL_ACCEPT(a,b,c)          ::accept(a,b,c)
#define ZL_CONNECT(a,b,c)         ::connect(a,b,c)
#define ZL_CLOSE(a)               ::closesocket(a)
#define ZL_READ(a,b,c)            ::recv(a,(char *)b,c,0)
#define ZL_RECV(a,b,c,d)          ::recv(a, (char *)b, c, d)
#define ZL_RECVFROM(a,b,c,d,e,f)  ::recvfrom(a, (char *)b, c, d, (sockaddr *)e, (int *)f)
#define ZL_SELECT(a,b,c,d,e)      ::select(a,b,c,d,e)
#define ZL_SEND(a,b,c,d)          ::send(a, (const char *)b, (int)c, d)
#define ZL_SENDTO(a,b,c,d,e,f)    ::sendto(a, (const char *)b, (int)c, d, e, f)
#define ZL_SENDFILE(a,b,c,d)      ::sendfile(a, b, c, d)
#define ZL_WRITE(a,b,c)           ::send(a,(const char *)b,c,0)
#define ZL_WRITEV(a,b,c)          ::writev(b, c)
#define ZL_GETSOCKOPT(a,b,c,d,e)  ::getsockopt(a,b,c,(char *)d, (int *)e)
#define ZL_SETSOCKOPT(a,b,c,d,e)  ::setsockopt(a,b,c,(char *)d, (int)e)
#define ZL_GETHOSTBYNAME(a)       ::gethostbyname((const char *)a)
#define ZL_LSEEK(a,b,c)           ::_lseek(a,b,c)

#elif defined(OS_LINUX)
typedef int          ZL_SOCKET;
typedef sockaddr_in  ZL_SOCKADDR_IN;
typedef socklen_t    ZL_SOCKLEN;

#define ZL_INVALID_SOCKET         -1
#define RECV_FLAGS                0
#define SEND_FLAGS                0
#define SOCKET_ERROR              errno
#define SOCK_ERR_EINTR            EINTR
#define SOCK_ERR_EAGAIN           EAGAIN
#define SOCK_ERR_EINPROGRESS      EINPROGRESS
#define SOCK_ERR_EWOULDBLOCK      EWOULDBLOCK
#define SOCK_ERR_ECONNABORTED     ECONNABORTED
#define SOCK_ERR_ECONNREFUSED     ECONNREFUSED
#define SOCK_ERR_EBADF            EBADF
#define SOCK_ERR_EADDRINUSE       EADDRINUSE
#define SOCK_ERR_NOTSOCK          ENOTSOCK
#define SOCK_ERR_EINVAL           EINVAL
#define SOCK_ERR_EMFILE           EMFILE

#define ZL_CREATE_SOCKET(a,b,c)   ::socket(a,b,c)
#define ZL_BIND(a,b,c)            ::bind(a,b,c)
#define ZL_LISTEN(a,b)            ::listen(a,b)
#define ZL_ACCEPT(a,b,c)          ::accept(a,b,c)
#define ZL_CONNECT(a,b,c)         ::connect(a,b,c)
#define ZL_CLOSE(a)               ::close(a)
#define ZL_READ(a,b,c)            ::read(a,b,c)
#define ZL_RECV(a,b,c,d)          ::recv(a, b, c, d)
#define ZL_RECVFROM(a,b,c,d,e,f)  ::recvfrom(a, (char *)b, c, d, (sockaddr *)e, f)
#define ZL_SELECT(a,b,c,d,e)      ::select(a,b,c,d,e)
#define ZL_SEND(a,b,c,d)          ::send(a, (const char *)b, c, d)
#define ZL_SENDTO(a,b,c,d,e,f)    ::sendto(a, (const char *)b, c, d, e, f)
#define ZL_SENDFILE(a,b,c,d)      ::sendfile(a, b, c, d)
#define ZL_WRITE(a,b,c)           ::write(a,b,c)
#define ZL_WRITEV(a,b,c)          ::writev(a, b, c)
#define ZL_GETSOCKOPT(a,b,c,d,e)  ::getsockopt((int)a,(int)b,(int)c,(void *)d,(socklen_t *)e)
#define ZL_SETSOCKOPT(a,b,c,d,e)  ::setsockopt((int)a,(int)b,(int)c,(const void *)d,(int)e)
#define ZL_GETHOSTBYNAME(a)       ::gethostbyname((const char *)a)
#define ZL_LSEEK(a,b,c)           ::lseek(a,b,c)

#endif

// 判断错误码e是否表示一个socket的read/write/connect等操作没有错误，但需要等待
#if SOCK_ERR_EAGAIN == SOCK_ERR_EWOULDBLOCK
#define SOCK_ERR_IS_EAGAIN(e) ((e) == SOCK_ERR_EAGAIN)
#else
#define SOCK_ERR_IS_EAGAIN(e) ((e) == SOCK_ERR_EAGAIN || (e) == SOCK_ERR_EWOULDBLOCK)
#endif

// 判断错误码e是否表示一个socket的read/write操作可以重试
#define SOCK_ERR_RW_RETRY(e)  ((e) == SOCK_ERR_EINTR || SOCK_ERR_IS_EAGAIN(e))

// 判断错误码e是否表示一个socket的connect操作被拒绝
#define SOCK_ERR_CONNECT_REFUSED(e)    ((e) == SOCK_ERR_ECONNREFUSED)

#if defined(OS_WINDOWS)

#define SOCK_ERR_CONNECT_RETRY(e)            \
        ((e) == SOCK_ERR_EWOULDBLOCK         \
        || (e) == SOCK_ERR_EINTR             \
        || (e) == SOCK_ERR_EINPROGRESS       \
        || (e) == SOCK_ERR_EINVAL)

#define SOCK_ERR_ACCEPT_RETRY(e)    SOCK_ERR_RW_RETRY(e)

#else

// 判断错误码e是否表示一个socket的connect操作可以重试
#define SOCK_ERR_CONNECT_RETRY(e) ((e) == SOCK_ERR_EINTR || (e) == SOCK_ERR_EINPROGRESS)

// 判断错误码e是否表示一个socket的accept操作可以重试
#define SOCK_ERR_ACCEPT_RETRY(e)        \
       ((e) == SOCK_ERR_EINTR || SOCK_ERR_IS_EAGAIN(e) || (e) == ECONNABORTED)

#endif

NAMESPACE_ZL_NET_START

class SocketUtil
{
public:
    static int socketInitialise();
    static int socketCleanup();

    static ZL_SOCKET createSocket();
    static ZL_SOCKET createSocketAndListen(const char *ip, int port, int backlog = 5);
    static int closeSocket(ZL_SOCKET fd);
    static void shutDown(ZL_SOCKET fd);
    static void shutdownWrite(ZL_SOCKET sockfd);

    static int  connect(ZL_SOCKET sockfd, const struct sockaddr_in& addr);
    static ZL_SOCKET acceptOne(ZL_SOCKET sockfd, struct sockaddr_in *addr);
    static ssize_t read(ZL_SOCKET sockfd, void *buf, size_t count);
    static ssize_t write(ZL_SOCKET sockfd, const void *buf, size_t count);

    static int setNonBlocking(ZL_SOCKET fd, bool nonBlocking = true);
    static int setNoDelay(ZL_SOCKET fd, bool noDelay = true);
    static int setReuseAddr(ZL_SOCKET fd, bool flag = true);
    static int setSendBuffer(ZL_SOCKET fd, int readSize);
    static int setRecvBuffer(ZL_SOCKET fd, int writeSize);
    static int getSendBuffer(ZL_SOCKET fd);
    static int getRecvBuffer(ZL_SOCKET fd);

    static struct sockaddr_in getLocalAddr(ZL_SOCKET sockfd);
    static struct sockaddr_in getPeerAddr(ZL_SOCKET sockfd);

    static bool isSelfConnect(ZL_SOCKET sockfd);
    static int getSocketError(ZL_SOCKET sockfd);
};

namespace
{
    class SocketInitialization
    {
    public:
        SocketInitialization()
        {
            SocketUtil::socketInitialise();
        }
        ~SocketInitialization()
        {
            SocketUtil::socketCleanup();
        }
    };

    extern  SocketInitialization  g_socket_init_once;
}

NAMESPACE_ZL_NET_END

#endif  /* ZL_SOCKETUTIL_H */
