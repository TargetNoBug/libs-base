/* 
   NSLock.h

   Definitions for locking protocol and classes

   Copyright (C) 1996 Free Software Foundation, Inc.

   Author:  Scott Christley <scottc@net-community.com>
   Date: 1996
   
   This file is part of the GNUstep Objective-C Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   If you are interested in a warranty or support for this source code,
   contact Scott Christley <scottc@net-community.com> for more information.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/ 

#ifndef _GNUstep_H_NSLock
#define _GNUstep_H_NSLock

#include <Foundation/NSObject.h>
#include <objc/thr.h>

//
// NSLocking protocol
//
@protocol NSLocking

- (void)lock;
- (void)unlock;

@end

//
// NSLock class
// Simplest lock for protecting critical sections of code
//
@interface NSLock : NSObject <NSLocking>
{
@private
    _objc_mutex_t mutex;
}

- (BOOL)tryLock;

// NSLocking protocol
- (void)lock;
- (void)unlock;

@end

//
// NSConditionLock
// Allows locking and unlocking to be based upon a condition
//
@interface NSConditionLock : NSObject <NSLocking>
{
@private
    _objc_mutex_t mutex;
    int condition;
}

// Initialize lock with condition
- (id)initWithCondition:(int)value;

// Return the current condition of the lock
- (int)condition;

// Acquiring and release the lock
- (void)lockWhenCondition:(int)value;
- (void)unlockWithCondition:(int)value;
- (BOOL)tryLock;
- (BOOL)tryLockWhenCondition:(int)value;

// NSLocking protocol
- (void)lock;
- (void)unlock;

@end

//
// NSRecursiveLock
// Allows the lock to be recursively acquired by the same thread
//
// If the same thread locks the mutex (n) times then that same 
// thread must also unlock it (n) times before another thread 
// can acquire the lock.
//
@interface NSRecursiveLock : NSObject <NSLocking>
{
@private
    _objc_mutex_t mutex;
}

- (BOOL)tryLock;

// NSLocking protocol
- (void)lock;
- (void)unlock;

@end

#endif /* _GNUstep_H_NSLock */
