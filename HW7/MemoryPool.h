#ifndef _MEMORYPOOL_
#define _MEMORYPOOL_

#include <climits>
#include <cstddef>

template <typename T>
class MemoryPool
{
public:
    /* Member types */
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;
    typedef std::true_type  propagate_on_container_move_assignment;
    typedef std::true_type  propagate_on_container_swap;

    template <typename U> struct rebind {
        typedef MemoryPool<U> other;
    };

    /* Member functions */
    MemoryPool() noexcept;
    MemoryPool(const MemoryPool& memoryPool) noexcept;
    MemoryPool(MemoryPool&& memoryPool) noexcept;
    template <class U> MemoryPool(const MemoryPool<U>& memoryPool) noexcept;

    ~MemoryPool() noexcept;

    // Forbid assign operator for const MemoryPool&
    MemoryPool& operator=(const MemoryPool& memoryPool) = delete;

    MemoryPool& operator=(MemoryPool&& memoryPool) noexcept;

    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;

    // hint are ignored
    pointer allocate(size_type n = 1, const_pointer hint = 0);
    void deallocate(pointer p, size_type n = 1);

    // Returns the largest value n for which the call allocate(n,0) might succeed
    size_type max_size() const noexcept;

    template <class U, class... Args> void construct(U* p, Args&&... args);
    template <class U> void destroy(U* p);

    template <class... Args> pointer newElement(Args&&... args);
    void deleteElement(pointer p);

private:
    /* Member types */
    typedef unsigned char* data_pointer;
    // Size of each small memory slice
    const size_type blockSize = 4096;

    // We divide each memory slice in the smallest unit of slot
    // For better use the memory, we use union to store the next pointer
    // and the element itself in the same memory.
    // So Pointers don't introduce extra memory, 
    // but this is unfriendly for smaller types, such as char
    union Slot {
        value_type element;
        Slot* next;
    };
    typedef Slot slot_type;
    typedef Slot* slot_pointer;

    // Stores memory slices that have not been fully allocated
    slot_pointer currentBlock;
    // Points to the next unassigned element in the current memory slice
    slot_pointer currentSlot;
    // Points to the last memory slice in the current memory slice
    slot_pointer lastSlot;
    // Points to the next free memory slice
    slot_pointer freeSlots;

    /* Member functions */
    // Aligns p to the nearest multiple of align for better memory use
    size_type AlignPointer(data_pointer p, size_type align) const noexcept;
    // For small block request, we allocate a new block when the current block is full
    void allocateSmallBlock();
    // For big block request, we allocate a new block for each request
    pointer allocateBigBlock(size_type n);
};

template <typename T>
MemoryPool<T>::MemoryPool() noexcept 
: currentBlock(nullptr), currentSlot(nullptr), lastSlot(nullptr), freeSlots(nullptr)
{}

template <typename T>
MemoryPool<T>::MemoryPool(const MemoryPool& memoryPool) noexcept 
: MemoryPool()
{}

template <typename T>
MemoryPool<T>::MemoryPool(MemoryPool&& memoryPool) noexcept
{
    std::swap(currentBlock, memoryPool.currentBlock);
    std::swap(currentSlot, memoryPool.currentSlot);
    std::swap(lastSlot, memoryPool.lastSlot);
    std::swap(freeSlots, memoryPool.freeSlots);
}

template <typename T>
template <class U>
MemoryPool<T>::MemoryPool(const MemoryPool<U>& memoryPool) noexcept 
: MemoryPool()
{}

template <typename T>
MemoryPool<T>& MemoryPool<T>::operator=(MemoryPool&& memoryPool) noexcept
{
    if (this != &memoryPool)
    {
        std::swap(currentBlock, memoryPool.currentBlock);
        std::swap(currentSlot, memoryPool.currentSlot);
        std::swap(lastSlot, memoryPool.lastSlot);
        std::swap(freeSlots, memoryPool.freeSlots);
    }
    return *this;
}

template <typename T>
MemoryPool<T>::~MemoryPool() noexcept
{
    // Release all the memory we allocated
    slot_pointer curr = currentBlock;
    while (curr != nullptr) {
        slot_pointer nextptr = curr->next;
        operator delete(reinterpret_cast<void*>(curr));
        curr = nextptr;
    }
}

template <typename T>
typename MemoryPool<T>::pointer MemoryPool<T>::address(reference x) const noexcept
{
    return &x;
}

