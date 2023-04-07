#ifndef __PROJ_CONFIGS_H__
#define __PROJ_CONFIGS_H__

#include <cstddef>

constexpr size_t QP_MAX_SEND_WR= 1024; // depth of send queue
constexpr size_t QP_MAX_RECV_WR = 1024; // depth of receive queue
constexpr size_t QP_MAX_SEND_SGE = 1; // max number of sge of send request
constexpr size_t QP_MAX_RECV_SGE = 1; // max number of sge of receive request

#endif //__PROJ_CONFIGS_H__
