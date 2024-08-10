#pragma once
#ifndef K_VISITOR_H
#define K_VISITOR_H
#include "AST.h"

typedef struct VISITOR_STRUCT {
	AST_T** srcdefs;
	size_t srcdefs_size;
} visitor_T;

visitor_T* init_visitor();

AST_T* vt_visit(visitor_T* visitor, AST_T* node);

AST_T* vt_VSrcDef(visitor_T* visitor, AST_T* node);

AST_T* vt_VSrc(visitor_T* visitor, AST_T* node);

AST_T* vt_VFCall(visitor_T* visitor, AST_T* node);

AST_T* vt_VStr(visitor_T* visitor, AST_T* node);

AST_T* vt_VCompound(visitor_T* visitor, AST_T* node);


#endif // !K_VISITOR_H
