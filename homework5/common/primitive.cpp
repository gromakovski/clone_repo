#include "primitive.h"
#include "primitive_visitor.h"

void Rect::accept(IPrimitiveVisitor &v) { v.visit(this); }

void Circle::accept(IPrimitiveVisitor &v) { v.visit(this); }
