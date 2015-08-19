//
//  gui.c
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#include <stdio.h>
#include "baye/compa.h"
#include "inc/dictsys.h"
#include "sem.h"


struct QueueNode {
    struct QueueNode* next;
    struct QueueNode* prev;
};

static struct MsgQueue {
    struct QueueNode node;
    GAM_SEM msg_queue_sem;
    GAM_SEM msg_queue_lck;
}msg_queue;

struct MsgNode {
    struct QueueNode node;
    MsgType msg;
};

static void msg_queue_put(struct MsgQueue*q, MsgType* pMsg)
{
    struct MsgNode *node = calloc(1, sizeof(struct MsgNode));
    struct QueueNode *first, *last;
    node->msg = *pMsg;
    
    gam_sem_wait(q->msg_queue_lck);
    
    first = q->node.next;
    last = q->node.prev;
    
    q->node.prev = &node->node;
    node->node.prev = last;
    node->node.next = &q->node;
    last->next = &node->node;
    
    gam_sem_signal(q->msg_queue_lck);
    gam_sem_signal(q->msg_queue_sem);
}

static int msg_queue_get(struct MsgQueue*q, MsgType *msg)
{
    struct QueueNode *first;
    
    gam_sem_wait(q->msg_queue_sem);
    
    gam_sem_wait(q->msg_queue_lck);
    first = q->node.next;
    if (first->next == first) {
        gam_sem_signal(q->msg_queue_lck);
        return 0;
    }
    first->next->prev = first->prev;
    first->prev->next = first->next;
    gam_sem_signal(q->msg_queue_lck);
    
    *msg = ((struct MsgNode*)first)->msg;
    free(first);
    return 1;
}


U16 GuiGetKbdState()
{
    return 0;
}

U8 GuiInit(void){
    msg_queue.msg_queue_sem = gam_sem_create();
    msg_queue.msg_queue_lck = gam_sem_create();
    gam_sem_signal(msg_queue.msg_queue_lck);
    msg_queue.node.prev = &msg_queue.node;
    msg_queue.node.next = &msg_queue.node;
    return 1;
}
void	GuiSetKbdState(U16 state){}
void	GuiSetInputFilter(U8	filter){}		/* 键盘屏蔽属性 */
void	GuiSetKbdType(U8	type){}				/* 键盘类型		*/
U8		GuiTranslateMsg(PtrMsg	pMsg){
    return 1;
}

U8 GuiPushMsg(PtrMsg pMsg)
{
    msg_queue_put(&msg_queue, pMsg);
    return 1;
}

U8 GuiGetMsg(PtrMsg pMsg)
{
    return msg_queue_get(&msg_queue, pMsg);
}


FAR	U8		GuiMsgBox( U8*  strMsg, U16		nTimeout)
{
    printf("GuiMsgBox:%s\n", strMsg);
    return 0;
}

FAR	U8		GuiQueryBox(U8	sel , U8	infoType , U8	*infoData)
{
    printf("GuiQueryBox:%s\n", infoData);
    return 1;
}
