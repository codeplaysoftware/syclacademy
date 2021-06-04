## Unit 1 > Unified Shared Memory > **Introduction to USM**

Unified shared memory, commonly referred to as USM, is an alternative data management model to the accessor-buffer model described in earlier chapters.

USM provides an API for allocating and moving data within a unified virtual address space, which means the pointers returned from USM memory allocations are consistent between the host application and kernel functions.

Many co-processors, including GPUs have a hierarchical memory structure, where there is more than one distinct memory region, and therefore more than one distinct address space, i.e. a pointer to one is not compatible with another. These different address spaces can not be natively expressed in C++ as C++ as there is only a single address space, this is one of the reasons for the accessor abstraction in SYCL.

However, a unified virtual address space provides an abstraction which allows memory allocations within a single address space, this can be underpinned by a shared physical memory or a cache coherent system.

+ Explicit data movement

### Why use USM

There are a number of reasons why you may wish to use USM as opposed to the accessor-buffer data management model.

As the USM model is a pointer-based approach, it should be more familiar to C or C++ programmers, and therefore is a more preferable place to start when offloading existing C++ codes.

For the same reason USM also allows you to manipulate pointer-based structures such as a liked list.

USM also provides a lower-level API, which allows for more fine-grained control over the management of the data.

### Variations of USM

There are different variations of USM which provide varying levels of support 

However, USM goes further than this, and there are different levels of USM which a SYCL 2020 implementation can provide which reflect the different capabilities. These levels also determine the kinds of USM allocations which can be performed and the APIs which must be used when working with USM allocations. 

The table below shows the various levels of USM which a SYCL 2020 implementation may provide. 

**Explicit USM** is the minimum that any SYCL 2020 implementation must support, and it supports consistent pointers, pointer-based structures, and explicit data movement as I described above. All other levels of USM are optional and can be queried per device. 

**Restricted USM** builds on this by providing shared access, which allows you to allocate memory which is accessible by both the host and the device(s) without needing to explicitly copy between them. 

**Concurrent USM** builds on this further by providing concurrent access, which allows you to access shared USM allocations on the host and device(s) concurrently. 

**System USM** provides all of the above, but also allows you to use system allocation such as malloc and new, rather than using the SYCL USM allocation API. 

| | Explicit USM (minimum) | Restricted USM​ (optional)​ | Concurrent USM​ (optional)​ | System USM​ (optional)​ |
|-|------------------------|---------------------------|---------------------------|-----------------------|
| Consistent pointers​  | ✓​ | ✓​ | ✓​ | ✓​ |
| Pointer-based structures​ | ✓​ | ✓​ | ✓​ | ✓​ |
| Explicit data movement | ✓​ | ✓​ | ✓​ | ✓​ |
| Shared access | ✗​ | ✓​ | ✓​ | ✓​ |
| Concurrent access | ✗​ | ✗​ | ✓​ | ✓​ |
| System allocations (malloc/new) | ✗​ | ✗​ | ✗​ | ✓​ |


 



