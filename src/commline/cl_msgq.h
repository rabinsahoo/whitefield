/*
 * Copyright (C) 2017 Rahul Jadhav <nyrahul@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU
 * General Public License v2. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     commline
 * @{
 *
 * @file
 * @brief       SysV message queue for commline
 *
 * @author      Rahul Jadhav <nyrahul@gmail.com>
 *
 * @}
 */

#ifndef	_CL_MSGQ_H_
#define	_CL_MSGQ_H_

int msgq_init(const uint8_t flags);
void msgq_cleanup(void);
int msgq_recvfrom(const long mtype, msg_buf_t *mbuf, uint16_t len);
int msgq_sendto(const long mtype, msg_buf_t *mbuf, uint16_t len);

#endif //_CL_MSGQ_H_
