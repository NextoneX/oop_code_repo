#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

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
    typedef unsigned char* data_pointer;
    // For better use the memory, we use union to store the next pointer
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

    const size_type BlockSize = 4096;

    size_type padPointer(data_pointer p, size_type align) const noexcept;
    void allocateSmallBlock();
    pointer allocateBigBlock(size_type n);
};

template <typename T>
typename MemoryPool<T>::size_type MemoryPool<T>::padPointer(data_pointer p, size_type align) const noexcept
{
  size_type result = reinterpret_cast<uintptr_t>(p);
  return ((align - result) % align);
}

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
    currentBlock = memoryPool.currentBlock;
    memoryPool.currentBlock = nullptr;
    currentSlot = memoryPool.currentSlot;
    lastSlot = memoryPool.lastSlot;
    freeSlots = memoryPool.freeSlots;
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
        currentSlot = memoryPool.currentSlot;
        lastSlot = memoryPool.lastSlot;
        freeSlots = memoryPool.freeSlots;
    }
    return *this;
}

template <typename T>
MemoryPool<T>::~MemoryPool() noexcept
{
    slot_pointer curr = currentBlock;
    while (curr != nullptr) {
        slot_pointer prev = curr->next;
        operator delete(reinterpret_cast<void*>(curr));
        curr = prev;
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
void MemoryPool<T>::allocateSmallBlock()
{
    // Allocate space for the new block and store a pointer to the previous one
    data_pointer newBlock = reinterpret_cast<data_pointer>
                            (operator new(BlockSize));
    reinterpret_cast<slot_pointer>(newBlock)->next = currentBlock;
    currentBlock = reinterpret_cast<slot_pointer>(newBlock);
    // Pad block body to staisfy the alignment requirements for elements
    data_pointer body = newBlock + sizeof(slot_pointer);
    size_type bodyPadding = padPointer(body, alignof(slot_type));
    currentSlot = reinterpret_cast<slot_pointer>(body + bodyPadding);
    lastSlot = reinterpret_cast<slot_pointer>
                (newBlock + BlockSize - sizeof(slot_type) + 1);
}

template <typename T>
typename MemoryPool<T>::pointer MemoryPool<T>::allocateBigBlock(size_type n)
{
    size_type newBlockSize = n * sizeof(slot_type) + sizeof(slot_pointer) + alignof(slot_type);
    data_pointer newBlock = reinterpret_cast<data_pointer>
                            (operator new(newBlockSize));
    reinterpret_cast<slot_pointer>(newBlock)->next = currentBlock;
    currentBlock = reinterpret_cast<slot_pointer>(newBlock);
    // Pad block body to staisfy the alignment requirements for elements
    data_pointer body = newBlock + sizeof(slot_pointer);
    size_type bodyPadding = padPointer(body, alignof(slot_type));
    pointer result = reinterpret_cast<pointer>(body + bodyPadding);
    currentSlot = reinterpret_cast<slot_pointer>
                (newBlock + BlockSize);
    lastSlot = reinterpret_cast<slot_pointer>
                (newBlock + BlockSize - sizeof(slot_type) + 1);
    return result;
}

template <typename T>
typename MemoryPool<T>::pointer MemoryPool<T>::allocate(size_type n, const_pointer hint)
{
    if(n * sizeof(slot_type) + sizeof(slot_pointer) + alignof(slot_type) > BlockSize){
        return allocateBigBlock(n);
    }
    if (n == 1 && freeSlots != nullptr) {
        pointer result = reinterpret_cast<pointer>(freeSlots);
        freeSlots = freeSlots->next;
        return result;
    }
    else {
        if (currentSlot + (n - 1) >= lastSlot){
            while(currentSlot < lastSlot){
                currentSlot->next = freeSlots;
                freeSlots = currentSlot;
                currentSlot++;
            }
            allocateSmallBlock();
        }
        pointer result = reinterpret_cast<pointer>(currentSlot);
        currentSlot += n;
        return reinterpret_cast<pointer>(result);
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

#endif // MEMORY_POOL_H