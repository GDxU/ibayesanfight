//
//  sem.h
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#ifndef __baye_ios__lock__
#define __baye_ios__lock__

#include <stdio.h>

typedef void* GAM_SEM;

GAM_SEM gam_sem_create();
void gam_sem_delete(GAM_SEM sem);
void gam_sem_wait(GAM_SEM sem);
void gam_sem_signal(GAM_SEM sem);

#endif /* defined(__baye_ios__lock__) */
