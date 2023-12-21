/**
 * @file mylist.h
 * @author kevin (happyj2me@aliyun.com)
 * @brief 
   *节点的链接成员指向的是下一个节点的链接成员。使用侵入式链表的好处是：
   *节点类型无需一致，只需要成员节点（element_t）包含list_node_t成员即可
   *泛化能力强，所有链表的操作方式均可统一；
 * @version 0.1
 * @date 2023-11-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _MY_LIST_H
#define _MY_LIST_H

#if defined _MSC_VER && !defined _CRT_USE_BUILTIN_OFFSETOF
    #ifdef __cplusplus
        #define offsetof(s,m)  \
           ((::size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))
    #else
        #define offsetof(s,m) ((size_t)&(((s*)0)->m))
    #endif
#else
    #define offsetof(s,m) __builtin_offsetof(s,m)
#endif

#define container_of(ptr, type, member) \
  ((type*)(((char*)((type*)(ptr))) - offsetof(type, member))


    typedef struct list_node list_node_t;
    typedef struct list_node {
        list_node_t* prev;
        list_node_t* next;
    } list_node_t;

    typedef struct list {
        int size;
        list_node_t head;
    } list_t;
#endif