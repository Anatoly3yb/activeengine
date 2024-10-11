#include "rid.h"

#ifndef RID_HANDLES_ENABLED
RID_Data::~RID_Data() {
}

SafeRefCount RID_OwnerBase::refcount;

void RID_OwnerBase::init_rid() {
	refcount.init();
}
#endif // not RID_HANDLES_ENABLED