template <typename T>
typename MemoryPool<T>::const_pointer MemoryPool<T>::address(const_reference x) const noexcept
{
    return &x;
}

template <typename T>
typename MemoryPool<T>::size_type MemoryPool<T>::AlignPointer(data_pointer p, size_type align) const noexcept
{
  size_type result = reinterpret_cast<size_type>(p);
  return ((align - result) % align);
}

template <typename T>
void MemoryPool<T>::allocateSmallBlock()
{
    // Allocate space for the new block and store a pointer to the previous one
    data_pointer newBlock = reinterpret_cast<data_pointer>(operator new(blockSize));
    reinterpret_cast<slot_pointer>(newBlock)->next = currentBlock;
    currentBlock = reinterpret_cast<slot_pointer>(newBlock);

    // Pad block body to staisfy the alignment requirements for elements
    data_pointer body = newBlock + sizeof(slot_pointer);
    size_type bodyPadding = AlignPointer(body, alignof(slot_type));

    currentSlot = reinterpret_cast<slot_pointer>(body + bodyPadding);
    lastSlot = reinterpret_cast<slot_pointer>(newBlock + blockSize - sizeof(slot_type) + 1);

}

template <typename T>
typename MemoryPool<T>::pointer MemoryPool<T>::allocateBigBlock(size_type n)
{
    // Allocate space for the new block and store a pointer to the previous one
    size_type newblockSize = n * sizeof(slot_type) + sizeof(slot_pointer) + alignof(slot_type);
    data_pointer newBlock = reinterpret_cast<data_pointer>(operator new(newblockSize));

    // Insert it after the current memory block(if have)
    if(currentBlock != nullptr){
        reinterpret_cast<slot_pointer>(newBlock)->next = currentBlock->next;
        currentBlock->next = reinterpret_cast<slot_pointer>(newBlock);
    }else{
        reinterpret_cast<slot_pointer>(newBlock)->next = nullptr;
        currentBlock = reinterpret_cast<slot_pointer>(newBlock);
    }

    // Pad block body to staisfy the alignment requirements for elements
    data_pointer body = newBlock + sizeof(slot_pointer);
    size_type bodyPadding = AlignPointer(body, alignof(slot_type));
    pointer result = reinterpret_cast<pointer>(body + bodyPadding);

    return result;
}

template <typename T>
typename MemoryPool<T>::pointer MemoryPool<T>::allocate(size_type n, const_pointer hint)
{
    if(n * sizeof(slot_type) + sizeof(slot_pointer) + alignof(slot_type) > blockSize){
        return allocateBigBlock(n);
    }
    if (n == 1 && freeSlots != nullptr) {
        pointer result = reinterpret_cast<pointer>(freeSlots);
        freeSlots = freeSlots->next;
        return result;
    }
    else {
        if (currentSlot + (n - 1) >= lastSlot){
            // Put the remaining slots into freeSlots
            while(currentSlot < lastSlot){
                currentSlot->next = freeSlots;
                freeSlots = currentSlot;
                currentSlot++;
            }
            allocateSmallBlock();
        }
        pointer result = reinterpret_cast<pointer>(currentSlot);
        currentSlot += n;
        return result;
    }
}

template <typename T>
void MemoryPool<T>::deallocate(pointer p, size_type n)
{
    if (p != nullptr) {
        slot_pointer curr = reinterpret_cast<slot_pointer>(p);
        for(int i = n-1; i >= 0; --i){
            (curr + i)->next = freeSlots;
            freeSlots = curr + i;
        }
    }
}

template <typename T>
typename MemoryPool<T>::size_type MemoryPool<T>::max_size() const noexcept
{
    size_type maxMemory = -1;
    return maxMemory;
}

template <typename T>
template <class U, class... Args>
void MemoryPool<T>::construct(U* p, Args&&... args)
{
    new (p) U (std::forward<Args>(args)...);
}

template <typename T>
template <class U>
void MemoryPool<T>::destroy(U* p)
{
    p->~U();
}

template <typename T>
template <class... Args>
typename MemoryPool<T>::pointer MemoryPool<T>::newElement(Args&&... args)
{
    pointer result = allocate();
    construct<value_type>(result, std::forward<Args>(args)...);
    return result;
}

template <typename T>
void MemoryPool<T>::deleteElement(pointer p)
{
    if (p != nullptr) {
        p->~value_type();
        deallocate(p);
    }
}

#endif
