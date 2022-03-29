#include <memory>

void* aligned_malloc(size_t required_bytes, size_t alignment)
{
    int offset = alignment - 1 + sizeof(void*);
    void* p1 = (void*)malloc(required_bytes + offset);
    if (p1 == nullptr)
        return nullptr;
    void** p2 = (void**)( ( (size_t)p1 + offset ) & ~(alignment - 1) );
    p2[-1] = p1;
    return p2;
}
 
void aligned_free(void *p2)
{
    void* p1 = ((void**)p2)[-1];
    free(p1);
}